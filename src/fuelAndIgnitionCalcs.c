/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010, 2011 Fred Cooke
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


/**	@file fuelAndIgnitionCalcs.c
 * @ingroup measurementsAndCalculations
 *
 * @brief Fuel and ignition calculations.
 *
 * This file contains all of the main fuel and ignition calculations based
 * upon the variables that we have already determined in previous stages.
 *
 * @author Fred Cooke
 */


#define FUELANDIGNITIONCALCS_C
#include "inc/freeEMS.h"
#include "inc/utils.h"
#include "inc/commsCore.h"
#include "inc/interrupts.h"
#include "inc/tableLookup.h"
#include "inc/decoderInterface.h"
#include "inc/fuelAndIgnitionCalcs.h"


/** @brief Fuel and ignition calculations
 *
 * Using a variety of primary algorithms calculate a base pulsewidth and then
 * apply various corrections to it such as injector dead time, transient fuel
 * correction, engine temperature enrichment and per cylinder trims. The fuel
 * injection timing is also determined here.
 *
 * Calculate the ignition timing and dwell here too. Several corrections are
 * applied to these as well.
 *
 * @todo TODO implement the all of the ignition stuff and finish off all of the fuel injection stuff.
 * @todo TODO change the way configuration is done and make sure the most common options are after the first if().
 * @todo TODO add actual configuration options to the fixed config blocks for these items.
 *
 * @author Fred Cooke
 */
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
			/// @todo TODO figure out what the correct "temperature" is to make MAF work correctly!
			airInletTemp = roomTemperature; // 293.15k is 20c * 100 to get value, so divide by 100 to get real number
		}else if(FALSE /*FixedAF*/){ /* Fixed air flow from config */
			DerivedVars->AirFlow = fixedConfigs2.sensorPresets.presetAF;
		}else{ /* Default to no fuel delivery and error */
			DerivedVars->AirFlow = 0;
			/* If anyone is listening, let them know something is wrong */
//			sendError(AIRFLOW_NOT_CONFIGURED_CODE); // or maybe queue it?
		}


		/* This won't overflow until well past 125C inlet, 1.5 Lambda and fuel as dense as water */
		DerivedVars->densityAndFuel = (((unsigned long)((unsigned long)airInletTemp * DerivedVars->Lambda) / stoichiometricLambda) * fixedConfigs1.engineSettings.densityOfFuelAtSTP) / densityOfFuelTotalDivisor;
		/* Result is 7500 - 60000 always. */

		/* Divisors for air inlet temp and pressure :
		 * #define airInletTempDivisor 100
		 * #define airPressureDivisor 100
		 * cancel each other out! all others are used. */


		DerivedVars->BasePW = (bootFuelConst * DerivedVars->AirFlow) / DerivedVars->densityAndFuel;
	}else if(FALSE /*configured*/){ /* Fixed PW from config */
		DerivedVars->BasePW = fixedConfigs2.sensorPresets.presetBPW;
	}else{ /* Default to no fuel delivery and error */
		DerivedVars->BasePW = 0;
		/* If anyone is listening, let them know something is wrong */
//		sendError(BPW_NOT_CONFIGURED_CODE); // or maybe queue it?
	}

	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&& Apply All Corrections PCFC, ETE, IDT, TFC etc &&&&&&&&&&&&&&&&&&&&&&&&&&&*/

	/* Apply the corrections after calculating */
	DerivedVars->EffectivePW = safeTrim(DerivedVars->BasePW, DerivedVars->TFCTotal);
	DerivedVars->EffectivePW = safeScale(DerivedVars->EffectivePW, DerivedVars->ETE);


	unsigned char channel; // the declaration of this variable is used in multiple loops below.

	/* "Calculate" the individual fuel pulse widths */
	for(channel = 0; channel < INJECTION_CHANNELS; channel++){ /// @todo TODO make injector channels come from config, not defines.
		/* Add or subtract the per cylinder fuel trims */
		unsigned short channelPW;
		channelPW = safeScale(DerivedVars->EffectivePW, TablesB.SmallTablesB.perCylinderFuelTrims[channel]);

		/* Add on the IDT to get the final value and put it into the array */
		injectorMainPulseWidthsMath[channel] = safeAdd(channelPW, DerivedVars->IDT);
	}

	/* Reference PW for comparisons etc */
	unsigned short refPW = safeAdd(DerivedVars->EffectivePW, DerivedVars->IDT);
	DerivedVars->RefPW = refPW;
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
	/* "Calculate" the nominal total pulse width before per channel corrections */
	masterPulseWidth = refPW;

/// @todo accumulate errors such that we know what sort of PW WOULD have been requested and enable a "over duty cut" to protect boosted users with insufficient injector size on cold nights







/// TODO @todo FIXME part of to schedule or not to schedule should be : (masterPulseWidth > injectorMinimumPulseWidth)

// IE, NOT in the decoders... KISS in the decoders. This is a hangover from (very) early decoder dev

	// schedule even when RPM = zero and not synced, as sync could start any time and we want it to start injection/igniting then, up to decoder to not allow scheduling if not synced...
	// do not schedule, or schedule specially if rpm > max or hysteresis not met etc.

	/*&&&&&&&&&&&&&&&&& Based on IDT schedule PW start such that Fuel is correctly timed &&&&&&&&&&&&&&&&&&&*/

//	for(channel = 0;channel < INJECTION_CHANNELS;channel++){ /// @todo TODO make injector channels come from config, not defines.
		//injectorMainAdvances[channel] = IDT blah blah.
//	}

	/* This will involve using RPM, injector firing angle and IDT to schedule the events correctly */

	/** @todo TODO work needs to be done on scheduling before this can be completed. */

	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
	/*&&&&&&&&&&&&&&& Based on Dwell and Ignition angle schedule the start and end of dwell &&&&&&&&&&&&&&&&*/
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




/**
 * @todo TODO split this stuff into fueling calc/logic/stuff and ignition calc/stuff/logic
 * and finally, after those, scheduling inc limiting and othe weirdness and logic etc. If
 * not doing this, this file and function will end up HUGE...
 */


	// Required vars for scheduling!
	unsigned short anglesOfTDC[6];
	unsigned short decoderEngineOffset;
	unsigned char numberOfIgnitionEvents;


	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& RULES FOR HAVING CONFIG IN THE CODE &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
	/*&&&&&&&&&&&&&&& you are building frequently, for a vehicle, and contributing dev time &&&&&&&&&&&&&&&&*/
	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/


// add this to code degrees to find 0/TDC for cyl/output 1 or subtract from real degrees to get code degrees
#define Mitsi4and1OffsetOnTruck ( 90.00 * oneDegree) // FE-DOHC, CAS approximately centre
#define HyundaiHackOffset       ( 30.00 * oneDegree) // Distributor fully retarded
#define SilverTop4age           (128.52 * oneDegree) /// Stock silver-top using G? for RPM2 and NE for RPM1, CAS approximately centre, @todo TODO find values for extremes of dizzy placement

// Fred's Ford Courier http://forum.diyefi.org/viewtopic.php?f=55&t=1069
#ifdef TRUCK
anglesOfTDC[0] =   0 * oneDegree; // Cylinder 1
anglesOfTDC[1] = 180 * oneDegree; // Cylinder 3
anglesOfTDC[2] = 360 * oneDegree; // Cylinder 4
anglesOfTDC[3] = 540 * oneDegree; // Cylinder 2
#define cliConfigredNumberOfIgnitionEvents 4
#define numberOfInjectionEvents 2
#define cliConfiguredOffset Mitsi4and1OffsetOnTruck
pinEventNumbers[4] = 1;
pinEventNumbers[5] = 5;
postReferenceEventDelays[4] = decoderMaxCodeTime;
postReferenceEventDelays[5] = decoderMaxCodeTime;
injectorMainPulseWidthsMath[4] = masterPulseWidth;
injectorMainPulseWidthsMath[5] = masterPulseWidth;

// Fred's Hyundai Stellar http://forum.diyefi.org/viewtopic.php?f=55&t=1086
#elif HOTEL
anglesOfTDC[0] = 0 * oneDegree; // 1,2,3,4, repeating pattern
#define cliConfigredNumberOfIgnitionEvents 1
#define numberOfInjectionEvents 0
#define cliConfiguredOffset HyundaiHackOffset
//pinEventNumbers[?] = ?;
//postReferenceEventDelays[?] = decoderMaxCodeTime;
//injectorMainPulseWidthsMath[?] = masterPulseWidth;

// Preston's silver-top-on-a-stand http://forum.diyefi.org/viewtopic.php?f=55&t=1101
#elif PRESTO
anglesOfTDC[0] =   0 * oneDegree;   // 1 and 4, hack converts this to 360 as well
anglesOfTDC[1] = 180 * oneDegree; // 2 and 3, hack converts this to 540 as well
#define cliConfigredNumberOfIgnitionEvents 2
#define numberOfInjectionEvents 2
#define cliConfiguredOffset SilverTop4age
pinEventNumbers[4] = 0;
pinEventNumbers[5] = 12;
postReferenceEventDelays[4] = decoderMaxCodeTime;
postReferenceEventDelays[5] = decoderMaxCodeTime;
injectorMainPulseWidthsMath[4] = masterPulseWidth;
injectorMainPulseWidthsMath[5] = masterPulseWidth;

// Looking forwared to there being a link to a thread here soon!
#elif SEANKLT1
anglesOfTDC[0] =   0 * oneDegree;
anglesOfTDC[1] = 120 * oneDegree;
anglesOfTDC[2] = 240 * oneDegree;
anglesOfTDC[3] = 360 * oneDegree;
anglesOfTDC[4] = 480 * oneDegree;
anglesOfTDC[5] = 600 * oneDegree;
#define cliConfigredNumberOfIgnitionEvents 6
#define numberOfInjectionEvents 0
#define cliConfiguredOffset 0
//pinEventNumbers[?] = ?;
//postReferenceEventDelays[?] = decoderMaxCodeTime;
//injectorMainPulseWidthsMath[?] = masterPulseWidth;

// Looking forwared to there being a link to a thread here soon!
#elif SEANKR1
// anglesOfTDC[?] = ? * oneDegree;
#define cliConfigredNumberOfIgnitionEvents 0
#define numberOfInjectionEvents 0
#define cliConfiguredOffset 0
//pinEventNumbers[?] = ? * oneDegree;
//postReferenceEventDelays[?] = decoderMaxCodeTime;
//injectorMainPulseWidthsMath[?] = masterPulseWidth;

// Sadly, FreeEMS car numero uno is gone, RIP Volvo! http://forum.diyefi.org/viewtopic.php?f=55&t=1068
#else
// anglesOfTDC[?] = ? * oneDegree;
#define cliConfigredNumberOfIgnitionEvents 0
#define numberOfInjectionEvents 0
#define cliConfiguredOffset 0
//pinEventNumbers[?] = ?;
//postReferenceEventDelays[?] = decoderMaxCodeTime;
//injectorMainPulseWidthsMath[?] = masterPulseWidth;
#endif


	decoderEngineOffset = cliConfiguredOffset;
	numberOfIgnitionEvents = cliConfigredNumberOfIgnitionEvents;


	// Sanity checks:
	if(decoderEngineOffset >= totalEventAngleRange){
		return; /// @todo don't bother doing anything, settings don't make sense... TODO move this to init time to prevent bad config
	}
	if(numberOfIgnitionEvents > 6){
		return; /// @todo don't bother doing anything, settings don't make sense... TODO move this to init time to prevent bad config
	}
	if((cliConfigredNumberOfIgnitionEvents + numberOfInjectionEvents) > 6){
		return; /// @todo TODO temp, fix up
	}
/// @todo TODO create this check:
//	if(event angles not valid order/numbers/etc){
//		return;
//	}


	/// @todo TODO Schedule injection with real timing, requires some tweaks to work right.


	/** @todo TODO move this loop variable to fixedConfig and make a subset of
	 * the remainder of channels configured for fuel with a start time/tooth
	 * directly set for now, ie, make the 6 channels usable as fuel or ignition
	 * from reasonable configuration and write a guide on how to set it up for
	 * any engine.
	 */
	unsigned char ignitionEvent;
	for(ignitionEvent = 0;ignitionEvent < numberOfIgnitionEvents;ignitionEvent++){

		/* pseudo code
		 *
		 * we have:
		 *
		 * - offset between engine and code
		 * - offset for each output event TDC
		 * - desired timing value in degrees BTDC
		 * - a minimum post tooth delay
		 * - angle to ticks conversion number
		 *
		 * we want:
		 *
		 * - which event to fire from
		 * - how much to wait after that event before firing
		 *
		 * we need to:
		 *
		 * - to find the code angle that the spark must jump at
		 * - find nearest event
		 * - find time after nearest event to spark needing to jump
		 * - check that dwell + min delay < time after nearest
		 * - if so, set event number in output as nearest
		 * - and, set after delay to (distance between - dwell)
		 * - if not, set event number in output to one before nearest
		 * - and, set after delay to same + expected delay between nearest and next
		 *
		 * repeat per pin (this is in a loop)
		 *
		 * NOTE this is sub-optimal, the spark firing should be scheduled close to the closest tooth
		 *      and dwell start should be = or greater than requested dwell and equal or less than max dwell
		 *      ie, dwell can be MUCH more than requested in order to get the closest to event spark possible
		 *      the output code was designed for fuel use, hence this current behaviour. It will be adjusted
		 *      once xgate bit banging works sweetly.
		 */


		/** @todo TODO move sched code to a function or functions (inline?)
		 * that can be unit tested such that we KNOW it performs as anticipated
		 * rather than just trying it out on a 400hp turbo truck engine.
		 */

		/// @todo TODO refactor this partly into init.c as per more detailed TD above
		unsigned short codeAngleOfIgnition = 0;
		if(anglesOfTDC[ignitionEvent] > ((unsigned long)decoderEngineOffset + DerivedVars->Advance)){ /// @todo TODO keep an eye on overflow here when increasing resolution by scaling angles
			codeAngleOfIgnition = anglesOfTDC[ignitionEvent] - (decoderEngineOffset + DerivedVars->Advance);
		}else{
			codeAngleOfIgnition = (unsigned short)(((unsigned long)totalEventAngleRange + anglesOfTDC[ignitionEvent]) - ((unsigned long)decoderEngineOffset + DerivedVars->Advance));
		}
		/** @todo TODO, do this ^ at init time from fixed config as an array of
		 * angles and a single engine offset combined into this runtime array.
		 */

		/// @todo TODO rather than look for the nearest tooth and then step through till you find the right one that can work, instead figure out the dwell in angle and subtract that too, and find the correct tooth first time, will save cpu cycles, and get same answer and be less complex...


		// Find the closest event to our desired angle of ignition by working through from what is, by definition, the farthest
		unsigned char lastGoodEvent = ONES;
		if(codeAngleOfIgnition == 0){ // Special case, if equal to zero, the last good event will not be found
			// And the last good event is the last event!
			lastGoodEvent = numberOfVirtualEvents - 1;
		}else{
			// Otherwise iterate through and find the closest one.
			unsigned char possibleEvent;
			for(possibleEvent = 0;possibleEvent < numberOfVirtualEvents;possibleEvent++){
				if(eventAngles[possibleEvent] < codeAngleOfIgnition){
					lastGoodEvent = possibleEvent;
				}
			}
		}

		// Don't actually use this var, just need that many iterations to work back from the closest tooth that we found above
		unsigned char possibleEvent;
		for(possibleEvent = 0;possibleEvent < numberOfVirtualEvents;possibleEvent++){
			unsigned long ticksBetweenEventAndSpark = LONGMAX;
			if(codeAngleOfIgnition > eventAngles[lastGoodEvent]){
				ticksBetweenEventAndSpark = ((unsigned long)*ticksPerDegree * (codeAngleOfIgnition - eventAngles[lastGoodEvent])) / ticks_per_degree_multiplier;
			}else{
				ticksBetweenEventAndSpark = ((unsigned long)*ticksPerDegree * ((unsigned long)codeAngleOfIgnition + (totalEventAngleRange - eventAngles[lastGoodEvent]))) / ticks_per_degree_multiplier;
			}

			if(ticksBetweenEventAndSpark > ((unsigned long)DerivedVars->Dwell + decoderMaxCodeTime)){
				// generate event mapping from real vs virtual counts, how? better with a cylinder ratio?
				unsigned char mappedEvent = 0xFF;
				if(numberOfRealEvents == numberOfVirtualEvents){
					mappedEvent = lastGoodEvent;
				}else{
					mappedEvent = lastGoodEvent % numberOfRealEvents;
				}

				unsigned long potentialDelay = ticksBetweenEventAndSpark - DerivedVars->Dwell;
				if(potentialDelay <= SHORTMAX){ // We can use dwell as is
					// Determine the eventBeforeCurrent outside the atomic block
					unsigned char eventBeforeCurrent = 0;
					if(pinEventNumbers[ignitionEvent] == 0){
						eventBeforeCurrent = numberOfRealEvents - 1;
					}else{
						eventBeforeCurrent = pinEventNumbers[ignitionEvent] - 1;
					}

					ATOMIC_START(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

					/* For this block we need to provide a flag AFTER disabling the interrupts
					 * such that the next input isr can figure out if it should run from the
					 * previous data for a single cycle in the case when moving forward a tooth
					 * between the tooth you are moving forward from and the one you are moving
					 * forward to. In this case a scheduled event will be lost, because the
					 * one its intended for has past, and the one after that is yet to arrive is
					 * not going to fire it.
					 *
					 * Some trickery around the post input min delay could benefit timing or be
					 * required as you will be operating under dynamic conditions and trying to
					 * use a tooth you're not supposed to be, not doing fancy delay semantics will
					 * just mean a single cycle of scheduling is slightly too retarded for a single
					 * event around change of tooth time which could easily be acceptable.
					 */
					if((mappedEvent == eventBeforeCurrent) && ((unsigned short)potentialDelay > postReferenceEventDelays[ignitionEvent])){
						skipEventFlags |= injectorMainOnMasks[ignitionEvent];
					}

					pinEventNumbers[ignitionEvent] = mappedEvent;
					postReferenceEventDelays[ignitionEvent] = (unsigned short)potentialDelay;
					injectorMainPulseWidthsMath[ignitionEvent] = DerivedVars->Dwell;
					ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
				}else if(((DerivedVars->Dwell + potentialDelay) - SHORTMAX) <= SHORTMAX){ // Max distance from nearest event to spark is two 16 bit timer periods
					/// @todo TODO For those that require exact dwell, a flag and mask can be inserted in this condition with an && to prevent scheduling and just not fire. Necessary for coils/ignitors that fire when excess dwell is reached. Thanks SeanK for mentioning this! :-)
					unsigned short finalDwell = (unsigned short)((DerivedVars->Dwell + potentialDelay) - SHORTMAX);
					ATOMIC_START(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
					pinEventNumbers[ignitionEvent] = mappedEvent;
					postReferenceEventDelays[ignitionEvent] = SHORTMAX;
					injectorMainPulseWidthsMath[ignitionEvent] = finalDwell;
					ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
					Counters.DwellStretchedToSchedule++;
				}else{
					/* ELSE leave unscheduled rather than advance too much
					 * This indicates that the output event is too far from the input event
					 * This will only occur on input patterns with too few teeth, or bad alignment
					 */
					pinEventNumbers[ignitionEvent] = ONES; // unschedule this pin... lockout not required because the operation is naturally atomic
					Counters.TooFarToSchedule++;
				}
				break;
			}else{
				if(lastGoodEvent > 0){
					lastGoodEvent--;
				}else{
					lastGoodEvent = numberOfVirtualEvents - 1;
				}
			}
		}
	}
	// nothing much, L&P:
}
