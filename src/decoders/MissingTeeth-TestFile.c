/*	FreeEMS - the open source engine management system

	Copyright 2011 Fred Cooke

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


/** @file
 *
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief For test purposes only!
 *
 * Just something convenient to hack on without interfering with working files.
 * To be removed once MissingTeeth decoder development is more mature.
 */


#define DECODER_IMPLEMENTATION_C
//#define CRANK_ONLY
#define CAM_ONLY
//#define CRANK_WITH_CAM_SYNC
#define TOTAL_TEETH   24
#define MISSING_TEETH  1

#include "inc/MissingTeeth.h"
#include "code/MissingTeeth-Either-XminusY.c"
