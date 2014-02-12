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
 * @ingroup interruptHandlers
 *
 * @brief XGATE Interrupt Vector Table
 *
 * This file contains the definition of the XGATE interrupt vector table.
 * This table consists only of pointers to xgate code blocks which are by
 * definition void. These will be called by the hardware when an interrupt
 * of a certain type occurs.
 *
 * @author Sean Keys
 */


#define XGATEVECTORS_C
#include "inc/freeEMS.h"
#include "inc/xgateVectors.h"


/* Currently this gets copied from wherever it ends up into the XGATE flash pages */
const xgateIntVector xgateIntVectorTable[] PPAGE_E0X = {
		/* Channel ID = vector address offset / 4 */
		/* channel 0x00-0x08 are not used, 0x09-0x1D are reserved first used must match macro XGATE_VECTOR_OFFSET in xgate.h */
		{XGATE_ERROR_HANDLER, 0x00},  /* NOT USED */
		{XGATE_ERROR_HANDLER, 0x01},  /* NOT USED */
		{XGATE_ERROR_HANDLER, 0x02},  /* NOT USED */
		{XGATE_ERROR_HANDLER, 0x03},  /* NOT USED */
		{XGATE_ERROR_HANDLER, 0x04},  /* NOT USED */
		{XGATE_ERROR_HANDLER, 0x05},  /* NOT USED */
		{XGATE_ERROR_HANDLER, 0x06},  /* NOT USED */
		{XGATE_ERROR_HANDLER, 0x07},  /* NOT USED */
		{XGATE_ERROR_HANDLER, 0x08},  /* NOT USED */
		{XGATE_ERROR_HANDLER, 0x09},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x0A},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x0B},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x0C},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x0D},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x0E},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x0F},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x10},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x11},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x12},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x13},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x14},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x15},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x16},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x17},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x18},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x19},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x1A},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x1B},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x1C},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x1D},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x1E},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x1F},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x20},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x21},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x22},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x23},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x24},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x25},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x26},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x27},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x28},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x29},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x2A},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x2B},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x2C},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x2D},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x2E},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x2F},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x30},  // special    - Reserved S12XCPU RAM access violation
		{XGATE_ERROR_HANDLER, 0x31},  // special    - Reserved XGATE software error interrupt
		{XGATE_ERROR_HANDLER, 0x32},  // Channel 32 - XGATE Software Trigger 7
		{XGATE_ERROR_HANDLER, 0x33},  // Channel 33 - XGATE Software Trigger 6
		{XGATE_ERROR_HANDLER, 0x34},  // Channel 34 - XGATE Software Trigger 5
		{XGATE_ERROR_HANDLER, 0x35},  // Channel 35 - XGATE Software Trigger 4
		{XGATE_ERROR_HANDLER, 0x36},  // Channel 36 - XGATE Software Trigger 3
		{XGATE_ERROR_HANDLER, 0x37},  // Channel 37 - XGATE Software Trigger 2
		{XGATE_ERROR_HANDLER, 0x38},  // Channel 38 - XGATE Software Trigger 1
		{(unsigned short)xgateSchedule, (unsigned short)&PORTP}, // Channel 39 - XGATE Software Trigger 0 address in first field is from xgate linear 64k point of view. The VMA MUST BE CHANGED IN THE COPYOPTS PORTION OF THE MAKEFILE to reflect how xgate see's this section
		{XGATE_ERROR_HANDLER, 0x3A},  // Channel 3A - Periodic Interrupt Timer 3
		{(unsigned short)xgateDelayCounter, 0x3B},  // Channel 3B - Periodic Interrupt Timer 2
		{(unsigned short)xgatePITTurnOff, 0x3C},  // Channel 3C - Periodic Interrupt Timer 1
		{(unsigned short)xgatePITTurnOn, 0x3D},  // Channel 3D - Periodic Interrupt Timer 0
		{XGATE_ERROR_HANDLER, 0x3E},  // Reserved
		{XGATE_ERROR_HANDLER, 0x3F},  // Channel 3F - Autonomous Periodical interrupt API
		{XGATE_ERROR_HANDLER, 0x40},  // Channel 40 - Low Voltage interrupt LVI
		{XGATE_ERROR_HANDLER, 0x41},  // Channel 41 - IIC1 Bus
		{XGATE_ERROR_HANDLER, 0x42},  // Channel 42 - SCI5
		{XGATE_ERROR_HANDLER, 0x43},  // Channel 43 - SCI4
		{XGATE_ERROR_HANDLER, 0x44},  // Channel 44 - SCI3
		{XGATE_ERROR_HANDLER, 0x45},  // Channel 45 - SCI2
		{XGATE_ERROR_HANDLER, 0x46},  // Channel 46 - PWM Emergency Shutdown
		{XGATE_ERROR_HANDLER, 0x47},  // Channel 47 - Port P Interrupt
		{XGATE_ERROR_HANDLER, 0x48},  // Channel 48 - CAN4 transmit
		{XGATE_ERROR_HANDLER, 0x49},  // Channel 49 - CAN4 receive
		{XGATE_ERROR_HANDLER, 0x4A},  // Channel 4A - CAN4 errors
		{XGATE_ERROR_HANDLER, 0x4B},  // Channel 4B - CAN4 wake-up
		{XGATE_ERROR_HANDLER, 0x4C},  // Channel 4C - CAN3 transmit
		{XGATE_ERROR_HANDLER, 0x4D},  // Channel 4D - CAN3 receive
		{XGATE_ERROR_HANDLER, 0x4E},  // Channel 4E - CAN3 errors
		{XGATE_ERROR_HANDLER, 0x4F},  // Channel 4F - CAN3 wake-up
		{XGATE_ERROR_HANDLER, 0x50},  // Channel 50 - CAN2 transmit
		{XGATE_ERROR_HANDLER, 0x51},  // Channel 51 - CAN2 receive
		{XGATE_ERROR_HANDLER, 0x52},  // Channel 52 - CAN2 errors
		{XGATE_ERROR_HANDLER, 0x53},  // Channel 53 - CAN2 wake-up
		{XGATE_ERROR_HANDLER, 0x54},  // Channel 54 - CAN1 transmit
		{XGATE_ERROR_HANDLER, 0x55},  // Channel 55 - CAN1 receive
		{XGATE_ERROR_HANDLER, 0x56},  // Channel 56 - CAN1 errors
		{XGATE_ERROR_HANDLER, 0x57},  // Channel 57 - CAN1 wake-up
		{XGATE_ERROR_HANDLER, 0x58},  // Channel 58 - CAN0 transmit
		{XGATE_ERROR_HANDLER, 0x59},  // Channel 59 - CAN0 receive
		{XGATE_ERROR_HANDLER, 0x5A},  // Channel 5A - CAN0 errors
		{XGATE_ERROR_HANDLER, 0x5B},  // Channel 5B - CAN0 wake-up
		{XGATE_ERROR_HANDLER, 0x5C},  // Channel 5C - FLASH
		{XGATE_ERROR_HANDLER, 0x5D},  // Channel 5D - EEPROM
		{XGATE_ERROR_HANDLER, 0x5E},  // Channel 5E - SPI2
		{XGATE_ERROR_HANDLER, 0x5F},  // Channel 5F - SPI1
		{XGATE_ERROR_HANDLER, 0x60},  // Channel 60 - IIC0 Bus
		{XGATE_ERROR_HANDLER, 0x61},  // RESERVED
		{XGATE_ERROR_HANDLER, 0x62},  // Channel 62 - CRG Self Clock Mode
		{XGATE_ERROR_HANDLER, 0x63},  // Channel 63 - CRG PLL lock
		{XGATE_ERROR_HANDLER, 0x64},  // Channel 64 - Pulse Accumulator B Overflow
		{XGATE_ERROR_HANDLER, 0x65},  // Channel 65 - Modulus Down Counter underflow
		{XGATE_ERROR_HANDLER, 0x66},  // Channel 66 - Port H
		{XGATE_ERROR_HANDLER, 0x67},  // Channel 67 - Port J
		{XGATE_ERROR_HANDLER, 0x68},  // Channel 68 - ATD1
		{XGATE_ERROR_HANDLER, 0x69},  // Channel 69 - ATD0
		{XGATE_ERROR_HANDLER, 0x6A},  // Channel 6A - SCI1
		{XGATE_ERROR_HANDLER, 0x6B},  // Channel 6B - SCI0
		{XGATE_ERROR_HANDLER, 0x6C},  // Channel 6C - SPI0
		{XGATE_ERROR_HANDLER, 0x6D},  // Channel 6D - ECT Pulse accumulator input edge
		{XGATE_ERROR_HANDLER, 0x6E},  // Channel 6E - ECT Pulse accumulator A overflow
		{XGATE_ERROR_HANDLER, 0x6F},  // Channel 6F - Enhanced Capture Timer overflow
		{XGATE_ERROR_HANDLER, 0x70},  // Channel 70 - Enhanced Capture Timer channel 7
		{XGATE_ERROR_HANDLER, 0x71},  // Channel 71 - Enhanced Capture Timer channel 6
		{XGATE_ERROR_HANDLER, 0x72},  // Channel 72 - Enhanced Capture Timer channel 5
		{XGATE_ERROR_HANDLER, 0x73},  // Channel 73 - Enhanced Capture Timer channel 4
		{XGATE_ERROR_HANDLER, 0x74},  // Channel 74 - Enhanced Capture Timer channel 3
		{XGATE_ERROR_HANDLER, 0x75},  // Channel 75 - Enhanced Capture Timer channel 2
		{XGATE_ERROR_HANDLER, 0x76},  // Channel 76 - Enhanced Capture Timer channel 1
		{XGATE_ERROR_HANDLER, 0x77},  // Channel 77 - Enhanced Capture Timer channel 0
		{XGATE_ERROR_HANDLER, 0x78}  // Channel 78 - Real Time Interrupt
};
