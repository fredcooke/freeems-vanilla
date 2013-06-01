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
 * @brief Fuel and ignition calculations.
 *
 * This file contains all of the main fuel and ignition calculations based
 * upon the variables that we have already determined in previous stages.
 */


#define FUELANDIGNITIONCALCS_C
#include "inc/freeEMS.h"
#include "inc/utils.h"
#include "inc/locationIDs.h"
#include "inc/tableLookup.h"
#include "inc/fuelAndIgnitionCalcs.h"


/**
 * Final fuel and ignition calculations. Using a variety of primary algorithms
 * calculate a base pulsewidth and then apply various corrections to it such as
 * injector dead time, transient fuel correction, engine temperature enrichment
 * and per cylinder trims. The ignition timing and fuel injection timing are
 * also determined here, as are the various limiters and cuts.
 */
void calculateFuelAndIgnition(){
	unsigned short airInletTemp = CoreVars->IAT; /* All except MAF use this. */
	/* Determine the type of air flow data */
	if(!(fixedConfigs2.algorithmSettings.algorithmType)){
		/* Look up VE with RPM and MAP */
		DerivedVars->VEMain = lookupMainTable(CoreVars->RPM, CoreVars->MAP, VETableMainLocationID);
		/* This won't overflow until 512kPa or about 60psi of boost with 128% VE. */
		DerivedVars->AirFlow = ((unsigned long)CoreVars->MAP * DerivedVars->VEMain) / VE(100);
		/* Result is 450 - 65535 always. */
	}else if(fixedConfigs2.algorithmSettings.algorithmType == ALGO_ALPHA_N){
		/* Look up Airflow with RPM and TPS */
		DerivedVars->AirFlow = lookupMainTable(CoreVars->RPM, CoreVars->TPS, AirflowTableLocationID); /* Tuned air flow without density information */
	}else if(fixedConfigs2.algorithmSettings.algorithmType == ALGO_MAF){
		DerivedVars->AirFlow = CoreVars->MAF; /* Just fix temperature at appropriate level to provide correct Lambda */
		/// @todo TODO figure out what the correct "temperature" is to make MAF work correctly!
		airInletTemp = DEGREES_C(20); // Room temperature?
	}else{ /* Default to no fuel delivery and error */
		DerivedVars->AirFlow = 0;
	}


	/* This won't overflow until well past 125C inlet, 1.5 Lambda and fuel as dense as water */
	DerivedVars->densityAndFuel = (((unsigned long)((unsigned long)airInletTemp * DerivedVars->Lambda) / LAMBDA(1.0)) * fixedConfigs1.engineSettings.densityOfFuelAtSTP) / FUEL_DENSITY(FUEL_DENSITY_UNIT_FACTOR);
	/* Result is 7500 - 60000 always. TODO clean up the last item on the above line */

	/* Divisors for air inlet temp and pressure :
	 * #define airInletTempDivisor 100
	 * #define airPressureDivisor 100
	 * cancel each other out! all others are used. */

	DerivedVars->BasePW = (bootFuelConst * DerivedVars->AirFlow) / DerivedVars->densityAndFuel;

	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&& Apply All Corrections PCFC, ETE, IDT, TFC etc &&&&&&&&&&&&&&&&&&&&&&&&&&&*/

	/* Apply the corrections after calculating */
	DerivedVars->EffectivePW = safeTrim(DerivedVars->BasePW, DerivedVars->TFCTotal);
	DerivedVars->EffectivePW = safeScale(DerivedVars->EffectivePW, DerivedVars->ETE, SHORT4TH);


//	unsigned char channel; // the declaration of this variable is used in multiple loops below.
//
//	/* "Calculate" the individual fuel pulse widths */
//	for(channel = 0; channel < INJECTION_CHANNELS; channel++){ /// @todo TODO make injector channels come from config, not defines.
//		/* Add or subtract the per cylinder fuel trims */
//		unsigned short channelPW;
//		channelPW = safeScale(DerivedVars->EffectivePW, TablesB.SmallTablesB.perCylinderFuelTrims[channel]);
//
//		/* Add on the IDT to get the final value and put it into the array */
//		//outputEventPulseWidthsMath[channel] = safeAdd(channelPW, DerivedVars->IDT); do not re-enable this without fixing it properly...
//	}

	// Make sure we don't have a PW if PW is supposed to be zero, ie, zero the IDT as well.
	if(!(DerivedVars->EffectivePW)){
		DerivedVars->IDT = 0; // This also makes fuel and electrical duty work consistently in external apps.
	}

	/* Reference PW for comparisons etc */
	DerivedVars->RefPW = safeAdd(DerivedVars->EffectivePW, DerivedVars->IDT);
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

/// @todo accumulate errors such that we know what sort of PW WOULD have been requested and enable a "over duty cut" to protect boosted users with insufficient injector size on cold nights

/// TODO @todo FIXME part of to schedule or not to schedule should be : (masterPulseWidth > injectorMinimumPulseWidth)
// IE, NOT in the decoders... KISS in the decoders. This is a hangover from (very) early decoder dev

//	for(channel = 0;channel < INJECTION_CHANNELS;channel++){ /// @todo TODO make injector channels come from config, not defines.
		//injectorMainAdvances[channel] = IDT blah blah.
//	}

	/* "Calculate" the nominal total pulse width before per channel corrections */
	masterPulseWidth = safeAdd((DerivedVars->EffectivePW / fixedConfigs1.schedulingSettings.numberOfInjectionsPerEngineCycle), DerivedVars->IDT); // div by number of injections per cycle, configured above
	// but requires to know how big a cycle is, 1/4 1, 1/2, etc

	// Note, conversions to address and then pointer are necessary to avoid error on direct cast
	// Cuts and limiters TODO move these to their own special place?
	// TODO Make source of threshold either struct or temp based curve for these

	if(fixedConfigs1.cutAndLimiterSettings.cutsEnabled.IgnitionRPM){
		unsigned short confirmedReenableThreshold = fixedConfigs1.cutAndLimiterSettings.IgnitionRPM.reenableThreshold;
		if(confirmedReenableThreshold >= fixedConfigs1.cutAndLimiterSettings.IgnitionRPM.disableThreshold){
			confirmedReenableThreshold = fixedConfigs1.cutAndLimiterSettings.IgnitionRPM.disableThreshold / 2;
		}
		if(CoreVars->RPM > fixedConfigs1.cutAndLimiterSettings.IgnitionRPM.disableThreshold){
			((ignitionCutFlags *)&KeyUserDebugs.ignitionCuts)->IgnitionRPM = 1;
		}else if(CoreVars->RPM < confirmedReenableThreshold){
			((ignitionCutFlags *)&KeyUserDebugs.ignitionCuts)->IgnitionRPM = 0;
		}
	}

	if(fixedConfigs1.cutAndLimiterSettings.cutsEnabled.InjectionRPM){
		unsigned short confirmedReenableThreshold = fixedConfigs1.cutAndLimiterSettings.InjectionRPM.reenableThreshold;
		if(confirmedReenableThreshold >= fixedConfigs1.cutAndLimiterSettings.InjectionRPM.disableThreshold){
			confirmedReenableThreshold = fixedConfigs1.cutAndLimiterSettings.InjectionRPM.disableThreshold / 2;
		}
		if(CoreVars->RPM > fixedConfigs1.cutAndLimiterSettings.InjectionRPM.disableThreshold){
			((injectionCutFlags *)&KeyUserDebugs.injectionCuts)->InjectionRPM = 1;
		}else if(CoreVars->RPM < confirmedReenableThreshold){
			((injectionCutFlags *)&KeyUserDebugs.injectionCuts)->InjectionRPM = 0;
		}
	}

	// TODO add time based lock out as well as threshold based as threshold could re-enable too quickly
	if(fixedConfigs1.cutAndLimiterSettings.cutsEnabled.InjOverBoost || fixedConfigs1.cutAndLimiterSettings.cutsEnabled.IgnOverBoost){
		unsigned short confirmedReenableThreshold = fixedConfigs1.cutAndLimiterSettings.OverBoost.reenableThreshold;
		if(confirmedReenableThreshold >= fixedConfigs1.cutAndLimiterSettings.OverBoost.disableThreshold){
			confirmedReenableThreshold = fixedConfigs1.cutAndLimiterSettings.OverBoost.disableThreshold / 2;
		}
		if(CoreVars->MAP > fixedConfigs1.cutAndLimiterSettings.OverBoost.disableThreshold){
			((injectionCutFlags *)&KeyUserDebugs.injectionCuts)->InjOverBoost = fixedConfigs1.cutAndLimiterSettings.cutsEnabled.InjOverBoost;
			((ignitionCutFlags *)&KeyUserDebugs.ignitionCuts)->IgnOverBoost = fixedConfigs1.cutAndLimiterSettings.cutsEnabled.IgnOverBoost;
		}else if(CoreVars->MAP < confirmedReenableThreshold){
			((injectionCutFlags *)&KeyUserDebugs.injectionCuts)->InjOverBoost = 0;
			((ignitionCutFlags *)&KeyUserDebugs.ignitionCuts)->IgnOverBoost = 0;
		}
	}
}
