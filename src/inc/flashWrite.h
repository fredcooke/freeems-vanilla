/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009 Sean Keys
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
#ifndef FILE_FLASHWRITE_H_SEEN
#define FILE_FLASHWRITE_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef FLASHWRITE_C
#define EXTERN
#else
#define EXTERN extern
#endif


/// @todo TODO add mass erase function and replace ?? with the real value
#define MASS_ERASE  	0x?? /* Used to erase 128k flash blocks */
#define WORD_PROGRAM	0x20 /* Word = 2 bytes, this is the minimum write size, 64K of these per block, 512 per sector	*/
#define SECTOR_ERASE	0x40 /* Sector = 1024 bytes, there are 128 sectors to a block, and 4 blocks to the chip			*/
/// @todo TODO CBEIF mask hash define - is this still needed?


/* The following code must run from unpaged space for obvious reasons. Location explicitly set to text. */
EXTERN unsigned short writeWord(unsigned short*, unsigned short) TEXT;
EXTERN unsigned short eraseSector(unsigned char, unsigned short*) TEXT;
EXTERN unsigned short writeSector(unsigned char, unsigned short*, unsigned char, unsigned short*) TEXT;
EXTERN unsigned short writeBlock(blockDetails*, void*) TEXT;


#undef EXTERN


#else
	/* let us know ifunsigned short writeBlock(unsigned short* flashAddr, unsigned short* RAMAddr, unsigned short size){
	 *  we are being untidy with headers */
	#warning "Header file FLASHWRITE_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
