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


/**	@file realtimeISRs.c
 * @ingroup interruptHandlers
 *
 * @brief Real time interrupts
 *
 * This file contains real time interrupt handlers. Mainly it holds the RTI
 * handler itself, however the modulus down counter and ETC timer overflow
 * functions are here too.
 *
 * @author Fred Cooke
 */


#define REALTIMEISRS_C
#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/commsISRs.h"


/** @brief Real Time Interrupt Handler
 *
 * Handles time keeping, including all internal clocks, and generic periodic
 * tasks that run quickly and must be done on time.
 *
 * @author Fred Cooke
 */
void RTIISR(){
	/* Clear the RTI flag */
	CRGFLG = 0x80;

	/* Record time stamp for code run time reporting */
	unsigned short startTimeRTI = TCNT;

	/* Increment the counter */
	Clocks.realTimeClockMain++;

	/* This function could be performed without the extra variables by rolling over the main ones at the largest multiples of the next ones, but I'm not sure thats better */

	// TODO add content to eighths of a milli RTC ?

	/* Every 8th RTI execution is one milli */
	if(Clocks.realTimeClockMain % 8 == 0){
		/* Increment the milli counter */
		Clocks.realTimeClockMillis++;

		/* Increment the milli roll over variable */
		Clocks.millisToTenths++;

		/* Perform all tasks that are once per millisecond here or preferably main */
		Clocks.timeoutADCreadingClock++;
		if(Clocks.timeoutADCreadingClock > fixedConfigs2.sensorSettings.readingTimeout){
			/* Set force read adc flag */
			coreStatusA |= FORCE_READING;
			Clocks.timeoutADCreadingClock = 0;
		}

		/* Every 100 millis is one tenth */
		if(Clocks.millisToTenths % 100 == 0){
			/* Increment the tenths counter */
			Clocks.realTimeClockTenths++;

			/* Increment the tenths roll over variable */
			Clocks.tenthsToSeconds++;

			/* Reset the millis roll over variable */
			Clocks.millisToTenths = 0;

			/* Perform all tasks that are once per tenth of a second here or preferably main */
			// decrement port H debounce variable till it's zero again.
			if(portHDebounce != 0){
				portHDebounce -= 1;
			}

			/* Every 10 tenths is one second */
			if(Clocks.tenthsToSeconds % 10 == 0){
				/* Increment the seconds counter */
				Clocks.realTimeClockSeconds++;

				/* Increment the seconds roll over variable */
				Clocks.secondsToMinutes++;

				/* Reset the tenths roll over variable */
				Clocks.tenthsToSeconds = 0;
				/* Perform all tasks that are once per second here or preferably main */

				// temp throttling for log due to tuner performance issues (in the bedroom)
				ShouldSendLog = TRUE;
				/* Flash the user LED as a "heartbeat" to let new users know it's alive */
				PORTP ^= 0x80;

				/* Every 60 seconds is one minute, 65535 minutes is enough for us :-) */
				if(Clocks.secondsToMinutes % 60 == 0){
					/* Increment the minutes counter */
					Clocks.realTimeClockMinutes++;

					/* Potentially put an hours field in here and below, but that would be excessive */
					// TODO add hours RTC ?

					/* Reset the seconds roll over variable */
					Clocks.secondsToMinutes = 0;

					/* Perform all tasks that are once per minute here or preferably main */
					// TODO add content in minutes RTC ?

					/* Hours if statement here if we do hours which we probably won't */
				}
			}
		}
	}
	RuntimeVars.RTCRuntime = TCNT - startTimeRTI;
}


/** @brief Tacho pulse generator
 *
 * Currently this is being used to generate a variable frequency tachometer
 * output. Although this is a bit of a waste of a timer resource it does allow
 * tachometers that were intended for engines with a different cylinder count
 * to be used where it would otherwise not be possible.
 *
 * @author Fred Cooke
 */
void ModDownCtrISR(){
	/* Clear the modulus down counter interrupt flag */
	MCFLG = 0x80;

	/* If the rpm isn't genuine go ultra slow */
	if(engineCyclePeriod == ticksPerCycleAtOneRPM){
		tachoPeriod = 65535;
	}else{
		/* Use engine cycle period to setup the frequency of this counter and thereby act as a tacho out */
		tachoPeriod = (unsigned long)engineCyclePeriod / fixedConfigs1.tachoSettings.tachoTotalFactor;
	}
	/* Set the count down value */
	MCCNT = tachoPeriod;

	/* Bit bang the output port */
	PORTA ^= 0x40; // SM pin (A6)
}


/** @brief ECT overflow handler
 *
 * When the ECT free running timer hits 65535 and rolls over, this is run. Its
 * job is to extend the timer to an effective 32 bits for longer measuring much
 * longer periods with the same resolution.
 *
 * @author Fred Cooke
 */
void TimerOverflow(){
	/* Increment the timer extension variable */
	timerExtensionClock++;

	/* Clear the timer overflow interrupt flag */
	TFLGOF = 0x80;
}


/** @todo TODO This could be useful in future once sleeping is implemented.
// Generic periodic interrupt (This only works from wait mode...)
void VRegAPIISR(){
	// Clear the flag needs check because writing a 1 can set this one
	//if(VREGAPICL & 0x01){ // if the flag is set...
		VREGAPICL |= 0x01; // clear it...
	//} // and not otherwise!

	// DO stuff
}
*/
