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


/**	@file BenchTest.c
 *
 * To facilitate testing of output circuits and physical hardware such as
 * injectors and coils on the bench or in the car.
 *
 * @author Fred Cooke
 */


#define DECODER_IMPLEMENTATION_C
#define DECODER_MAX_CODE_TIME    666 // This is optimal!
#define NUMBER_OF_REAL_EVENTS      1 // no events really...
#define NUMBER_OF_VIRTUAL_EVENTS   1 // no events really...


#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"


// Setup the timer interrupts as internal timers only triggered by a serial call that returns if this isn't the decoder.
void decoderInitPreliminary(){
	/// @todo TODO do the setup as required.
}


const unsigned char decoderName[] = "BenchTest";
const unsigned short eventAngles[] = {0};           // no events really...
const unsigned char eventValidForCrankSync[] = {0}; // no events really...


/** Primary RPM ISR
 *
 * @author Fred Cooke
 */
void PrimaryRPMISR(){} // Fire from serial, then repeat X revolutions or seconds or whatever and trigger Z outputs of various types etc


/** Secondary RPM ISR
 *
 * @author Fred Cooke
 */
void SecondaryRPMISR(){} // Possibly unused
