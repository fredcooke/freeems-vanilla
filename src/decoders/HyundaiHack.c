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


/**	@file HyundaiHack.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Echos the input on the first ignition output
 *
 * This decoder is for unlocked distributor cars such as the MIGHTY Hyundai
 * that I've been living in for 6 months. The mechanical distributor continues
 * to set the timing, the ECU just logs RPM and MAP and any other senors and/or
 * solenoids you hook up and configure.
 *
 * No plugs cranking LA test results:
 *

17302
17346
17451
17498
17600
17646
17751
17795
17900

0
44
149
196
298
344
449
493
598

0
52.98
179.4
235.99
358.8
414.18
540.6
593.58
720

52.98
126.42
56.59
122.81
55.38
126.42
52.98
126.42

54.48
125.52

54,126

 *
 * Approximately 1000 samples per second
 *
 *
 * @author Fred Cooke
 */


#define DECODER_IMPLEMENTATION_C

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"
#include "../inc/utils.h"


const unsigned char decoderName[] = "HyundaiHack.c";
const unsigned char numberOfEvents = 2;
const unsigned short eventAngles[] = {0, 54}; // 1/4 cycle events.
const unsigned short totalEventAngleRange = 180;
const unsigned short decoderMaxCodeTime = 100; // To be optimised (shortened)!


/** Primary RPM ISR
 *
 * Take an ADC reading on one edge, and mimic the output on ign 1!
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

	// set as synced for volvo always as loss of sync not actually possible
	decoderFlags |= COMBUSTION_SYNC;

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

	if(PTITCurrentState & 0x01){
		// temporary data from inputs
		unsigned long primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
		unsigned long timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp - lastPrimaryEventTimeStamp;
		lastPrimaryEventTimeStamp = primaryLeadingEdgeTimeStamp;


		*ticksPerDegreeRecord = (unsigned short)(timeBetweenSuccessivePrimaryPulses / 16);

		// TODO Once sampling/RPM is configurable, use this tooth for a lower MAP reading.
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;
		*mathSampleTimeStampRecord = TCNT;

		/* Set flag to say calc required */
		coreStatusA |= CALC_FUEL_IGN;

		/* Reset the clock for reading timeout */
		Clocks.timeoutADCreadingClock = 0;

		currentEvent = 1;

		RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	}else{
		// temporary data from inputs
		unsigned long secondaryLeadingEdgeTimeStamp = timeStamp.timeLong;
		unsigned long timeBetweenSuccessiveSecondaryPulses = secondaryLeadingEdgeTimeStamp - lastSecondaryEventTimeStamp;
		lastSecondaryEventTimeStamp = secondaryLeadingEdgeTimeStamp;


		*ticksPerDegreeRecord = (unsigned short)(timeBetweenSuccessiveSecondaryPulses / 16);

		/// @todo TODO make this stuff behave correctly, this one will only run at startup, and the other will always run, but do it by generic config and split this stuff out into a shared function, soon.
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;
		*mathSampleTimeStampRecord = TCNT;

		/* Set flag to say calc required */
		coreStatusA |= CALC_FUEL_IGN;

		/* Reset the clock for reading timeout */
		Clocks.timeoutADCreadingClock = 0;

		currentEvent = 0;

		RuntimeVars.primaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
	}

		/// @todo TODO gain and lose combustion sync based on timing between teeth, and save state and use flags to only check if good, etc
//		if(decoderFlags & COMBUSTION_SYNC){
			if(pinEventNumbers[0] == currentEvent){
				skipEventFlags &= injectorMainOffMasks[0];
				schedulePortTPin(0, timeStamp);
			}else if(skipEventFlags & injectorMainOnMasks[0]){
				schedulePortTPin(0, timeStamp);
			}
//		}
}


/** Secondary RPM ISR
 *
 * Unused.
 *
 * @author Fred Cooke
 */
void SecondaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;
}
