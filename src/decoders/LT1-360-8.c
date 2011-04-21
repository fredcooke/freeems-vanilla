/* FreeEMS - the open source engine management system
 *
 * Copyright 2009, 2010, 2011 Sean Keys, Fred Cooke
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


/**	@file LT1-360-8.c
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
 * @todo TODO This file contains SFA but Sean Keys is going to fill it up with
 * @todo TODO wonderful goodness very soon ;-)
 *
 * @author Sean Keys
 */
#define DECODER_IMPLEMENTATION_C
#define LT1_360_8_C

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/LT1-360-8.h"
#include "../inc/decoderInterface.h"
#include "../inc/utils.h"

const unsigned char decoderName[] = "LT1-360-8";
const unsigned short eventAngles[] = {(  0 * oneDegree), ( 86 * oneDegree), (130 * oneDegree), (176 * oneDegree),
                                      (180 * oneDegree), (266 * oneDegree), (280 * oneDegree), (356 * oneDegree),
                                      (360 * oneDegree), (446 * oneDegree), (470 * oneDegree), (536 * oneDegree),
                                      (540 * oneDegree), (626 * oneDegree), (660 * oneDegree), (716 * oneDegree)};
const unsigned char eventValidForCrankSync[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // This is wrong, but will never be used on this decoder anyway.
const unsigned char windowCounts[] = {4,86,44,46,4,86,14,76,4,86,24,66,4,86,34,56};
unsigned char lastAccumulatorCount = 0xFF; /* set to bogus number */
unsigned char lastPARegisterReading = 0xFF;
unsigned char windowState = 0x00;
unsigned char lastNumberOfRealEvents = 0x00;
unsigned char accumulatorRegisterCount = 0x00;
signed char bastardTeeth = 0x00;


/** Setup PT Capturing so that we can decode the LT1 pattern
 *  @todo TODO Put this in the correct place
 *
 */
void decoderInitPreliminary(void){
	/* set pt1 to capture on rising and falling */

	// set PACMX to 0 which is the default so there should be no need
	// set to capture on rising and falling this way if we have an odd number in the PA we know something went wrong
	// disable interrupt on PT1
	ICPAR = 0x02; // set the second bit in ICPAR (PAC1) to enable PT1's pulse accumulator
	// enable interrupt on overflow and set count to 0xFF-245 to enable an int on every ten teeth
	PACN1 = 0x00; // reset our count register
	TCTL4 = 0xFF; /* Capture on both edges of pin 0 and only on the falling edges of pin 1, capture off for 2,3 */ // FRED why interrupt on the other one at all, there is no code and you're *causing* jitter in your primary rpm by doing this, along with eating CPU up.
	//TIE = 0x01; // FRED necessary to do this too? I think so, but check the docs.
}


/**
 * @brief Interrupt on rising and falling edges to count the number of teeth that have passed
 * in that window. 4 of the windows on the 8 tooth channel have a unique width. The pulse
 * accumulator will hold that count so there is no need to interrupt on the 360 tooth channel.
 *
 * @notes Primary LT1 Optispark Interrupt wired to the 8x channel.
 * @todo TODO Docs here!
 * @todo TODO config pulse accumulator to fire its own RPM interrupt to give the wheel more
 * resoloution. Such as fire on every 10x.
 */
void PrimaryRPMISR(void){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;
	// Grab this first as it is the most critical var in this decoder
	accumulatorRegisterCount = PACN1;/* save count before it changes */

	/* Save all relevant available data here */
	unsigned char PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */
	unsigned short codeStartTimeStamp = TCNT; /* Save the current timer count */
	unsigned short edgeTimeStamp = TC0; /* Save the edge time stamp */
	windowState = PTITCurrentState & 0x01; /* Save the high/low state of the port, HIGH PRIORITY some windows are only 2deg wide */
	ISRLatencyVars.primaryInputLatency = codeStartTimeStamp - edgeTimeStamp; /* Calculate the latency in ticks */
	unsigned char accumulatorCount = accumulatorRegisterCount - lastPARegisterReading;/* save count before it changes */
	lastPARegisterReading = accumulatorRegisterCount;
	unsigned char i; /* temp loop var */

	Counters.primaryTeethSeen++;
	Counters.secondaryTeethSeen += accumulatorCount;
	Counters.testCounter5 = accumulatorCount; /// @todo TODO remove DEBUG

	/* always make sure you have two good counts(there are a few windows that share counts) */
	if(!(decoderFlags & CAM_SYNC)){
		// FRED do this on a per edge basis to lower chances of false match with +/- 1 counts
		if(accumulatorCount == AMBIGUOUS_COUNT){
			return;
		}else{
			unsigned char lastEvent = 0xFF;
			for(i = 0; numberOfRealEvents > i; i++){
				if(windowCounts[i] == accumulatorCount){
					if(i == 0){ /* keep our counter from going out of range */
						currentEvent = 0xFF; // Will be rolled over to 0
						lastEvent = NUMBER_OF_REAL_EVENTS - 1;
					}else{
						lastEvent = i - 1;
						currentEvent = lastEvent; // Will be rolled up to current
					}
					PORTB |= 0x01; /// @todo TODO remove DEBUG found count
					break;
				}
			}

			if(lastEvent == 0xFF){ // Indicates that we didn't find a match, previously uncaught, would have occasionally matched last event with i = max and no match found on THIS event
				return;
			}else if(windowCounts[lastEvent] == lastAccumulatorCount){ /* if true we are in sync! */
				decoderFlags |= CAM_SYNC;
				PORTB = 0x0F; /* light the board DEBUG */
			}else{
				/// @todo TODO missedsync opportunity ++ or something
			}

			lastAccumulatorCount = accumulatorCount;

			/// @todo TODO put fuzzy initial sync in place, maybe.
			//		// If still not synced, try to do fuzzy sync
			//		if(!(decoderFlags & CAM_SYNC)){
			//			// loop with +1 and -1
			//			// count fuzzy syncs, if genuine, should only be one + and one -
			//			// if not, give up and clear all state
			//		}
			//		return; /// @todo TODO remove and continue on down the thread
		}
	}

	unsigned char numberScheduled = 0; /// @todo TODO remove DEBUG
	if(decoderFlags & CAM_SYNC){
		currentEvent++;
		if(currentEvent == numberOfRealEvents){ /* roll our event over if we are at the end */
			currentEvent = 0;
		}

		/*
		 * bastardTeeth will be zero if things are going well, and a low number
		 * if there is some latency, and a large number if totally wrong. This
		 * will not catch sequences of same direction errors, though. We need
		 * to keep a running track of past bastardTeeth too. TODO
		 */
		bastardTeeth += accumulatorCount - windowCounts[currentEvent];

		Counters.testCounter4 = bastardTeeth; /// @todo TODO remove DEBUG
		Counters.testCounter6 = windowCounts[currentEvent]; /// @todo TODO remove DEBUG

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

		if((bastardTeeth > 2) || (bastardTeeth < -2)){
			resetToNonRunningState(BASTARD_BASE + bastardTeeth);
			PORTB = 0xFF; /// @todo TODO remove DEBUG
			return;
		}else{
			/* TODO all required calcs etc as shown in other working decoders */
			if((currentEvent % 2) == 1){ /* if we captured on a rising edge that is to say an evenly spaced edge perform the cacls */
				// temporary data from inputs
				unsigned long primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
				unsigned long timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp - lastPrimaryEventTimeStamp;
				lastPrimaryEventTimeStamp = primaryLeadingEdgeTimeStamp;

				/* RPM CALC, KISS for now and only run this part of the ISR when the edge has gone high
				 * this way we have evenly spaced teeth
				 */
				*ticksPerDegreeRecord = (unsigned short) (timeBetweenSuccessivePrimaryPulses / 16 ); /* 8 * 2 for crankshaft RPM */

				// TODO Once sampling/RPM is configurable, use this tooth for a lower MAP reading.
				sampleEachADC(ADCArrays);
				Counters.syncedADCreadings++;
				*mathSampleTimeStampRecord = TCNT;
				/* Set flag to say calc required */
				coreStatusA |= CALC_FUEL_IGN;
				/* Reset the clock for reading timeout */
				Clocks.timeoutADCreadingClock = 0;
				RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
				PORTB = 0x00; /// @todo TODO remove DEBUG
			}
		}

		RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
		/// @todo TODO behave differently depending upon sync level? Genericise this loop/logic? YES, move this to macro/function and call from all decoders.
		unsigned char outputEventNumber;
		for(outputEventNumber=0;outputEventNumber<MAX_NUMBER_OF_OUTPUT_EVENTS;outputEventNumber++){
			if(outputEventInputEventNumbers[outputEventNumber] == currentEvent){
				skipEventFlags &= ~(1UL << outputEventNumber);
				schedulePortTPin(outputEventNumber, timeStamp);
				numberScheduled++;
			}else if(skipEventFlags & (1UL << outputEventNumber)){
				unsigned char eventBeforeCurrent = 0;
				if(currentEvent == 0){
					eventBeforeCurrent = numberOfRealEvents - 1;
				}else{
					eventBeforeCurrent = currentEvent - 1;
				}

				if(outputEventInputEventNumbers[outputEventNumber] == eventBeforeCurrent){
					schedulePortTPin(outputEventNumber, timeStamp);
					numberScheduled++;
				}
			}
		}
	}
	RuntimeVars.secondaryInputTrailingRuntime = numberScheduled;
	RuntimeVars.primaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
}


/** Secondary RPM ISR
 *
 * @brief Update the scheduler every time 5 teeth are counted by the pulse accumulator
 *
 * @todo TODO Change the accumulator mode to overflow every 5 inputs on PT0 making our 360 tooth wheel interrupt like a 72 tooth wheel
 * @todo TODO Decide if an explicit parameter is necessary if not use a existing status var instead for now it's explicit.
 */
void SecondaryRPMISR(void){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;
}
