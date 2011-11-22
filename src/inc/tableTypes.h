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
 * @brief Table struct typedefs
 *
 * This file contains all of the tabular struct typedefs.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_TABLE_TYPES_H_SEEN
#define FILE_TABLE_TYPES_H_SEEN


#define TWODTABLEUS_LENGTH 16
/// This block used for various curves
typedef struct {
	unsigned short Axis[TWODTABLEUS_LENGTH];
	unsigned short Values[TWODTABLEUS_LENGTH];
} twoDTableUS;


#define MAINTABLE_RPM_LENGTH 16       ///< How many cells on the X axis Should be, will be and was 24
#define MAINTABLE_LOAD_LENGTH 16      ///< How many cells on the Y axis Should be, will be and was 19
#define MAINTABLE_MAX_RPM_LENGTH 27   ///< How many cells on the X axis max
#define MAINTABLE_MAX_LOAD_LENGTH 21  ///< How many cells on the Y axis max
#define MAINTABLE_MAX_MAIN_LENGTH 462 ///< 924B 462 shorts maximum main table length


/**	Main Table Structure definition
 *
 * Use this table descriptor to manage the
 * - main VE table
 * - Lambda table
 * - Timing tables
 *
 * Tables can be made any size from 1x1 to 27x17 or 22x21 provided that the multiple of
 * the two doesn't exceed the max main length and neither axis exceeds it's
 * specified maximum.
 *
 * For a more detailed discussion of how this structure is actually used...
 *
 * @see lookupPagedMainTableCellValue
 */
typedef struct {
	unsigned short RPMLength;                        ///< The length of the RPM axis array
	unsigned short LoadLength;                       ///< The length of the Load axis array
	unsigned short RPM[MAINTABLE_MAX_RPM_LENGTH];    ///< The array of RPM (X) axis values
	unsigned short Load[MAINTABLE_MAX_LOAD_LENGTH];  ///< The array of Load (Y) axis values
	unsigned short Table[MAINTABLE_MAX_MAIN_LENGTH]; ///< The table as an array of values
} mainTable;


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file TABLE_TYPES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
