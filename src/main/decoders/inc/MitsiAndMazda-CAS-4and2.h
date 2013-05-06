/* FreeEMS - the open source engine management system
 *
 * Copyright 2012-2013 Fred Cooke
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
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Unique MitsiCAS-4and2 setup data and variables
 *
 * Development thread: http://forum.diyefi.org/viewtopic.php?f=56&t=1110
 */


#define DECODER_MAX_CODE_TIME    100 // To be optimised (shortened)!
#define NUMBER_OF_REAL_EVENTS     12
#define NUMBER_OF_VIRTUAL_EVENTS  12


#include "../../inc/freeEMS.h"
#include "../../inc/utils.h"
#include "../../inc/interrupts.h"
#include "../../inc/decoderInterface.h"


// Variables unique to this decoder, should be kept to a minimum!
static unsigned short edgeTimeStamp; /// @todo TODO why is this here, and why is it static/shared, investigate
static LongTime timeStamp; /// @todo TODO why is this here, and why is it static/shared, investigate
unsigned char doubleHighSeen = 0;


// Slot angles used below
#define OuterSlotAngle ANGLE( 69.74)
#define LargeInnerSlotAngle ANGLE(140.00)
#define SmallInnerSlotAngle ANGLE(70.00) // TODO @todo fine tune!

// Outer slot fixed events - these are, by definition, correct!
#define E0 ANGLE(  0)
#define E3 ANGLE(180)
#define E6 ANGLE(360)
#define E9 ANGLE(540)

// These are offset from the fixed ones by the angle of the slot
#define  E1 (E0 + OuterSlotAngle)
#define  E5 (E3 + OuterSlotAngle)
#define  E7 (E6 + OuterSlotAngle)
#define E10 (E9 + OuterSlotAngle)

// Large inner slot events
#define E8 ANGLE(525.50)
#define E11 (E8 + LargeInnerSlotAngle)

// Small inner slot events
#define E2 E8 - ANGLE(360) // TODO verify this is really exactly 360 including diffraction effects
#define E4 (E2 + SmallInnerSlotAngle)


// Definitions of decoder interface constants
const unsigned short eventAngles[] = {E0, E1, E2, E3, E4, E5, E6, E7, E8, E9, E10, E11};
const unsigned char eventValidForCrankSync[] = {1,1,1,1,1,1,0,1,1,0}; // Unused for now, but correct anyway.
