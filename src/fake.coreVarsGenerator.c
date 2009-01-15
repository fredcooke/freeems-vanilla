/*	FreeEMS - the open source engine management system

	Copyright 2009 Fred Cooke

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


/**	@file fake.coreVarsGenerator.c
 * @ingroup measurementsAndCalculations
 * @ingroup testing
 *
 * @brief Iterate through possible sensor values
 *
 * A very basic way of trying out all possible input values to the system.
 *
 * @author Fred Cooke
 */


#define COREVARSGENERATOR_C
#include "inc/freeEMS.h"
#include "inc/commsCore.h"
#include "inc/coreVarsGenerator.h"


/** @brief Iterate through possible sensor values
 *
 * A very basic way of trying out all possible input values to the system.
 *
 * This file needs to be manually added to the output instead of the normal one
 * by renaming the real version with a suffix (eg .real) and renaming this one
 * by removing the prefix (ie fake.).
 *
 * @author Fred Cooke
 */
void generateCoreVars(){

	/*
	 * Fastest rate of change for RPM at the top, lowest rate of change for
	 * battery voltage at the bottom. Each time a variable reaches its maximum
	 * it rolls over back to zero. Because the numbers are prime they will not
	 * remain synchronised and should give a nice mix of output value sets.
	 */
	CoreVars->RPM += 11;
	CoreVars->MAP += 7;
	CoreVars->IAT += 5;
	CoreVars->CHT += 3;
	CoreVars->BRV += 1;

	/* Not currently used... */
	CoreVars->DDRPM = 0;
	CoreVars->DRPM = 0;
	CoreVars->AAP = 0;
	CoreVars->TPS = 0;
	CoreVars->EGO = 0;
	CoreVars->EGO2 = 0;
	CoreVars->MAT = 0;
	CoreVars->IAP = 0;
	CoreVars->MAF = 0;
}
