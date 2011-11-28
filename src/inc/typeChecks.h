/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2011 Fred Cooke
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
 * @ingroup globalHeaders
 * @ingroup dataStructures
 *
 * @brief Compile time checks on types
 *
 * This file contains checks on sizes of various structs.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_TYPE_CHECKS_H_SEEN
#define FILE_TYPE_CHECKS_H_SEEN


/** A compile time assertion check.
 *
 * Validate at compile time that the predicate is true without
 * generating code. This can be used at any point in a source file
 * where typedef is legal.
 *
 * On success, compilation proceeds normally.
 *
 * On failure, attempts to typedef an array type of negative size. The
 * offending line will look like
 *     typedef assertion_failed_file_h_42[-1]
 * where file is the content of the second parameter which should
 * typically be related in some obvious way to the containing file
 * name, 42 is the line number in the file on which the assertion
 * appears, and -1 is the result of a calculation based on the
 * predicate failing.
 *
 * @param predicate The predicate to test. It must evaluate to
 * something that can be coerced to a normal C boolean.
 *
 * @param file A sequence of legal identifier characters that should
 * uniquely identify the source file in which this condition appears.
 */
#define CASSERT(predicate, file) _impl_CASSERT_LINE(predicate,__LINE__,file)
#define _impl_PASTE(a,b) a##b
#define _impl_CASSERT_LINE(predicate, line, file) typedef char _impl_PASTE(assertion_failed_##file##_,line)[2*!!(predicate)-1];


// Things with specific sizes:
CASSERT(sizeof(Flaggable) == 16, Flaggable)
CASSERT(sizeof(ADCBuffer)  == 32, ADCBuffer)
CASSERT(sizeof(twoDTableUS) == 64, twoDTableUS)
CASSERT(sizeof(mainTable) == flashSectorSize, mainTable)

// Short alignment checks:
CASSERT((sizeof(Clock) % 2) == 0, Clock)
CASSERT((sizeof(Counter) % 2) == 0, Counter)
CASSERT((sizeof(CoreVar) % 2) == 0, CoreVar)
CASSERT((sizeof(DerivedVar) % 2) == 0, DerivedVar)
CASSERT((sizeof(KeyUserDebug) % 2) == 0, KeyUserDebug)

// Flash block alignment checks:
CASSERT((sizeof(SmallTables1) == flashSectorSize), SmallTables1)
CASSERT((sizeof(SmallTables2) == flashSectorSize), SmallTables2)
CASSERT((sizeof(SmallTables3) == flashSectorSize), SmallTables3)
CASSERT((sizeof(SmallTables4) == flashSectorSize), SmallTables4)

CASSERT((sizeof(fixedConfig1) == flashSectorSize), fixedConfig1)
CASSERT((sizeof(fixedConfig2) == flashSectorSize), fixedConfig2)

// The following is just a reminder that updates to MTX and OLV are required
CASSERT(maxBasicDatalogLength == 96, DatalogLength) // Sum of the ones below
CASSERT(sizeof(CoreVar) == 32, CoreVar)
CASSERT(sizeof(DerivedVar) == 26, DerivedVar)
CASSERT(sizeof(KeyUserDebug) == 38, KeyUserDebug)


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file TYPE_CHECKS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
