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

	/* Clear all sync flags to lost state */
	decoderFlags &= (CLEAR_CAM_SYNC & CLEAR_CRANK_SYNC & CLEAR_COMBUSTION_SYNC & CLEAR_LAST_PERIOD_VALID & CLEAR_LAST_TIMESTAMP_VALID);

	// TODO more stuff needs resetting here, but only critical things.
}


// Need to make this available to all decoders and cut out code from those that have it built in.
void schedulePortTPin(unsigned char pin, unsigned short edgeTimeStamp){
	/// @todo TODO if the other stuff isn't needed then neither is this!
	/* Determine if half the cycle is bigger than short-max */
	unsigned short maxAngleAfter;
	if((engineCyclePeriod >> 1) > 0xFFFF){
		maxAngleAfter = 0xFFFF;
	}else{
		maxAngleAfter = (unsigned short)(engineCyclePeriod >> 1);
	}

	/// @todo TODO rename advance to something more honest, do we really need to do these checks here? Why not do them in the scheduler instead? Maybe we can just trust the delay and add it to the stamp?
	/* Check advance to ensure it is less than 1/2 of the previous engine cycle and more than codetime away */
	unsigned short advance;
	if(postReferenceEventDelays[pin] > maxAngleAfter){ // if too big, make it max
		advance = maxAngleAfter;
	}else if(postReferenceEventDelays[pin] < trailingEdgeSecondaryRPMInputCodeTime){ // if too small, make it min
		advance = trailingEdgeSecondaryRPMInputCodeTime;
	}else{ // else use it as is
		advance = postReferenceEventDelays[pin];
	}

	// determine the long and short start times
	unsigned short startTime = edgeTimeStamp + advance;
	// remove this temporarily too, no need for it without the later conditional code
//	unsigned long startTimeLong = timeStamp.timeLong + advance;
//
//	// determine whether or not to reschedule
//	unsigned char reschedule = 0;
//	unsigned long diff = startTimeLong - (injectorMainEndTimes[pin] + injectorSwitchOffCodeTime);
//	if(diff > LONGHALF){
//		reschedule = 1; // http://forum.diyefi.org/viewtopic.php?f=8&t=57&p=861#p861
//	}

	// schedule the appropriate channel
	// Removed conditions for now, known fix to intermittent random output bug found by someone else. Needs more work on a scope to get really good.
//	if(!(*injectorMainControlRegisters[pin] & injectorMainEnableMasks[pin]) || reschedule){ /* If the timer isn't still running, or if its set too long, set it to start again at the right time soon */
		*injectorMainControlRegisters[pin] |= injectorMainEnableMasks[pin];
		*injectorMainTimeRegisters[pin] = startTime;
		TIE |= injectorMainOnMasks[pin];
		TFLG = injectorMainOnMasks[pin];
//	}else{
//		injectorMainStartTimesHolding[pin] = startTime;
//		selfSetTimer |= injectorMainOnMasks[pin]; // setup a bit to let the timer interrupt know to set its own new start from a var
//	}
}
