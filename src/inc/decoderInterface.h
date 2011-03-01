/* FreeEMS - the open source engine management system
 *
 * Copyright 2010, 2011 Fred Cooke
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


/**	@file decoderInterface.h
 * @ingroup allHeaders
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Objects through which a decoder communicates.
 *
 * This file contains the declarations of objects used as a common interface
 * between all of the different wheel decoders and the main loop scheduler.
 *
 * @author Fred Cooke
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_DECODER_INTERFACE_H_SEEN
#define FILE_DECODER_INTERFACE_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef DECODER_IMPLEMENTATION_C
#define EXTERN
#else
#define EXTERN extern
#endif


// Change these together...
#define degreeTicksPerMinute 4166667
#define ticks_per_degree_multiplier 10
/// @todo TODO make this ^ scaling better x10 yields 64rpm minimum functional engine speed.


// ADC

// RPM
EXTERN unsigned short ticksPerDegree0; // to be replaced with logging scheme for teeth.
EXTERN unsigned short ticksPerDegree1; // to be replaced with logging scheme for teeth.
EXTERN unsigned short* ticksPerDegree; // final output variable, probably move into inputVars struct?
EXTERN unsigned short* ticksPerDegreeRecord; // intermediate storage variable, do something with this?

// Time/Sync

/*
what is common between different setups? Add others here as required/desired/discussed.

		M-N setup - to sync we need gap that has just passed, and gap before, cases are: two gaps approx equal = who knows where. current gap = N * bigger means tooth after gap, current gap = N times smaller = second tooth after gap. Two opportunities to sync. by definition we always have these two gap measurements once synced. from these two gap measurements we can obtain a rough first RPM, then later RPM can be got from opposing teeth.
		4and1 setup - sync is obtained via logic, to get a rough RPM we need only one gap measurement, to verify noise free operation we need two. When we sync we may or may not have a previous gap measurement. For one sync opportunity we could have 0, 1, 2 gaps, for another we could have 0 or 1 gaps, and for the rest we will not have a gap measurement till a subsequent  event.
		24and2 setup - sync is obtained simply by watching for second trigger, sync is maintained by checking that second trigger falls when it should again. When a second trigger arrives, we could have 0, 1, 2 - ~12 primary gaps measured
		Simple setup - sync is not required, fire on all valid pulses. check for noise based on previous gaps, one event per ign event, correctly spaced timing required. Can be V twin, dizzy/points/outer of dsm/4and1 cas units, etc.

From this we need:

this stamp - have while running only. - so not required in header
previous stamp
stamp before previous stamp - only required on previous execution, at which time it is actually previous stamp, so not required.

this gap - have while running only. - so not required in header
previous gap - stored last time

flags to know if gap and stamp are valid - if gap is valid, stamp is not the oldest we effectively have.
previous gap valid - one flag
previous stamp valid - one flag

event counter - single unsigned value, 256 enough? probably can't cope with more than that anyway, except at low rpm, which is useless.

event angles - array of shorts, range required is 0 - 719.9999999999999 - can we provide sub degree accuracy with an unsigned short array? yes, what is best scale figure?

States:
* no sync (not of or of other three, no flag required, obviously)
* cylinder sync - one flag
* crank sync - one flag
* cam sync - one flag

from the above we can check one gap+angle with the next gap+angle and ensure smooth noise free operation is occurring.

*/

// unsigned long thisEventTimeStamp; recommended variable naming, may be enforced for/with macro use
// unsigned long thisInterEventPeriod; ditto
EXTERN unsigned char syncCaughtOnThisEvent;
EXTERN unsigned long lastEventTimeStamp;
EXTERN unsigned short lastTicksPerDegree;
EXTERN unsigned char currentEvent;
EXTERN unsigned char decoderFlags;
EXTERN unsigned long engineCyclePeriod;
#define COMBUSTION_SYNC      BIT0 // Dizzy/Batch Injection
#define CRANK_SYNC           BIT1 // Wasted Spark/Semi-Sequential
#define CAM_SYNC             BIT2 // COP/CNP/Sequential
#define LAST_TIMESTAMP_VALID BIT3
#define LAST_PERIOD_VALID    BIT4
#define CLEAR_COMBUSTION_SYNC      NBIT0
#define CLEAR_CRANK_SYNC           NBIT1
#define CLEAR_CAM_SYNC             NBIT2
#define CLEAR_LAST_TIMESTAMP_VALID NBIT3
#define CLEAR_LAST_PERIOD_VALID    NBIT4

// These are defined per decoder and used elsewhere!
EXTERN const unsigned short eventAngles[256]; // From 0 - 720 degrees, scale: not at all, x10 x60 or x90?
EXTERN const unsigned char decoderName[32];


// specific to one decoder, generalise this later! Or put a call to an inline function in the main reset sync function and the definition in every decoder
EXTERN unsigned char unknownEdges;



// Scheduling

// prelim, will change...
EXTERN unsigned char pinEventNumbers[6]; // 6 pins, which even should they go on? 255/0xFF = not fired. populated by scheduler in main loop
/* IDEA: array of chars 256 long, where a number of 0 means nothing scheduled,
 * and anothe number is a reference to a struct in a block of structs, each of
 * which contains scheduling info for all things that event must do.
 *
 * lots of ideas, none seem good on memory and fast...
 *
// TODO @todo the below vars are just drafts so far, nothing is used, except the RPM stuff which I migrated here from the main header. More work to come.
//#define numberOfWheelEvents 1 // not teeth, teeth is misleading - could be leading or trailing edge or both
//unsigned char currentWheelEvent; // Current or last wheel event index.
//unsigned long wheelEventTimeStamps[numberOfWheelEvents]; // For logging wheel patterns as observed. LOTS of memory :-/ may not be possible except by sending lastStamp rapidly at low RPM
//unsigned char ignitionEvents[6];
//unsigned char injectionEvents[12];
//unsigned char ADCSampleEvents[12]; // ???
//unsigned char stagedInjectionEvents; // ???
//unsigned char chickenCookerEvents; //  ??? */


// Helpers - force all these to be inlined!
EXTERN void resetToNonRunningState(void);


#undef EXTERN


/**
 * RPM Calculations:
 *
 * Either need a per decoder function that is called from the main loop OR...
 * RPM calculation is done in real time inside one of the RPM interrupts OR...
 * The choice of either, up to the decoder to decide how it is done, in this
 * case the function can either do nothing, or swap some pointers/var values
 * around or similar.
 *
 * MAP Sampling:
 *
 * Max number of samples = max number of cylinders, has to be handled by
 * decoder due to potential mismatch between wheel pattern and cylinder firing
 * pattern unless it is done on a rough multiple sample basis in generic code
 * that runs often and can approximate timing/position for sampling.
 *
 * Scheduling:
 *
 * Fueling pins could be expected to fire once per cylinder event (1 - 12), or
 * once per engine cycle, or something in between, but what is a reasonable
 * maximum, and is it workable to allow some cases and not others?
 *
 *            |-----------------------------------------------------------|
 *            |                           Pins                            |
 *            |-----------------------------------------------------------|
 *            |  1 |  2 |  3 |  4 |  5 |  6 |  7 |  8 |  9 | 10 | 11 | 12 |
 * -----------|-----------------------------------------------------------|
 * |     |  1 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  2 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  3 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  4 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  5 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  6 |    |    |    |    |    |    |    |    |    |    |    |    |
 * | Cyl |----|-----------------------------------------------------------|
 * |     |  7 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  8 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     |  9 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     | 10 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     | 11 |    |    |    |    |    |    |    |    |    |    |    |    |
 * |     |----|-----------------------------------------------------------|
 * |     | 12 |    |    |    |    |    |    |    |    |    |    |    |    |
 * -----------|-----------------------------------------------------------|
 *
 *
 * Ignition pins will only need to be fired once per cycle (COP/CNP), twice per
 * cycle (Wasted Spark) or once per cylinder event (distributor) unless
 * multiple-spark startup is required, however this could be done with cascaded
 * dwell events, timer self-set:
 *
 * on dwell off spark on dwell off spark on dwell off and disable spark
 *
 * This example is for triple spark, 2 or more than 3 are also possible.
 *
 * When coils are wired one per cylinder for COP/CNP, during starting or loss
 * of cam sync two opposing coils will be fired at the same time in pseudo
 * wasted spark mode.
 *
 * Possible states of sync are as follows:
 *
 * Full cycle engine sync - COP/CNP/Sequential
 * Half cycle revolution sync - Wasted Spark/Semi Sequential
 * Cylinder sync - Distributor/Many pulses or un-timed batch pulses
 *
 * Wheels will have various patterns of rising/falling edges. Scheduling may be
 * done from either the rising or falling edge on some, or only on one edge of
 * others. VR sensors have only one reliable edge, the other varies with speed
 * and associated rise/fall times of the approximately sinusoidal wave form.
 * Simple patterns shall be required to be timed to the engine such that at low
 * engine speeds the timer delays available with high accuracy are sufficient
 * to properly time ignition events. At the least, there should be a wheel
 * event per cylinder event, and in close proximity to that cylinder event.
 * Allowing even more relaxed wheel patterns would mean compromising the
 * performance for other more common setups and/or increasing code complexity
 * by an unacceptable amount.
 *
 * OLD notes:
 *
 * arrays of output channels, iterate and check for wheel event number, if matched, fire:
 * doesn't allow for firing a pin more than once a cycle!! no use.
 * allows multi channel on a single wheel event (virtually useless) but is slow, one loop
 * and array per type of output channel.
 *
 * array of wheel events, do lookup for wheel event, then if output channel valid, schedule it.
 * single channel per tooth event (acceptable, wire in parallel if required), fast, memory hog,
 * need one array per type of channel, array length = max expected tooth count! do we need to
 * support every single tooth on a Nissan 360 style decoder or just cyl event count, what about
 * Porsche 130? next stop is 60, seems good. can we use bit-fields to save memory, 1 bit =
 * 2 possible pins, 2 bits = 4, etc, this will be slower, though. probably just an unsigned char[]
 */


// Init routine:
//
// Allow configuration of timer details? tick size? If so, need to introduce scaling to calcs to
// produce correct tick count and therefore pulsewidth. Migrate dead time to time units and scale
// to get ticks to add to final pw.
//
// We require some configuration to allow the Nissan style decoder to use the pulse accumulators to
// count those one degree slots accurately to a high rpm without excessive cpu load.


// move the following to  fuel calcs or sched code header, it doesn't belong here...
//
// stuff to do with timing and sync etc. ie, figuring out upon which



#else
	/* let us know if we are being untidy with headers */
	#warning "Header file DECODER_INTERFACE_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
