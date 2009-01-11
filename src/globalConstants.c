/*	FreeEMS - the open source engine management system

	Copyright 2008 Fred Cooke

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


/**	@file globalConstants.c
 * @ingroup dataInitialisers
 *
 * @brief Global constant values
 *
 * All global constants values are, and should be, defined here.
 *
 * @author Fred Cooke
 */


#define GLOBAL_CONSTANTS_C
#define NO_CONST_ARRAYS
#include "inc/freeEMS.h"


/* Types summary
 *
 * BEWARE : Be explicit!!
 *
 * char			8 bit (defaults to unsigned, but always specify signed/unsigned anyway)
 * short		16 bit (defaults to signed, but always specify signed/unsigned anyway)
 * int			16 bit DO NOT USE! (current compile flags make this 16 bits, but a change of flags could will change your program if you use this because they will all be 32 bit all of a sudden)
 * long			32 bit (defaults to signed, but always specify signed/unsigned anyway)
 * long long	64 bit (inefficient, avoid these, if using : defaults to signed, but always specify signed/unsigned anyway)
 * float		32 bit IEEE floating point numbers (inefficient, avoid these, used fixed point math)
 * double		64 bit IEEE floating point numbers (inefficient, avoid these, used fixed point math)
 */


const unsigned short memdumplength = 0x100;
const unsigned short maxBasicDatalogLength = sizeof(CoreVar) + sizeof(DerivedVar) + sizeof(ADCArray);


/* Constants */
/* &&&&&&&&&& WARNING &&&&&&&&&& These need to be changed if the timer period is changed at all!! &&&&&&&&&& WARNING &&&&&&&&&& */
/* TODO It may be better to make these actual times and calculate the number of timer units such that a change in time base of the timer doesn't affect the code. */

/** Serial interface unique identifier
 *
 * This should only change when the serial interface changes (even a little)
 *
 * This field consists of 3 chars for a 3 part version number and a free form string. For any unique string the version
 * number is also unique. In this way tools can easily support a range of versions for a specific unique string ID
 */
const unsigned char interfaceVersionAndType[20] = {0,0,2,'I','F','r','e','e','E','M','S',' ','V','a','n','i','l','l','a',0};

/** Displayable firmware version identifier
 *
 * This should change every time the code is changed at all (even a little) before each release.
 */
const unsigned char firmwareVersion[45] = {"FreeEMS Vanilla 0.0.19 Doxygenated pre-alpha"};

/** Divisors and untunable physical constants combined into a single master fuel constant
 *
 * const unsigned short molarMassOfAir = 2897; // in grams per 100 moles, so divide by 100 to get gm/mol
 * const unsigned short msToTicks = 1250; // constant to bring ms into 0.8us chunks
 * const unsigned short universalGasConstant = 34056; // 8.314472 * 4096, so divide by 4096 to get real number
 *
 * hash define injectorFlowDivisor 1024
 * hash define injectorFlowUnitDivisor 1000 - to get it into litres/second
 * hash define injectorFlowTotalDivisor 1024000
 * hash define stoichiometricAFRDivisor 1024
 * hash define universalGasConstantDivisor 4096
 * hash define molarMassOfAirDivisor 100
 * hash define perCylinderVolumeDivisor 32768
 *
 * master = (msToTicks * molarMassOfAir * universalGasConstantDivisor * stoichiometricAFRDivisor * injectorFlowTotalDivisor) / (universalGasConstant * molarMassOfAirDivisor * perCylinderVolumeDivisor);
 * master = (1250	   * 2897			* 4096						  * 1024				     * 1024000				   ) / (34056				 * 100					 * 32768				   );
 * http://www.google.com/search?hl=en&safe=off&q=((1250+*+2897+*+4096+*+1024+*+1024000)+%2F+(34056+*++100+*+32768)&btnG=Search
 *
 * ((1250 * 2897 * 4096 * 1024 * 1024000) / (34056 *  100 * 32768) = 139371764
 */
const unsigned long masterFuelConstant = 139371764;

/** MAF fuel constant
 *
 * @todo TODO Determine what the value of MAF fuel constant should be
 */
const unsigned long MAFFuelConstant = 0;

/* Injection limits */
/* The number of timer units it takes for the switch on scheduling code to run */
const unsigned short injectorSwitchOnCodeTime = 100; /* Measured 4 timer cycles, going on the safe side by a lot, and limiting minimum pulse to 0.02ms which is well below any dead time I've heard of */

/* The number of timer units it takes for the switch off scheduling code to run */
const unsigned short injectorSwitchOffCodeTime = 100; /* This is actually shorter than the switch on time above as measured between 0.0.8 and 0.0.9 */

/* The maximum a requested pulsewidth can be before it is truncated to this amount */
const unsigned short injectorMaximumPulseWidth = 0xF424; /* 62500 clock cycles, = exactly 50ms, which is an arbitrary limit but I like round numbers :-) */

/* The minimum a requested pulsewidth can be before it is not switched on at all */
const unsigned short injectorMinimumPulseWidth = 100;


/* Ignition limits */
/* Ignition maximum dwell in timer units */
const unsigned short ignitionMaximumDwell = 50000; /* meaningless us value for now, currently unused */

/* Ignition minimum dwell in timer units */
const unsigned short ignitionMinimumDwell = 500; /* meaningless us value for now, currently unused */

/* Ignition maximum delay post schedule tooth in timer units */
const unsigned short ignitionMaximumDelayToDwellStartAfterTooth = 50000; /* (max retard) meaningless us value for now, currently unused */

/* Ignition maximum delay post schedule tooth in timer units */
const unsigned short ignitionMinimumDelayToDwellStartAfterTooth = 500; /* (max advance) meaningless us value for now, currently unused */


/* Engine position/RPM decoder limits */
/*  */
const unsigned short leadingEdgePrimaryRPMInputCodeTime = 100; /* random large safe value */

/*  */
const unsigned short trailingEdgePrimaryRPMInputCodeTime = 100; /* random large safe value */

/*  */
const unsigned short leadingEdgeSecondaryRPMInputCodeTime = 100; /* random large safe value */

/*  */
const unsigned short trailingEdgeSecondaryRPMInputCodeTime = 100; /* random large safe value */

// TODO put these where they belong, just dumped from other file for now...
/* Main injector channel bit masks and registers for use in both injection_isrs.c and engine_position_isrs.c */
/* Masks for setting mainOn flags and checking state of pin and therefore which change of state just occured */
/* Masks for clearing mainOn flags */
/* Masks for setting mainOn flags and checking state of pin and therefore which change of state just occured */
/* Masks to be used with |= to switch a channel to "turn on compare" mode */
/* Masks to be used dissable with &= to switch a channel to "turn off compare" mode */
/* Masks to be used with |= to switch a channel to "turn on on compare" mode from "turn off on compare" mode */
/* Masks to be used with &= to switch a channel to "turn off on compare" mode from "turn on on compare" mode */
/* Ignition channel bit masks for use in both PIT timer ISRs and engine_position_isrs.c */
/* Masks for setting ignition status bits and turning on the channels themselves */
/* Masks for clearing ignition status bits and turning off the channels themselves */


/* Dwell masks                                            { CYL1 B0, CYL2 B1, CYL3  B2, CYL4  B3, CYL5  B4, CYL6  B5, CYL7  B6, CYL8  B7, CYL9 A0,CYL10 A1,CYL11 A2,CYL12 A3}; */
const unsigned short dwellStartMasks[IGNITION_CHANNELS] = { BIT8_16, BIT9_16, BIT10_16, BIT11_16, BIT12_16, BIT13_16, BIT14_16, BIT15_16, BIT0_16, BIT1_16, BIT2_16, BIT3_16};		/* Set of masks such that a cylinder can be dwelled with a single line of code */
const unsigned short ignitionMasks[IGNITION_CHANNELS]   = {NBIT8_16,NBIT9_16,NBIT10_16,NBIT11_16,NBIT12_16,NBIT13_16,NBIT14_16,NBIT15_16,NBIT0_16,NBIT1_16,NBIT2_16,NBIT3_16};		/* Set of masks such that a cylinder can be fired with a single line of code */

/* Injection masks */
const unsigned char injectorMainOnMasks[INJECTION_CHANNELS] = {BIT2,  BIT3,  BIT4,  BIT5,  BIT6,  BIT7};
const unsigned char injectorMainOffMasks[INJECTION_CHANNELS] = {NBIT2, NBIT3, NBIT4, NBIT5, NBIT6, NBIT7};
const unsigned char injectorMainEnableMasks[INJECTION_CHANNELS] = {0x30, 0xC0, 0x03, 0x0C, 0x30, 0xC0};
const unsigned char injectorMainDisableMasks[INJECTION_CHANNELS] = {0xCF, 0x3F, 0xFC, 0xF3, 0xCF, 0x3F};
const unsigned char injectorMainGoHighMasks[INJECTION_CHANNELS] = {BIT4, BIT6, BIT0, BIT2, BIT4, BIT6};
const unsigned char injectorMainGoLowMasks[INJECTION_CHANNELS] = {NBIT4, NBIT6, NBIT0, NBIT2, NBIT4, NBIT6};
