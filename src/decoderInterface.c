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


void schedulePortTPin(unsigned char pin, LongTime timeStamp){
	// determine the long and short start times
	unsigned short startTime = timeStamp.timeShorts[1] + postReferenceEventDelays[pin];
	// remove this temporarily too, no need for it without the later conditional code
	unsigned long startTimeLong = timeStamp.timeLong + postReferenceEventDelays[pin];

	// determine whether or not to reschedule or self schedule assuming pin is currently scheduled
	unsigned long diff = startTimeLong - (injectorMainEndTimes[pin] + injectorSwitchOffCodeTime);
#define newStartIsAfterOutputEndTimeAndCanSelfSet	(diff > LONGHALF)
// http://forum.diyefi.org/viewtopic.php?f=8&t=57&p=861#p861

	// pin is set to activate AND can self set
	if((*injectorMainControlRegisters[pin] & injectorMainEnableMasks[pin]) && newStartIsAfterOutputEndTimeAndCanSelfSet){
		injectorMainStartTimesHolding[pin] = startTime;
		selfSetTimer |= injectorMainOnMasks[pin]; // setup a bit to let the timer interrupt know to set its own new start from a var
		Counters.testCounter1++;
	}else{ // pin is not set to active OR pin is set to active and can't self set
		*injectorMainControlRegisters[pin] |= injectorMainEnableMasks[pin];
		*injectorMainTimeRegisters[pin] = startTime;
		TIE |= injectorMainOnMasks[pin];
		TFLG = injectorMainOnMasks[pin];
		Counters.testCounter3++;
	}
}
