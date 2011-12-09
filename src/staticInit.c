/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009 Fred Cooke
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
 * @brief Static initialisation of non-zero variables
 *
 * This file contains static initialisations for fields that require a non-zero
 * initial value after reset. Zero fields are taken care of by GCC and doing
 * this here means less init time and init code, both good things. Variables
 * initialised here are placed together by the compiler in flash and copied up
 * to RAM as a linear block before the main method runs. This is significantly
 * more efficient than doing them one-by-one in an init routine.
 *
 * @author Fred Cooke
 */


#include "inc/freeEMS.h"


unsigned short tachoPeriod = 65535;	/* Lowest RPM at start up time. */

// Values for testing
unsigned short masterPulseWidth = 10;

	/* Setup the pointers to the registers for fueling use, this does NOT work if done in global.c, I still don't know why. */
//	injectorMainTimeRegisters[0] = TC2_ADDR;
//	injectorMainTimeRegisters[1] = TC3_ADDR;
//	injectorMainTimeRegisters[2] = TC4_ADDR;
//	injectorMainTimeRegisters[3] = TC5_ADDR;
//	injectorMainTimeRegisters[4] = TC6_ADDR;
//	injectorMainTimeRegisters[5] = TC7_ADDR;
//	injectorMainControlRegisters[0] = TCTL2_ADDR;
//	injectorMainControlRegisters[1] = TCTL2_ADDR;
//	injectorMainControlRegisters[2] = TCTL1_ADDR;
//	injectorMainControlRegisters[3] = TCTL1_ADDR;
//	injectorMainControlRegisters[4] = TCTL1_ADDR;
//	injectorMainControlRegisters[5] = TCTL1_ADDR;

	// TODO perhaps read from the ds1302 once at start up and init the values or different ones with the actual time and date then update them in RTI

/* Setup so that the tacho reads low when the engine isn't running */
unsigned long engineCyclePeriod = ticksPerCycleAtOneRPM;

#ifdef XGATE
#include "xgateGlobals.c"
#endif
