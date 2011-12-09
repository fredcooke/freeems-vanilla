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


/** @file
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
 * @param uniqueLossID 0 is reserved for system use, within your decoder never use the same value twice.
 * @author Fred Cooke
 */
void resetToNonRunningState(unsigned char uniqueLossID){
	if(uniqueLossID){
		KeyUserDebugs.syncResetCalls++;
	}

	/* Reset RPM to zero */
	ticksPerDegree0 = 0;
	ticksPerDegree1 = 0;

	/* Ensure tacho reads lowest possible value */
	engineCyclePeriod = ticksPerCycleAtOneRPM;

	// Keep track of lost sync in counters
	if(KeyUserDebugs.decoderFlags & (CAM_SYNC | CRANK_SYNC | COMBUSTION_SYNC)){
		FLAG_AND_INC_FLAGGABLE(FLAG_DECODER_SYNC_LOSSES_OFFSET);
	}else{
		FLAG_AND_INC_FLAGGABLE(FLAG_DECODER_SYNC_STATE_CLEARS_OFFSET);
	}

	// record unique loss ID
	KeyUserDebugs.syncLostWithThisID = uniqueLossID;

	// record current event
	KeyUserDebugs.syncLostOnThisEvent = KeyUserDebugs.currentEvent;

	/* Clear all sync flags to lost state */
	KeyUserDebugs.decoderFlags = 0; // Nothing should use this except for us anyway!
	perDecoderReset();
	// TODO more stuff needs resetting here, but only critical things.
}


/** Schedule an ignition output event on port T
 *
 * @author Fred Cooke
 * @warning If you do not handle the skipEventFlags then excess advance may occur!
 */
void schedulePortTPin(unsigned char outputEventNumber, LongTime timeStamp){
	unsigned char pin = outputEventPinNumbers[outputEventNumber];
	unsigned short postReferenceEventDelay = 0;
	if(skipEventFlags & (1UL << outputEventNumber)){
		postReferenceEventDelay = decoderMaxCodeTime;
		skipEventFlags &= ~(1UL << outputEventNumber); // Clear the flag
	}else{
		postReferenceEventDelay = outputEventDelayFinalPeriod[outputEventNumber];
	}
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
	fresh code again, five states, 6 possible behaviours:

	not enabled - sched!!! always
	enabled and low, ready to turn on - if too close, do nothing, or if far enough away, resched
	enabled and high, ready to turn off - if too close, resched to turn on, if far enough away, self sched
*/

	// Is it enabled and about to do *something*?
	if(TIE & injectorMainOnMasks[pin]){
		// If configured to do something specific
		if(*injectorMainControlRegisters[pin] & injectorMainActiveMasks[pin]){
			// If that something is go high
			if(*injectorMainControlRegisters[pin] & injectorMainGoHighMasks[pin]){
				// GO HIGH SHOULD DO NOTHING CEPT COUNTER
				// if too close, do nothing, or if far enough away, resched
				// for now just always do nothing as it's going to fire, and whatever configured got it close enough...
				Counters.pinScheduledAlready++;
			}else{ // Otherwise it's go low
				// if too close, resched to turn, ie, stay on... , if far enough away, self sched
				if(newStartIsAfterOutputEndTimeAndCanSelfSet){
					// self sched
					injectorMainStartOffsetHolding[pin] = startTime - *injectorMainTimeRegisters[pin];
					outputEventPulseWidthsHolding[pin] = outputEventPulseWidthsMath[outputEventNumber];
					outputEventExtendNumberOfRepeatsHolding[pin] = outputEventExtendNumberOfRepeats[outputEventNumber];
					outputEventExtendRepeatPeriodHolding[pin] = outputEventExtendRepeatPeriod[outputEventNumber];
					outputEventDelayFinalPeriodHolding[pin] = outputEventDelayFinalPeriod[outputEventNumber];
					selfSetTimer |= injectorMainOnMasks[pin]; // setup a bit to let the timer interrupt know to set its own new start from a var
					Counters.pinScheduledToSelfSchedule++;
				}else{
					SCHEDULE_ONE_ECT_OUTPUT();
					Counters.pinScheduledAgainToStayOn++;
				}
			}
		}else{ // Configured to do nothing, or toggle
			if(*injectorMainControlRegisters[pin] & injectorMainGoHighMasks[pin]){
				// TOGGLE SHOULD EARN SOME SORT OF ERROR CONDITION/COUNTER
				Counters.pinScheduledToToggleError++;
			}else{
				// DO NOTHING SHOULD DO THE SAME AS GO HIGH
				// ie, do nothing
				// if too close, do nothing, or if far enough away, resched
				// for now just always do nothing as it's going to fire, and whatever configured got it close enough...
				Counters.pinScheduledToDoNothing++;
			}
		}
	}else{ // not enabled, schedule as normal
		SCHEDULE_ONE_ECT_OUTPUT();
		Counters.pinScheduledFromCold++;
	}

#ifdef XGATE // This has to be here because the timing of the ECT stuff is critical and it must run first.
#include "xgateScheduler.c"
#endif // Also, this should always run so can't be inside the above if/else block.
}
