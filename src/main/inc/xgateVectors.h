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

/** @file
 *
 * @ingroup xgateFiles
 * @ingroup xgateHeaders
 *
 * @brief C header for assembly xgate functions
 *
 * Because we need to call the assembly flash burning function from C code an
 * extern function declaration is required to allow successful compilation.
 *
 * @author Sean Keys
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

#define START_OF_FLASH_WINDOW            (unsigned short*)0x8000 /* 16KB long */
#define START_OF_RAM_WINDOW              (unsigned short*)0x1000 /* 4KB long  */
#define XGATE_RAM_ALLOCATION_SIZE        0x0200 /* 512Bytes */
#define RPAGE_TUNE_TWO_WINDOW_DIFFERENCE (0x8000) /*xgate RPAGE2 starts at 0x9000 but the s12 window starts at 0x10000 */
#define XGATE_INTERRUPT                  0x80
#define PRIORITY_LEVEL_ONE               0x01

#define ROUTE_INTERRUPT(channel_id, cpu_assignment, priority) \
        INT_CFADDR = (channel_id * 2) & 0xF0;                 \
        INT_CFDATA_ARR[((channel_id * 2) & 0x0F) >> 1] = (cpu_assignment | priority);

typedef struct {
	unsigned short programCounterValue; /* This data is forced into the XGATE PC register */
	unsigned short initialVariable; /* This data is forced into the XGATE R1 register */
} xgateIntVector;

// This statement imports the symbol from the xgate ASM for use in the vector table
void xgateSchedule();
void xgatePITTurnOff();
void xgatePITTurnOn();
void xgateDelayCounter();
void startXGATECode();
void endXGATECode();
void parameterGuard(); /* counter that gets update when a write to shared RAM begins and again when the write is complete */

EXTERN const xgateIntVector xgateIntVectorTable[121];


// Xgate control value
#define XGATE_ERROR_HANDLER 0x0000 /* TODO Create the XGATE error handling thread in asm. */


#else
        /* let us know if we are being untidy with headers */
        #warning "Header file XGATEVECTORS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
