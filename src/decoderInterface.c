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

/** @file decoderInterface.c
 *
 * @ingroup enginePositionRPMDecoders
 *
 * @brief shared functions used by all decoders
 *
 * To maximise code reuse and minimise bugs it is strongly recommended that you
 * use these pre-canned functions to do work required in your decoder.
 */

#define DECODER_INTERFACE_C
#include "inc/freeEMS.h"
#include "inc/decoderInterface.h"


/** @brief Reset key state
 *
 * Reset all important variables to their non-running state.
 *
 * @todo TODO bring this up to date and/or find a better way to do it.
 *
 * @author Fred Cooke
 */
void resetToNonRunningState(){
	/* Reset RPM to zero */
	ticksPerDegree0 = 0;
	ticksPerDegree1 = 0;

	// Temporary from 4and1 :
	unknownEdges = 0;

	/* Ensure tacho reads lowest possible value */
	engineCyclePeriod = ticksPerCycleAtOneRPM;

	// Keep track of lost sync in counters
	if(decoderFlags & CAM_SYNC){
		Counters.camSyncLosses++;
	}
	if(decoderFlags & CRANK_SYNC){
		Counters.crankSyncLosses++;
	}
	if(decoderFlags & COMBUSTION_SYNC){
		Counters.combustionSyncLosses++;
	}

	/* Clear all sync flags to lost state */
	decoderFlags &= (CLEAR_CAM_SYNC & CLEAR_CRANK_SYNC & CLEAR_COMBUSTION_SYNC & CLEAR_LAST_PERIOD_VALID & CLEAR_LAST_TIMESTAMP_VALID);

	// TODO more stuff needs resetting here, but only critical things.
}


/** Schedule an ignition output event on port T
 *
 * @author Fred Cooke
 * @warning If you do not handle the skipEventFlags then excess advance may occur!
 */
void schedulePortTPin(unsigned char pin, LongTime timeStamp){
	unsigned short postReferenceEventDelay = 0;
//	if(skipEventFlags & injectorMainOnMasks[pin]){
//		postReferenceEventDelay = trailingEdgeSecondaryRPMInputCodeTime;
//		skipEventFlags &= injectorMainOffMasks[pin]; // Clear the flag
//	}else{
		postReferenceEventDelay = postReferenceEventDelays[pin];
//	}
	// determine the long and short start times
	unsigned short startTime = timeStamp.timeShorts[1] + postReferenceEventDelay;
	// remove this temporarily too, no need for it without the later conditional code
	unsigned long startTimeLong = timeStamp.timeLong + postReferenceEventDelay;

	/// @todo TODO Make this more understandable as right now it is difficult to grok.
	// determine whether or not to reschedule or self schedule assuming pin is currently scheduled
	unsigned long diff = (injectorMainEndTimes[pin] + injectorSwitchOffCodeTime) - startTimeLong;
#define newStartIsAfterOutputEndTimeAndCanSelfSet	(diff > LONGHALF)
// http://forum.diyefi.org/viewtopic.php?f=8&t=57&p=861#p861

/*
	fresh code again, three states, 5 behaviours:

	not enabled - sched!!! always
	enabled and low, ready to turn on - if too close, do nothing, or if far enough away, resched
	enabled and high, ready to turn off - if too close, resched to turn on, if far enough away, self sched
*/

	// Is it enabled and about to do *something*?
	if(*injectorMainControlRegisters[pin] & injectorMainActiveMasks[pin]){
		// Is that something "go high" from a low state?
		if(*injectorMainControlRegisters[pin] & injectorMainGoHighMasks[pin]){
			Counters.testCounter0++;
			// if too close, do nothing, or if far enough away, resched
			// for now just always do nothing as it's going to fire, and whatever configured got it close enough...
		}else{ // ELSE "go low" from a high state!
			// if too close, resched to turn, ie, stay on... , if far enough away, self sched
			if(newStartIsAfterOutputEndTimeAndCanSelfSet){
				// self sched
				injectorMainStartTimesHolding[pin] = startTime;
				selfSetTimer |= injectorMainOnMasks[pin]; // setup a bit to let the timer interrupt know to set its own new start from a var
				Counters.testCounter1++;
			}else{
				*injectorMainControlRegisters[pin] |= injectorMainEnableMasks[pin];
				*injectorMainTimeRegisters[pin] = startTime;
				TIE |= injectorMainOnMasks[pin];
				TFLG = injectorMainOnMasks[pin];
				selfSetTimer &= injectorMainOffMasks[pin];
				Counters.testCounter2++;
			}
		}
	}else{
		*injectorMainControlRegisters[pin] |= injectorMainEnableMasks[pin];
		*injectorMainTimeRegisters[pin] = startTime;
		TIE |= injectorMainOnMasks[pin];
		TFLG = injectorMainOnMasks[pin];
		selfSetTimer &= injectorMainOffMasks[pin];
		Counters.testCounter3++;
	}


	// This code is broken and checks for an effective OR of the enable and direction pins causing self sched to occur when it shouldnt...
//	// pin is set to activate AND can self set
//	if((*injectorMainControlRegisters[pin] & injectorMainEnableMasks[pin]) && newStartIsAfterOutputEndTimeAndCanSelfSet){
//		injectorMainStartTimesHolding[pin] = startTime;
//		selfSetTimer |= injectorMainOnMasks[pin]; // setup a bit to let the timer interrupt know to set its own new start from a var
//		Counters.testCounter1++;
//	}else{ // pin is not set to active OR pin is set to active and can't self set
//		*injectorMainControlRegisters[pin] |= injectorMainEnableMasks[pin];
//		*injectorMainTimeRegisters[pin] = startTime;
//		TIE |= injectorMainOnMasks[pin];
//		TFLG = injectorMainOnMasks[pin];
//		selfSetTimer &= injectorMainOffMasks[pin];
//		Counters.testCounter3++;
//	}
}
