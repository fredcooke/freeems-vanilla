/*	ignitionISRs.c

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

void IgnitionDwellISR(void)
{
	// clear flag
	PITTF = DWELL_ENABLE;

	// start dwelling asap
	PORTS_BA |= dwellStartMasks[nextDwellChannel];

	if(dwellQueueLength == 0){
		// turn off the int
		PITINTE &= DWELL_DISABLE;

		// disable channels
		PITCE &= DWELL_DISABLE;
	}else{
		// reduce queue length by one
		dwellQueueLength--;

		// increment channel counter to next channel
		if(nextDwellChannel < (fixedConfigs2.combustionEventsPerEngineCycle - 1)){
			nextDwellChannel++; // if not the last channel, increment
		}else{
			nextDwellChannel = 0; // if the last channel, reset to zero
		}

		// if the queue length after decrement is greater than 0 then we need to load the timer, if it is zero and we decremented, the timer was already loaded.
		if(dwellQueueLength > 0){
			if(dwellQueueLength > 8){ // TODO ???? why 8 ???? 12 or combustion events per... or ?
				//throw a nasty error of some sort for index out of range issue that should never occur (for now just light a LED)
				PORTS |= 0x20;
			}else{
				// load the timer if the index is good
				PITLD0 = queuedDwellOffsets[dwellQueueLength - 1];
			}
		}
	}

	// blink a led
	PORTS ^= 0x80;
}


void IgnitionFireISR(void)
{
	// clear flag
	PITTF = IGNITION_ENABLE;

	// fire the coil asap
	PORTS_BA &= ignitionMasks[nextIgnitionChannel];

	if(ignitionQueueLength == 0){
		// turn off the int
		PITINTE &= IGNITION_DISABLE;

		// disable channels
		PITCE &= IGNITION_DISABLE ;
	}else{
		// reduce queue length by one
		ignitionQueueLength--;

		// increment channel counter to next channel
		if(nextIgnitionChannel < (fixedConfigs2.combustionEventsPerEngineCycle - 1)){
			nextIgnitionChannel++; // if not the last channel, increment
		}else{
			nextIgnitionChannel = 0; // if the last channel, reset to zero
		}

		// if the queue length after decrement is greater than 0 then we need to load the timer, if it is zero and we decremented, the timer was already loaded.
		if(ignitionQueueLength > 0){
			if(ignitionQueueLength > fixedConfigs2.combustionEventsPerEngineCycle){ // TODO as above!!!!!!!!!!
				//throw a nasty error of some sort for index out of range issue that should never occur (for now just light a LED)
				PORTS |= 0x10;
			}else{
				// load the timer if the index is good
				PITLD0 = queuedIgnitionOffsets[ignitionQueueLength - 1];
			}
		}
	}

	// blink a led
	PORTS ^= 0x40;
}
