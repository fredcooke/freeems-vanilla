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
 * @author Fred Cooke
 */


#define DECODER_IMPLEMENTATION_C

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"
#include "../inc/utils.h"


const unsigned short eventAngles[] = {0}; // no events really...
const unsigned char decoderName[] = "Listener.c";


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

	if(PTITCurrentState & 0x01){
		/* Invert input condition on ign 1 */
		PORTT &= NBIT2;

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

		// temporary data from inputs
		unsigned long primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
		unsigned long timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp - lastEventTimeStamp;
		lastEventTimeStamp = primaryLeadingEdgeTimeStamp;


		*ticksPerDegreeRecord = (unsigned short)(timeBetweenSuccessivePrimaryPulses / 4);

		// TODO sample ADCs on teeth other than that used by the scheduler in order to minimise peak run time and get clean signals
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;
		*mathSampleTimeStampRecord = TCNT;

		/* Set flag to say calc required */
		coreStatusA |= CALC_FUEL_IGN;

		/* Reset the clock for reading timeout */
		Clocks.timeoutADCreadingClock = 0;

		RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	}else{
		/* Invert input condition on ign 1 */
		PORTT |= BIT2;
		RuntimeVars.primaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
	}
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
