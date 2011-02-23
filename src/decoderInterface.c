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

/** @file decoderInterface.c
 *
 * @ingroup enginePositionRPMDecoders
 *
 * @brief shared functions used by all decoders
 *
 * To maximise code reuse and minimise bugs it is strongly recommended that you
 * use these pre-canned functions to do work required in your decoder.
 */

#define DECODER_INTERFACE_C
#include "inc/freeEMS.h"
#include "inc/decoderInterface.h"


/** @brief Reset key state
 *
 * Reset all important variables to their non-running state.
 *
 * @todo TODO bring this up to date and/or find a better way to do it.
 *
 * @author Fred Cooke
 */
void resetToNonRunningState(){
	/* Reset RPM to zero */
	RPM0 = 0;
	RPM1 = 0;

	/* Ensure tacho reads lowest possible value */
	engineCyclePeriod = ticksPerCycleAtOneRPM;

	/* Clear all sync flags to lost state */
	//coreStatusA &= CLEAR_RPM_VALID;
	coreStatusA &= CLEAR_PRIMARY_SYNC;
	//coreStatusA &= CLEAR_SECONDARY_SYNC;

	// TODO more stuff needs resetting here, but only critical things.
}
