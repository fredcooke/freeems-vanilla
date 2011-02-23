/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010 Fred Cooke
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


/**	@file Simple.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Reads any signal that is once per cylinder
 *
 * This file contains the two interrupt service routines required for to build
 * cleanly. However, only the first one is used due to the simple nature of it.
 *
 * The functional ISR just blindly injects fuel for every input it receives.
 * Thus a perfectly clean input is absolutely essential at this time.
 *
 * Supported engines include:
 * B230F
 *
 * @author Fred Cooke
 *
 * @note Even though I ran my US road trip car on this exact code, I don't recommend it unless you REALLY know what you are doing!
 */


#define DECODER_IMPLEMENTATION_C

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"
#include "../inc/utils.h"


const unsigned short eventAngles[] = {0, 1}; /// @todo TODO fill this out... maybe unused for this decoder? In sched "if(compare(decoderName, "Simple.c")){just always sched 1 fuel and 1 ign delayed after the tooth by some amount.}
const unsigned char decoderName[] = "Simple.c";


/** Primary RPM ISR
 *
 * Schedule events :
 * Blindly start fuel pulses for each and every input pulse.
 *
 * Sample ADCs :
 * Grab a unified set of ADC readings at one time in a consistent crank location to eliminate engine cycle dependent noise.
 * Set flag stating that New pulse, advance, etc should be calculated.
 *
 * @author Fred Cooke
 *
 * @warning These are for testing and demonstration only, not suitable for driving with just yet.
 *
 * @todo TODO make this code more general and robust such that it can be used for real simple applications
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
		/* Echo input condition on J7 */
		PORTJ |= 0x80;

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

// = 60 * (1000000 / 0.8)
#define ticksPerMinute   75000000 // this is correct.

		*RPMRecord = (unsigned short) (ticksPerMinute / timeBetweenSuccessivePrimaryPulses);

		// TODO sample ADCs on teeth other than that used by the scheduler in order to minimise peak run time and get clean signals
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;
		*mathSampleTimeStampRecord = TCNT;

		/* Set flag to say calc required */
		coreStatusA |= CALC_FUEL_IGN;

		/* Reset the clock for reading timeout */
		Clocks.timeoutADCreadingClock = 0;

		if(masterPulseWidth > injectorMinimumPulseWidth){ // use reference PW to decide. spark needs moving outside this area though TODO
			/* Determine if half the cycle is bigger than short-max */
			unsigned short maxAngleAfter;
			if((engineCyclePeriod >> 1) > 0xFFFF){
				maxAngleAfter = 0xFFFF;
			}else{
				maxAngleAfter = (unsigned short)(engineCyclePeriod >> 1);
			}

			/* Check advance to ensure it is less than 1/2 of the previous engine cycle and more than codetime away */
			unsigned short advance;
			if(totalAngleAfterReferenceInjection > maxAngleAfter){ // if too big, make it max
				advance = maxAngleAfter;
			}else if(totalAngleAfterReferenceInjection < trailingEdgeSecondaryRPMInputCodeTime){ // if too small, make it min
				advance = trailingEdgeSecondaryRPMInputCodeTime;
			}else{ // else use it as is
				advance = totalAngleAfterReferenceInjection;
			}

			// determine the long and short start times
			unsigned short startTime = edgeTimeStamp + advance;
			unsigned long startTimeLong = timeStamp.timeLong + advance;

			/* Determine the channels to schedule */
			unsigned char fuelChannel = 0;//(primaryPulsesPerSecondaryPulse / 2) - 1;

			// determine whether or not to reschedule
			unsigned char reschedule = 0;
			unsigned long diff = startTimeLong - (injectorMainEndTimes[fuelChannel] + injectorSwitchOffCodeTime);
			if(diff > LONGHALF){
				reschedule = 1; // http://forum.diyefi.org/viewtopic.php?f=8&t=57&p=861#p861
			}

			// schedule the appropriate channel
			if(!(*injectorMainControlRegisters[fuelChannel] & injectorMainEnableMasks[fuelChannel]) || reschedule){ /* If the timer isn't still running, or if its set too long, set it to start again at the right time soon */
				*injectorMainControlRegisters[fuelChannel] |= injectorMainEnableMasks[fuelChannel];
				*injectorMainTimeRegisters[fuelChannel] = startTime;
				TIE |= injectorMainOnMasks[fuelChannel];
				TFLG = injectorMainOnMasks[fuelChannel];
			}else{
				injectorMainStartTimesHolding[fuelChannel] = startTime;
				selfSetTimer |= injectorMainOnMasks[fuelChannel]; // setup a bit to let the timer interrupt know to set its own new start from a var
			}
		}
		RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	}else{
		PORTJ &= 0x7F;
		RuntimeVars.primaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
	}
}


/** Secondary RPM ISR
 *
 * Unused in this decoder.
 */
void SecondaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	unsigned short edgeTimeStamp = TC1;				/* Save the timestamp */
	unsigned char PTITCurrentState = PTIT;			/* Save the values on port T regardless of the state of DDRT */
//	unsigned short PORTS_BACurrentState = PORTS_BA;	/* Save ignition output state */

	/* Calculate the latency in ticks */
	ISRLatencyVars.secondaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	/** @todo TODO discard narrow ones! test for tooth width and tooth period
	 * the width should be based on how the hardware is setup. IE the LM1815
	 * is adjusted to have a pulse output of a particular width. This noise
	 * filter should be matched to that width as should the hardware filter.
	 */

	LongTime timeStamp;

	/* Install the low word */
	timeStamp.timeShorts[1] = edgeTimeStamp;
	/* Find out what our timer value means and put it in the high word */
	if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
		timeStamp.timeShorts[0] = timerExtensionClock + 1;
	}else{
		timeStamp.timeShorts[0] = timerExtensionClock;
	}

	if(PTITCurrentState & 0x02){
		// echo input condition
		PORTJ |= 0x40;
	}else{
		PORTJ &= 0xBF;
	}
}
