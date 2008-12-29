/*	init.h

	Copyright 2008 Fred Cooke

	This file is part of the FreeEMS project.

	FreeEMS software is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FreeEMS software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with any FreeEMS software.  If not, see <http://www.gnu.org/licenses/>.

	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org

	Thank you for choosing FreeEMS to run your engine! */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_INIT_H_SEEN
#define FILE_INIT_H_SEEN

#ifdef INIT_C
#define EXTERN
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

// TODO define other macros such that raw values aren't used in the code

#undef EXTERN

#else
	/* let us know if we are being untidy with headers */
	#warning "Header file INIT_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
