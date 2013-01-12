/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2012 Fred Cooke
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
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Template showing how to setup each available type of even tooth decoder.
 *
 * If copying this file to make a new decoder variant, please edit this comment block to describe the purpose.
 *
 * @see EvenTeeth-Xand1.c
 */


#define DECODER_IMPLEMENTATION_C


// Uncomment ONE of these ONLY! Edit values to suit.

// TEST dizzy 4 cyl use (early 4AGE engine)
//#define WITH_COMBUSTION_SYNC
//#define NUMBER_OF_EVENTS_PER_SYNC 6
//#define CYLINDER_COUNT 4
//#define TOTAL_EVENT_COUNT 24

// OR

// TEST crank use
//#define WITH_CRANK_SYNC
//#define NUMBER_OF_EVENTS_ON_CRANK 12

// OR

// TEST cam use
//#define WITH_CAM_SYNC
//#define NUMBER_OF_EVENTS_ON_CAM 24


#include "inc/EvenTeeth-Xand1.h"
#include "code/EvenTeeth-Xand1.c"
