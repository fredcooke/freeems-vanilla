/* FreeEMS - the open source engine management system
 *
 * Copyright 2011 Fred Cooke
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
 * This is suitable for engines with 24 evenly spaced teeth on the cam shaft which
 * is equivalent to 12 on the crank shaft. Sync is provided by the second input
 * allowing a sequential and/or COP/CNP setup to be used.
 *
 * @see EvenTeeth-Both-Nand1.c
 *
 * @author Fred Cooke
 */


#define DECODER_IMPLEMENTATION_C
#define DECODER_MAX_CODE_TIME    100 // To be optimised (shortened)!
#define NUMBER_OF_REAL_EVENTS     24
#define NUMBER_OF_VIRTUAL_EVENTS  24

#include "../inc/freeEMS.h"
#include "../inc/utils.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"

const unsigned short eventAngles[] = {(0 * oneDegree), (30 * oneDegree), (60 * oneDegree), (90 * oneDegree), (120 * oneDegree), (150 * oneDegree), (180 * oneDegree), (210 * oneDegree), (240 * oneDegree), (270 * oneDegree), (300 * oneDegree), (330 * oneDegree), (360 * oneDegree), (390 * oneDegree), (420 * oneDegree), (450 * oneDegree), (480 * oneDegree), (510 * oneDegree), (540 * oneDegree), (570 * oneDegree), (600 * oneDegree), (630 * oneDegree), (660 * oneDegree), (690 * oneDegree)};
const unsigned char eventValidForCrankSync[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // Unused for now, but correct anyway.

// Bring in the actual code.
#include "code/EvenTeeth-Both-Xand1.c"
