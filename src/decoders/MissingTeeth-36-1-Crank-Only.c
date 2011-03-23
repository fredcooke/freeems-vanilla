/*	FreeEMS - the open source engine management system

	Copyright 2009, 2010, 2011 Philip L Johnson, Fred Cooke

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

	We ask that if you make any changes to this file you email them upstream to
	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!

	Thank you for choosing FreeEMS to run your engine! */


/**	@file MissingTeeth36-1-Crank-Only.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Missing teeth, 36-1, Crank only
 *
 * This will be made generic, and built as an include with multiple headers containing the parameters required to make it function.
 *
 * @author Philip Johnson
 */


#define DECODER_IMPLEMENTATION_C

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"


const unsigned char decoderName[] = "MissingTeeth36-1-Crank-Only";
const unsigned char numberOfRealEvents = 35;
const unsigned char numberOfVirtualEvents = 35;
const unsigned short eventAngles[] = {0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230, 240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340};
const unsigned char eventMapping[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34};
const unsigned char eventValidForCrankSync[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // this is only correct while doing pure crank sync, wrong once doing more, i think, TBC...
const unsigned short totalEventAngleRange = 360; // set up for crank only at this point, build twice, once for crank only,
const unsigned short decoderMaxCodeTime = 100; // To be optimised (shortened)!
/// @todo TODO make the below code generic and bullet proof, add all of the above to a header, and make the secondary code not run if not configured to run in the header, then make headers for every common combo


/** Primary RPM ISR
 *
 * @todo TODO Docs here!
 */
void PrimaryRPMISR(void) {
	static LongTime thisHighLowTime = { 0 };
	static LongTime lastHighLowTime = { 0 };
	static LongTime lowTime = { 0 };
	static LongTime lastPeriod = { 0 };
	static LongTime lastTimeStamp = { 0 };
	static unsigned int count = 0;

	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT; /* Save the current timer count */
	unsigned short edgeTimeStamp = TC0; /* Save the edge time stamp */
	unsigned char PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */

	/* Calculate the latency in ticks */
	ISRLatencyVars.primaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	LongTime thisTimeStamp;
	/* Install the low word */
	thisTimeStamp.timeShorts[1] = edgeTimeStamp;
	/* Find out what our timer value means and put it in the high word */
	if (TFLGOF && !(edgeTimeStamp & 0x8000)) { /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
		thisTimeStamp.timeShorts[0] = timerExtensionClock + 1;
	} else {
		thisTimeStamp.timeShorts[0] = timerExtensionClock;
	}

	/* How many ticks between transitions? */
	LongTime thisPeriod;
	if (thisTimeStamp.timeLong > lastTimeStamp.timeLong) {
		thisPeriod.timeLong = thisTimeStamp.timeLong - lastTimeStamp.timeLong;
	} else {
		thisPeriod.timeLong = thisTimeStamp.timeLong + (0xFFFFFFFF
				- lastTimeStamp.timeLong);
	}
	lastTimeStamp.timeLong = thisTimeStamp.timeLong;

	/* Set up edges as per config */
	unsigned char risingEdge = PTITCurrentState & 0x01;

	if (lastPeriod.timeLong != 0) {
		if (risingEdge) {
			thisHighLowTime.timeLong = thisPeriod.timeLong + lowTime.timeLong;
			//Find the missing tooth
			if (count == 0 || count == 70) {
				if (thisHighLowTime.timeLong > (lastHighLowTime.timeLong + (lastHighLowTime.timeLong>>1)) &&
						thisHighLowTime.timeLong < ((lastHighLowTime.timeLong<<1) + (lastHighLowTime.timeLong>>1))) {
					// save temporary data from inputs
					unsigned long primaryLeadingEdgeTimeStamp = thisTimeStamp.timeLong;
					unsigned long timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp - lastEventTimeStamp;	//I'd name it timeBetweenSuccessiveReferencePulses
					lastEventTimeStamp = primaryLeadingEdgeTimeStamp;

					// this is totally broken, fix at some point in some way...
					*ticksPerDegreeRecord = (unsigned short)timeBetweenSuccessivePrimaryPulses;
					// We have sync
					PORTP |= 0x80;
					count = 1;
				} else {
					//We have lost sync
					count = 0;
					PORTP &= 0x7F;
				}
			}else if (count == 2 || (count%2 == 0 &&
					thisHighLowTime.timeLong > (lastHighLowTime.timeLong>>1) &&
					thisHighLowTime.timeLong < (lastHighLowTime.timeLong<<1) )) {
				count++;
			} else {
				//We have lost sync
				count = 0;
				PORTP &= 0x7F;
			}

			/* Echo input condition on J7 */
			PORTJ |= 0x80;
			// increment crank pulses TODO this needs to be wrapped in tooth period and width checking
			lastHighLowTime.timeLong = thisHighLowTime.timeLong;
//			primaryPulsesPerSecondaryPulse++; unused elsewhere in this file, thus unused, alltogether!
			RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
		} else {
			if (count%2 == 1) {
				count++;
			} else {
				//We have lost sync
				count = 0;
				PORTP &= 0x7F;
			}
			/* Echo input condition on J7 */
			PORTJ &= 0x7F;
			RuntimeVars.primaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
			lowTime.timeLong = thisPeriod.timeLong;
		}
	}
	lastPeriod.timeLong = thisPeriod.timeLong;
	Counters.primaryTeethSeen++;
}


/** Secondary RPM ISR
 *
 * @todo TODO Docs here!
 */
void SecondaryRPMISR(void) {
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT; /* Save the current timer count */
	unsigned short edgeTimeStamp = TC1; /* Save the timestamp */
	unsigned char PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */

	/* Calculate the latency in ticks */
	ISRLatencyVars.secondaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	// TODO discard narrow ones! test for tooth width and tooth period

	/* Set up edges as per config */
	unsigned char risingEdge;
	if (fixedConfigs1.coreSettingsA & SECONDARY_POLARITY) {
		risingEdge = PTITCurrentState & 0x02;
	} else {
		risingEdge = !(PTITCurrentState & 0x02);
	}

	if (risingEdge) {
		// echo input condition
		PORTJ |= 0x40;

		LongTime timeStamp;

		/* Install the low word */
		timeStamp.timeShorts[1] = edgeTimeStamp;
		/* Find out what our timer value means and put it in the high word */
		if (TFLGOF && !(edgeTimeStamp & 0x8000)) { /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
			timeStamp.timeShorts[0] = timerExtensionClock + 1;
		} else {
			timeStamp.timeShorts[0] = timerExtensionClock;
		}

		RuntimeVars.secondaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	} else {
		PORTJ &= 0xBF;
		RuntimeVars.secondaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
	}

	Counters.secondaryTeethSeen++;
}
