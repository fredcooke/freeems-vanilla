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


/**	@file NipponDenso.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Reads Nippon Denso 24/2 sensors
 *
 * This file contains the two interrupt service routines for handling engine
 * position and RPM signals from mainly Toyota engines using this sensor style.
 *
 * One ISR handles the 24 evenly spaced teeth and the other handles the two
 * adjacent teeth. This signal style provides enough information for wasted
 * spark ignition and semi sequential fuel injection.
 *
 * Supported engines include:
 * - 4A-GE
 * - 7A-FE
 * - 3S-GE
 * - 1UZ-FE
 * - Mazda F2T
 *
 * @author Fred Cooke
 *
 * @note Pseudo code that does not compile with zero warnings and errors MUST be commented out.
 *
 * @todo TODO make this generic for evenly spaced teeth with a pulse per revolution from the second input.
 */


#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/utils.h"


/** Primary RPM ISR
 *
 * Summary of intended engine position capture scheme (out of date as at 3/1/09)
 *
 * Position/RPM signal interpretation :
 * Discard edges that have arrived too soon (lose sync here?)
 * Check to ensure we haven't lost sync (pulse arrives too late)
 * Compare time stamps of successive edges and calculate RPM
 * Store RPM and position in globals
 *
 * Schedule events :
 * loop through all events (spark and fuel), schedule those that fall sufficiently after this tooth and before the next one we expect.
 *
 * Sample ADCs :
 * Grab a unified set of ADC readings at one time in a consistent crank location to eliminate engine cycle dependent noise.
 * Set flag stating that New pulse, advance, etc should be calculated.
 *
 * @author Fred Cooke
 *
 * @warning These are for testing and demonstration only, not suitable for driving with just yet.
 *
 * @todo TODO bring the above docs up to date with reality
 * @todo TODO finish this off to a usable standard
 */
void PrimaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	unsigned short edgeTimeStamp = TC0;				/* Save the edge time stamp */
	unsigned char PTITCurrentState = PTIT;			/* Save the values on port T regardless of the state of DDRT */

	// set as synced for volvo always as loss of sync not actually possible
	coreStatusA |= PRIMARY_SYNC;

	/* Calculate the latency in ticks */
	ISRLatencyVars.primaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	if(PTITCurrentState & 0x01){
		/* Echo input condition on J7 */
		PORTJ |= 0x80;

		Counters.primaryTeethSeen++;

		LongTime timeStamp;

		/* Install the low word */
		timeStamp.timeShorts[1] = edgeTimeStamp;
		/* Find out what our timer value means and put it in the high word */
		if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
			timeStamp.timeShorts[0] = timerExtensionClock + 1;
		}else{
			timeStamp.timeShorts[0] = timerExtensionClock;
		}

		// temporary data from inputs
		primaryLeadingEdgeTimeStamp = timeStamp.timeLong;
		timeBetweenSuccessivePrimaryPulses = primaryLeadingEdgeTimeStamp - lastPrimaryPulseTimeStamp;
		lastPrimaryPulseTimeStamp = primaryLeadingEdgeTimeStamp;

#define ticksPerMinute   75000000
//#define ticksPerCylinder 37500000
		*RPMRecord = (unsigned short) (ticksPerMinute / timeBetweenSuccessivePrimaryPulses);

		// TODO sample ADCs on teeth other than that used by the scheduler in order to minimise peak run time and get clean signals
		sampleEachADC(ADCArrays);
		Counters.syncedADCreadings++;
		*mathSampleTimeStampRecord = TCNT;

		/* Set flag to say calc required */
		coreStatusA |= CALC_FUEL_IGN;

		/* Reset the clock for reading timeout */
		Clocks.timeoutADCreadingClock = 0;

		if(masterPulseWidth > injectorMinimumPulseWidth){ // use reference PW to decide. spark needs moving outside this area though TODO
			/* Determine if half the cycle is bigger than short-max */
			unsigned short maxAngleAfter;
			if((engineCyclePeriod >> 1) > 0xFFFF){
				maxAngleAfter = 0xFFFF;
			}else{
				maxAngleAfter = (unsigned short)(engineCyclePeriod >> 1);
			}

			/* Check advance to ensure it is less than 1/2 of the previous engine cycle and more than codetime away */
			unsigned short advance;
			if(totalAngleAfterReferenceInjection > maxAngleAfter){ // if too big, make it max
				advance = maxAngleAfter;
			}else if(totalAngleAfterReferenceInjection < trailingEdgeSecondaryRPMInputCodeTime){ // if too small, make it min
				advance = trailingEdgeSecondaryRPMInputCodeTime;
			}else{ // else use it as is
				advance = totalAngleAfterReferenceInjection;
			}

			// determine the long and short start times
			unsigned short startTime = edgeTimeStamp + advance;
			unsigned long startTimeLong = timeStamp.timeLong + advance;

			/* Determine the channels to schedule */
			unsigned char fuelChannel = 0;//(primaryPulsesPerSecondaryPulse / 2) - 1;

			// determine whether or not to reschedule
			unsigned char reschedule = 0;
			unsigned long diff = startTimeLong - (injectorMainEndTimes[fuelChannel] + injectorSwitchOffCodeTime);
			if(diff > LONGHALF){
				reschedule = 1; // http://www.diyefi.org/forum/viewtopic.php?f=8&t=57&p=861#p861
			}

			// schedule the appropriate channel
			if(!(*injectorMainControlRegisters[fuelChannel] & injectorMainEnableMasks[fuelChannel]) || reschedule){ /* If the timer isn't still running, or if its set too long, set it to start again at the right time soon */
				*injectorMainControlRegisters[fuelChannel] |= injectorMainEnableMasks[fuelChannel];
				*injectorMainTimeRegisters[fuelChannel] = startTime;
				TIE |= injectorMainOnMasks[fuelChannel];
				TFLG = injectorMainOnMasks[fuelChannel];
			}else{
				injectorMainStartTimesHolding[fuelChannel] = startTime;
				selfSetTimer |= injectorMainOnMasks[fuelChannel]; // setup a bit to let the timer interrupt know to set its own new start from a var
			}
		}
		RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	}else{
		PORTJ &= 0x7F;
		RuntimeVars.primaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
	}
}


/** Secondary RPM ISR
 *
 * Similar to the primary one.
 *
 * @todo TODO bring this documentation up to date.
 * @todo TODO finish this off to a usable standard.
 */
void SecondaryRPMISR(){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	unsigned short edgeTimeStamp = TC1;				/* Save the timestamp */
	unsigned char PTITCurrentState = PTIT;			/* Save the values on port T regardless of the state of DDRT */
//	unsigned short PORTS_BACurrentState = PORTS_BA;	/* Save ignition output state */

	/* Calculate the latency in ticks */
	ISRLatencyVars.secondaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	/** @todo TODO discard narrow ones! test for tooth width and tooth period
	 * the width should be based on how the hardware is setup. IE the LM1815
	 * is adjusted to have a pulse output of a particular width. This noise
	 * filter should be matched to that width as should the hardware filter.
	 */

	LongTime timeStamp;

	/* Install the low word */
	timeStamp.timeShorts[1] = edgeTimeStamp;
	/* Find out what our timer value means and put it in the high word */
	if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
		timeStamp.timeShorts[0] = timerExtensionClock + 1;
	}else{
		timeStamp.timeShorts[0] = timerExtensionClock;
	}

	/* The LM1815 variable reluctance sensor amplifier allows the output to be
	 * pulled high starting at the center of a tooth. So, what we see as the
	 * start of a tooth is actually the centre of a physical tooth. Because
	 * tooth shape, profile and spacing may vary this is the only reliable edge
	 * for us to schedule from, hence the trailing edge code is very simple.
	 */
	if(PTITCurrentState & 0x02){
		// echo input condition
		PORTJ |= 0x40;

		Counters.secondaryTeethSeen++;

		/* leading code
		 *
		 * subtract lastTrailing from currentLeading
		 * record currentLeading as lastLeading
		 *
		 * record pw as highDuration
		 */
		lengthOfSecondaryLowPulses = timeStamp.timeLong - lastSecondaryPulseTrailingTimeStamp;
		lastSecondaryPulseLeadingTimeStamp = timeStamp.timeLong;
	}else{

		/* trailing code
		 *
		 * subtract lastLeading from currentTrailing
		 * record currentTrailing as lastTrailing
		 *
		 * record pw as lowDuration
		 */
//		lengthOfSecondaryHighPulses = timeStamp.timeLong - lastSecondaryPulseLeadingTimeStamp;
		lastSecondaryPulseTrailingTimeStamp = timeStamp.timeLong;

		PORTJ &= 0xBF;
	}
}
