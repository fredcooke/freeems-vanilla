/* FreeEMS - the open source engine management system
 *
 * Copyright 2013-2014 Fred Cooke
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
 * Decoder for the Honda R18A1 I4 engine.
 *
 * http://pastebin.com/QMdhE55v
 */


#define DECODER_MAX_CODE_TIME    150
#define NUMBER_OF_REAL_EVENTS     26 // 12+1 Mostly Even Crank teeth, twice
#define NUMBER_OF_VIRTUAL_EVENTS  26 // Ditto.
#define DECODER_IMPLEMENTATION_C

#include "../inc/freeEMS.h"
#include "../inc/utils.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"

unsigned char camTeethSeen = 0;
unsigned char previousCrankTeethSeen = 0;
unsigned char crankTeethSinceLastCamTooth = 0;

#define FIRST_GAP ANGLE(10) // With the 20 degree balance of the 30 degree segment following

#define  E0 ANGLE(  0)
#define  E1 ANGLE( 30)
#define  E2 ANGLE( 60)
#define  E3 ANGLE( 90)
#define  E4 ANGLE(120)
#define  E5 ANGLE(150)
#define  E6 ANGLE(180)
#define  E7 ANGLE(210)
#define  E8 ANGLE(240)
#define  E9 ANGLE(270)
#define E10 ANGLE(300)
#define E11 ANGLE(330)
#define E12 (E11 + FIRST_GAP)
#define E13 ANGLE(360)
#define E14 ANGLE(390)
#define E15 ANGLE(420)
#define E16 ANGLE(450)
#define E17 ANGLE(480)
#define E18 ANGLE(510)
#define E19 ANGLE(540)
#define E20 ANGLE(570)
#define E21 ANGLE(600)
#define E22 ANGLE(630)
#define E23 ANGLE(660)
#define E24 ANGLE(690)
#define E25 (E24 + FIRST_GAP)

// 3  >> 16
// 10 >> 23
// Note, if used in 360 degree crank only mode, the upper 13 values are simply ignored.

CASSERT(E12 > E11, MID_ANGLE_LOWER)
CASSERT(E12 < E13, MID_ANGLE_UPPER)
CASSERT(E25 > E24, FINAL_ANGLE_LOWER)
CASSERT(E25 < ANGLE(720), FINAL_ANGLE_UPPER)

const unsigned short eventAngles[] = {E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11, E12, E13, E14, E15, E16, E17, E18, E19, E20, E21, E22, E23, E24, E25};
const unsigned char eventValidForCrankSync[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};

void decoderInitPreliminary(){
	// Set PT0 and PT1 to only capture on rising edges
	TCTL4 = 0x05;
}

void perDecoderReset(){
	camTeethSeen = 0;
	previousCrankTeethSeen = 0;
	crankTeethSinceLastCamTooth = 0;

	// Re-enable secondary interrupt so we can sync again!
	TCTL4 |= BIT2;
}

// Just count and check time stamps, sync is handled by the secondary ISR
void PrimaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT0, PORTB);

	/* Save all relevant available data here */
	unsigned short edgeTimeStamp = TC0;     /* Save the edge time stamp */
	unsigned char PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */

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
	unsigned long thisEventTimeStamp = timeStamp.timeLong;

	unsigned long thisInterEventPeriod = 0;
	if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
		thisInterEventPeriod = thisEventTimeStamp - lastPrimaryEventTimeStamp;
		KeyUserDebugs.zsp7 = (unsigned short)thisInterEventPeriod; // Could truncate if under ~100rpm TODO DEBUG REMOVE
	}

	unsigned short thisTicksPerDegree = 0;
	if(KeyUserDebugs.decoderFlags & CAM_SYNC){

		unsigned char lastEvent = KeyUserDebugs.currentEvent;
		KeyUserDebugs.currentEvent++;
		if(KeyUserDebugs.currentEvent == numberOfRealEvents){
			KeyUserDebugs.currentEvent = 0;
		}

		unsigned short thisAngle = 0;
		if(KeyUserDebugs.currentEvent == 0){
			thisAngle = eventAngles[KeyUserDebugs.currentEvent] + totalEventAngleRange - eventAngles[lastEvent] ; // Optimisable... leave readable for now! :-p J/K learn from this...
		}else{
			thisAngle = eventAngles[KeyUserDebugs.currentEvent] - eventAngles[lastEvent];
		}

		thisTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * thisInterEventPeriod) / thisAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error

		if(KeyUserDebugs.decoderFlags & LAST_PERIOD_VALID){
			unsigned short ratioBetweenThisAndLast = (unsigned short)(((unsigned long)lastPrimaryTicksPerDegree * 1000) / thisTicksPerDegree);
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
		}

		if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){
			lastPrimaryTicksPerDegree = thisTicksPerDegree;
			KeyUserDebugs.decoderFlags |= LAST_PERIOD_VALID;
		}

		/*else*/ if(KeyUserDebugs.decoderFlags & LAST_TIMESTAMP_VALID){ // TODO temp for testing just do rpm this way, fill above out later.
			*ticksPerDegreeRecord = thisTicksPerDegree;
			sampleEachADC(ADCBuffers);
			Counters.syncedADCreadings++;

			// Set flag to say calc required
			coreStatusA |= CALC_FUEL_IGN;

			// Reset the clock for reading timeout
			Clocks.timeoutADCreadingClock = 0;
		}

		SCHEDULE_ECT_OUTPUTS();

		OUTPUT_COARSE_BBS();
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
	KeyUserDebugs.secondaryTeethSeen++;
	if(camTeethSeen == 0){
		camTeethSeen = 1;
		previousCrankTeethSeen = KeyUserDebugs.primaryTeethSeen;
	}else{
		crankTeethSinceLastCamTooth = KeyUserDebugs.primaryTeethSeen - previousCrankTeethSeen;
		previousCrankTeethSeen =  KeyUserDebugs.primaryTeethSeen;

		if(crankTeethSinceLastCamTooth == 7){
			KeyUserDebugs.currentEvent = 16;
			SET_SYNC_LEVEL_TO(CAM_SYNC);
		}else if(crankTeethSinceLastCamTooth == 1){
			KeyUserDebugs.currentEvent = 23;
			SET_SYNC_LEVEL_TO(CAM_SYNC);
		}else if(crankTeethSinceLastCamTooth != 6){
			if(crankTeethSinceLastCamTooth > 7){
				resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_HIGH_NOISE);
			}else if(crankTeethSinceLastCamTooth < 6){
				resetToNonRunningState(COUNT_OF_EVENTS_IMPOSSIBLY_LOW_NOISE);
			}else if(!crankTeethSinceLastCamTooth){ // Should never be zero :-p
				resetToNonRunningState(STATE_MISMATCH_IN_SECONDARY_RPM_ISR);
			}else{
				resetToNonRunningState(BUG_REACHED_UNREACHABLE_CODE);
			}
			return;
		} // else is 6, just ignore.

		// Disable the interrupt for this ISR
		if(KeyUserDebugs.decoderFlags & OK_TO_SCHEDULE){
			TCTL4 &= NBIT2;
		}
	}

	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT0, PORTB);
}
