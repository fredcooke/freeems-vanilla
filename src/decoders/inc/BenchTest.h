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


/** @file
 *
 * @ingroup allHeaders
 * @ingroup testing
 *
 * Contains bench test only vars and defines etc.
 *
 * To add a file to the project :
 * - Change all 4 hash defines to the filename uppercased and underscored
 *
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_BENCH_TEST_H_SEEN
#define FILE_BENCH_TEST_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef STATIC_BENCH_TEST_C
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN unsigned short testTicksPerEvent;
EXTERN unsigned short testNumberOfCycles;
EXTERN unsigned char testEventsPerCycle;
EXTERN unsigned char testNumberOfMissing;
EXTERN unsigned char testMode;
#define TEST_MODE_STOP                0
#define TEST_MODE_ITERATIONS          1
#define TEST_MODE_BUMP_UP_CYCLES      2
#define TEST_MODE_DODGY_MISSING_TOOTH TEST_MODE_BUMP_UP_CYCLES // Genuine bumps exit before getting here, so this is being reused in the hackiest most horrible way imaginable!
#define TEST_MODE_TIME_UNITS_SECONDS  3
#define TEST_MODE_TIME_UNITS_MINUTES  4
#define TEST_MODE_TIME_UNITS_HOURS    5
#define TEST_MODE_REVOLUTIONS         6 // Default of dizzy, sub modes of different patterns:
#define TEST_MODE_REVOLUTIONS_12_1    7
#define TEST_MODE_REVOLUTIONS_24_1    8
#define TEST_MODE_REVOLUTIONS_36_1    9
#define TEST_MODE_REVOLUTIONS_60_2   10
#define TEST_MODE_REVOLUTIONS_4and1  11
#define TEST_MODE_REVOLUTIONS_4and2  12
#define TEST_MODE_REVOLUTIONS_24and1 13
#define TEST_MODE_REVOLUTIONS_24and2 14
#define TEST_MODE_REVOLUTIONS_LT1    15


/// @todo TODO make event array length a var, and populate it with the const at init time, and with the chosen fake array type
/// @todo TODO make the event array itself be a pointer, and switch this pointer in the bench test call with it pre-inited to the address of the const array for real decoders


#undef EXTERN


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file BENCH_TEST_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
