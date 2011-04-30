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
 * @ingroup enginePositionRPMDecoders
 *
 * To facilitate testing of output circuits and physical hardware such as
 * injectors and coils on the bench or in the car.
 *
 * @todo TODO setup the timer registers as required.
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
#include "../inc/BenchTest.h"


// Setup the timer interrupts as internal timers only triggered by a serial call that returns if this isn't the decoder.
void decoderInitPreliminary(){}
void perDecoderReset(){} // Nothing special to reset for this code


const unsigned char decoderName[] = BENCH_TEST_NAME;
const unsigned short eventAngles[] = {0};           // no events really...
const unsigned char eventValidForCrankSync[] = {0}; // no events really...


unsigned short testCount; // move this to where it can be set from the comms switch


/* Fire from serial, then repeat X revolutions or seconds or whatever and trigger Z outputs of various types etc
 *
 * Possible modes of repetition:
 * - Iterations
 * - Revolutions
 * - Time units
 */
void PrimaryRPMISR(){
	TFLG = 0x01;

	unsigned char shouldFire = 0;
//	unsigned long localPeriod = 0; // mutlifire or busy wait, if doing this, check last period for some min, and if too small, shrink second to last and increase last
	unsigned short localPeriod = 0; // normal mode
	if(testMode == TEST_MODE_ITERATIONS){
		testCount--;
		if(testCount == 0){
			//TIE = disable;
		}else{
			//localPeriod = decoderPeriod;
		}
		shouldFire = ONES;
	// no else just yet, refactor for more advanced testing such as
	}else if(testMode == TEST_MODE_REVOLUTIONS){
		// sub modes of different patterns, use scheduler for this by setting the ADC array up and probing/triggering/touching/poking/starting/
		// switch statement for selecting different const arrays of angles, use busy wait, or multiple interrupt to do larger gaps for lower rpms/coarse events
		// perhaps accept the pattern in the input packet and busy wait on some "run completed" flag before returning and freeing the buffer.
	}else if(testMode == TEST_MODE_TIME_UNITS_SECONDS){
		// reset all timer modes for first time around, then check for timer >= requested value, check appropriate units of time, obviously...
	}else if(testMode == TEST_MODE_TIME_UNITS_MINUTES){
		// ditto
	}else if(testMode == TEST_MODE_TIME_UNITS_HOURS){
		// ditto again
	}else{
		// de-configure timers and leave shouldFire zeroed.
	}

	if(TRUE /*TIE == enabled*/){
		TC0 += localPeriod;
		// configuration for multiple periods setup here.

		// fire outputs here
		unsigned char channel;
		for(channel = 3;channel<(3+6);channel++){
			if(shouldFire & (1 << channel)){
				//TCTL? = ?; // setup to switch on outputs as required
				//TCX = future value;
				//TIE = ?; // turn on interrupts for configured channels
			}
		}
	}

	// TODO do i check in decoders for outputs that have gone off recently? ie, are off, with interrupt set? if so, what do i do? i can just take control of such pins again at that point. i may just check for pins that aren't on, and not look at flags, etc.
}


void SecondaryRPMISR(){
	TFLG = 0x02;
}
