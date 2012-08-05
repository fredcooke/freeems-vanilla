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
 * @brief For evenly spaced teeth on the cam or crank with a single second input.
 *
 * Fill out a data reverse header and include this file. Sync is provided by the
 * second input allowing a sequential and/or COP/CNP setup to be used.
 *
 * VR edition with only one edge used!
 */


#define DECODER_MAX_CODE_TIME    100 // To be optimised (shortened)!


#include "../inc/freeEMS.h"
#include "../inc/utils.h"
#include "../inc/interrupts.h"


#if defined(WITH_COMBUSTION_SYNC) // ###########################################
#ifndef NUMBER_OF_EVENTS_PER_SYNC
#error "Number of events per sync not defined!"
#endif
#ifndef CYLINDER_COUNT
#error "Cylinder count must be defined!"
#elif CYLINDER_COUNT > 12 || CYLINDER_COUNT < 1
#error "Cylinder count must be in the range 1 to 12!"
#endif
#define CONFIGURED_SYNC COMBUSTION_SYNC
#define NUMBER_OF_REAL_EVENTS NUMBER_OF_EVENTS_PER_SYNC
#define NUMBER_OF_VIRTUAL_EVENTS (CYLINDER_COUNT * NUMBER_OF_REAL_EVENTS)
#define ANGLE_BETWEEN_EVENTS ((ANGLE_FACTOR * 720.0) / NUMBER_OF_VIRTUAL_EVENTS)
#if NUMBER_OF_VIRTUAL_EVENTS != TOTAL_EVENT_COUNT
#error "Total, per sync and cylinder count don't match!"
#endif
#elif defined(WITH_CRANK_SYNC) // ##############################################
#ifndef NUMBER_OF_EVENTS_ON_CRANK
#error "Number of events on crank not defined!"
#endif
#define CONFIGURED_SYNC CRANK_SYNC
#define NUMBER_OF_REAL_EVENTS NUMBER_OF_EVENTS_ON_CRANK
#define NUMBER_OF_VIRTUAL_EVENTS (2 * NUMBER_OF_REAL_EVENTS)
#define ANGLE_BETWEEN_EVENTS ((ANGLE_FACTOR * 360.0) / NUMBER_OF_EVENTS_ON_CRANK)
#elif defined(WITH_CAM_SYNC) // ################################################
#ifndef NUMBER_OF_EVENTS_ON_CAM
#error "Number of events on cam not defined!"
#endif
#define CONFIGURED_SYNC CAM_SYNC
#define NUMBER_OF_REAL_EVENTS NUMBER_OF_EVENTS_ON_CAM
#define NUMBER_OF_VIRTUAL_EVENTS NUMBER_OF_REAL_EVENTS
#define ANGLE_BETWEEN_EVENTS ((ANGLE_FACTOR * 720.0) / NUMBER_OF_EVENTS_ON_CAM)
#else // #######################################################################
#error "You MUST configure the style of this decoder!"
#endif


#if NUMBER_OF_VIRTUAL_EVENTS > 64
#error "Currently only 64 real events are handled! Request an upgrade!"
#endif


#include "../inc/decoderInterface.h"


// Evenly spaced event angles defined recursively and ready for use
#define   E0 0
#define   E1 ANGLE_BETWEEN_EVENTS
#define   E2 (  E1 + ANGLE_BETWEEN_EVENTS)
#define   E3 (  E2 + ANGLE_BETWEEN_EVENTS)
#define   E4 (  E3 + ANGLE_BETWEEN_EVENTS)
#define   E5 (  E4 + ANGLE_BETWEEN_EVENTS)
#define   E6 (  E5 + ANGLE_BETWEEN_EVENTS)
#define   E7 (  E6 + ANGLE_BETWEEN_EVENTS)
#define   E8 (  E7 + ANGLE_BETWEEN_EVENTS)
#define   E9 (  E8 + ANGLE_BETWEEN_EVENTS)
#define  E10 (  E9 + ANGLE_BETWEEN_EVENTS)
#define  E11 ( E10 + ANGLE_BETWEEN_EVENTS)
#define  E12 ( E11 + ANGLE_BETWEEN_EVENTS)
#define  E13 ( E12 + ANGLE_BETWEEN_EVENTS)
#define  E14 ( E13 + ANGLE_BETWEEN_EVENTS)
#define  E15 ( E14 + ANGLE_BETWEEN_EVENTS)
#define  E16 ( E15 + ANGLE_BETWEEN_EVENTS)
#define  E17 ( E16 + ANGLE_BETWEEN_EVENTS)
#define  E18 ( E17 + ANGLE_BETWEEN_EVENTS)
#define  E19 ( E18 + ANGLE_BETWEEN_EVENTS)
#define  E20 ( E19 + ANGLE_BETWEEN_EVENTS)
#define  E21 ( E20 + ANGLE_BETWEEN_EVENTS)
#define  E22 ( E21 + ANGLE_BETWEEN_EVENTS)
#define  E23 ( E22 + ANGLE_BETWEEN_EVENTS)
#define  E24 ( E23 + ANGLE_BETWEEN_EVENTS)
#define  E25 ( E24 + ANGLE_BETWEEN_EVENTS)
#define  E26 ( E25 + ANGLE_BETWEEN_EVENTS)
#define  E27 ( E26 + ANGLE_BETWEEN_EVENTS)
#define  E28 ( E27 + ANGLE_BETWEEN_EVENTS)
#define  E29 ( E28 + ANGLE_BETWEEN_EVENTS)
#define  E30 ( E29 + ANGLE_BETWEEN_EVENTS)
#define  E31 ( E30 + ANGLE_BETWEEN_EVENTS)
#define  E32 ( E31 + ANGLE_BETWEEN_EVENTS)
#define  E33 ( E32 + ANGLE_BETWEEN_EVENTS)
#define  E34 ( E33 + ANGLE_BETWEEN_EVENTS)
#define  E35 ( E34 + ANGLE_BETWEEN_EVENTS)
#define  E36 ( E35 + ANGLE_BETWEEN_EVENTS)
#define  E37 ( E36 + ANGLE_BETWEEN_EVENTS)
#define  E38 ( E37 + ANGLE_BETWEEN_EVENTS)
#define  E39 ( E38 + ANGLE_BETWEEN_EVENTS)
#define  E40 ( E39 + ANGLE_BETWEEN_EVENTS)
#define  E41 ( E40 + ANGLE_BETWEEN_EVENTS)
#define  E42 ( E41 + ANGLE_BETWEEN_EVENTS)
#define  E43 ( E42 + ANGLE_BETWEEN_EVENTS)
#define  E44 ( E43 + ANGLE_BETWEEN_EVENTS)
#define  E45 ( E44 + ANGLE_BETWEEN_EVENTS)
#define  E46 ( E45 + ANGLE_BETWEEN_EVENTS)
#define  E47 ( E46 + ANGLE_BETWEEN_EVENTS)
#define  E48 ( E47 + ANGLE_BETWEEN_EVENTS)
#define  E49 ( E48 + ANGLE_BETWEEN_EVENTS)
#define  E50 ( E49 + ANGLE_BETWEEN_EVENTS)
#define  E51 ( E50 + ANGLE_BETWEEN_EVENTS)
#define  E52 ( E51 + ANGLE_BETWEEN_EVENTS)
#define  E53 ( E52 + ANGLE_BETWEEN_EVENTS)
#define  E54 ( E53 + ANGLE_BETWEEN_EVENTS)
#define  E55 ( E54 + ANGLE_BETWEEN_EVENTS)
#define  E56 ( E55 + ANGLE_BETWEEN_EVENTS)
#define  E57 ( E56 + ANGLE_BETWEEN_EVENTS)
#define  E58 ( E57 + ANGLE_BETWEEN_EVENTS)
#define  E59 ( E58 + ANGLE_BETWEEN_EVENTS)
#define  E60 ( E59 + ANGLE_BETWEEN_EVENTS)
#define  E61 ( E60 + ANGLE_BETWEEN_EVENTS)
#define  E62 ( E61 + ANGLE_BETWEEN_EVENTS)
#define  E63 ( E62 + ANGLE_BETWEEN_EVENTS)

// Simply including all of them and only using the first N is acceptable
const unsigned short eventAngles[] = {
E0 // Always this event...

#if (NUMBER_OF_VIRTUAL_EVENTS > 1)
,E1
#if (NUMBER_OF_VIRTUAL_EVENTS > 2)
,E2
#if (NUMBER_OF_VIRTUAL_EVENTS > 3)
,E3
#if (NUMBER_OF_VIRTUAL_EVENTS > 4)
,E4
#if (NUMBER_OF_VIRTUAL_EVENTS > 5)
,E5
#if (NUMBER_OF_VIRTUAL_EVENTS > 6)
,E6
#if (NUMBER_OF_VIRTUAL_EVENTS > 7)
,E7
#if (NUMBER_OF_VIRTUAL_EVENTS > 8)
,E8
#if (NUMBER_OF_VIRTUAL_EVENTS > 9)
,E9
#if (NUMBER_OF_VIRTUAL_EVENTS > 10)
,E10
#if (NUMBER_OF_VIRTUAL_EVENTS > 11)
,E11
#if (NUMBER_OF_VIRTUAL_EVENTS > 12)
,E12
#if (NUMBER_OF_VIRTUAL_EVENTS > 13)
,E13
#if (NUMBER_OF_VIRTUAL_EVENTS > 14)
,E14
#if (NUMBER_OF_VIRTUAL_EVENTS > 15)
,E15
#if (NUMBER_OF_VIRTUAL_EVENTS > 16)
,E16
#if (NUMBER_OF_VIRTUAL_EVENTS > 17)
,E17
#if (NUMBER_OF_VIRTUAL_EVENTS > 18)
,E18
#if (NUMBER_OF_VIRTUAL_EVENTS > 19)
,E19
#if (NUMBER_OF_VIRTUAL_EVENTS > 20)
,E20
#if (NUMBER_OF_VIRTUAL_EVENTS > 21)
,E21
#if (NUMBER_OF_VIRTUAL_EVENTS > 22)
,E22
#if (NUMBER_OF_VIRTUAL_EVENTS > 23)
,E23
#if (NUMBER_OF_VIRTUAL_EVENTS > 24)
,E24
#if (NUMBER_OF_VIRTUAL_EVENTS > 25)
,E25
#if (NUMBER_OF_VIRTUAL_EVENTS > 26)
,E26
#if (NUMBER_OF_VIRTUAL_EVENTS > 27)
,E27
#if (NUMBER_OF_VIRTUAL_EVENTS > 28)
,E28
#if (NUMBER_OF_VIRTUAL_EVENTS > 29)
,E29
#if (NUMBER_OF_VIRTUAL_EVENTS > 30)
,E30
#if (NUMBER_OF_VIRTUAL_EVENTS > 31)
,E31
#if (NUMBER_OF_VIRTUAL_EVENTS > 32)
,E32
#if (NUMBER_OF_VIRTUAL_EVENTS > 33)
,E33
#if (NUMBER_OF_VIRTUAL_EVENTS > 34)
,E34
#if (NUMBER_OF_VIRTUAL_EVENTS > 35)
,E35
#if (NUMBER_OF_VIRTUAL_EVENTS > 36)
,E36
#if (NUMBER_OF_VIRTUAL_EVENTS > 37)
,E37
#if (NUMBER_OF_VIRTUAL_EVENTS > 38)
,E38
#if (NUMBER_OF_VIRTUAL_EVENTS > 39)
,E39
#if (NUMBER_OF_VIRTUAL_EVENTS > 40)
,E40
#if (NUMBER_OF_VIRTUAL_EVENTS > 41)
,E41
#if (NUMBER_OF_VIRTUAL_EVENTS > 42)
,E42
#if (NUMBER_OF_VIRTUAL_EVENTS > 43)
,E43
#if (NUMBER_OF_VIRTUAL_EVENTS > 44)
,E44
#if (NUMBER_OF_VIRTUAL_EVENTS > 45)
,E45
#if (NUMBER_OF_VIRTUAL_EVENTS > 46)
,E46
#if (NUMBER_OF_VIRTUAL_EVENTS > 47)
,E47
#if (NUMBER_OF_VIRTUAL_EVENTS > 48)
,E48
#if (NUMBER_OF_VIRTUAL_EVENTS > 49)
,E49
#if (NUMBER_OF_VIRTUAL_EVENTS > 50)
,E50
#if (NUMBER_OF_VIRTUAL_EVENTS > 51)
,E51
#if (NUMBER_OF_VIRTUAL_EVENTS > 52)
,E52
#if (NUMBER_OF_VIRTUAL_EVENTS > 53)
,E53
#if (NUMBER_OF_VIRTUAL_EVENTS > 54)
,E54
#if (NUMBER_OF_VIRTUAL_EVENTS > 55)
,E55
#if (NUMBER_OF_VIRTUAL_EVENTS > 56)
,E56
#if (NUMBER_OF_VIRTUAL_EVENTS > 57)
,E57
#if (NUMBER_OF_VIRTUAL_EVENTS > 58)
,E58
#if (NUMBER_OF_VIRTUAL_EVENTS > 59)
,E59
#if (NUMBER_OF_VIRTUAL_EVENTS > 60)
,E60
#if (NUMBER_OF_VIRTUAL_EVENTS > 61)
,E61
#if (NUMBER_OF_VIRTUAL_EVENTS > 62)
,E62
#if (NUMBER_OF_VIRTUAL_EVENTS > 63)
,E63
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
#endif
};
