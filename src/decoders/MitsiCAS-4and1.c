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
measured values with compression effect = {0, 73, 184, 257, 367, 436, 530, 545, 612, 671}
                            differences = {0, 13,  14,  17,   7,  16,   8,   5,  12,  19}
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

if outer = on to off AND inner = on, then position = 600
if outer = off to on AND inner = on, then position = 540
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
	if(pinEventNumbers[pin] == event){
		firePin(pin, delayFromEventInTicks);
	}
}

Checking tooth timing! :

record time stamps from all events outside of IF conditions, and before sync,
and set flag saying that stamp is valid such that when the first sync point is
found we MIGHT be able to get an RPM instantly and verify the second event
timing when it arrives, rather than one later. This concept could be extended
to record the previous two, but not yet...

record time stamps, set stamp valid flags
record periods, set period valid flags
once synced, compare recorded data with expected history, drop sync if not, so will never get sync if noisy, great!


WARNING: THESE CONTAIN COMPRESSION EFFECTS!!!


Visual version courtesy of hacked OLV:

http://stuff.fredcooke.com/high.res.4and1.cas.la.trace.png

Binary log of format (Start, flags, payloadID(2), PTIT, checksum, Stop, Stop) :

http://stuff.fredcooke.com/portT.min.1.la


Real readings from truck cranking test:

14213 - start of first outer slot (goes low at CPU, goes high outside)
14262 - end of first outer slot (goes high at CPU, goes low outside)
14337 - start of second outer slot (goes low at CPU, goes high outside)
14386 - end of second outer slot (goes high at CPU, goes low outside)
14460 - start of third outer slot (goes low at CPU, goes high outside)
14507 - end of third outer slot (goes high at CPU, goes low outside)
14570 - start of inner slot (goes low at CPU, goes high outside)
14580 - start of fourth outer slot (goes low at CPU, goes high outside)
14625 - end of fourth outer slot (goes high at CPU, goes low outside)
14665 - end of inner slot (goes high at CPU, goes low outside)
14698 - start of first outer on next cycleÉ.

remove 14k from each:

213 - start of first outer slot (goes low at CPU, goes high outside)
262 - end of first outer slot (goes high at CPU, goes low outside)
337 - start of second outer slot (goes low at CPU, goes high outside)
386 - end of second outer slot (goes high at CPU, goes low outside)
460 - start of third outer slot (goes low at CPU, goes high outside)
507 - end of third outer slot (goes high at CPU, goes low outside)
570 - start of inner slot (goes low at CPU, goes high outside)
580 - start of fourth outer slot (goes low at CPU, goes high outside)
625 - end of fourth outer slot (goes high at CPU, goes low outside)
665 - end of inner slot (goes high at CPU, goes low outside)
698 - start of first outer on next cycleÉ.

remove 213 from each:

0 - start of first outer slot (goes low at CPU, goes high outside)
49 end of first outer slot (goes high at CPU, goes low outside)
124 start of second outer slot (goes low at CPU, goes high outside)
173 end of second outer slot (goes high at CPU, goes low outside)
247 start of third outer slot (goes low at CPU, goes high outside)
294 end of third outer slot (goes high at CPU, goes low outside)
357 start of inner slot (goes low at CPU, goes high outside)
367 start of fourth outer slot (goes low at CPU, goes high outside)
412 end of fourth outer slot (goes high at CPU, goes low outside)
452 end of inner slot (goes high at CPU, goes low outside)
485 start of first outer on next cycleÉ.

scale for degrees: (720/485) * num = degrees

0 - start of first outer slot (goes low at CPU, goes high outside)
72.742268 end of first outer slot (goes high at CPU, goes low outside)
184.082474 start of second outer slot (goes low at CPU, goes high outside)
256.824742 end of second outer slot (goes high at CPU, goes low outside)
366.680412 start of third outer slot (goes low at CPU, goes high outside)
436.453608 end of third outer slot (goes high at CPU, goes low outside)
529.979381 start of inner slot (goes low at CPU, goes high outside)
544.824742 start of fourth outer slot (goes low at CPU, goes high outside)
611.628866 end of fourth outer slot (goes high at CPU, goes low outside)
671.010309 end of inner slot (goes high at CPU, goes low outside)
720/0 start of first outer on next cycleÉ.

Broken into widths:

Outer:
72.742268 first outer slot (low at CPU, high outside)
111.340206 solid between first and second outer slots (high at CPU, low outside)
72.742268 second outer slot (low at CPU, high outside)
109.85567 solid between second and third outer slots (high at CPU, low outside)
69.773196 third outer slot (low at CPU, high outside)
108.371134 solid between third and fourth outer slots (high at CPU, low outside)
66.804124 fourth outer slot (low at CPU, high outside)
108.371134 solid between fourth and first outer slots (high at CPU, low outside)

Inner:
141.030928 inner slot (low at CPU, high outside)
578.969072 solid that isn't the inner slot (high at CPU, low outside)

Offsets:
93.525773 end of third outer slot to start of inner slot (no state)
14.845361 start of inner slot to start of fourth outer slot (no state)
59.381443 end of fourth outer slot to end of inner slot (no state)
48.989691 end of inner slot to start of first outer slot (no state)

Latest WITHOUT compression effects, but still with variations from engine friction etc etc...

logic.test.flat.battery.5.log.la

17363 = 0
17463 = 1
17633 = 2
17739 = 3
17900 = 4
18001 = 5
18144 = 6
18166 = 7
18266 = 8
18346 = 9
18425 = 0

100 - 0 - 1 slot
170 - 1 - 2 solid
106 - 2 - 3 slot
161 - 3 - 4 solid
101 - 4 - 5 slot
165 - 5 - 7 solid
100 - 7 - 8 slot
159 - 8 - 0 solid

rolling with 101.75 and 163.75

101.75/1062 = 0.0958097928
 * 720 = 68.9830508

163.75/1062 = 0.154190207
 * 720 = 111.016949

rounds to 69 / 111
close to 70/110


143 - 5 - 6 end outer start inner
  22 - 6 - 7 start inner start outer
  80 - 8 - 9 end outer end inner
  79 - 9 - 0 end inner start outer

202 - 6 - 9 - inner slot
860 - 9 - 6 = inner solid

202/1062 = 136.949153
860/1062 = 583.050847
137/583
140/580?

total period = 1062

0
100
270
376
537
638
803
903
1062

From file http://stuff.fredcooke.com/logic.test.flat.battery.5.log.la

 *
 * @author Fred Cooke
 */


#define DECODER_IMPLEMENTATION_C

#include "../inc/freeEMS.h"
#include "../inc/utils.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"
//#include "../inc/MitsiCAS-4and1.h"


// Change these together...
#define degreeTicksPerMinute 4166667
#define ticks_per_degree_multiplier


static unsigned short edgeTimeStamp;
static LongTime timeStamp;
//static unsigned short ticksPerCrankDegree; // need some sort of state to say not to use this first time through...
#define NUMBER_OF_EVENTS 10
#define MAX_POSSIBLE_EVENT_ANGLE 720

// These are fixed and by definition correct
#define E0   0
#define E2 180
#define E4 360
#define E7 540

#define OuterSlotAngle   69 // BUT 69 is too high, and 68 is even more too low = need to refactor to specify these angles accurately enough for perfect RPM/scheduling

// These are offset from the fixed ones by the angle of the slot
#define E1 (E0 + OuterSlotAngle)
#define E3 (E2 + OuterSlotAngle)
#define E5 (E4 + OuterSlotAngle)
#define E8 (E7 + OuterSlotAngle)

#define InnerSlotAngle 140 // WAS 138 // WAS 139 // WAS 137 // Speculation: 140? Close to it... ignore my affection for round numbers... :-) HA! I was close to right this time, the other was right first guess and wants to be a little lower.

#define E6 525 // WAS 527 // WAS 526 // Start position measured, just like outer on/off duty.
#define E9 (E6 + InnerSlotAngle)

// 529 from E0 for E6 measured                      so (529 + 137 = 666)

// 526 from E5 for E6 measured from (360 + 69 + 97) so (526 + 137 = 663)
// 525 from E7 for E6 measured from (540 - 15)      so (525 + 137 = 662)

// 666 from E0 for E9 measured

// 663 from E8 for E9 measured from (540 + 69 + 54) so (663 - 137 = 526)
// 666 from 10 for E9 measured from (720 - 54)      so (666 - 137 = 529)

const unsigned short eventAngles[] = {E0, E1, E2, E3, E4, E5, E6, E7, E8, E9}; // needs to be shared with other decoders, defined here and referenced by the scheduler or similar
const unsigned char decoderName[] = "MitsiCAS-4and1.c";


/// @todo TODO migrate ALL decoder vars, arrays, fields, whatever to the decoder header out of the global header...


// Need to make this available to all decoders and cut out code from those that have it built in.
void schedulePortTPin(unsigned char pin){
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

	// determine whether or not to reschedule
	unsigned char reschedule = 0;
	unsigned long diff = startTimeLong - (injectorMainEndTimes[pin] + injectorSwitchOffCodeTime);
	if(diff > LONGHALF){
		reschedule = 1; // http://forum.diyefi.org/viewtopic.php?f=8&t=57&p=861#p861
	}

	// schedule the appropriate channel
	if(!(*injectorMainControlRegisters[pin] & injectorMainEnableMasks[pin]) || reschedule){ /* If the timer isn't still running, or if its set too long, set it to start again at the right time soon */
		*injectorMainControlRegisters[pin] |= injectorMainEnableMasks[pin];
		*injectorMainTimeRegisters[pin] = startTime;
		TIE |= injectorMainOnMasks[pin];
		TFLG = injectorMainOnMasks[pin];
	}else{
		injectorMainStartTimesHolding[pin] = startTime;
		selfSetTimer |= injectorMainOnMasks[pin]; // setup a bit to let the timer interrupt know to set its own new start from a var
	}
}


/* block 1 RPM code from simple/volvo, similar style of RPM calc to what is required in primary ISR

 		primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
		timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp - lastPrimaryPulseTimeStamp;
		lastPrimaryPulseTimeStamp = primaryLeadingEdgeTimeStamp;

// = 60 * (1000000 / 0.8)
#define ticksPerMinute   75000000 // this is correct.

		*RPMRecord = (unsigned short) (ticksPerMinute / timeBetweenSuccessivePrimaryPulses);
 */


/** Primary RPM ISR
 *
 * Schedule events :
 * Fire off port T events based on whatever is scheduled in the main loop.
 *
 * Sample ADCs :
 * Grab a unified set of ADC readings at one time in a consistent crank location to eliminate engine cycle dependent noise.
 * Set flag stating that New pulse, advance, etc should be calculated.
 *
 * @author Fred Cooke
 */
void PrimaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	edgeTimeStamp = TC0;				/* Save the edge time stamp */
	unsigned char PTITCurrentState = ~PTIT;			/* Save the values on port T regardless of the state of DDRT */

	/* Calculate the latency in ticks */
	ISRLatencyVars.primaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	Counters.primaryTeethSeen++;

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
	if(decoderFlags & LAST_TIMESTAMP_VALID){
		thisInterEventPeriod = thisEventTimeStamp - lastEventTimeStamp;
	}

	// Determine the correct event based on post transition state (and toggle debug pins)
	unsigned char correctEvent = 0;
	if(PTITCurrentState & 0x01){
		PORTJ |= 0x80;

		// Pins 0, 2, 4 and 7 - no need to check for numbers, just always do on rising edge and only in primary isr same for RPM above
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;
		*mathSampleTimeStampRecord = TCNT;

		// Set flag to say calc required
		coreStatusA |= CALC_FUEL_IGN;

		// Reset the clock for reading timeout
		Clocks.timeoutADCreadingClock = 0;

		if(PTITCurrentState & 0x02){
			correctEvent = 7;
			unknownEdges = 0;
		}else{
			unknownEdges++;
			if(unknownEdges == 3){
				correctEvent = 4;
			}
		}
	}else{
		PORTJ &= 0x7F;


		//temp
		// Pins 0, 2, 4 and 7 - no need to check for numbers, just always do on rising edge and only in primary isr same for RPM above
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;
		*mathSampleTimeStampRecord = TCNT;

		// Set flag to say calc required
		coreStatusA |= CALC_FUEL_IGN;

		// Reset the clock for reading timeout
		Clocks.timeoutADCreadingClock = 0;

		if(PTITCurrentState & 0x02){
			correctEvent = 8;
		}
	}

	unsigned char lastEvent = 0;
	unsigned char eventBeforeLastEvent = 0;
	if(decoderFlags & CAM_SYNC){
		eventBeforeLastEvent = lastEvent;
		lastEvent = currentEvent;
		currentEvent++;
		if(currentEvent == NUMBER_OF_EVENTS){
			currentEvent = 0;
		}

		// ...and check that it's correct
		if((correctEvent != 0) && (currentEvent != correctEvent)){
			currentEvent = correctEvent;
			lastEvent = currentEvent - 1;
			eventBeforeLastEvent = currentEvent - 2;

			// Record that we had to reset position...
			Counters.camSyncCorrections++;
			// Should never happen, or should be caught by timing checks below
		}
	}else if(correctEvent != 0){
		decoderFlags |= CAM_SYNC;
		currentEvent = correctEvent;
		lastEvent = currentEvent - 1;
		eventBeforeLastEvent = currentEvent - 2;
		syncCaughtOnThisEvent = correctEvent;
	}

	if(decoderFlags & CAM_SYNC){
		unsigned short thisAngle = 0;
		if(currentEvent == 0){
			thisAngle = eventAngles[currentEvent] + MAX_POSSIBLE_EVENT_ANGLE - eventAngles[lastEvent] ; // Optimisable... leave readable for now! :-p J/K learn from this...
		}else{
			thisAngle = eventAngles[currentEvent] - eventAngles[lastEvent];
		}

		/// @todo TODO make this scaling better x20 yields 64rpm minimum functional engine speed.
		unsigned short thisTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * thisInterEventPeriod) / thisAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error

		if(decoderFlags & LAST_PERIOD_VALID){
			unsigned short lastAngle = 0;
			if(lastEvent == 0){
				lastAngle = eventAngles[lastEvent] + MAX_POSSIBLE_EVENT_ANGLE - eventAngles[eventBeforeLastEvent] ; // Optimisable... leave readable for now! :-p J/K learn from this...
			}else{
				lastAngle = eventAngles[lastEvent] - eventAngles[eventBeforeLastEvent];
			}

			/// @todo TODO make this scaling better x20 yields 64rpm minimum functional engine speed.
			unsigned short lastTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * lastInterEventPeriod) / lastAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error

			unsigned short ratioBetweenThisAndLast = (unsigned short)(((unsigned long)lastTicksPerDegree * 1000) / thisTicksPerDegree);
			DerivedVars->sp1 = lastTicksPerDegree;
			DerivedVars->sp2 = thisTicksPerDegree;
			DerivedVars->sp4 = ratioBetweenThisAndLast;
			if((ratioBetweenThisAndLast > 1500) || (ratioBetweenThisAndLast < 667)){ /// @todo TODO hard coded tolerance, needs tweaking to be reliable, BEFORE I drive mine in boost, needs making configurable/generic too...
				//resetToNonRunningState();
				Counters.camSyncCorrections;
			}else{
				if(PTITCurrentState & 0x01){
					/// @todo TODO Calculate RPM from last primaryLeadingEdgeTimeStamp
				}else{
					/// @todo TODO Calculate RPM from last primaryTrailingEdgeTimeStamp
				}
			}
		}/*else*/ if(decoderFlags & LAST_TIMESTAMP_VALID){ /// @todo TODO temp for testing just do rpm this way, fill above out later.
			*RPMRecord = (unsigned short)(degreeTicksPerMinute / thisTicksPerDegree);
		}
	}

	if(decoderFlags & CAM_SYNC){
		unsigned char pin;
		for(pin=0;pin<6;pin++){
			if(pinEventNumbers[pin] == currentEvent){
				schedulePortTPin(pin);
			}
		}
	}

	if(decoderFlags & LAST_TIMESTAMP_VALID){
		lastInterEventPeriod = thisInterEventPeriod;
		decoderFlags |= LAST_PERIOD_VALID;
	}
	// Always
	lastEventTimeStamp = thisEventTimeStamp;
	decoderFlags |= LAST_TIMESTAMP_VALID;

	RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
}


/** Secondary RPM ISR
 *
 * Reads the inner slot on the disk.
 */
void SecondaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	edgeTimeStamp = TC1;				/* Save the timestamp */
	unsigned char PTITCurrentState = ~PTIT;			/* Save the values on port T regardless of the state of DDRT */

	/* Calculate the latency in ticks */
	ISRLatencyVars.secondaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	Counters.secondaryTeethSeen++;
	// remember that this is both edges, though... 8 per cycle, 4 per rev for the outter wheel, 2/1 for this wheel.

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
	if(decoderFlags & LAST_TIMESTAMP_VALID){
		thisInterEventPeriod = thisEventTimeStamp - lastEventTimeStamp;
	}

	// Determine the correct event based on post transition state (and toggle debug pins)
	unsigned char correctEvent;
	if(PTITCurrentState & 0x02){
		PORTB = ONES; // bang port B and hope for led action
		PORTJ |= 0x40;

		//temp
		// Pins 0, 2, 4 and 7 - no need to check for numbers, just always do on rising edge and only in primary isr same for RPM above
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;
		*mathSampleTimeStampRecord = TCNT;

		// Set flag to say calc required
		coreStatusA |= CALC_FUEL_IGN;

		// Reset the clock for reading timeout
		Clocks.timeoutADCreadingClock = 0;

		correctEvent = 6;
	}else{
		PORTB = ZEROS; // match above
		PORTJ &= 0xBF;

		//temp
		// Pins 0, 2, 4 and 7 - no need to check for numbers, just always do on rising edge and only in primary isr same for RPM above
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;
		*mathSampleTimeStampRecord = TCNT;

		// Set flag to say calc required
		coreStatusA |= CALC_FUEL_IGN;

		// Reset the clock for reading timeout
		Clocks.timeoutADCreadingClock = 0;

		correctEvent = 9;
	}

	unsigned char lastEvent = 0;
	unsigned char eventBeforeLastEvent = 0;
	if(decoderFlags & CAM_SYNC){
		eventBeforeLastEvent = lastEvent;
		lastEvent = currentEvent;
		currentEvent++;

		// ...and check that it's correct
		if(currentEvent != correctEvent){
			currentEvent = correctEvent;
			lastEvent = currentEvent - 1;
			eventBeforeLastEvent = currentEvent - 2;

			// Record that we had to reset position...
			Counters.camSyncCorrections++;
			// Should never happen, or should be caught by timing checks below
		}
	}else{	// If not synced, sync, as in this ISR we always know where we are.
		decoderFlags |= CAM_SYNC;
		currentEvent = correctEvent;
		lastEvent = currentEvent - 1;
		eventBeforeLastEvent = currentEvent - 2;
		syncCaughtOnThisEvent = correctEvent;
	}

	if(decoderFlags & CAM_SYNC){
		unsigned short thisAngle = eventAngles[currentEvent] - eventAngles[lastEvent];

		/// @todo TODO make this scaling better x10 yields 64rpm minimum functional engine speed.
		unsigned short thisTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * thisInterEventPeriod) / thisAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error

		if(decoderFlags & LAST_PERIOD_VALID){
			unsigned short lastAngle = eventAngles[lastEvent] - eventAngles[eventBeforeLastEvent];

			/// @todo TODO make this scaling better x10 yields 64rpm minimum functional engine speed.
			unsigned short lastTicksPerDegree = (unsigned short)((ticks_per_degree_multiplier * lastInterEventPeriod) / lastAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error

			// this var is less than 667, why? because ticks/degree is BIG or lastTicks is SMALL
			unsigned short ratioBetweenThisAndLast = (unsigned short)(((unsigned long)lastTicksPerDegree * 1000) / thisTicksPerDegree);
			DerivedVars->sp1 = lastTicksPerDegree;
			DerivedVars->sp2 = thisTicksPerDegree;
			DerivedVars->sp4 = ratioBetweenThisAndLast;
//			if((ratioBetweenThisAndLast > 1500) || (ratioBetweenThisAndLast < 667)){ /// @todo TODO hard coded tolerance, needs tweaking to be reliable, BEFORE I drive mine in boost, needs making configurable/generic too...
				//	resetToNonRunningState();
//			}
			if((ratioBetweenThisAndLast < 667)){ /// @todo TODO hard coded tolerance, needs tweaking to be reliable, BEFORE I drive mine in boost, needs making configurable/generic too...
				Counters.camSyncLosses++;
			}
			if((ratioBetweenThisAndLast > 1500)){ /// @todo TODO hard coded tolerance, needs tweaking to be reliable, BEFORE I drive mine in boost, needs making configurable/generic too...
				Counters.crankSyncLosses++;
			}
		}/*else*/ if(decoderFlags & LAST_TIMESTAMP_VALID){
			*RPMRecord = (unsigned short)(degreeTicksPerMinute / thisTicksPerDegree);
		}
	}

	if(decoderFlags & CAM_SYNC){
		unsigned char pin;
		for(pin=0;pin<6;pin++){
			if(pinEventNumbers[pin] == currentEvent){
				schedulePortTPin(pin);
			}
		}
	}

	if(decoderFlags & LAST_TIMESTAMP_VALID){
		lastInterEventPeriod = thisInterEventPeriod;
		decoderFlags |= LAST_PERIOD_VALID;
	}
	// Always
	lastEventTimeStamp = thisEventTimeStamp;
	decoderFlags |= LAST_TIMESTAMP_VALID;

	RuntimeVars.secondaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
}
