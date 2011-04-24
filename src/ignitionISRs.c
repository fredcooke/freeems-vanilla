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


/**	@file ignitionISRs.c
 * @ingroup interruptHandlers
 *
 * @brief Turn ignition channels on and off
 *
 * As of 6am 25/4/11 nzst this file has been stripped and de-commissioned.
 *
 * This currently semi-working but broken code is intended to one day provide
 * multi-channel ignition capabilities. The basic method will be to turn a pin
 * or set of pins on or another pin or set of pins off during each run of the
 * appropriate handler. Each run will be triggered either by the scheduler and
 * possibly this code itself as well. Currently it does not work correctly and
 * isn't suitable for actual use as an ignition control solution.
 */


#define IGNITIONISRS_C
#include "inc/freeEMS.h"
#include "inc/interrupts.h"


/* Summary of intended ignition timing scheme
 *
 * Set TWO PIT timers based on a reference point (probably single cam trigger or optionally toggle bit based on missing tooth on crank)
 * Arm one PIT timer interrupt to trigger when we need to start dwelling
 * Arm the other PIT timer interrupt to trigger when we need to fire
 * Configure a variable to point to the next pin to turn on for dwell
 * Configure a variable to point to the next pin to turn off to fire
 * On PIT interrupt for dwell check to see that spark should have finished
 * If so, turn on coil to dwell
 * If not, reset dwell timer interrupt for end of spark event
 * On PIT interrupt for spark, turn off coil (amything else?)
 * Repeat for each cylinder.
 */

/* Further consideration to spark duration and dwell starting possibly needs to be done. */

/* further reading : ftp://ftp-sop.inria.fr/esterel/pub/papers/FDL99-camready.pdf section 4.1 has a nice diagram */


/**	@brief Ignition dwell control
 *
 * This function turns ignition pins on to dwell when required.
 *
 * @author Fred Cooke
 *
 * @todo TODO make this actually work.
 */
void IgnitionDwellISR(void)
{
	// clear flag
	PITTF = DWELL_ENABLE;
}


/**	@brief Ignition discharge control
 *
 * This function turns ignition pins off to discharge when required.
 *
 * @author Fred Cooke
 *
 * @todo TODO make this actually work.
 */
void IgnitionFireISR(void)
{
	// clear flag
	PITTF = IGNITION_ENABLE;
}
