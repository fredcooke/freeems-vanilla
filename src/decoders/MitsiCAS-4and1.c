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


/**	@file MitsiCAS-4and1.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Reads Mitsi 4 and 1 CAS units
 *
 * Two interrupts share state and cross communicate to
 * find and maintain sync and position information.
 *

Outer           Inner
30 signal    295
60                65 signal
30 signal
60
30 signal
60
30 signal
60

Outer:
0
on
30
off
90
on
120
off
180
on
210
off
270
on
300
off
360/0

Inner:
0
off
295
on
360/0

Inner:
off
261
on
326
off

Crank (double all cam angles):

Outer:
0
on
60
off
180
on
240
off
360
on
420
off
540
on
600
off
720/0

Inner (disk):
0
off
590
on
720/0

Inner (actual):
off
522
on
652
off

figures for inner above are wrong due to offset LEDs in CAS body!!!! Find offset value and adjust these figures. Note this in docs re disk pattern and actual pattern.

34 cam degrees or slightly less (inner degrees earlier than on disk.

use #define and let the compiler take care of the math so that its easier to change.

Logic:

const unsigned short eventCrankAngles[] = {0, 60, 180, 240, 360, 420, 522, 540, 600, 652}
the above needs verify on init to ensure order is sequential!
unsigned char array pinEventNumbers[6] = {} // 6 pins, which even should they go on? 255/0xFF = not fired. populated by scheduler in main loop
^ only good enough in short term, in longer term, could expect same pin to fire on multiple events in a cycle...

event number, pin number

if(synced){

if inner fires, increment, then event should be  6th or 9th (zero index)
if outer fires, increment, then event should be 0th - 5th, 7th, 8th. If 9th make equal 0th, not 10th

only outer needs check for 9th > 0th, inner will catch based on not 6th/9th/rising/falling.

for either:

take last period, and last angle gap, calc ticks per degree or similar, generate limits, compare measured with limits, drop sync if wrong.

else if(not synced){ look for logic as per below:

ten transitional events total per engine cycle:

5 provide sync:

if inner = off to on, position = 522 degrees
if inner = on to off, position = 652 degrees
if outer = off to on AND inner = on, then position = 540
if outer = on to off AND inner = on, then position = 600
if outer = off to on AND is third while inner = off, then position = 360

information of no use for obtaining sync:

outer on to off and is third while inner = already synced by definition
other four outer events are not identifiable as anything specific and therefore cant sync

Loss of sync:

Lose sync if time between one event and next is not within allowable range, or if ordering of inner/outer events is not correct.
Possibility of ignoring narrow pulses in order to be noise tolerant, but this comes with risk.

Summary:

Sync obtainable for 292 degrees of crank rotation and not for remaining 428 degrees

worst case is 428 degrees of rotation before sync/injection/ignition, average case is 214 degrees rotation, best case is instant sync.

temporary pin sched code:

for(pin 0 - 5){
	if(pinEventNumbers[pin] == thisEvent){
		firePin(pin, delayFromEventInTicks);
	}
}

 *
 * @author Fred Cooke
 */


#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"
#include "../inc/utils.h"

#define sensorOffsetInCamDegrees 34
#define sensorOffsetInCrankDegrees (sensorOffsetInCamDegrees * 2)
#define innerAngleOfOnEvent (590 - sensorOffsetInCrankDegrees)
#define innerAngleOfOffEvent (720 - sensorOffsetInCrankDegrees)

#if (innerAngleOfOnEvent != 522)
#error "Unexpected inner on angle value"
#endif

#if (innerAngleOfOffEvent != 652)
#error "Unexpected inner off angle value"
#endif



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
	coreStatusA |= PRIMARY_SYNC;

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
		primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
		timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp - lastPrimaryPulseTimeStamp;
		lastPrimaryPulseTimeStamp = primaryLeadingEdgeTimeStamp;

// = 60 * (1000000 / 0.8)
#define ticksPerMinute   75000000 // this is correct.

		*RPMRecord = (unsigned short) (ticksPerMinute / timeBetweenSuccessivePrimaryPulses);

		// TODO sample ADCs on teeth other than that used by the scheduler in order to minimise peak run time and get clean signals

		//if(0, 2, 4, 7){ no need to check for numbers, just always do on rising or always on falling and only in primary isr same for RPM above
			sampleEachADC(ADCArrays);
			Counters.syncedADCreadings++;
			*mathSampleTimeStampRecord = TCNT;

			/* Set flag to say calc required */
			coreStatusA |= CALC_FUEL_IGN;

			/* Reset the clock for reading timeout */
			Clocks.timeoutADCreadingClock = 0;
//		}

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

	/* The LM1815 variable reluctance sensor amplifier allows the output to be
	 * pulled high starting at the center of a tooth. So, what we see as the
	 * start of a tooth is actually the centre of a physical tooth. Because
	 * tooth shape, profile and spacing may vary this is the only reliable edge
	 * for us to schedule from, hence the trailing edge code is very simple.
	 */
	if(PTITCurrentState & 0x02){
		// echo input condition
		PORTJ |= 0x40;

		Counters.secondaryTeethSeen++;

		/* leading code
		 *
		 * subtract lastTrailing from currentLeading
		 * record currentLeading as lastLeading
		 *
		 * record pw as highDuration
		 */
		lengthOfSecondaryLowPulses = timeStamp.timeLong - lastSecondaryPulseTrailingTimeStamp;
		lastSecondaryPulseLeadingTimeStamp = timeStamp.timeLong;
	}else{

		/* trailing code
		 *
		 * subtract lastLeading from currentTrailing
		 * record currentTrailing as lastTrailing
		 *
		 * record pw as lowDuration
		 */
//		lengthOfSecondaryHighPulses = timeStamp.timeLong - lastSecondaryPulseLeadingTimeStamp;
		lastSecondaryPulseTrailingTimeStamp = timeStamp.timeLong;

		PORTJ &= 0xBF;
	}
}
