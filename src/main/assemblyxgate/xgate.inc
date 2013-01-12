/* FreeEMS - the open source engine management system
 *
 * Copyright 2009, 2010 Sean Keys, Fred Cooke
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

/* Flag Masks */ 
.equ	SW_ISR_ZERO_CFLAG_MASK, 0x0100
.equ	PIT0_CFLAG_MASK, 0x0001
.equ	PIT1_CFLAG_MASK, 0x0002
.equ	PIT2_CFLAG_MASK, 0x0003

/* Registers */
.equ	SW_ISR_FLAG_REG, 0x0398
.equ	PITTF, 0x0345     /* PIT Time-Out Flag Register, low 4 bits set when each counter reaches 0 */
.equ    PITINTE, 0x0344   /* PIT Interrupt Enable Register, low four bits control the ISRs */
.equ    PITCE, 0x0342     /* PIT Channel Enable Register, low 4 bits let the channel count */
.equ    PITFLT, 0x0341    /* PIT Force Load Timer Register, low 4 bits force load timers */
.equ	PORTP, 0x0258     /* PORT-P register */
.equ	PORTBA, 0x0000	  /* PORT-BA register */
.equ	PORTB, 0x0001	  /* PORT-B register */

/* General Defines */
.equ	ZERO_OFFSET, 0x0000

/* Bit Masks */
.equ	PORTBA_PROTECTION_MASK, 0x0FFF ; only use the first 12 pins on PORTBA 


