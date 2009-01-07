/*	Copyright 2008 Fred Cooke

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
	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/

	We ask that if you make any changes to this file you email them upstream to
	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!

	Thank you for choosing FreeEMS to run your engine! */


/**	@file injectionISRs.h
 * @ingroup allHeaders
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_INJECTION_ISRS_H_SEEN
#define FILE_INJECTION_ISRS_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef INJECTIONISRS_C
#define EXTERN
#else
#define EXTERN extern
#endif


/* Staged injector channel bit masks and registers */

/* Use port K for staged injector output */
#define STAGEDPORT PORTK

/* Masks for setting and checking stagedOn status var and turning the channel on */
#define STAGED1ON BIT0
#define STAGED2ON BIT1
#define STAGED3ON BIT2
#define STAGED4ON BIT3
#define STAGED5ON BIT4
#define STAGED6ON BIT5

/* Masks for unsetting stagedOn status var and turning the channel off */
#define STAGED1OFF NBIT0
#define STAGED2OFF NBIT1
#define STAGED3OFF NBIT2
#define STAGED4OFF NBIT3
#define STAGED5OFF NBIT4
#define STAGED6OFF NBIT5

/* Internal use to decide if staged is actually required or not based on pulsewidth etc */
unsigned char stagedRequired;


#undef EXTERN


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file INJECTION_ISRS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
