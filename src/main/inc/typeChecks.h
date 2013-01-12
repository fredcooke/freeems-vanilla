/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
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
CASSERT(sizeof(cutEnabled) == 2, cutEnabled)
CASSERT(sizeof(ignitionCutFlags) == 1, ignitionCutFlags)
CASSERT(sizeof(injectionCutFlags) == 1, injectionCutFlags)

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

// Check the fixed point readability macros for correct behaviour
CASSERT(KPA(655.36) > SHORTMAX, PRESSURE)          // Overflow gets caught
CASSERT(KPA(655.35) == SHORTMAX, PRESSURE)         // Centre == max
CASSERT(KPA(655.3450000000) == SHORTMAX, PRESSURE) // Lowest to round up
CASSERT(KPA(655.3549999999) == SHORTMAX, PRESSURE) // Highest to round down

CASSERT(DEGREES_K(655.36) > SHORTMAX, TEMPERATURE_K)          // Overflow gets caught
CASSERT(DEGREES_K(655.35) == SHORTMAX, TEMPERATURE_K)         // Centre == max
CASSERT(DEGREES_K(655.3450000000) == SHORTMAX, TEMPERATURE_K) // Lowest to round up
CASSERT(DEGREES_K(655.3549999999) == SHORTMAX, TEMPERATURE_K) // Highest to round down

CASSERT(CC_PER_MINUTE(3840) > SHORTMAX, INJECTOR_FLOW)             // Overflow gets caught
CASSERT(CC_PER_MINUTE(3839.94140625) == SHORTMAX, INJECTOR_FLOW)   // Centre == max
CASSERT(CC_PER_MINUTE(3839.9701171875) == SHORTMAX, INJECTOR_FLOW) // Lowest to round up
CASSERT(CC_PER_MINUTE(3839.9121093750) == SHORTMAX, INJECTOR_FLOW) // Highest to round down

CASSERT(CYLINDER_VOLUME(2000) > SHORTMAX, CYL_VOLUME)            // Overflow gets caught
CASSERT(CYLINDER_VOLUME(1999.969482422) == SHORTMAX, CYL_VOLUME) // Centre == max
CASSERT(CYLINDER_VOLUME(1999.954223633) == SHORTMAX, CYL_VOLUME) // Lowest to round up
CASSERT(CYLINDER_VOLUME(1999.984740906) == SHORTMAX, CYL_VOLUME) // Highest to round down

CASSERT(VOLTS(65.536) > SHORTMAX, VOLTAGE)         // Overflow gets caught
CASSERT(VOLTS(65.535) == SHORTMAX, VOLTAGE)        // Centre == max
CASSERT(VOLTS(65.5345000001) == SHORTMAX, VOLTAGE) // Lowest to round up
CASSERT(VOLTS(65.5354999999) == SHORTMAX, VOLTAGE) // Highest to round down

CASSERT(LAMBDA(2.0) > SHORTMAX, LAMBDA)          // Overflow gets caught
CASSERT(LAMBDA(1.999969482) == SHORTMAX, LAMBDA) // Centre == max
CASSERT(LAMBDA(1.999954224) == SHORTMAX, LAMBDA) // Lowest to round up
CASSERT(LAMBDA(1.999984741) == SHORTMAX, LAMBDA) // Highest to round down

CASSERT(RPM(32767.75) > SHORTMAX, RPM)           // Overflow gets caught
CASSERT(RPM(32767.5) == SHORTMAX, RPM)           // Centre == max
CASSERT(RPM(32767.25) == SHORTMAX, RPM)          // Lowest to round up
CASSERT(RPM(32767.74999999999) == SHORTMAX, RPM) // Highest to round down

// Only used with values less than 720, overflows over 720 handled in the code
CASSERT(ANGLE(1310.71) > SHORTMAX, ANGLE)          // Overflow gets caught
CASSERT(ANGLE(1310.7) == SHORTMAX, ANGLE)          // Centre == max
CASSERT(ANGLE(1310.69) == SHORTMAX, ANGLE)         // Lowest to round up
CASSERT(ANGLE(1310.7099999999) == SHORTMAX, ANGLE) // Highest to round down

CASSERT(PW_MS(52.4284) > SHORTMAX, PW_MS)          // Overflow gets caught
CASSERT(PW_MS(52.428) == SHORTMAX, PW_MS)          // Centre == max
CASSERT(PW_MS(52.4276) == SHORTMAX, PW_MS)         // Lowest to round up
CASSERT(PW_MS(52.428399999999) == SHORTMAX, PW_MS) // Highest to round down

CASSERT(PERCENT(102.39921875) > SHORTMAX, PERCENT)  // Overflow gets caught
CASSERT(PERCENT(102.3984375) == SHORTMAX, PERCENT)  // Centre == max
CASSERT(PERCENT(102.39765625) == SHORTMAX, PERCENT) // Lowest to round up
CASSERT(PERCENT(102.39921874) == SHORTMAX, PERCENT) // Highest to round down

CASSERT(VE(127.9990234375) > SHORTMAX, VE)     // Overflow gets caught
CASSERT(VE(127.998046875) == SHORTMAX, VE)     // Centre == max
CASSERT(VE(127.9970703125) == SHORTMAX, VE)    // Lowest to round up
CASSERT(VE(127.9990234374999) == SHORTMAX, VE) // Highest to round down

CASSERT(W(399.996948242188) > SHORTMAX, WARMUP)  // Overflow gets caught
CASSERT(W(399.993896484375) == SHORTMAX, WARMUP) // Centre == max
CASSERT(W(399.990844726563) == SHORTMAX, WARMUP) // Lowest to round up
CASSERT(W(399.996948242187) == SHORTMAX, WARMUP) // Highest to round down

CASSERT(AP(29.4) > SHORTMAX, AFR) // Overflow gets caught
CASSERT(AP(14.7) == LR(1.0), AFR) // Matches lambda macro
CASSERT(AP(7.35) == LR(0.5), AFR) // Matches lambda macro
CASSERT(AP(0) == 0, AFR)          // Minimum is OK


// TODO Add checks for the IT() macro once new format is setup


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file TYPE_CHECKS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
