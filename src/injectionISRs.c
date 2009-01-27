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


/**	@file injectionISRs.c
 * @ingroup interruptHandlers
 *
 * @brief Injection ISR substitutions
 *
 * This file defines the pin specific names for each interrupt and all of it's
 * pin specific variables then imports the actual code from inc/injectorISR.c
 * for each pin such that each one is unique and references a separate set of
 * values specific to it while only maintaining a single copy of the code.
 *
 * @see injectorISR.c
 *
 * @author Fred Cooke
 */


#define INJECTIONISRS_C
#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/injectionISRs.h"


/* Staged control algorithms for PIT2 and PIT3 */
/* Staged injection switch on timer */
void StagedOnISR(void){
	// clear the flag
	PITINTE |= 0x04;

	// bit bang on the correct injector channel
	// TODO figure out which channel and switch it
	// TODO set the flag for that channel

	// if there are other staged channels pending, schedule them and adjust the data
	// TODO

	/* If staged injection needs the end point scheduled, do it now (otherwise it will turn off naturally with the main injector) */
	if(!(fixedConfigs1.coreSettingsA & STAGED_END)){
		// TODO schedule the end of staged injection with PIT 3
	}

	/* Clear the PIT2 flag */
	// TODO
}

/* Staged injection switch off timer */
void StagedOffISR(void){
	// clear the flag
	PITINTE |= 0x08;

	// bit bang off the correct injector channel
	// TODO figure out which channel and switch it
	// TODO set the flag for that channel

	// if there are other staged channels pending, schedule them and adjust the data
	// TODO

	/* Clear the PIT3 flag */
	// TODO
}


/* Define the variables correctly for each channel then import the code */

/* Channel 1 */
#define INJECTOR_CHANNEL_NUMBER 0
#define InjectorXISR Injector1ISR
#define STAGEDXOFF STAGED1OFF
#define STAGEDXON STAGED1ON
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef STAGEDXOFF
#undef STAGEDXON
#undef INJECTOR_CHANNEL_NUMBER

/* Channel 2 */
#define INJECTOR_CHANNEL_NUMBER 1
#define InjectorXISR Injector2ISR
#define STAGEDXOFF STAGED2OFF
#define STAGEDXON STAGED2ON
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef STAGEDXOFF
#undef STAGEDXON
#undef INJECTOR_CHANNEL_NUMBER

/* Channel 3 */
#define INJECTOR_CHANNEL_NUMBER 2
#define InjectorXISR Injector3ISR
#define STAGEDXOFF STAGED3OFF
#define STAGEDXON STAGED3ON
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef STAGEDXOFF
#undef STAGEDXON
#undef INJECTOR_CHANNEL_NUMBER

/* Channel 4 */
#define INJECTOR_CHANNEL_NUMBER 3
#define InjectorXISR Injector4ISR
#define STAGEDXOFF STAGED4OFF
#define STAGEDXON STAGED4ON
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef STAGEDXOFF
#undef STAGEDXON
#undef INJECTOR_CHANNEL_NUMBER

/* Channel 5 */
#define INJECTOR_CHANNEL_NUMBER 4
#define InjectorXISR Injector5ISR
#define STAGEDXOFF STAGED5OFF
#define STAGEDXON STAGED5ON
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef STAGEDXOFF
#undef STAGEDXON
#undef INJECTOR_CHANNEL_NUMBER

/* Channel 6 */
#define INJECTOR_CHANNEL_NUMBER 5
#define InjectorXISR Injector6ISR
#define STAGEDXOFF STAGED6OFF
#define STAGEDXON STAGED6ON
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef STAGEDXOFF
#undef STAGEDXON
#undef INJECTOR_CHANNEL_NUMBER

/* If switching to 8 OC channels with non-IC engine input, place two more sets of defines here :-) (along with all the other mods needed of course) */
