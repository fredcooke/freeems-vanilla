/* FreeEMS - the open source engine management system
 *
 * Copyright 2009-2012 Sean Keys, Fred Cooke
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


/** @file
 *
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief LT1 Optispark
 *
 * Uses PT1 to interrupt on rising and falling events of the 8x cam sensor track.
 * A certain number of 360x teeth will pass while PT1 is in a high or low state.
 * Using that uniquek count we can set the positing of your Virtual CAS clock.
 * After VCAS's position is set set PT7 to only interrupt on every 5th tooth, lowering
 * the amount of interrupts generated, to a reasonable level.
 *
 * @note Pseudo code that does not compile with zero warnings and errors MUST be commented out.
 *
 * @todo TODO config pulse accumulator to fire its own RPM interrupt to give the wheel more
 * resoloution. Such as fire on every 10x.
 *
 * @author Sean Keys
 */
#define DECODER_IMPLEMENTATION_C
#define LT1_360_8_C

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "inc/GM-LT1-CAS-360and8.h"
#include "../inc/decoderInterface.h"
#include "../inc/utils.h"

const unsigned short eventAngles[] = {ANGLE(  0), ANGLE( 86), ANGLE(130), ANGLE(176),
                                      ANGLE(180), ANGLE(266), ANGLE(280), ANGLE(356),
                                      ANGLE(360), ANGLE(446), ANGLE(470), ANGLE(536),
                                      ANGLE(540), ANGLE(626), ANGLE(660), ANGLE(716)};
const unsigned char eventValidForCrankSync[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // This is wrong, but will never be used on this decoder anyway.
const unsigned char windowCounts[] = {4,86,44,46,4,86,14,76,4,86,24,66,4,86,34,56};
unsigned char lastAccumulatorCount = 0xFF; /* set to bogus number */
unsigned char lastPARegisterReading = 0xFF;
unsigned char windowState = 0;
unsigned char lastNumberOfRealEvents = 0;
unsigned char accumulatorRegisterCount = 0;
signed char cumulativeBastardTeeth = 0;


// Rolling tolerance to cumulative noise issues feature.
//
// This rolling tolerance for cumulative bastard teeth count is available to
// allow users to tune the system such that mild noise on the fine pitch input
// doesn't cause loss of sync over a period of seconds, minutes or hours. This
// feature should be tuned to the most conservative level possible and actually
// used to improve the quality of the wiring, not to mask bad noise issues.
// Default will always be off, hard coded on for now with only one user, Sean.
// ----------------------------------------------------------------------------
// 0 is disabled, this is the default such that you find out that your system is noisy quickly
// 1 means you can have one extra/missing tooth per window continuously without loss of sync
// 2 means you can have one extra/missing tooth per 2 windows continuously without loss of sync etc
// 65535 is max and the most conservative possible with this feature enabled.
#define windowsPerAllowedCumulativeBastardTooth 8
// TODO future enhancement allow fractional stuff by having N extra/missing per M windows
unsigned short cumulativeBastardTeethEroderCounter = 0;


// Setup PT Capturing so that we can decode the LT1 pattern
void decoderInitPreliminary(void){
	/* set pt1 to capture on rising and falling */

	// set PACMX to 0 which is the default so there should be no need
	// set to capture on rising and falling this way if we have an odd number in the PA we know something went wrong
	// disable interrupt on PT1
	ICPAR = 0x02; // set the second bit in ICPAR (PAC1) to enable PT1's pulse accumulator
	// enable interrupt on overflow and set count to 0xFF-245 to enable an interrupt on every ten teeth
	PACN1 = 0x00; // reset our count register
	TCTL4 = 0xFF; /* Capture on both edges of pin 0 and only on the falling edges of pin 1, capture off for 2,3 */ // FRED why interrupt on the other one at all, there is no code and you're *causing* jitter in your primary rpm by doing this, along with eating CPU up.
	//TIE = 0x01; // FRED necessary to do this too? I think so, but check the docs.
}


void perDecoderReset(){
	cumulativeBastardTeeth = 0;
	cumulativeBastardTeethEroderCounter = 0;
}


/* Interrupt on rising and falling edges to count the number of teeth that have passed
 * in that window. 4 of the windows on the 8 tooth channel have a unique width. The pulse
 * accumulator will hold that count so there is no need to interrupt on the 360 tooth channel.
 *
 * Note: Primary LT1 Optispark Interrupt wired to the 8x channel.
 */
void PrimaryRPMISR(void){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;
	// Grab this first as it is the most critical var in this decoder
	accumulatorRegisterCount = PACN1;/* save count before it changes */
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT0, PORTB);

	/* Save all relevant available data here */
	unsigned char PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */
	unsigned short edgeTimeStamp = TC0; /* Save the edge time stamp */

	windowState = PTITCurrentState & 0x01; /* Save the high/low state of the port, HIGH PRIORITY some windows are only 2deg wide */
	unsigned char accumulatorCount = accumulatorRegisterCount - lastPARegisterReading;/* save count before it changes */
	lastPARegisterReading = accumulatorRegisterCount;
	unsigned char i; /* temp loop var */

	KeyUserDebugs.primaryTeethSeen++;
	KeyUserDebugs.secondaryTeethSeen += accumulatorCount;
//	DEBUG = accumulatorCount; // TODO remove DEBUG

	/* always make sure you have two good counts(there are a few windows that share counts) */
	if(!(KeyUserDebugs.decoderFlags & CAM_SYNC)){
		// FRED do this on a per edge basis to lower chances of false match with +/- 1 counts
		if(accumulatorCount == AMBIGUOUS_COUNT){
			return;
		}else{
			unsigned char lastEvent = 0xFF;
			for(i = 0; numberOfRealEvents > i; i++){
				if(windowCounts[i] == accumulatorCount){
					if(i == 0){ /* keep our counter from going out of range */
						KeyUserDebugs.currentEvent = 0xFF; // Will be rolled over to 0
						lastEvent = NUMBER_OF_REAL_EVENTS - 1;
					}else{
						lastEvent = i - 1;
						KeyUserDebugs.currentEvent = lastEvent; // Will be rolled up to current
					}
					break;
				}
			}

			if(lastEvent == 0xFF){ // Indicates that we didn't find a match, previously uncaught, would have occasionally matched last event with i = max and no match found on THIS event
				return;
			}else if(windowCounts[lastEvent] == lastAccumulatorCount){ /* if true we are in sync! */
				SET_SYNC_LEVEL_TO(CAM_SYNC);
			}else{
				// TODO missedsync opportunity ++ or something
			}

			lastAccumulatorCount = accumulatorCount;

			// TODO put fuzzy initial sync in place, maybe.
			//		// If still not synced, try to do fuzzy sync
			//		if(!(decoderFlags & CAM_SYNC)){
			//			// loop with +1 and -1
			//			// count fuzzy syncs, if genuine, should only be one + and one -
			//			// if not, give up and clear all state
			//		}
			//		return; // TODO remove and continue on down the thread
		}
	}

	if(KeyUserDebugs.decoderFlags & CAM_SYNC){
		KeyUserDebugs.currentEvent++;
		if(KeyUserDebugs.currentEvent == numberOfRealEvents){ /* roll our event over if we are at the end */
			KeyUserDebugs.currentEvent = 0;
		}

		/*
		 * bastardTeeth will be zero if things are going well, and a low number
		 * if there is some latency, and a large number if totally wrong. This
		 * will not catch sequences of same direction errors, though. We need
		 * to keep a running track of past bastardTeeth too. TODO
		 */

		signed char bastardTeeth = accumulatorCount - windowCounts[KeyUserDebugs.currentEvent];
		cumulativeBastardTeeth += bastardTeeth;

//		DEBUG = cumulativeBastardTeeth; // TODO remove DEBUG
//		DEBUG = bastardTeeth;
//		DEBUG = windowCounts[currentEvent]; // TODO remove DEBUG

		// Cumulative Tolerance Code TODO add counters to monitor aggressiveness of this
		if(windowsPerAllowedCumulativeBastardTooth){
			cumulativeBastardTeethEroderCounter++;
			if(cumulativeBastardTeethEroderCounter == windowsPerAllowedCumulativeBastardTooth){
				cumulativeBastardTeethEroderCounter = 0;
				if(cumulativeBastardTeeth > 0){
					cumulativeBastardTeeth--;
					// DEBUG++;
					// counter for decrement
				}else if(cumulativeBastardTeeth < 0){
					cumulativeBastardTeeth++;
					// counter for increment
				}else{
					// counter for does nothing
				}
			}
		}

		/* if we are in-sync continue checking and perform required decoder calcs */
		LongTime timeStamp;

		/* Install the low word */
		timeStamp.timeShorts[1] = edgeTimeStamp;
		/* Find out what our timer value means and put it in the high word */
		if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
			timeStamp.timeShorts[0] = timerExtensionClock + 1;
		}else{
			timeStamp.timeShorts[0] = timerExtensionClock;
		}

		if((bastardTeeth > MAX_BASTARD_TEETH) || (bastardTeeth < -MAX_BASTARD_TEETH)){
			resetToNonRunningState(BASTARD_SYNC_LOSS_ID_BASE + bastardTeeth); // TODO move this to the syncLossIDs.h header
			return;
		}else if((cumulativeBastardTeeth > MAX_CUMULATIVE_BASTARD_TEETH) || (cumulativeBastardTeeth < -MAX_CUMULATIVE_BASTARD_TEETH)){
			resetToNonRunningState(BASTARD_CUMULATIVE_SYNC_LOSS_ID_BASE + cumulativeBastardTeeth); // TODO move this to the syncLossIDs.h header
			return;
		}else{
			/* TODO all required calcs etc as shown in other working decoders */
			if((KeyUserDebugs.currentEvent % 2) == 1){ /* if we captured on a rising edge that is to say an evenly spaced edge perform the cacls */
				// temporary data from inputs
				unsigned long primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
				unsigned long timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp - lastPrimaryEventTimeStamp;
				lastPrimaryEventTimeStamp = primaryLeadingEdgeTimeStamp;

				/* RPM CALC, KISS for now and only run this part of the ISR when the edge has gone high
				 * this way we have evenly spaced teeth
				 */
				*ticksPerDegreeRecord = (unsigned short)((ticks_per_degree_multiplier * timeBetweenSuccessivePrimaryPulses) / (90 * ANGLE_FACTOR));
				// instead of above:
				// save time difference
				// have angle of time difference as setting
				// do whole rpm calc in main loop to save ISR time, make more sense, and be more coherent to read
				// then it's possible to use different tpdm figures for different RPM levels, thereby allowing a large range AND fine granularity!
				// tpd would still need to be calculated for scheduling reasons, and the different scalings would need to be checked for overflow there.

				// TODO Once sampling/RPM is configurable, use this tooth for a lower MAP reading.
				sampleEachADC(ADCBuffers);
				Counters.syncedADCreadings++;
				/* Set flag to say calc required */
				coreStatusA |= CALC_FUEL_IGN;
				/* Reset the clock for reading timeout */
				Clocks.timeoutADCreadingClock = 0;
			}
		}
		SCHEDULE_ECT_OUTPUTS();
	}

	OUTPUT_COARSE_BBS();

	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT0, PORTB);
}


#include "inc/defaultSecondaryRPMISR.c"
