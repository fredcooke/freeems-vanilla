/* FreeEMS - the open source engine management system
 *
 * Copyright 2010 Fred Cooke
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


/**	@file DecoderInterface.h
 * @ingroup allHeaders
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
 * Max number of samples = max number of cylinders, has to be handled by decoder due to
 * potential mismatch between wheel pattern and cylinder firing pattern.
 *
 * Scheduling:
 *
 * Fueling pins could be expected to fire once per cylinder event (1 - 12), or
 * once per engine cycle, or something in between, but what is a reasonable
 * max, and is it workable to allow some cases and not others?
 *
 * Ignition pins will only need to be fired once per cycle or twice per cycle,
 * unless multi-spark startup is required, however this could be done with
 * cascaded dwell events, timer self-set:
 *
 * on dwell off spark on dwell off spark on dwell off and disable spark
 *
 * This example is for triple spark, 2 or more than 3 are also possible.
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
 * support every single tooth on a nissan 360 style decoder or just cyl event count, what about
 * porsche 130? next stop is 60, seems good. can we use bit-fields to save memory, 1 bit =
 * 2 possible pins, 2 bits = 4, etc, this will be slower, though. probably just an unsigned char[]
 */


// TODO @todo the below vars are just drafts so far, nothing is used, except the RPM stuff which I migrated here from the main header. More work to come.
#define numberOfWheelEvents 1 // not teeth, teeth is misleading - could be leading or trailing edge or both
unsigned char currentWheelEvent; // Current or last wheel event index.
unsigned long wheelEventTimeStamps[numberOfWheelEvents]; // For logging wheel patterns as observed. LOTS of memory :-/ may not be possible except by sending lastStamp rapidly at low RPM
unsigned short* RPM; // final output variable, probably move into inputVars struct?
unsigned short* RPMRecord; // intermediate storage variable, do something with this?
unsigned char ignitionEvents[6];
unsigned char injectionEvents[12];
unsigned char ADCSampleEvents[12]; // ???
unsigned char stagedInjectionEvents; // ???
unsigned char chickenCookerEvents; //  ???


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
