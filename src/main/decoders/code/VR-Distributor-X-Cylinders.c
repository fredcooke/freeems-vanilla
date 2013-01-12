/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2011 Fred Cooke
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
 * @brief Reads any signal that is once per cylinder and only has one good edge.
 *
 * This file contains the two interrupt service routines required for to build
 * cleanly. However, only the first one is used due to the simple nature of it.
 */


#define DECODER_IMPLEMENTATION_C
#define DECODER_MAX_CODE_TIME    100 // To be optimised (shortened)!
#define NUMBER_OF_REAL_EVENTS     1
#define NUMBER_OF_VIRTUAL_EVENTS  4

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"
#include "../inc/utils.h"

void decoderInitPreliminary(){} // This decoder works with the defaults
void perDecoderReset(){} // Nothing special to reset for this code

const unsigned short eventAngles[] = {0,180,360,540};
const unsigned char eventValidForCrankSync[] = {0,0,0,0};


#include "../inc/defaultPrimaryRPMISR.c"
#include "../inc/defaultSecondaryRPMISR.c"
