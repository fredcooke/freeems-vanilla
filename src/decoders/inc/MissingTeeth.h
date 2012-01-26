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
 * @ingroup allHeaders
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Missing teeth, M-N, with or without cam sync, configured externally
 *
 * This sets up the required arrays and defines such that the generic missing
 * teeth decoder base can function in a specific way for the configured values.
 *
 * Choose one of these three options:
 * - CRANK_ONLY
 * - CAM_ONLY
 * - CRANK_WITH_CAM_SYNC
 *
 * @note The above setting will affect the init routine. CRANK_WITH_CAM_SYNC is
 * not currently supported.
 *
 * Define both of these values appropriately:
 * - TOTAL_TEETH
 * - MISSING_TEETH
 *
 * @note Please see the docs directory MissingTeethValidCombos.ods file first.
 */


typedef struct {
	unsigned lastPair: 4;
	unsigned thisPair: 4;
} twoPairs;

typedef union {
	twoPairs pairs;
	unsigned char pattern;
} match;


#define DECODER_MAX_CODE_TIME 250 // From Spudmn's measurements in NZ. 171us runtime was max = 214 ticks.

#include "../../inc/freeEMS.h"
#include "../../inc/utils.h"
#include "../../inc/interrupts.h"
// See approximately 72 lines below for decoderInterface.h include


#ifndef TOTAL_TEETH
#error "Total number of teeth not defined!"
#endif

#if (TOTAL_TEETH < 4)
#error "Total number of teeth must be greater than 4!"
#endif

#ifndef MISSING_TEETH
#error "Number of missing teeth not defined!"
#endif

#if (MISSING_TEETH < 1)
#error "Missing teeth must be greater than 0!"
#endif

#if ((MISSING_TEETH * 3) > TOTAL_TEETH)
#error "Too many missing teeth! (or not enough total teeth!)"
#endif


#define NUMBER_OF_WHEEL_EVENTS (TOTAL_TEETH - MISSING_TEETH)


#if (NUMBER_OF_WHEEL_EVENTS > 64)
#error "Real events over 64 are currently not supported by this decoder style!"
#endif


#if ((defined(CRANK_ONLY) && defined(CAM_ONLY)) || (defined(CRANK_ONLY) && defined(CRANK_WITH_CAM_SYNC)) || (defined(CRANK_WITH_CAM_SYNC) && defined(CAM_ONLY)))
#error "Can not be cam and crank, choose one!"
#endif


// Make current tolerance scheme work properly for different missing levels OOTB
#define TOLERANCE_LEVEL (MISSING_TEETH*1024)


#if defined(CRANK_ONLY)
#define NUMBER_OF_REAL_EVENTS NUMBER_OF_WHEEL_EVENTS
#define NUMBER_OF_VIRTUAL_EVENTS (2 * NUMBER_OF_REAL_EVENTS)
#define ANGLE_BETWEEN_EVENTS ((oneDegree * 360.0) / TOTAL_TEETH)
#define angleOfSingleIteration (360 * oneDegree)
#elif defined(CAM_ONLY)
#define NUMBER_OF_REAL_EVENTS NUMBER_OF_WHEEL_EVENTS
#define NUMBER_OF_VIRTUAL_EVENTS NUMBER_OF_REAL_EVENTS
#define ANGLE_BETWEEN_EVENTS ((oneDegree * 720.0) / TOTAL_TEETH)
#define angleOfSingleIteration (720 * oneDegree)
#elif defined(CRANK_WITH_CAM_SYNC)
#define NUMBER_OF_REAL_EVENTS (2 * NUMBER_OF_WHEEL_EVENTS)
#define NUMBER_OF_VIRTUAL_EVENTS NUMBER_OF_REAL_EVENTS
#define ANGLE_BETWEEN_EVENTS ((oneDegree * 360.0) / TOTAL_TEETH)
#define angleOfSingleIteration (720 * oneDegree)
#error "Not yet supported!" // And maybe done a different way, we'll see...
#else
#error "You MUST configure the style of this decoder!"
#endif


#include "../../inc/decoderInterface.h"


// For cam events, this is all that is used, for crank, this is the first half.
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
#define  E41 ( E30 + ANGLE_BETWEEN_EVENTS)
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


// For crank speed wheels we need a second set of events offset 360 degrees from the first set. With a cam sync, they are real, without, only virtual.
#define   E0_2 ((oneDegree * 360.0) +   E0)
#define   E1_2 ((oneDegree * 360.0) +   E1)
#define   E2_2 ((oneDegree * 360.0) +   E2)
#define   E3_2 ((oneDegree * 360.0) +   E3)
#define   E4_2 ((oneDegree * 360.0) +   E4)
#define   E5_2 ((oneDegree * 360.0) +   E5)
#define   E6_2 ((oneDegree * 360.0) +   E6)
#define   E7_2 ((oneDegree * 360.0) +   E7)
#define   E8_2 ((oneDegree * 360.0) +   E8)
#define   E9_2 ((oneDegree * 360.0) +   E9)
#define  E10_2 ((oneDegree * 360.0) +  E10)
#define  E11_2 ((oneDegree * 360.0) +  E11)
#define  E12_2 ((oneDegree * 360.0) +  E12)
#define  E13_2 ((oneDegree * 360.0) +  E13)
#define  E14_2 ((oneDegree * 360.0) +  E14)
#define  E15_2 ((oneDegree * 360.0) +  E15)
#define  E16_2 ((oneDegree * 360.0) +  E16)
#define  E17_2 ((oneDegree * 360.0) +  E17)
#define  E18_2 ((oneDegree * 360.0) +  E18)
#define  E19_2 ((oneDegree * 360.0) +  E19)
#define  E20_2 ((oneDegree * 360.0) +  E20)
#define  E21_2 ((oneDegree * 360.0) +  E21)
#define  E22_2 ((oneDegree * 360.0) +  E22)
#define  E23_2 ((oneDegree * 360.0) +  E23)
#define  E24_2 ((oneDegree * 360.0) +  E24)
#define  E25_2 ((oneDegree * 360.0) +  E25)
#define  E26_2 ((oneDegree * 360.0) +  E26)
#define  E27_2 ((oneDegree * 360.0) +  E27)
#define  E28_2 ((oneDegree * 360.0) +  E28)
#define  E29_2 ((oneDegree * 360.0) +  E29)
#define  E30_2 ((oneDegree * 360.0) +  E30)
#define  E31_2 ((oneDegree * 360.0) +  E31)
#define  E32_2 ((oneDegree * 360.0) +  E32)
#define  E33_2 ((oneDegree * 360.0) +  E33)
#define  E34_2 ((oneDegree * 360.0) +  E34)
#define  E35_2 ((oneDegree * 360.0) +  E35)
#define  E36_2 ((oneDegree * 360.0) +  E36)
#define  E37_2 ((oneDegree * 360.0) +  E37)
#define  E38_2 ((oneDegree * 360.0) +  E38)
#define  E39_2 ((oneDegree * 360.0) +  E39)
#define  E40_2 ((oneDegree * 360.0) +  E40)
#define  E41_2 ((oneDegree * 360.0) +  E41)
#define  E42_2 ((oneDegree * 360.0) +  E42)
#define  E43_2 ((oneDegree * 360.0) +  E43)
#define  E44_2 ((oneDegree * 360.0) +  E44)
#define  E45_2 ((oneDegree * 360.0) +  E45)
#define  E46_2 ((oneDegree * 360.0) +  E46)
#define  E47_2 ((oneDegree * 360.0) +  E47)
#define  E48_2 ((oneDegree * 360.0) +  E48)
#define  E49_2 ((oneDegree * 360.0) +  E49)
#define  E50_2 ((oneDegree * 360.0) +  E50)
#define  E51_2 ((oneDegree * 360.0) +  E51)
#define  E52_2 ((oneDegree * 360.0) +  E52)
#define  E53_2 ((oneDegree * 360.0) +  E53)
#define  E54_2 ((oneDegree * 360.0) +  E54)
#define  E55_2 ((oneDegree * 360.0) +  E55)
#define  E56_2 ((oneDegree * 360.0) +  E56)
#define  E57_2 ((oneDegree * 360.0) +  E57)
#define  E58_2 ((oneDegree * 360.0) +  E58)
#define  E59_2 ((oneDegree * 360.0) +  E59)
#define  E60_2 ((oneDegree * 360.0) +  E60)
#define  E61_2 ((oneDegree * 360.0) +  E61)
#define  E62_2 ((oneDegree * 360.0) +  E62)
#define  E63_2 ((oneDegree * 360.0) +  E63)


const unsigned short eventAngles[] = {
E0 // Always this event...

#if (NUMBER_OF_WHEEL_EVENTS > 1)
,E1
#if (NUMBER_OF_WHEEL_EVENTS > 2)
,E2
#if (NUMBER_OF_WHEEL_EVENTS > 3)
,E3
#if (NUMBER_OF_WHEEL_EVENTS > 4)
,E4
#if (NUMBER_OF_WHEEL_EVENTS > 5)
,E5
#if (NUMBER_OF_WHEEL_EVENTS > 6)
,E6
#if (NUMBER_OF_WHEEL_EVENTS > 7)
,E7
#if (NUMBER_OF_WHEEL_EVENTS > 8)
,E8
#if (NUMBER_OF_WHEEL_EVENTS > 9)
,E9
#if (NUMBER_OF_WHEEL_EVENTS > 10)
,E10
#if (NUMBER_OF_WHEEL_EVENTS > 11)
,E11
#if (NUMBER_OF_WHEEL_EVENTS > 12)
,E12
#if (NUMBER_OF_WHEEL_EVENTS > 13)
,E13
#if (NUMBER_OF_WHEEL_EVENTS > 14)
,E14
#if (NUMBER_OF_WHEEL_EVENTS > 15)
,E15
#if (NUMBER_OF_WHEEL_EVENTS > 16)
,E16
#if (NUMBER_OF_WHEEL_EVENTS > 17)
,E17
#if (NUMBER_OF_WHEEL_EVENTS > 18)
,E18
#if (NUMBER_OF_WHEEL_EVENTS > 19)
,E19
#if (NUMBER_OF_WHEEL_EVENTS > 20)
,E20
#if (NUMBER_OF_WHEEL_EVENTS > 21)
,E21
#if (NUMBER_OF_WHEEL_EVENTS > 22)
,E22
#if (NUMBER_OF_WHEEL_EVENTS > 23)
,E23
#if (NUMBER_OF_WHEEL_EVENTS > 24)
,E24
#if (NUMBER_OF_WHEEL_EVENTS > 25)
,E25
#if (NUMBER_OF_WHEEL_EVENTS > 26)
,E26
#if (NUMBER_OF_WHEEL_EVENTS > 27)
,E27
#if (NUMBER_OF_WHEEL_EVENTS > 28)
,E28
#if (NUMBER_OF_WHEEL_EVENTS > 29)
,E29
#if (NUMBER_OF_WHEEL_EVENTS > 30)
,E30
#if (NUMBER_OF_WHEEL_EVENTS > 31)
,E31
#if (NUMBER_OF_WHEEL_EVENTS > 32)
,E32
#if (NUMBER_OF_WHEEL_EVENTS > 33)
,E33
#if (NUMBER_OF_WHEEL_EVENTS > 34)
,E34
#if (NUMBER_OF_WHEEL_EVENTS > 35)
,E35
#if (NUMBER_OF_WHEEL_EVENTS > 36)
,E36
#if (NUMBER_OF_WHEEL_EVENTS > 37)
,E37
#if (NUMBER_OF_WHEEL_EVENTS > 38)
,E38
#if (NUMBER_OF_WHEEL_EVENTS > 39)
,E39
#if (NUMBER_OF_WHEEL_EVENTS > 40)
,E40
#if (NUMBER_OF_WHEEL_EVENTS > 41)
,E41
#if (NUMBER_OF_WHEEL_EVENTS > 42)
,E42
#if (NUMBER_OF_WHEEL_EVENTS > 43)
,E43
#if (NUMBER_OF_WHEEL_EVENTS > 44)
,E44
#if (NUMBER_OF_WHEEL_EVENTS > 45)
,E45
#if (NUMBER_OF_WHEEL_EVENTS > 46)
,E46
#if (NUMBER_OF_WHEEL_EVENTS > 47)
,E47
#if (NUMBER_OF_WHEEL_EVENTS > 48)
,E48
#if (NUMBER_OF_WHEEL_EVENTS > 49)
,E49
#if (NUMBER_OF_WHEEL_EVENTS > 50)
,E50
#if (NUMBER_OF_WHEEL_EVENTS > 51)
,E51
#if (NUMBER_OF_WHEEL_EVENTS > 52)
,E52
#if (NUMBER_OF_WHEEL_EVENTS > 53)
,E53
#if (NUMBER_OF_WHEEL_EVENTS > 54)
,E54
#if (NUMBER_OF_WHEEL_EVENTS > 55)
,E55
#if (NUMBER_OF_WHEEL_EVENTS > 56)
,E56
#if (NUMBER_OF_WHEEL_EVENTS > 57)
,E57
#if (NUMBER_OF_WHEEL_EVENTS > 58)
,E58
#if (NUMBER_OF_WHEEL_EVENTS > 59)
,E59
#if (NUMBER_OF_WHEEL_EVENTS > 60)
,E60
#if (NUMBER_OF_WHEEL_EVENTS > 61)
,E61
#if (NUMBER_OF_WHEEL_EVENTS > 62)
,E62
#if (NUMBER_OF_WHEEL_EVENTS > 63)
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


// If the missing tooth wheel is on the camshaft, it represents a full 720
// degree cycle and duplicating the events with 360 offset is not necessary.
#ifndef CAM_ONLY
,E0_2
// The following ifs are not strictly necessary as the array is only read up to
// where it should be read, and the balance, which would otherwise be random
// values in flash, are ignored. However it is consistent.
#if (NUMBER_OF_WHEEL_EVENTS > 1)
,E1_2
#if (NUMBER_OF_WHEEL_EVENTS > 2)
,E2_2
#if (NUMBER_OF_WHEEL_EVENTS > 3)
,E3_2
#if (NUMBER_OF_WHEEL_EVENTS > 4)
,E4_2
#if (NUMBER_OF_WHEEL_EVENTS > 5)
,E5_2
#if (NUMBER_OF_WHEEL_EVENTS > 6)
,E6_2
#if (NUMBER_OF_WHEEL_EVENTS > 7)
,E7_2
#if (NUMBER_OF_WHEEL_EVENTS > 8)
,E8_2
#if (NUMBER_OF_WHEEL_EVENTS > 9)
,E9_2
#if (NUMBER_OF_WHEEL_EVENTS > 10)
,E10_2
#if (NUMBER_OF_WHEEL_EVENTS > 11)
,E11_2
#if (NUMBER_OF_WHEEL_EVENTS > 12)
,E12_2
#if (NUMBER_OF_WHEEL_EVENTS > 13)
,E13_2
#if (NUMBER_OF_WHEEL_EVENTS > 14)
,E14_2
#if (NUMBER_OF_WHEEL_EVENTS > 15)
,E15_2
#if (NUMBER_OF_WHEEL_EVENTS > 16)
,E16_2
#if (NUMBER_OF_WHEEL_EVENTS > 17)
,E17_2
#if (NUMBER_OF_WHEEL_EVENTS > 18)
,E18_2
#if (NUMBER_OF_WHEEL_EVENTS > 19)
,E19_2
#if (NUMBER_OF_WHEEL_EVENTS > 20)
,E20_2
#if (NUMBER_OF_WHEEL_EVENTS > 21)
,E21_2
#if (NUMBER_OF_WHEEL_EVENTS > 22)
,E22_2
#if (NUMBER_OF_WHEEL_EVENTS > 23)
,E23_2
#if (NUMBER_OF_WHEEL_EVENTS > 24)
,E24_2
#if (NUMBER_OF_WHEEL_EVENTS > 25)
,E25_2
#if (NUMBER_OF_WHEEL_EVENTS > 26)
,E26_2
#if (NUMBER_OF_WHEEL_EVENTS > 27)
,E27_2
#if (NUMBER_OF_WHEEL_EVENTS > 28)
,E28_2
#if (NUMBER_OF_WHEEL_EVENTS > 29)
,E29_2
#if (NUMBER_OF_WHEEL_EVENTS > 30)
,E30_2
#if (NUMBER_OF_WHEEL_EVENTS > 31)
,E31_2
#if (NUMBER_OF_WHEEL_EVENTS > 32)
,E32_2
#if (NUMBER_OF_WHEEL_EVENTS > 33)
,E33_2
#if (NUMBER_OF_WHEEL_EVENTS > 34)
,E34_2
#if (NUMBER_OF_WHEEL_EVENTS > 35)
,E35_2
#if (NUMBER_OF_WHEEL_EVENTS > 36)
,E36_2
#if (NUMBER_OF_WHEEL_EVENTS > 37)
,E37_2
#if (NUMBER_OF_WHEEL_EVENTS > 38)
,E38_2
#if (NUMBER_OF_WHEEL_EVENTS > 39)
,E39_2
#if (NUMBER_OF_WHEEL_EVENTS > 40)
,E40_2
#if (NUMBER_OF_WHEEL_EVENTS > 41)
,E41_2
#if (NUMBER_OF_WHEEL_EVENTS > 42)
,E42_2
#if (NUMBER_OF_WHEEL_EVENTS > 43)
,E43_2
#if (NUMBER_OF_WHEEL_EVENTS > 44)
,E44_2
#if (NUMBER_OF_WHEEL_EVENTS > 45)
,E45_2
#if (NUMBER_OF_WHEEL_EVENTS > 46)
,E46_2
#if (NUMBER_OF_WHEEL_EVENTS > 47)
,E47_2
#if (NUMBER_OF_WHEEL_EVENTS > 48)
,E48_2
#if (NUMBER_OF_WHEEL_EVENTS > 49)
,E49_2
#if (NUMBER_OF_WHEEL_EVENTS > 50)
,E50_2
#if (NUMBER_OF_WHEEL_EVENTS > 51)
,E51_2
#if (NUMBER_OF_WHEEL_EVENTS > 52)
,E52_2
#if (NUMBER_OF_WHEEL_EVENTS > 53)
,E53_2
#if (NUMBER_OF_WHEEL_EVENTS > 54)
,E54_2
#if (NUMBER_OF_WHEEL_EVENTS > 55)
,E55_2
#if (NUMBER_OF_WHEEL_EVENTS > 56)
,E56_2
#if (NUMBER_OF_WHEEL_EVENTS > 57)
,E57_2
#if (NUMBER_OF_WHEEL_EVENTS > 58)
,E58_2
#if (NUMBER_OF_WHEEL_EVENTS > 59)
,E59_2
#if (NUMBER_OF_WHEEL_EVENTS > 60)
,E60_2
#if (NUMBER_OF_WHEEL_EVENTS > 61)
,E61_2
#if (NUMBER_OF_WHEEL_EVENTS > 62)
,E62_2
#if (NUMBER_OF_WHEEL_EVENTS > 63)
,E63_2
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
#endif

};


/// @todo TODO build this with similar hash if logic: need to reconsider how to use this or whether to even have it. A "corresponding event" table might be good instead, kinda like the mapping above, but from real to real, only when the angles are exactly 360 out.
const unsigned char eventValidForCrankSync[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}; // this is only correct while doing pure crank sync, wrong once doing more, i think, TBC...
