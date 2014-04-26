/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2013 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @ingroup measurementsAndCalculations
 *
 * @brief Generate and average the core variables.
 *
 * This file contains the function that transfers the raw ADC values to actual
 * physical measurements and averages them.
 */


#define COREVARSGENERATOR_C
#include "inc/freeEMS.h"
#include "inc/commsCore.h"
#include "inc/coreVarsGenerator.h"
#include "inc/decoderInterface.h"


/**
 * Calculate and obtain the core variables. Each raw ADC value is converted to a
 * usable measurement via a variety of methods. They are then stored in a struct
 * and used as input to the next phase.
 */
void generateCoreVars(){
	// Battery Reference Voltage
	unsigned short localBRV;
	if(!(fixedConfigs2.sensorSources.BRV)){
		localBRV = (((unsigned long)ADCBuffers->BRV * fixedConfigs2.sensorRanges.BRVRange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.BRVMinimum;
	}else if(fixedConfigs2.sensorSources.BRV == SOURCE_PRESET){
		localBRV = fixedConfigs2.sensorPresets.presetBRV;
	}else if(fixedConfigs2.sensorSources.BRV == SOURCE_LINEAR){
		localBRV = (ADCBuffers->BRV * 14) + VOLTS(7.2); // 0 ADC = 7.2V, 1023 ADC = 21.522C
	}else{ // Default to normal alternator charging voltage 14.4V
		localBRV = VOLTS(14.4);
	}

	// Coolant/Head Temperature
	unsigned short localCHT;
	if(!(fixedConfigs2.sensorSources.CHT)){
		localCHT = CHTTransferTable[ADCBuffers->CHT];
	}else if(fixedConfigs2.sensorSources.CHT == SOURCE_PRESET){
		localCHT = fixedConfigs2.sensorPresets.presetCHT;
	}else if(fixedConfigs2.sensorSources.CHT == SOURCE_LINEAR){
		localCHT = (ADCBuffers->CHT * 10) + DEGREES_C(0); // 0 ADC = 0C, 1023 ADC = 102.3C
	}else{ // Default to slightly cold and therefore rich: 65C
		localCHT = DEGREES_C(65);
	}

	// Inlet Air Temperature
	unsigned short localIAT;
	if(!(fixedConfigs2.sensorSources.IAT)){
		localIAT = IATTransferTable[ADCBuffers->IAT];
	}else if(fixedConfigs2.sensorSources.IAT == SOURCE_PRESET){
		localIAT = fixedConfigs2.sensorPresets.presetIAT;
	}else if(fixedConfigs2.sensorSources.IAT == SOURCE_LINEAR){
		localIAT = (ADCBuffers->IAT * 10) + DEGREES_C(0); // 0 ADC = 0C, 1023 ADC = 102.3C
	}else{ // Default to room temperature
		localIAT = DEGREES_C(20);
	}

	// Throttle Position Sensor
	/* Bound the TPS ADC reading and shift it to start at zero */
	unsigned short unboundedTPSADC = ADCBuffers->TPS;
	unsigned short boundedTPSADC = 0;
	if(unboundedTPSADC > fixedConfigs2.sensorRanges.TPSMaximumADC){
		boundedTPSADC = TPSADCRange;
	}else if(unboundedTPSADC > fixedConfigs2.sensorRanges.TPSMinimumADC){
		boundedTPSADC = unboundedTPSADC - fixedConfigs2.sensorRanges.TPSMinimumADC;
	}

	/* Get TPS from ADC no need to add TPS min as we know it is zero by definition */
	unsigned short localTPS = ((unsigned long)boundedTPSADC * PERCENT(100)) / TPSADCRange;
	// TODO fail safe mode, only if on the ADC rails AND configured to do so
	// Default to a low value that will get you home if you are in Alpha-N mode


	/* Get RPM by locking out ISRs for a second and grabbing the Tooth logging data */
	//atomic start
	// copy rpm data
	//atomic end

	// Calculate RPM and delta RPM and delta delta RPM from data recorded
	if(*ticksPerDegree != 0){
		CoreVars->RPM = (unsigned short)(degreeTicksPerMinute / *ticksPerDegree);
	}else{
		CoreVars->RPM = 0;
	}

	CoreVars->DRPM = *ticksPerDegree;
//	unsigned short localDRPM = 0;
//	unsigned short localDDRPM = 0;


	// TODO This might get done somewhere else, separation of concerns, etc
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&& Average the variables as per the configuration &&&&&&&&&&&&&&&&&&&&&&&&&&*/
	/* Strictly speaking only the primary variables need to be averaged. After that, the derived ones are   */
	/* already averaged in a way. However, there may be some advantage to some short term averaging on the  */
	/* derived ones also, so it is something to look into later.                                            */

	/// @todo TODO average the generated values here

//			newVal var word        ' the value from the ADC
//			smoothed var word    ' a nicely smoothed result
//
//			if newval > smoothed then
//			        smoothed = smoothed + (newval - smoothed)/alpha
//			else
//			        smoothed = smoothed - (smoothed - newval)/alpha
//			endif

	// from : http://www.tigoe.net/pcomp/code/category/code/arduinowiring/41

	// for now just copy them in.
	CoreVars->BRV = localBRV;
	CoreVars->CHT = localCHT;
	CoreVars->IAT = localIAT;
	CoreVars->TPS = localTPS;
	CoreVars->EGO = (((unsigned long)ADCBuffers->EGO * fixedConfigs2.sensorRanges.EGORange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.EGOMinimum;
	CoreVars->MAP = (((unsigned long)ADCBuffers->MAP * fixedConfigs2.sensorRanges.MAPRange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.MAPMinimum;
	CoreVars->AAP = (((unsigned long)ADCBuffers->AAP * fixedConfigs2.sensorRanges.AAPRange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.AAPMinimum;
	CoreVars->MAT = IATTransferTable[ADCBuffers->MAT];


	// Not actually used, feed raw values for now TODO migrate these to a SpecialVars struct or similar not included in default datalog
	CoreVars->EGO2 = ADCBuffers->EGO2;
	CoreVars->IAP = ADCBuffers->IAP;
	CoreVars->MAF = MAFTransferTable[ADCBuffers->MAF];

//	CoreVars->DRPM = localDRPM;
//	CoreVars->DDRPM = localDDRPM;
//	CoreVars->DTPS = localDTPS;
}
