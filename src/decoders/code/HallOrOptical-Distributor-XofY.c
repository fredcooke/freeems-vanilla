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


/**	@file HallOrOptical-Distributor-XofY.c
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


#define angleOfSingleIteration (180 * oneDegree)

#define E0 0
// Define E1 in your reverse header!
#define E2 (E0 + angleOfSingleIteration)
#define E3 (E1 + angleOfSingleIteration)
#define E4 (E0 + (2 * angleOfSingleIteration))
#define E5 (E1 + (2 * angleOfSingleIteration))
#define E6 (E0 + (3 * angleOfSingleIteration))
#define E7 (E1 + (3 * angleOfSingleIteration))


#if (E1 >= angleOfSingleIteration)
#error "Angle E1 defined to be larger than the available angle which it is within!"
#endif


const unsigned short eventAngles[] = {E0, E1, E2, E3, E4, E5, E6, E7};
const unsigned char eventValidForCrankSync[] = {0,0,0,0,0,0,0,0}; // Unused in this decoder.


void decoderInitPreliminary(){} // This decoder works with the defaults
void perDecoderReset(){} // Nothing special to reset for this code


void PrimaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;

	/* Save all relevant available data here */
	unsigned short edgeTimeStamp = TC0;				/* Save the edge time stamp */
	unsigned char PTITCurrentState = PTIT;			/* Save the values on port T regardless of the state of DDRT */

	// TODO DEBUG/TUNING MACRO HERE!

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
	unsigned long thisEventTimeStamp = timeStamp.timeLong;

	unsigned char lastEvent = 0;
	unsigned short thisTicksPerDegree = 0;
	if(PTITCurrentState & 0x01){
		// temporary data from inputs
		unsigned long primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
		unsigned long timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp - lastPrimaryEventTimeStamp;
		lastPrimaryEventTimeStamp = primaryLeadingEdgeTimeStamp;


		thisTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * timeBetweenSuccessivePrimaryPulses) / angleOfSingleIteration);
		*ticksPerDegreeRecord = thisTicksPerDegree;

		// TODO Once sampling/RPM is configurable, use this tooth for a lower MAP reading.
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;

		/* Set flag to say calc required */
		coreStatusA |= CALC_FUEL_IGN;

		/* Reset the clock for reading timeout */
		Clocks.timeoutADCreadingClock = 0;

		currentEvent = 1;
		lastEvent = 0;
	}else{
		// temporary data from inputs
		unsigned long secondaryLeadingEdgeTimeStamp = timeStamp.timeLong;
		unsigned long timeBetweenSuccessiveSecondaryPulses = secondaryLeadingEdgeTimeStamp - lastSecondaryEventTimeStamp;
		lastSecondaryEventTimeStamp = secondaryLeadingEdgeTimeStamp;


		thisTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * timeBetweenSuccessiveSecondaryPulses) / angleOfSingleIteration);
		*ticksPerDegreeRecord = thisTicksPerDegree;

		// TODO make this stuff behave correctly, this one will only run at startup, and the other will always run, but do it by generic config and split this stuff out into a shared function, soon.
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;

		/* Set flag to say calc required */
		coreStatusA |= CALC_FUEL_IGN;

		/* Reset the clock for reading timeout */
		Clocks.timeoutADCreadingClock = 0;

		currentEvent = 0;
		lastEvent = 1;
	}

	unsigned long thisInterEventPeriod = 0;
	if(decoderFlags & LAST_TIMESTAMP_VALID){
		thisInterEventPeriod = thisEventTimeStamp - lastEventTimeStamp;
	}

	// This should check during gain of sync too and prevent gaining sync if the numbers aren't right, however this is a step up for the Hotel at this time.
	if(decoderFlags & COMBUSTION_SYNC){
		unsigned short thisAngle = 0;
		if(currentEvent == 0){
			// Fix this to work for all:
//			thisAngle = eventAngles[currentEvent] + totalEventAngleRange - eventAngles[lastEvent] ; // Optimisable... leave readable for now! :-p J/K learn from this...
			thisAngle = eventAngles[currentEvent] + angleOfSingleIteration - eventAngles[lastEvent] ; // Optimisable... leave readable for now! :-p J/K learn from this...
		}else{
			thisAngle = eventAngles[currentEvent] - eventAngles[lastEvent];
		}

		thisTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * thisInterEventPeriod) / thisAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error

		if(decoderFlags & LAST_PERIOD_VALID){
			unsigned short ratioBetweenThisAndLast = (unsigned short)(((unsigned long)lastTicksPerDegree * 1000) / thisTicksPerDegree);
			if(ratioBetweenThisAndLast > fixedConfigs2.decoderSettings.decelerationInputEventTimeTolerance){
				resetToNonRunningState(1);
				return;
			}else if(ratioBetweenThisAndLast < fixedConfigs2.decoderSettings.accelerationInputEventTimeTolerance){
				resetToNonRunningState(2);
				return;
			}
		}
	}

	if(decoderFlags & COMBUSTION_SYNC){
		SCHEDULE_ECT_OUTPUTS();
	}

	/* TODO this delays outputs until the fourth ISR execution, but we could
	 * get them one execution or 1/8 of a rev sooner if we did a preliminary
	 * calc from the previous edge instead of the previous same edge now, and
	 *
	 * The proper way to do this is set sync when we have it and not set data
	 * as having been recorded until we know the data is good. That way the
	 * scheduler can keep things unscheduled until the time is right.
	 */
	if(decoderFlags & LAST_PERIOD_VALID){
		SET_SYNC_LEVEL_TO(COMBUSTION_SYNC);
	}

	if(decoderFlags & LAST_TIMESTAMP_VALID){
		lastTicksPerDegree = thisTicksPerDegree;
		decoderFlags |= LAST_PERIOD_VALID;
	}
	// Always
	lastEventTimeStamp = thisEventTimeStamp;
	decoderFlags |= LAST_TIMESTAMP_VALID;
	// TODO DEBUG/TUNING MACRO HERE!
}


void SecondaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;
}
