/* FreeEMS - the open source engine management system
 *
 * Copyright 2010 Sean Keys, Fred Cooke
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

/** @file xgateVectors.h
 * @ingroup xgateHeaders
 *
 * @brief C header for assembly xgate functions
 *
 * Because we need to call the assembly flash burning function from C code an
 * extern function declaration is required to allow successful compilation.
 */
#ifndef FILE_XGATEVECTORS_H_SEEN
#define FILE_XGATEVECTORS_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef XGATEVECTORS_C
#define EXTERN
#else
#define EXTERN extern
#endif


typedef struct {
	unsigned short programCounterValue; /* This data is forced into the XGATE PC register */
	unsigned short initialVariable; /* This data is forced into the XGATE R1 register */
} xgateIntVector;

// This statement imports the symbol from the xgate ASM for use in the vector table
extern void xgateSchedule(); // extern not EXTERN because it is defined outside of C

EXTERN const xgateIntVector xgateIntVectorTable[121];


// Xgate control value
#define XGATE_ERROR_HANDLER 0x0000 /* TODO Create the XGATE error handling thread in asm. */


#else
        /* let us know if we are being untidy with headers */
        #warning "Header file XGATEVECTORS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
