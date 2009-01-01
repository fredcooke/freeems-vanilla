/*	derivedVarsGenerator.h

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
	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/

	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org

	Thank you for choosing FreeEMS to run your engine! */

/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_DERIVEDVARSGENERATOR_H_SEEN
#define FILE_DERIVEDVARSGENERATOR_H_SEEN

#ifdef DERIVEDVARSGENERATOR_C
#define EXTERN
#else
#define EXTERN extern
#endif

EXTERN void generateDerivedVars(void) FPAGE_FE;

#undef EXTERN

#else
	/* let us know if we are being untidy with headers */
	#warning "Header file DERIVEDVARSGENERATOR_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
