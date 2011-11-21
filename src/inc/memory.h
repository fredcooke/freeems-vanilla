/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009 Fred Cooke
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
 * @brief Memory usage directives
 *
 * This file is solely for the definition of compiler memory usage directives.
 * Each one is just a short form of the larger statements DFAR and FFAR found
 * near the top of this file.
 *
 * @author Fred Cooke
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_MEMORY_H_SEEN
#define FILE_MEMORY_H_SEEN


/* http://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Variable-Attributes.html	*/

/* EEPROM */
//#define EEPROM __attribute__ ((section (".eeprom")))
/* EEPROM would appear to not be loadable by hcs12mem		*/
/* Furthermore it isn't really needed except in code anyway	*/

/* RAM divided up into special purpose blocks */
#define RWINDOW		__attribute__ ((section (".rpage")))		/* ~4k paged RAM window */
#define RXBUF		__attribute__ ((section (".rxbuf")))		/* ~2k block of RAM for receive buffer */
#define TXBUF		__attribute__ ((section (".txbuf")))		/* ~2k block of RAM for transmit buffer */
// 4k of RAM for general variable and stack use, need to put some aside for xgate!!

/* Direct flash blocks */
#define FIXEDCONF1	__attribute__ ((section (".fixedconf1"))) /*  1k unpaged block, primary static configuration.		*/
#define FIXEDCONF2	__attribute__ ((section (".fixedconf2"))) /*  1k unpaged block, secondary static configuration.		*/
#define TEXT1		__attribute__ ((section (".text1")))	  /* 14k unpaged block, must be explicitly used.			*/
#define TEXT		__attribute__ ((section (".text")))		  /* 14k unpaged block, code defaults to being stored here.	*/
/*define SERMON		__attribute__ ((section (".sermon")))	      2k unpaged block, occupied by AN2548 serial monitor. 	*/


/* far shortcut for data */
#define DFAR(label) __attribute__ ((section (label)))
/* far shortcut for functions */
#define FFAR(label) __attribute__ ((far)) __attribute__ ((section (label)))


/* Paged flash blocks for functions */
#define FPPAGE_E0X FFAR(".ppageE0X")
#define FPPAGE_E0S FFAR(".ppageE0S")
#define FPPAGE_E1 FFAR(".ppageE1")
#define FPPAGE_E2 FFAR(".ppageE2")
#define FPPAGE_E3 FFAR(".ppageE3")
#define FPPAGE_E4 FFAR(".ppageE4")
#define FPPAGE_E5 FFAR(".ppageE5")
#define FPPAGE_E6 FFAR(".ppageE6")
#define FPPAGE_E7 FFAR(".ppageE7")
#define FPPAGE_E8 FFAR(".ppageE8")
#define FPPAGE_E9 FFAR(".ppageE9")
#define FPPAGE_EA FFAR(".ppageEA")
#define FPPAGE_EB FFAR(".ppageEB")
#define FPPAGE_EC FFAR(".ppageEC")
#define FPPAGE_ED FFAR(".ppageED")
#define FPPAGE_EE FFAR(".ppageEE")
#define FPPAGE_EF FFAR(".ppageEF")
#define FPPAGE_F0 FFAR(".ppageF0")
#define FPPAGE_F1 FFAR(".ppageF1")
#define FPPAGE_F2 FFAR(".ppageF2")
#define FPPAGE_F3 FFAR(".ppageF3")
#define FPPAGE_F4 FFAR(".ppageF4")
#define FPPAGE_F5 FFAR(".ppageF5")
#define FPPAGE_F6 FFAR(".ppageF6")
#define FPPAGE_F7 FFAR(".ppageF7")

/* Paged flash blocks for data */
#define PPAGE_E0S DFAR(".ppageE0S")
#define PPAGE_E0X DFAR(".ppageE0X")
#define PPAGE_E1 DFAR(".ppageE1")
#define PPAGE_E2 DFAR(".ppageE2")
#define PPAGE_E3 DFAR(".ppageE3")
#define PPAGE_E4 DFAR(".ppageE4")
#define PPAGE_E5 DFAR(".ppageE5")
#define PPAGE_E6 DFAR(".ppageE6")
#define PPAGE_E7 DFAR(".ppageE7")
#define PPAGE_E8 DFAR(".ppageE8")
#define PPAGE_E9 DFAR(".ppageE9")
#define PPAGE_EA DFAR(".ppageEA")
#define PPAGE_EB DFAR(".ppageEB")
#define PPAGE_EC DFAR(".ppageEC")
#define PPAGE_ED DFAR(".ppageED")
#define PPAGE_EE DFAR(".ppageEE")
#define PPAGE_EF DFAR(".ppageEF")
#define PPAGE_F0 DFAR(".ppageF0")
#define PPAGE_F1 DFAR(".ppageF1")
#define PPAGE_F2 DFAR(".ppageF2")
#define PPAGE_F3 DFAR(".ppageF3")
#define PPAGE_F4 DFAR(".ppageF4")
#define PPAGE_F5 DFAR(".ppageF5")
#define PPAGE_F6 DFAR(".ppageF6")
#define PPAGE_F7 DFAR(".ppageF7")

/* ONLY use the pages below this line for now (Or you won't be able to load them...) */

/* General Purpose Page with PPAGE = 0xF8 */
#define FPAGE_F8 FFAR(".fpageF8")
#define DPAGE_F8 DFAR(".dpageF8")
#define PAGE_F8_PPAGE 0xF8

/* Function and large lookup tables for ADC to value mapping */
#define LOOKUPF FFAR(".fpageF9")
#define LOOKUPD DFAR(".dpageF9")
#define LOOKUP_PPAGE 0xF9

/* Fuel tables and the function for copying it up to RAM */
#define FUELTABLESF FFAR(".fpageFA")
#define FUELTABLESD DFAR(".dpageFA")
#define FUELTABLES_PPAGE 0xFA

/* Tunable tables etc and the function for copying them up to RAM */
#define TUNETABLESF FFAR(".fpageFB")
#define TUNETABLESD1 DFAR(".dpageFB1")
#define TUNETABLESD2 DFAR(".dpageFB2")
#define TUNETABLESD3 DFAR(".dpageFB3")
#define TUNETABLESD4 DFAR(".dpageFB4")
#define TUNETABLESD5 DFAR(".dpageFB5")
#define TUNETABLESD6 DFAR(".dpageFB6")
#define TUNETABLESD7 DFAR(".dpageFB7")
#define TUNETABLESD8 DFAR(".dpageFB8")
#define TUNETABLES_PPAGE 0xFB

/* Timing tables and the function for copying them up to RAM */
#define TIMETABLESF FFAR(".fpageFC")
#define TIMETABLESD DFAR(".dpageFC")
#define TIMETABLES_PPAGE 0xFC

/* General Purpose Page with PPAGE = 0xFE */
#define FPAGE_FE FFAR(".ppageFE")	/* This is the block that is present in the page window using linear addressing, represents 0x8000 - 0xBFFF ("text2" paged) */
#define DPAGE_FE DFAR(".ppageFE")	/* This is the block that is present in the page window using linear addressing, represents 0x8000 - 0xBFFF ("text2" paged) */
//#define FPAGE_FD FFAR(".ppageFD")	/* Represents 0x4000 - 0x7FFF ("text1" paged) */
//#define DPAGE_FD DFAR(".ppageFD")	/* Represents 0x4000 - 0x7FFF ("text1" paged) */
//#define FPAGE_FF FFAR(".ppageFF")	/* Represents 0xC000 - 0xFFFF ("text" paged) */
//#define DPAGE_FF DFAR(".ppageFF")	/* Represents 0xC000 - 0xFFFF ("text" paged) */
/* The previous four lines are included for clarity only. */
/* Changes to the memory layout should be reflected in memory.x and Makefile also */


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file MEMORY_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
