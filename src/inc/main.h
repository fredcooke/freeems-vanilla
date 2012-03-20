/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
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
#ifndef FILE_MAIN_H_SEEN
#define FILE_MAIN_H_SEEN


#include "freeEMS.h"
#include "interrupts.h"
#include "utils.h"
#include "init.h"
#include "commsISRs.h"
#include "commsCore.h"
#include "coreVarsGenerator.h"
#include "derivedVarsGenerator.h"
#include "fuelAndIgnitionCalcs.h"
#include "outputScheduler.h"
#include "decoderInterface.h"
#include "tableLookup.h"


/* Computer Operating Properly reset sequence MC9S12XDP512V2.PDF Section 2.4.1.5 */
#define COP_RESET1 0x55
#define COP_RESET2 0xAA

// method of ensuring no duplicate logs are sent.
unsigned short lastCalcCount;


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file MAIN_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
