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


/**	@file Generic4CylinderHallOrOptical.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Echos the input on the first ignition output
 *
 * This decoder is for any 4 tooth/slot hall or optical cam speed sensor and to
 * be used for distributor and/or 4 shot batch injection only.
 *
 * To build a version of this decoder with a specific angle pair for your hall
 * or optical distributor, just define the DECODER_IMPLEMENTATION_C flag,
 * include the four required headers, define the angle for E1, and define the
 * unique decoder name string!
 *
 * To effectively reverse the polarity, just subtract your angle from 180 and
 * it will then be correct, assuming that either angle is correct.
 *
 * @author Fred Cooke
 */


#define angleOfSingleIteration 180

#define E0 0
// Define E1 in your reverse header!
#define E2 (E0 + angleOfSingleIteration)
#define E3 (E1 + angleOfSingleIteration)
#define E4 (E0 + (2 * angleOfSingleIteration))
#define E5 (E1 + (2 * angleOfSingleIteration))
#define E6 (E0 + (3 * angleOfSingleIteration))
#define E7 (E1 + (3 * angleOfSingleIteration))

const unsigned char numberOfRealEvents = 2;
const unsigned char numberOfVirtualEvents = 8;
const unsigned short eventAngles[] = {E0, E1, E2, E3, E4, E5, E6, E7};
const unsigned char eventMapping[] = {0,1,0,1,0,1,0,1};
const unsigned short totalEventAngleRange = 720;
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
