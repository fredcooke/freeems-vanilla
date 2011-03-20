/* FreeEMS - the open source engine management system
 *
 * Copyright 2011 Fred Cooke
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


/**	@file EvenTeethOnCam-Nand1.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief For evenly spaced teeth on the camshaft with a single second input.
 *
 * Currently hard coded to read 24 evenly spaced teeth on the cam shaft which
 * is equivalent to 12 on the crank shaft. Sync is provided by the second input
 * allowing a sequential and/or COP/CNP setup to be used.
 *
 * VR edition with only one edge used!
 *
 * @author Fred Cooke
 */


#define DECODER_IMPLEMENTATION_C

#include "../inc/freeEMS.h"
#include "../inc/utils.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"


const unsigned char decoderName[] = "EvenTeethOnCam-Nand1.c";
const unsigned char numberOfEvents = 24;
const unsigned short eventAngles[] = {0, 30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330, 360, 390, 420, 450, 480, 510, 540, 570, 600, 630, 660, 690};
const unsigned short totalEventAngleRange = 720;
const unsigned short decoderMaxCodeTime = 100; // To be optimised (shortened)!


/** Primary RPM ISR
 *
 * @author Fred Cooke
 */
void PrimaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	unsigned short edgeTimeStamp = TC0;				/* Save the edge time stamp */
	unsigned char PTITCurrentState = PTIT;			/* Save the values on port T regardless of the state of DDRT */

	if(!(PTITCurrentState & 0x01)){
		/* Calculate the latency in ticks */
		ISRLatencyVars.primaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

		Counters.primaryTeethSeen++;

		LongTime timeStamp;
		/* Install the low word */
		timeStamp.timeShorts[1] = edgeTimeStamp;
		/* Find out what our timer value means and put it in the high word */
		if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
			timeStamp.timeShorts[0] = timerExtensionClock + 1;
		}else{
			timeStamp.timeShorts[0] = timerExtensionClock;
		}
		unsigned long thisEventTimeStamp = timeStamp.timeLong;

		unsigned long thisInterEventPeriod = 0;
		if(decoderFlags & LAST_TIMESTAMP_VALID){
			thisInterEventPeriod = thisEventTimeStamp - lastPrimaryEventTimeStamp;
		}

		unsigned char lastEvent = currentEvent;
		currentEvent++;
		if(currentEvent == 0){
			lastEvent = numberOfEvents - 1;
		}

		if(currentEvent == numberOfEvents){
			resetToNonRunningState();
			syncLostOnThisEvent = currentEvent;
			RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
			return;
		}// Can never be greater than without a code error or genuine noise issue, so give it a miss as we can not guarantee where we are now.

		unsigned short thisTicksPerDegree = 0;
		if(decoderFlags & CAM_SYNC){
			unsigned short thisAngle = 0;
			if(currentEvent == 0){
				thisAngle = eventAngles[currentEvent] + totalEventAngleRange - eventAngles[lastEvent] ; // Optimisable... leave readable for now! :-p J/K learn from this...
			}else{
				thisAngle = eventAngles[currentEvent] - eventAngles[lastEvent];
			}

			thisTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * thisInterEventPeriod) / thisAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error

			if(decoderFlags & LAST_PERIOD_VALID){
				unsigned short ratioBetweenThisAndLast = (unsigned short)(((unsigned long)lastPrimaryTicksPerDegree * 1000) / thisTicksPerDegree);
				if((ratioBetweenThisAndLast > 1500) || (ratioBetweenThisAndLast < 667)){ /// @todo TODO hard coded tolerance, needs tweaking to be reliable, BEFORE I drive mine in boost, needs making configurable/generic too...
					resetToNonRunningState();
				}else{
					if(PTITCurrentState & 0x01){
						/// @todo TODO Calculate RPM from last primaryLeadingEdgeTimeStamp
					}else{
						/// @todo TODO Calculate RPM from last primaryTrailingEdgeTimeStamp
					}
				}
			}/*else*/ if(decoderFlags & LAST_TIMESTAMP_VALID){ /// @todo TODO temp for testing just do rpm this way, fill above out later.
				*ticksPerDegreeRecord = thisTicksPerDegree;
				sampleEachADC(ADCArrays);
				Counters.syncedADCreadings++;
				*mathSampleTimeStampRecord = TCNT;

				// Set flag to say calc required
				coreStatusA |= CALC_FUEL_IGN;

				// Reset the clock for reading timeout
				Clocks.timeoutADCreadingClock = 0;
			}
		}

		// for now, sample always and see what we get result wise...
//		if((currentEvent % 6) == 0){
//			sampleEachADC(ADCArrays);
//			Counters.syncedADCreadings++;
//			*mathSampleTimeStampRecord = TCNT;
//
//			// Set flag to say calc required
//			coreStatusA |= CALC_FUEL_IGN;
//
//			// Reset the clock for reading timeout
//			Clocks.timeoutADCreadingClock = 0;
//		}

		// if sched is for is N and we are on N+1 and flag is set, sched with zero delay
		/// @todo TODO behave differently depending upon sync level? Genericise this loop/logic?
		if(decoderFlags & CAM_SYNC){
			unsigned char pin;
			for(pin=0;pin<6;pin++){
				// WARNING, hack... yuck...
				unsigned char dodgyHack = 0xFF; // set to unschedulable value such that if not one of our w/s ign pins, we wont get a successful test on this...
				if((pin == 0) || (pin == 1)){ // if it is one of our w/s ign pins then find the opposite pin, and act like we are on it, this hack will ONLY work with evenly spaced pins, not missing teeth or any other types...
					if(currentEvent < 12){
						dodgyHack = currentEvent + 12;
					}else{
						dodgyHack = currentEvent - 12;
					}
				}

				if((pinEventNumbers[pin] == currentEvent) || (pinEventNumbers[pin] == dodgyHack)){
					skipEventFlags &= injectorMainOffMasks[0];
					schedulePortTPin(pin, timeStamp);
				}else if (skipEventFlags & injectorMainOnMasks[pin]){
					unsigned char eventBeforeCurrent = 0;
					if(currentEvent == 0){
						eventBeforeCurrent = numberOfEvents - 1;
					}else{
						eventBeforeCurrent = currentEvent - 1;
					}

					unsigned char eventBeforeDodgyHack = 0;
					if(dodgyHack == 0){
						eventBeforeDodgyHack = numberOfEvents - 1;
					}else{
						eventBeforeDodgyHack = dodgyHack - 1;
					}

					if((pinEventNumbers[pin] == eventBeforeCurrent) || (pinEventNumbers[pin] == eventBeforeDodgyHack)){
						schedulePortTPin(pin, timeStamp);
					}
				}
			}
		}

		// do these always at first, and use them with a single 30 degree angle for the first cut
		if(decoderFlags & LAST_TIMESTAMP_VALID){
			lastPrimaryTicksPerDegree = thisTicksPerDegree;
			decoderFlags |= LAST_PERIOD_VALID;
		}
		// Always
		lastPrimaryEventTimeStamp = thisEventTimeStamp;
		decoderFlags |= LAST_TIMESTAMP_VALID;

		RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	}
}


/** Secondary RPM ISR
 *
 * Reads the inner slot on the disk.
 */
void SecondaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	unsigned short edgeTimeStamp = TC1;				/* Save the timestamp */
	unsigned char PTITCurrentState = PTIT;			/* Save the values on port T regardless of the state of DDRT */

	if(!(PTITCurrentState & 0x02)){ /// @todo TODO Remove this once the configuration can be adjusted to only fire on one edge!
		/* Calculate the latency in ticks */
		ISRLatencyVars.secondaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

		// Only count one edge, the other is irrelevant, and this comment will be two once the above todo is completed.
		Counters.secondaryTeethSeen++;

		LongTime timeStamp;
		/* Install the low word */
		timeStamp.timeShorts[1] = edgeTimeStamp;
		/* Find out what our timer value means and put it in the high word */
		if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
			timeStamp.timeShorts[0] = timerExtensionClock + 1;
		}else{
			timeStamp.timeShorts[0] = timerExtensionClock;
		}
		unsigned long thisEventTimeStamp = timeStamp.timeLong;

		unsigned long thisInterEventPeriod = 0;
		if(decoderFlags & LAST_TIMESTAMP_VALID){
			thisInterEventPeriod = thisEventTimeStamp - lastSecondaryEventTimeStamp;
		}

		// This sets currentEvent to 255 such that when the primary ISR runs it is rolled over to zero!
		if(decoderFlags & CAM_SYNC){
			if(currentEvent != (numberOfEvents - 1)){
				// Record that we had to reset position...
				Counters.camSyncCorrections++;
				syncLostOnThisEvent = currentEvent;				// Should never happen, or should be caught by timing checks below
			} // ELSE do nothing, and be happy :-)
		}else{	// If not synced, sync, as this is our reference point.
			decoderFlags |= CAM_SYNC;
			syncCaughtOnThisEvent = numberOfEvents; // Always caught here!
		}
		currentEvent = 0xFF; /// @todo TODO reset always, and catch noise induced errors below, this behaviour (now some lines above) may be bad/not fussy enough, or could be good, depending upon determinate nature of the inter event timing between primary and secondary, or not, perhaps move "lose sync or correct sync" as a configuration variable

		/// Check that it's within reason on a per engine cycle basis TODO : @todo (wider tolerance? if not, then generic settings will need to be less aggresive than they could be and detect less noise than they could) perhaps have 2 or 3 or ? different settings for tolerance that can be used within a specific decoder in any way that the author thinks is appropriate? Defaults set from each decoder and configurable by the user later too.
//		unsigned short thisTicksPerDegree = 0;
//		if(decoderFlags & CAM_SYNC){
//			unsigned short thisAngle = eventAngles[currentEvent] - eventAngles[lastEvent];
//
//			thisTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * thisInterEventPeriod) / thisAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error
//
//			if(decoderFlags & LAST_PERIOD_VALID){
//				unsigned short ratioBetweenThisAndLast = (unsigned short)(((unsigned long)lastTicksPerDegree * 1000) / thisTicksPerDegree);
//				if((ratioBetweenThisAndLast > 1500) || (ratioBetweenThisAndLast < 667)){ /// @todo TODO hard coded tolerance, needs tweaking to be reliable, BEFORE I drive mine in boost, needs making configurable/generic too...
//					resetToNonRunningState();
//				}
//			}/*else*/ if(decoderFlags & LAST_TIMESTAMP_VALID){
//				*ticksPerDegreeRecord = thisTicksPerDegree;
//			}
//		}

		RuntimeVars.secondaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	}
}
