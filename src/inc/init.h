/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010 Fred Cooke
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
#ifndef FILE_INIT_H_SEEN
#define FILE_INIT_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef INIT_C
#define EXTERN
/* For private internal use of init.c init() function only, hence wrapped in this ifdef */

/* Keep this non ISR stuff out of linear flash space */
void initPLL(void) FPAGE_FE;
void initIO(void) FPAGE_FE;
void initAllPagedRAM(void) FPAGE_FE;
void initAllPagedAddresses(void) FPAGE_FE;
void initVariables(void) FPAGE_FE;
void initFlash(void) FPAGE_FE;
void initXgate(void) TEXT1; // Can't be paged because it has to burn to a page, for now...
void initECTTimer(void) FPAGE_FE;
void initPITTimer(void) FPAGE_FE;
void initSCIStuff(void) FPAGE_FE;
void initConfiguration(void) FPAGE_FE;
void initInterrupts(void) FPAGE_FE;

// XGATE assembly symbols, only used for address/size
extern void xgateThread0(void);
extern void xgateThread0End(void);

/* Place these functions in the same block of flash as the data upon which they operate! */
void initLookupAddresses(void) LOOKUPF;
void initFuelAddresses(void) FUELTABLESF;
void initTimingAddresses(void) TIMETABLESF;
void initTunableAddresses(void) TUNETABLESF;
void initPagedRAMFuel(void) FUELTABLESF;
void initPagedRAMTime(void) TIMETABLESF;
void initPagedRAMTune(void) TUNETABLESF;

#else
#define EXTERN extern
#endif


/* Other function declarations are private and present in the C		*/
/* source file purely to assign them to a particular memory region.	*/
EXTERN void init(void) FPAGE_FE;


/* Various masks and values used for initialising the contents of control registers.	*/
/* For information on how these are being used, try this link :							*/
/* http://www.vipan.com/htdocs/bitwisehelp.html											*/


// PLL control values
#define PLLLOCK			0x08 /* Mask for checking to see when the PLL loop is locked onto its target */
#define PLLSELOFF		0x7F /* Mask for switching to base external OSCCLK clock 0b_0111_1111 */
#define PLLSELON		0x80 /* Mask for switching to internally multiplied PLL clock 0b_1000_0000 */
#define PLLOFF			0xBF /* Mask for turning the PLLON bit to ZERO 0b_1011_1111, IE, turning PLL off */
#define PLLON			0x40 /* Mask for setting PLLON bit to ONE  0b_0100_0000, IE, turning PLL on */
#define PLLDIVISOR		0x03 /* Input crystal frequency is divided by this number */
#define PLLMULTIPLIER	0x09 /* The result of the above is multiplied by this number to give the bus frequency */

// Flash control values
#define PRDIV8			0x40 /* Mask for flash module to divide the oscillator clock by 8  */


/// @todo TODO define other macros such that raw values aren't used in the code
/// @todo TODO move all the reg masks to a header of their own for general use.


#undef EXTERN


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file INIT_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
