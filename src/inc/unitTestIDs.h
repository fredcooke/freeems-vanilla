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
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_UNIT_TEST_IDS_H_SEEN
#define FILE_UNIT_TEST_IDS_H_SEEN

// Simple test example, cross between C and Java
// unsigned short result = (unsigned short*)callTest(testID, charArray, length);
// assertEquals(testID, result);
#define testEmptyTest         0x0000 // Returns its own ID value as the result.
#define testTwoDTableUSLookup 0x0001 /// XYZ args fill out later TODO @todo


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file UNIT_TEST_IDS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
