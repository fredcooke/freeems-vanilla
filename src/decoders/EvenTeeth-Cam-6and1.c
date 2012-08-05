/* FreeEMS - the open source engine management system
 *
 * Copyright 2012 Fred Cooke
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
 * @brief For evenly spaced teeth on the camshaft with a single second input.
 *
 * This is suitable for engines such as the GM DIS Wasted Spark Ignition engines
 * with 3x TACH output which would equal 3 teeth on the crank and equal for
 * something with 6 on the cam. Sync is provided by the second input from the
 * CAM 1x sensor allowing a sequential and/or COP/CNP setup to be used.
 *
 * @see EvenTeeth-Xand1.c
 */


#define DECODER_IMPLEMENTATION_C
#define WITH_CAM_SYNC
#define NUMBER_OF_EVENTS_ON_CAM 6

#include "inc/EvenTeeth-Xand1.h"
const unsigned char eventValidForCrankSync[] = {1,1,1,1,1,1}; // Unused for now, but correct anyway.
#include "code/EvenTeeth-Xand1.c"
