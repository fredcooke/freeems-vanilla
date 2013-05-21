/* FreeEMS - the open source engine management system
 *
 * Copyright 2013 Fred Cooke
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
 *
 * @brief MC9S12XDP512 flag definitions
 *
 * This is the flag header for the FreeScale MC9S12XDP512 MCU. It contains
 * a unified set of masks to be used with configuration registers.
 *
 * These are taken from MC9S12XDP512V2.pdf Appendix G, note some are shared across multiple registers.
 */


/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_FLAGS_H_SEEN
#define FILE_9S12XDP512_FLAGS_H_SEEN


// CRGFLG
#define RTIF          BIT7 // Mask for clearing the Real Time Interrupt flag
#define PORF          BIT6 // Mask for checking to see whether this was a fresh start, or not
#define LVRF          BIT5 // Mask for checking to see whether this was a post-low-Voltage start, or not
#define PLLLOCKIF     BIT4 // Mask for clearing the PLL Lock Interrupt flag
#define PLLLOCK       BIT3 // Mask for checking to see when the PLL is locked onto its target
#define PLLTRACK      BIT2 // Mask for checking to see when the PLL is tracking its target
#define SCMIF         BIT1 // Mask for clearing the Self Clock Mode Interrupt flag
#define SCM           BIT0 // Mask for checking to see whether we're in Self Clock Mode, or not

// CRGINT
#define RTIE          BIT7 // TODO
#define ILAF          BIT6 // TODO
//#define 0           BIT5 // Reserved
#define PLLLOCKIE     BIT4 // TODO
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
#define SCMIE         BIT1 // TODO
//#define 0           BIT0 // Reserved

// CLKSEL
#define PLLSEL        BIT7 // Mask for selecting internally multiplied PLL clock mode
#define PSTP          BIT6 // TODO
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
#define PLLWAI        BIT3 // TODO
//#define 0           BIT2 // Reserved
#define RTIWAI        BIT1 // TODO
#define COPWAI        BIT0 // TODO

// PLLCTL
#define CME           BIT7 // TODO
#define PLLON         BIT6 // Mask for turning PLL circuitry on
#define PLLAUTO       BIT5 // TODO
#define ACQ           BIT4 // TODO
#define FSTWKP        BIT3 // TODO
#define PRE           BIT2 // TODO
#define PCE           BIT1 // TODO
#define SCME          BIT0 // TODO

// RAMWPC
#define RPWE          BIT7 // TODO
//#define 0           BIT6 // Reserved
//#define 0           BIT5 // Reserved
//#define 0           BIT4 // Reserved
//#define 0           BIT3 // Reserved
//#define 0           BIT2 // Reserved
#define AVIE          BIT1 // TODO
#define AVIF          BIT0 // TODO

// XGMCTL
#define XGEM          BIT15_16 // TODO
#define XGFRZM        BIT14_16 // TODO
#define XGDBGM        BIT13_16 // TODO
#define XGSSM         BIT12_16 // TODO
#define XGFACTM       BIT11_16 // TODO
//#define 0           BIT10_16 // Reserved
#define XGSWEIFM      BIT9_16  // TODO
#define XGIEM         BIT8_16  // TODO
#define XGE           BIT7_16  // TODO
#define XGFRZ         BIT6_16  // TODO
#define XGDBG         BIT5_16  // TODO
#define XGSS          BIT4_16  // TODO
#define XGFACT        BIT3_16  // TODO
//#define 0           BIT2_16  // Reserved
#define XGSWEIF       BIT1_16  // TODO
#define XGIE          BIT0_16  // TODO


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file 9S12XDP512_FLAGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
