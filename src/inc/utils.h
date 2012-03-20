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
#ifndef FILE_UTILS_H_SEEN
#define FILE_UTILS_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef UTILS_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN unsigned short safeAdd(unsigned short, unsigned short);
EXTERN unsigned short safeTrim(unsigned short, signed short);
EXTERN unsigned short safeScale(unsigned short, unsigned short, unsigned short);

EXTERN void sleep(unsigned short) FPAGE_FE;
EXTERN void sleepMicro(unsigned short) FPAGE_FE;

EXTERN void adjustPWM(void) FPAGE_FE;
EXTERN void setupPagedRAM(unsigned char) FPAGE_F8;

EXTERN void sampleEachADC(ADCBuffer*) FPAGE_F8;
EXTERN void sampleLoopADC(ADCBuffer*) FPAGE_F8;
//EXTERN void sampleBlockADC(ADCBuffer*) FPAGE_F8; broken, do not use

EXTERN unsigned char checksum(unsigned char *, unsigned short) FPAGE_F8;
EXTERN unsigned short stringCopy(unsigned char*, unsigned char*) FPAGE_F8;
EXTERN unsigned short compare(unsigned char*, unsigned char*, unsigned short); // In unpaged flash as it needs to compare paged flash with unpaged things


#undef EXTERN


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file UTILS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
