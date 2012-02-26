/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2012 Fred Cooke
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
 * @brief Precision timed output scheduling.
 *
 * This file contains all of the mathematics and logic that lead to precise
 * ignition and injection events being output based on configuration parameters.
 */


#define OUTPUTSCHEDULER_C
#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/decoderInterface.h"
#include "inc/outputScheduler.h"

/**
 * Precision timed output scheduling. Calculates which input tooth and post
 * tooth delay any given event should used based on the configuration provided.
 */
void scheduleOutputs(){
        /// TODO @todo FIXME part of to schedule or not to schedule should be : (masterPulseWidth > injectorMinimumPulseWidth)
        // IE, NOT in the decoders... KISS in the decoders. This is a hangover from (very) early decoder dev

        // TODO Add ability to schedule start and centre of fuel pulse using RPM, injector firing angle and IDT to schedule the events correctly

	// Sanity checks: TODO migrate these to init time and do something meaninful with the failure
	if(fixedConfigs1.schedulingSettings.decoderEngineOffset >= totalEventAngleRange){
		return; /// @todo don't bother doing anything, settings don't make sense... TODO move this to init time to prevent bad config
	}
	if(fixedConfigs1.schedulingSettings.numberOfConfiguredOutputEvents > MAX_NUMBER_OF_OUTPUT_EVENTS){
		return; /// @todo don't bother doing anything, settings don't make sense... TODO move this to init time to prevent bad config
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
	for(ignitionEvent = 0;ignitionEvent < fixedConfigs1.schedulingSettings.numberOfConfiguredOutputEvents;ignitionEvent++){

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

		// Default to ignition
		unsigned short pulsewidthToUseForThisChannel = DerivedVars->Dwell;
		unsigned short endOfPulseTimingToUseForThisChannel = DerivedVars->Advance;
		if(fixedConfigs1.schedulingSettings.schedulingConfigurationBits[ignitionEvent]){ //
			pulsewidthToUseForThisChannel = masterPulseWidth;
			endOfPulseTimingToUseForThisChannel = 0; // Fixed flat timing for fueling for the time being
		} // Else we're doing ignition! Leave the defaults in place.

		/** @todo TODO move sched code to a function or functions (inline?)
		 * that can be unit tested such that we KNOW it performs as anticipated
		 * rather than just trying it out on a 400hp turbo truck engine.
		 */

		/// @todo TODO refactor this partly into init.c as per more detailed TD above
		unsigned short codeAngleOfIgnition = 0;
		if(fixedConfigs1.schedulingSettings.anglesOfTDC[ignitionEvent] > ((unsigned long)fixedConfigs1.schedulingSettings.decoderEngineOffset + endOfPulseTimingToUseForThisChannel)){ /// @todo TODO keep an eye on overflow here when increasing resolution by scaling angles
			codeAngleOfIgnition = fixedConfigs1.schedulingSettings.anglesOfTDC[ignitionEvent] - (fixedConfigs1.schedulingSettings.decoderEngineOffset + endOfPulseTimingToUseForThisChannel);
		}else{
			codeAngleOfIgnition = (unsigned short)(((unsigned long)totalEventAngleRange + fixedConfigs1.schedulingSettings.anglesOfTDC[ignitionEvent]) - ((unsigned long)fixedConfigs1.schedulingSettings.decoderEngineOffset + endOfPulseTimingToUseForThisChannel));
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

			if(ticksBetweenEventAndSpark > ((unsigned long)pulsewidthToUseForThisChannel + decoderMaxCodeTime)){
				// generate event mapping from real vs virtual counts, how? better with a cylinder ratio?
				unsigned char mappedEvent = 0xFF;
				if(numberOfRealEvents == numberOfVirtualEvents){
					mappedEvent = lastGoodEvent;
				}else{
					mappedEvent = lastGoodEvent % numberOfRealEvents;
				}

				// Determine the eventBeforeCurrent outside the atomic block
				unsigned char eventBeforeCurrent = 0;
				if(outputEventInputEventNumbers[ignitionEvent] == 0){
					eventBeforeCurrent = numberOfRealEvents - 1;
				}else{
					eventBeforeCurrent = outputEventInputEventNumbers[ignitionEvent] - 1;
				}

				unsigned long potentialDelay = ticksBetweenEventAndSpark - pulsewidthToUseForThisChannel;
				if(potentialDelay <= SHORTMAX){ // We can use dwell as is
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
					if((mappedEvent == eventBeforeCurrent) && (potentialDelay >  outputEventDelayTotalPeriod[ignitionEvent])){
						skipEventFlags |= (1UL << ignitionEvent);
					}

					outputEventInputEventNumbers[ignitionEvent] = mappedEvent;
					outputEventDelayFinalPeriod[ignitionEvent] = (unsigned short)potentialDelay;
					outputEventPulseWidthsMath[ignitionEvent] = pulsewidthToUseForThisChannel;
					outputEventExtendNumberOfRepeats[ignitionEvent] = 0;
					ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
					outputEventDelayTotalPeriod[ignitionEvent] = potentialDelay; // No async accesses occur
				}else{
					ATOMIC_START(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

					// See comment in above block
					if((mappedEvent == eventBeforeCurrent) && (potentialDelay > outputEventDelayTotalPeriod[ignitionEvent])){
						skipEventFlags |= (1UL << ignitionEvent);
					}

					outputEventInputEventNumbers[ignitionEvent] = mappedEvent;
					unsigned char numberOfRepeats = potentialDelay / SHORTMAX;
					unsigned short finalPeriod = potentialDelay % SHORTMAX;
					if(finalPeriod > decoderMaxCodeTime){
						outputEventDelayFinalPeriod[ignitionEvent] = finalPeriod;
						outputEventExtendRepeatPeriod[ignitionEvent] = SHORTMAX;
						outputEventExtendNumberOfRepeats[ignitionEvent] = numberOfRepeats;
					}else{
						unsigned short shortagePerRepeat = (decoderMaxCodeTime - finalPeriod) / numberOfRepeats;
						unsigned short repeatPeriod = (SHORTMAX - 1) - shortagePerRepeat;
						finalPeriod += (shortagePerRepeat + 1) * numberOfRepeats;
						outputEventDelayFinalPeriod[ignitionEvent] = finalPeriod;
						outputEventExtendRepeatPeriod[ignitionEvent] = repeatPeriod;
						outputEventExtendNumberOfRepeats[ignitionEvent] = numberOfRepeats;
					}
					// find number of max sized chunks and remainder
					// check remainder for being big enough compared to code runtime
					// if so, set repeat to max and final to remainder and number of iterations to divs
					// if not, decrease repeat size in some optimal way and provide new left over to work with that, and same number of divs/its
					// Always use dwell as requested
					outputEventPulseWidthsMath[ignitionEvent] = pulsewidthToUseForThisChannel;
					ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
					outputEventDelayTotalPeriod[ignitionEvent] = potentialDelay; // No async accesses occur
					Counters.timerStretchedToSchedule++;
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
