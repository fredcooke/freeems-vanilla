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
 * This is suitable for engines such as the Yamaha R1 with 8 teeth on the crank
 * and equally for something with 16 on the cam. Sync is provided by the second
 * input allowing a sequential and/or COP/CNP setup to be used.
 *
 * @see EvenTeeth-Both-Nand1.c
 *
 * @author Fred Cooke
 */


#define DECODER_IMPLEMENTATION_C
#define DECODER_MAX_CODE_TIME    100 // To be optimised (shortened)!
#define NUMBER_OF_REAL_EVENTS     16
#define NUMBER_OF_VIRTUAL_EVENTS  16

#include "../inc/freeEMS.h"
#include "../inc/utils.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"

const unsigned short eventAngles[] = {(0 * oneDegree), (45 * oneDegree), (90 * oneDegree), (135 * oneDegree), (180 * oneDegree), (225 * oneDegree), (270 * oneDegree), (315 * oneDegree), (360 * oneDegree), (405 * oneDegree), (450 * oneDegree), (495 * oneDegree), (540 * oneDegree), (585 * oneDegree), (630 * oneDegree), (675 * oneDegree)};
const unsigned char eventValidForCrankSync[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // Unused for now, but correct anyway.

// Bring in the actual code.
#include "code/EvenTeeth-Both-Xand1.c"
