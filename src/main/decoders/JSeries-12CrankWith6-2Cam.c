/* FreeEMS - the open source engine management system
 *
 * Copyright 2012 Fred Cooke
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
 * Decoder for the Honda J Series V6 engine, using one cam wheel and the crank wheel.
 *
 * @author Peter Johnson
 */


#define DECODER_MAX_CODE_TIME    300 // To be optimised (shortened)!
#define NUMBER_OF_REAL_EVENTS     24 // 12 Even Crank teeth
#define NUMBER_OF_VIRTUAL_EVENTS  24 // 24 Crank teeth in 720degrees
#define DECODER_IMPLEMENTATION_C

#include "../inc/freeEMS.h"
#include "../inc/utils.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"

unsigned char camTeethSeen = 0;
unsigned char previousCrankTeethSeen = 0;
unsigned char crankTeethSinceLastCamTooth = 0;
unsigned char PTITCurrentState;
unsigned char secondaryPTITCurrentState;
unsigned long thisEventTimeStamp;
unsigned short edgeTimeStamp;
unsigned long thisInterEventPeriod;
unsigned short thisTicksPerDegree;
unsigned short ratioBetweenThisAndLast;

const unsigned short eventAngles[] = {ANGLE(  0), ANGLE( 30), ANGLE( 60), ANGLE( 90),
                                      ANGLE(120), ANGLE(150), ANGLE(180), ANGLE(210),
                                      ANGLE(240), ANGLE(270), ANGLE(300), ANGLE(330),
                                      ANGLE(360), ANGLE(390), ANGLE(420), ANGLE(450),
                                      ANGLE(480), ANGLE(510), ANGLE(540), ANGLE(570),
                                      ANGLE(600), ANGLE(630), ANGLE(660), ANGLE(690)};
const unsigned char eventValidForCrankSync[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void decoderInitPreliminary(){
	// Set PT0 and PT1 to only capture on rising edges
	TCTL4 = 0x05;
}

void perDecoderReset(){
	camTeethSeen = 0;
	previousCrankTeethSeen = 0;
	crankTeethSinceLastCamTooth = 0;
}

// Just count and check time stamps, sync is handled by the secondary ISR
void PrimaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT0, PORTB);

	/* Save all relevant available data here */
	edgeTimeStamp = TC0;     /* Save the edge time stamp */
	PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */

	// Prevent main from clearing values before sync is obtained!
	Clocks.timeoutADCreadingClock = 0;

	KeyUserDebugs.primaryTeethSeen++;

	LongTime timeStamp;
	/* Install the low word */
	timeStamp.timeShorts[1] = edgeTimeStamp;
	/* Find out what our timer value means and put it in the high word */
	if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
		timeStamp.timeShorts[0] = timerExtensionClock + 1;
	}else{
		timeStamp.timeShorts[0] = timerExtensionClock;
	}
	thisEventTimeStamp = timeStamp.timeLong;

	thisInterEventPeriod = 0;
	thisTicksPerDegree = 0;
	if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
		thisInterEventPeriod = thisEventTimeStamp - lastPrimaryEventTimeStamp;
		thisTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * thisInterEventPeriod) / eventAngles[1]);
	}

	if(KeyUserDebugs.decoderFlags & CAM_SYNC){
		if(KeyUserDebugs.currentEvent == 23){
			KeyUserDebugs.currentEvent = 0;
		}else{
			KeyUserDebugs.currentEvent++;
		}
		if(KeyUserDebugs.currentEvent == numberOfRealEvents){
			resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_HIGH_NOISE);
			return;
		}// Can never be greater than without a code error or genuine noise issue, so give it a miss as we can not guarantee where we are now.

		if(KeyUserDebugs.decoderFlags & LAST_PERIOD_VALID){
			ratioBetweenThisAndLast = (unsigned short)(((unsigned long)lastPrimaryTicksPerDegree * 1000) / thisTicksPerDegree);
			KeyUserDebugs.inputEventTimeTolerance = ratioBetweenThisAndLast;
			if(ratioBetweenThisAndLast > fixedConfigs2.decoderSettings.decelerationInputEventTimeTolerance){
				resetToNonRunningState(PRIMARY_EVENT_ARRIVED_TOO_LATE);
				return;
			}else if(ratioBetweenThisAndLast < fixedConfigs2.decoderSettings.accelerationInputEventTimeTolerance){
				resetToNonRunningState(PRIMARY_EVENT_ARRIVED_TOO_EARLY);
				return;
			}else{
				if(PTITCurrentState & 0x02){
					// TODO Calculate RPM from last primaryLeadingEdgeTimeStamp
				}else{
					// TODO Calculate RPM from last primaryTrailingEdgeTimeStamp
				}
			}
		}/*else*/ if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){ // TODO temp for testing just do rpm this way, fill above out later.
			*ticksPerDegreeRecord = thisTicksPerDegree;
			sampleEachADC(ADCBuffers);
			Counters.syncedADCreadings++;

			// Set flag to say calc required
			coreStatusA |= CALC_FUEL_IGN;

			// Reset the clock for reading timeout
			Clocks.timeoutADCreadingClock = 0;
		}

		SCHEDULE_ECT_OUTPUTS();
	}

	OUTPUT_COARSE_BBS();

	// do these always at first, and use them with a single 30 degree angle for the first cut
	if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
		lastPrimaryTicksPerDegree = thisTicksPerDegree;
		KeyUserDebugs.decoderFlags |= LAST_PERIOD_VALID;
	}
	// Always
	lastPrimaryEventTimeStamp = thisEventTimeStamp;
	KeyUserDebugs.decoderFlags |= LAST_TIMESTAMP_VALID;

	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT0, PORTB);
}

// CAM sensor doesn't use time stamps due to timing belt tension vibration, plus the crank has 6 times more events, so any discrepancy would be caught that way
void SecondaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT0, PORTB);
	secondaryPTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */
	KeyUserDebugs.secondaryTeethSeen++;
	if(KeyUserDebugs.decoderFlags & CAM_SYNC){
		// check crankTeethSinceLastCamTooth to see if it's 4 or 12 and if not either of those, lose sync.
		crankTeethSinceLastCamTooth =  KeyUserDebugs.primaryTeethSeen - previousCrankTeethSeen;
		previousCrankTeethSeen =  KeyUserDebugs.primaryTeethSeen;
		if(crankTeethSinceLastCamTooth != 4 && crankTeethSinceLastCamTooth != 12){
			if(crankTeethSinceLastCamTooth < 4){
				resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_LOW_NOISE);
			}else{
				resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_HIGH_NOISE);
			}
		}
	}else{
		if(camTeethSeen == 0){
			camTeethSeen = 1;
			previousCrankTeethSeen =  KeyUserDebugs.primaryTeethSeen;
		}else if(camTeethSeen == 1){
			camTeethSeen = 2;
			crankTeethSinceLastCamTooth =  KeyUserDebugs.primaryTeethSeen - previousCrankTeethSeen;
			previousCrankTeethSeen =  KeyUserDebugs.primaryTeethSeen;
			if(crankTeethSinceLastCamTooth == 12){ // 12 Crank teeth in the 2 missing Cam teeth
				SET_SYNC_LEVEL_TO(CAM_SYNC);
				KeyUserDebugs.currentEvent = 0;
			}else if(crankTeethSinceLastCamTooth != 4){ // 4 Crank teeth in 1 Cam tooth
				if(crankTeethSinceLastCamTooth > 4){
					resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_HIGH_NOISE);
				}else{
					resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_LOW_NOISE);
				}
			}
		}else if(camTeethSeen == 2){
			camTeethSeen = 3;
			crankTeethSinceLastCamTooth =  KeyUserDebugs.primaryTeethSeen - previousCrankTeethSeen;
			previousCrankTeethSeen =  KeyUserDebugs.primaryTeethSeen;
			if(crankTeethSinceLastCamTooth == 12){
				SET_SYNC_LEVEL_TO(CAM_SYNC);
				KeyUserDebugs.currentEvent = 0;
			}else if(crankTeethSinceLastCamTooth != 4){
				if(crankTeethSinceLastCamTooth > 4){
					resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_HIGH_NOISE);
				}else{
					resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_LOW_NOISE);
				}
			}
		}else if(camTeethSeen == 3){
			camTeethSeen = 4;
			crankTeethSinceLastCamTooth =   KeyUserDebugs.primaryTeethSeen - previousCrankTeethSeen;
			previousCrankTeethSeen =  KeyUserDebugs.primaryTeethSeen;
			if(crankTeethSinceLastCamTooth == 12){
				SET_SYNC_LEVEL_TO(CAM_SYNC);
				KeyUserDebugs.currentEvent = 0;
			}else if(crankTeethSinceLastCamTooth != 4){
				if(crankTeethSinceLastCamTooth > 4){
					resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_HIGH_NOISE);
				}else{
					resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_LOW_NOISE);
				}
			}else{
				SET_SYNC_LEVEL_TO(CAM_SYNC); // Set the sync on the eventAngle[12] 360 degrees
				KeyUserDebugs.currentEvent = 12;
			}
		}else{
			resetToNonRunningState(BUG_REACHED_UNREACHABLE_CODE);
		}
	}
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT0, PORTB);
}
