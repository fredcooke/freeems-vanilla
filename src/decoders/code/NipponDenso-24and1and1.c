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


/**	@file NipponDenso-24and1and1.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Reads Nippon Denso 24/2 sensors
 *
 * This file contains the two interrupt service routines for handling engine
 * position and RPM signals from mainly Toyota engines using this sensor style.
 *
 * One ISR handles the 24 evenly spaced teeth and the other handles the two
 * adjacent teeth. This signal style provides enough information for wasted
 * spark ignition and semi sequential fuel injection.
 *
 * Supported engines include:
 * - 4A-GE
 * - 7A-FE
 * - 3S-GE
 * - 1UZ-FE
 * - Mazda F2T
 *
 * @author Fred Cooke
 *
 * @note Pseudo code that does not compile with zero warnings and errors MUST be commented out.
 *
 * @todo TODO make this generic for evenly spaced teeth with a pulse per revolution from the second input.
 */


#define DECODER_IMPLEMENTATION_C
#define DECODER_MAX_CODE_TIME    100 // To be optimised (shortened)!
#define NUMBER_OF_REAL_EVENTS     24
#define NUMBER_OF_VIRTUAL_EVENTS  24

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "inc/NipponDenso-24and1and1.h"
#include "../inc/decoderInterface.h"
#include "../inc/utils.h"


const unsigned char decoderName[] = "NipponDenso-24and1and1";
const unsigned short eventAngles[] = {0, 30, 60, 90, 120, 150, 180, 210, 240, 270, 300, 330, 360, 390, 420, 450, 480, 510, 540, 570, 600, 630, 660, 690};
//const unsigned char eventValidForCrankSync[] = {?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?}; // Needs some thought.


void PrimaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	unsigned short edgeTimeStamp = TC0;				/* Save the edge time stamp */
	unsigned char PTITCurrentState = PTIT;			/* Save the values on port T regardless of the state of DDRT */

	/* Calculate the latency in ticks */
	ISRLatencyVars.primaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	/* TODO discard narrow ones! test for tooth width and tooth period
	 * the width should be based on how the hardware is setup. IE the LM1815
	 * is adjusted to have a pulse output of a particular width. This noise
	 * filter should be matched to that width as should the hardware filter.
	 */

	/* The LM1815 variable reluctance sensor amplifier allows the output to be
	 * pulled high starting at the center of a tooth. So, what we see as the
	 * start of a tooth is actually the centre of a physical tooth. Because
	 * tooth shape, profile and spacing may vary this is the only reliable edge
	 * for us to schedule from, hence the trailing edge code is very simple.
	 */
	if(PTITCurrentState & 0x01){
		// increment crank pulses TODO this needs to be wrapped in tooth period and width checking
		primaryPulsesPerSecondaryPulse++;

		// calculate rough rpm (this will be wrong when the var is used correctly) THIS is horrible now... fix up with rest of decoder.
		*ticksPerDegreeRecord = engineCyclePeriod / 720; /* 0.8us ticks, 150mil = 2 x 60 seconds, times rpm scale factor of 2 */

		// don't run until the second trigger has come in and the period is correct (VERY temporary)
		if(!(decoderFlags & CRANK_SYNC)){
			primaryTeethDroppedFromLackOfSync++;
			return;
		}

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
//		unsigned long primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
//		unsigned long timeBetweenSuccessivePrimaryPulses = lastPrimaryPulseTimeStamp - primaryLeadingEdgeTimeStamp;
//		lastPrimaryPulseTimeStamp = primaryLeadingEdgeTimeStamp;
//		timeBetweenSuccessivePrimaryPulsesBuffer = (timeBetweenSuccessivePrimaryPulses >> 1) + (timeBetweenSuccessivePrimaryPulsesBuffer >> 1);

		// TODO make scheduling either fixed from boot with a limited range, OR preferably if its practical scheduled on the fly to allow arbitrary advance and retard of both fuel and ignition.

		/* Check for loss of sync by too high a count */
		if(primaryPulsesPerSecondaryPulse > 12){
			/* Increment the lost sync count */
			Counters.crankSyncLosses++;

			/* Clear synced status */
			decoderFlags &= CLEAR_CRANK_SYNC;

			/* Reset the count of teeth */
			primaryPulsesPerSecondaryPulse = 0;

			/* Get the hell out of here before we do something bad */
			return;
		}

		// CAUTION came to me lying in bed half asleep idea :

		// TODO move tooth selection to the calc loop in main such that this routine just iterates through an array of events and schedules those that are destined for this tooth.

		// if ign enabled
			// iterate through ignition first, schedule all of those
			// iterate through dwell next, schedule all of those
		// if fuel enabled
			// iterate through main fuel next, schedule all of those
			// if staging enabled and required
				// iterate through staged fuel last,

		// TODO should make for a clean compact scheduling implementation. the fuel code doesn't care when/how it has started in the past, and hopefully ign will be the same.

		// this will be done with an array and per tooth check in future
		if((primaryPulsesPerSecondaryPulse % 2) == 0){

			// TODO sample ADCs on teeth other than that used by the scheduler in order to minimise peak run time and get clean signals
			sampleEachADC(ADCArrays);
			Counters.syncedADCreadings++;
			*mathSampleTimeStampRecord = TCNT;

			/* Set flag to say calc required */
			coreStatusA |= CALC_FUEL_IGN;

			/* Reset the clock for reading timeout */
			Clocks.timeoutADCreadingClock = 0;
		}

		SCHEDULE_ECT_OUTPUTS();

		RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	}else{
		RuntimeVars.primaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
	}

	Counters.primaryTeethSeen++;
	// suss out rpm and accurate TDC reference
}


void SecondaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	unsigned short edgeTimeStamp = TC1;				/* Save the timestamp */
	unsigned char PTITCurrentState = PTIT;			/* Save the values on port T regardless of the state of DDRT */

	/* Calculate the latency in ticks */
	ISRLatencyVars.secondaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	/* TODO discard narrow ones! test for tooth width and tooth period
	 * the width should be based on how the hardware is setup. IE the LM1815
	 * is adjusted to have a pulse output of a particular width. This noise
	 * filter should be matched to that width as should the hardware filter.
	 */

	/* The LM1815 variable reluctance sensor amplifier allows the output to be
	 * pulled high starting at the center of a tooth. So, what we see as the
	 * start of a tooth is actually the centre of a physical tooth. Because
	 * tooth shape, profile and spacing may vary this is the only reliable edge
	 * for us to schedule from, hence the trailing edge code is very simple.
	 */
	if(PTITCurrentState & 0x02){
// was this code like this because of a good reason?
//		primaryPulsesPerSecondaryPulseBuffer = primaryPulsesPerSecondaryPulse;
		primaryPulsesPerSecondaryPulse = 0;

		// if we didn't get the right number of pulses drop sync and start over
		if((primaryPulsesPerSecondaryPulse != 12) && (decoderFlags & CRANK_SYNC)){
			decoderFlags &= CLEAR_CRANK_SYNC;
			Counters.crankSyncLosses++;
		}

		LongTime timeStamp;

		/* Install the low word */
		timeStamp.timeShorts[1] = edgeTimeStamp;
		/* Find out what our timer value means and put it in the high word */
		if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
			timeStamp.timeShorts[0] = timerExtensionClock + 1;
		}else{
			timeStamp.timeShorts[0] = timerExtensionClock;
		}

		// get the data we actually want
		engineCyclePeriod = 2 * (timeStamp.timeLong - lastSecondaryOddTimeStamp); // save the engine cycle period
		lastSecondaryOddTimeStamp = timeStamp.timeLong; // save this stamp for next time round

		// Because this is our only reference, each time we get this pulse, we know where we are at (simple mode so far)
		decoderFlags |= CRANK_SYNC;
		RuntimeVars.secondaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	}else{
		RuntimeVars.secondaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
	}

	Counters.secondaryTeethSeen++;
	// suss out phase/engine cycle reference showing which bank we are on

	/* If the flag is not cleared at the beginning then the interrupt gets rescheduled while it is running, hence it can't be done at the end of the ISR */
}
