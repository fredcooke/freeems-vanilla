/*	FreeEMS - the open source engine management system

	Copyright 2009 Philip Johnson

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


/**	@file MissingTeeth.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Missing teeth, mostly 36-1 and 60-2
 *
 * @note Pseudo code that does not compile with zero warnings and errors MUST be commented out.
 *
 * @author Philip Johnson
 */


#include "inc/freeEMS.h"
#include "inc/interrupts.h"


/** Primary RPM ISR
 *
 * @todo TODO Docs here!
 */
void PrimaryRPMISR(void) {
	static LongTime lastPeriod = { 0 };
	static LongTime lastTimeStamp = { 0 };
	static unsigned int count = 0;
	LongTime thisTimeStamp;
	LongTime thisPeriod;
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT; /* Save the current timer count */
	unsigned short edgeTimeStamp = TC0; /* Save the edge time stamp */
	unsigned char PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */
	//	unsigned short PORTS_BACurrentState = PORTS_BA;	/* Save ignition output state */

	/* Calculate the latency in ticks */
	ISRLatencyVars.primaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	/* Install the low word */
	thisTimeStamp.timeShorts[1] = edgeTimeStamp;
	/* Find out what our timer value means and put it in the high word */
	if (TFLGOF && !(edgeTimeStamp & 0x8000)) { /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
		thisTimeStamp.timeShorts[0] = timerExtensionClock + 1;
	} else {
		thisTimeStamp.timeShorts[0] = timerExtensionClock;
	}

	/* How many ticks between transitions? */
	if (thisTimeStamp.timeLong > lastTimeStamp.timeLong) {
		thisPeriod.timeLong = thisTimeStamp.timeLong - lastTimeStamp.timeLong;
	} else {
		thisPeriod.timeLong = thisTimeStamp.timeLong + (0xFFFFFFFF
				- lastTimeStamp.timeLong);
	}
	lastTimeStamp.timeLong = thisTimeStamp.timeLong;

	/* Set up edges as per config */
	unsigned char risingEdge;
	if (fixedConfigs1.coreSettingsA & PRIMARY_POLARITY) {
		risingEdge = PTITCurrentState & 0x01;
	} else {
		risingEdge = !(PTITCurrentState & 0x01);
	}

	if (lastPeriod.timeLong != 0) {
		if (risingEdge) {
			//Find the missing tooth
			if (count == 0 || count == 70) {
				PORTP &= 0x7F;
				if (thisPeriod.timeLong > (lastPeriod.timeLong + (lastPeriod.timeLong>>1)) &&
					thisPeriod.timeLong < ((lastPeriod.timeLong<<1) + (lastPeriod.timeLong>>1))) {
					count = 1;
				} else {
					//We have lost sync
					count = 0;
				}
			}else if (count >= 2) {
				count++;
			}
			/* Echo input condition on J7 */
			PORTJ |= 0x80;
			// increment crank pulses TODO this needs to be wrapped in tooth period and width checking
			primaryPulsesPerSecondaryPulse++;
			RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
		} else {
			//Is this really a missing tooth?
			if (count == 1) {
				if ((thisPeriod.timeLong > ((lastPeriod.timeLong) - (lastPeriod.timeLong>>2))) &&
						(thisPeriod.timeLong < ((lastPeriod.timeLong) + (lastPeriod.timeLong>>2)))) {
					count++;
					PORTP |= 0x80;
				} else {
					//We have lost sync
					count=0;
					PORTP &= 0x7F;
				}
			}else if (count >= 3) {
				count++;
			}
			PORTJ &= 0x7F;
			RuntimeVars.primaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
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
	//	unsigned short PORTS_BACurrentState = PORTS_BA;	/* Save ignition output state */

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
