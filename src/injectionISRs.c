/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010, 2011 Fred Cooke
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
#include "inc/decoderInterface.h"


/* Staged control algorithms for PIT2 and PIT3 */
/* Staged injection switch on timer */
void StagedOnISR(void){
	// clear the flag
	PITINTE |= 0x04;
	/// @todo TODO This will be handled by XGATE, somehow, in the mean time, move to UISR file along with others.
}

/* Staged injection switch off timer */
void StagedOffISR(void){
	// clear the flag
	PITINTE |= 0x08;
	/// @todo TODO This will be handled by XGATE, somehow, in the mean time, move to UISR file along with others.
}


/* Define the variables correctly for each channel then import the code */

/* Channel 1 */
#define INJECTOR_CHANNEL_NUMBER 0
#define InjectorXISR Injector1ISR
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef INJECTOR_CHANNEL_NUMBER

/* Channel 2 */
#define INJECTOR_CHANNEL_NUMBER 1
#define InjectorXISR Injector2ISR
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef INJECTOR_CHANNEL_NUMBER

/* Channel 3 */
#define INJECTOR_CHANNEL_NUMBER 2
#define InjectorXISR Injector3ISR
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef INJECTOR_CHANNEL_NUMBER

/* Channel 4 */
#define INJECTOR_CHANNEL_NUMBER 3
#define InjectorXISR Injector4ISR
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef INJECTOR_CHANNEL_NUMBER

/* Channel 5 */
#define INJECTOR_CHANNEL_NUMBER 4
#define InjectorXISR Injector5ISR
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef INJECTOR_CHANNEL_NUMBER

/* Channel 6 */
#define INJECTOR_CHANNEL_NUMBER 5
#define InjectorXISR Injector6ISR
#include "inc/injectorISR.c"
#undef InjectorXISR
#undef INJECTOR_CHANNEL_NUMBER
