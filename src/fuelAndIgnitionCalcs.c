/*	fuelAndIgnitionCalcs.c

	Copyright 2008 Fred Cooke

	This file is part of the FreeEMS project.

	FreeEMS software is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FreeEMS software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/

	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org

	Thank you for choosing FreeEMS to run your engine! */


#define FUELANDIGNITIONCALCS_C
#include "inc/freeEMS.h"
#include "inc/commsCore.h"
#include "inc/tableLookup.h"
#include "inc/fuelAndIgnitionCalcs.h"


/* Based on the latest ADC readings, determine pulsewidth, dwell, and advance for all channels */
void calculateFuelAndIgnition(){
	/*&&&&&&&&&&&&& Perform the basic calculations one step at a time to get a final pulsewidth &&&&&&&&&&&&*/

	if(TRUE /* Genuine method */){
		unsigned short airInletTemp = CoreVars->IAT; /* All except MAF use this. */
		/* Determine the type of air flow data */
		if(TRUE /* SpeedDensity */){
			/* This won't overflow until 512kPa or about 60psi of boost with 128% VE. */
			DerivedVars->AirFlow = ((unsigned long)CoreVars->MAP * DerivedVars->VEMain) / oneHundredPercentVE;
			/* Result is 450 - 65535 always. */
		}else if(FALSE /*AlphaN*/){
			DerivedVars->AirFlow = DerivedVars->VEMain; /* Not actually VE, but rather tuned air flow without density information */
		}else if(FALSE /*MAF*/){
			DerivedVars->AirFlow = CoreVars->MAF; /* Just fix temperature at appropriate level to provide correct Lambda */
			// TODO figure out what the correct "temperature" is to make MAF work correctly!
			airInletTemp = roomTemperature; // 293.15k is 20c * 100 to get value, so divide by 100 to get real number
		}else if(FALSE /*FixedAF*/){ /* Fixed air flow from config */
			DerivedVars->AirFlow = fixedConfigs1.presetAF;
		}else{ /* Default to no fuel delivery and error */
			DerivedVars->AirFlow = 0;
			/* If anyone is listening, let them know something is wrong */
//			sendError(AIRFLOW_NOT_CONFIGURED_CODE); // or maybe queue it?
		}


		/* This won't overflow until well past 125C inlet, 1.5 Lambda and fuel as dense as water */
		DerivedVars->densityAndFuel = (((unsigned long)((unsigned long)airInletTemp * DerivedVars->Lambda) / stoichiometricLambda) * fixedConfigs1.densityOfFuelAtSTP) / densityOfFuelTotalDivisor;
		/* Result is 7500 - 60000 always. */

		/* Divisors for air inlet temp and pressure :
		 * #define airInletTempDivisor 100
		 * #define airPressureDivisor 100
		 * cancel each other out! all others are used. */


		DerivedVars->BasePW = (bootFuelConst * DerivedVars->AirFlow) / DerivedVars->densityAndFuel;
	}else if(FALSE /*configured*/){ /* Fixed PW from config */
		DerivedVars->BasePW = fixedConfigs1.presetBPW;
	}else{ /* Default to no fuel delivery and error */
		DerivedVars->BasePW = 0;
		/* If anyone is listening, let them know something is wrong */
//		sendError(BPW_NOT_CONFIGURED_CODE); // or maybe queue it?
	}

	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&& Apply All Corrections PCFC, ETE, IDT, TFC etc &&&&&&&&&&&&&&&&&&&&&&&&&&&*/

	/* Apply the corrections after calculating */
	DerivedVars->FinalPW = DerivedVars->BasePW;
	DerivedVars->FinalPW += DerivedVars->TFCTotal; /* TODO check for overflow when TFC is positive and underflow when negative */
	DerivedVars->FinalPW += DerivedVars->ETE; /* TODO check for overflow always */


	/* "Calculate" the individual fuel pulse widths */
	unsigned char channel;
	/* TODO move this to a header with all other #defines found in code */
	#define oneHundredPercentPCFT 32768
	for(channel = 0; channel < INJECTION_CHANNELS; channel++){ // TODO make injector channels come from config, not defines.
		/* Add or subtract the per cylinder fuel trims */
		unsigned short trimmedPW;
		trimmedPW = ((unsigned long)DerivedVars->FinalPW * TablesB.SmallTablesB.perCylinderFuelTrims[channel]) / oneHundredPercentPCFT;

		/* Check for overflow */
		unsigned short absoluteLastPW;
		/* If the trim is greater than 100% then the trimmedPW MUST be larger */
		/* If it's less than 100% it can't have overflowed */		 /* If it's not larger, it overflowed */
		if((TablesB.SmallTablesB.perCylinderFuelTrims[channel] > oneHundredPercentPCFT) && (DerivedVars->FinalPW > trimmedPW)){
			absoluteLastPW = SHORTMAX; /* So max it out! */
		}else{
			/* Add on the IDT and check again */
			unsigned short withIDTPW = trimmedPW + DerivedVars->IDT;
			if(trimmedPW > withIDTPW){ /* If it's not larger, it overflowed */
				absoluteLastPW = SHORTMAX; /* So max it out! */
			}else{
				absoluteLastPW = withIDTPW;
			}
		}

		/* Load the final value with trim and opening time checked for overflow into the array */
		injectorMainPulseWidthsMath[channel] = absoluteLastPW;
	}

	/* Reference PW for comparisons etc */
	unsigned short refPW = DerivedVars->FinalPW + DerivedVars->IDT;
	if(DerivedVars->FinalPW > refPW){ /* If it's not larger, it overflowed */
		refPW = SHORTMAX; /* So max it out! */
	}
	DerivedVars->RefPW = refPW;
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




	/*&&&&&&&&&&&&&&&&& Based on IDT schedule PW start such that Fuel is correctly timed &&&&&&&&&&&&&&&&&&&*/

//	unsigned char channel;
	for(channel = 0;channel < INJECTION_CHANNELS;channel++){ // TODO make injector channels come from config, not defines.
		//injectorMainAdvances[channel] = IDT blah blah.
	}

	/* This will involve using RPM, injector firing angle and IDT to schedule the events correctly */

	/* TODO work needs to be done on scheduling before this can be completed. */

	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& Calculate Dwell and Ignition angle &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




	/*&&&&&&&&&&&&&&& Based on Dwell and Ignition angle schedule the start and end of dwell &&&&&&&&&&&&&&&&*/
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& TEMPORARY (and old) &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

	/* "Calculate" the nominal total pulse width before per channel corrections */
	masterPulseWidth = (ADCArrays->EGO << 6) + (ADCArrays->MAP >> 4);

	/* "Calculate" the individual fuel pulse widths */
//	unsigned char channel;
	for(channel = 0; channel < INJECTION_CHANNELS; channel++){
		injectorMainPulseWidthsMath[channel] = masterPulseWidth;
	}

	// TODO x 6 main, x 6 staged, x 6 flags for staged if(coreSettingsA & STAGED_ON){}

	/* Set the staged status on or off (for now based on changeable settings) */
	if(fixedConfigs1.coreSettingsA & STAGED_ON){
		coreStatusA |= STAGED_REQUIRED;
	}else{
		coreStatusA &= STAGED_NOT_REQUIRED;
	}

	// temporary ign tests
	unsigned short intendedAdvance = ADCArrays->MAT << 6;
	unsigned short intendedDwell = intendedAdvance >> 1;

	short c;
	for(c=0;c<IGNITION_CHANNELS;c++){
		ignitionAdvances[IGNITION_CHANNELS] = intendedAdvance;
	}
	*currentDwellMath = intendedDwell;

//	unsigned short minPeriod = ignitionMinimumDwell << 1;
	//	if(intendedDwell < ignitionMinimumDwell){
//		dwellLength = ignitionMinimumDwell;
//	}else{
//		dwellLength = intendedDwell;
//	}
//	if(intendedPeriod < minPeriod){
//		dwellPeriod = minPeriod;
//	}else{
//		dwellPeriod = intendedPeriod;
//	}
//	PITLD0 = dwellPeriod;

	/* Calculate the fuel advances */
	// TODO x 6
	// just use one for all for now
	totalAngleAfterReferenceInjection = (ADCArrays->TPS << 6);

	/* Calculate the dwell period */
	// TODO x 1

	/* Calculate the ignition advances */
	//TODO x 12

	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& TEMPORARY END &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
}
