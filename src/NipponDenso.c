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
//	unsigned short PORTS_BACurrentState = PORTS_BA;	/* Save ignition output state */

	/* Calculate the latency in ticks */
	ISRLatencyVars.primaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	// TODO discard narrow ones! test for tooth width and tooth period

	/* Set up edges as per config */
	unsigned char risingEdge;
	if(fixedConfigs1.coreSettingsA & PRIMARY_POLARITY){
		risingEdge = PTITCurrentState & 0x01;
	}else{
		risingEdge = !(PTITCurrentState & 0x01);
	}

	if(risingEdge){
		/* Echo input condition on J7 */
		PORTJ |= 0x80;

		// increment crank pulses TODO this needs to be wrapped in tooth period and width checking
		primaryPulsesPerSecondaryPulse++;

		// calculate rough rpm (this will be wrong when the var is used correctly)
		*RPMRecord = ticksPerCycleAtOneRPMx2 / engineCyclePeriod; /* 0.8us ticks, 150mil = 2 x 60 seconds, times rpm scale factor of 2 */

		// don't run until the second trigger has come in and the period is correct (VERY temporary)
		if(!(coreStatusA & PRIMARY_SYNC)){
			primaryTeethDroppedFromLackOfSync++;
			return;
		}

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
		primaryLeadingEdgeTimeStamp = edgeTimeStamp;
		timeBetweenSuccessivePrimaryPulses = lastPrimaryPulseTimeStamp - primaryLeadingEdgeTimeStamp;
		lastPrimaryPulseTimeStamp = primaryLeadingEdgeTimeStamp;
		timeBetweenSuccessivePrimaryPulsesBuffer = (timeBetweenSuccessivePrimaryPulses >> 1) + (timeBetweenSuccessivePrimaryPulsesBuffer >> 1);

		// TODO make scheduling either fixed from boot with a limited range, OR preferrably if its practical scheduled on the fly to allow arbitrary advance and retard of both fuel and ignition.

		/* Check for loss of sync by too high a count */
		if(primaryPulsesPerSecondaryPulse > 12){
			/* Increment the lost sync count */
			Counters.crankSyncLosses++;

			/* Clear synced status */
			coreStatusA &= CLEAR_PRIMARY_SYNC;

			/* Reset the count of teeth */
			primaryPulsesPerSecondaryPulse = 0;

			/* Get the hell out of here before we do something bad */
			return;
		}

		// CAUTION came to me lying in bed half asleep idea :

		// TODO move tooth selection to the calc loop in main such that this routine just iterates through an array of events and schedules those that are destined for this tooth.

		// if ign enabled
			// iterate through ignition first, schedule all of those
			// iterate through dwell next, schedule all of those
		// if fuel enabled
			// iterate through main fuel next, schedule all of those
			// if staging enabled and required
				// iterate through staged fuel last,

		// TODO should make for a clean compact scheduling implementation. the fuel code doesn't care when/how it has started in the past, and hopefully ign will be the same.

		// this will be done with an array and per tooth check in future
		if((primaryPulsesPerSecondaryPulse % 2) == 0){

			// TODO sample ADCs on teeth other than that used by the scheduler in order to minimise peak run time and get clean signals
			sampleBlockADC(ADCArrays);
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
				unsigned short startTime = primaryLeadingEdgeTimeStamp + advance;
				unsigned long startTimeLong = timeStamp.timeLong + advance;

				/* Determine the channels to schedule */
				unsigned char fuelChannel = (primaryPulsesPerSecondaryPulse / 2) - 1;
				unsigned char ignitionChannel = (primaryPulsesPerSecondaryPulse / 2) - 1;

				if(fuelChannel > 5 || ignitionChannel > 5){
//					send("bad fuel : ");
	//				sendUC(fuelChannel);
		//			send("bad  ign : ");
			//		sendUC(ignitionChannel);
					return;
				}

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

				// TODO advance/retard/dwell numbers all need range checking etc done. some of this should be done in the calculator section, and some here. currently none is done at all and for that reason, this will not work in a real system yet, if it works at all.
				// as do array indexs here and in the ISRs...


				// TODO implement mechanism for dropping a cylinder in event of over queueing or spark cut/round robin
				// important as ignition sequence disrupted when this occurs as it stands.

				// TODO check queue length checks to ensure we dont count up to somewhere we can never count down from. This could be causing the hanging long phenomina

				// DWELL

				// If dwell is not currently enabled, set it all up
				if(!(PITCE & DWELL_ENABLE)){
					/* Schedule Dwell event (do this first because it comes earliest. */
					// set the channel to fire
					nextDwellChannel = ignitionChannel;

					// set the time
					PITLD0 = advance;
					//				PITLD0 = ignitionAdvances[ignitionChannel] - *currentDwellRealtime; BAD for various reasons!

					// clear the flags first as they apparently become set any old time whether enabled or not.
					PITTF |= DWELL_ENABLE;

					// turn on the ints
					PITINTE |= DWELL_ENABLE;

					// clear the flags first as they apparently become set any old time whether enabled or not.
					PITTF |= DWELL_ENABLE;

					// enable channels
					PITCE |= DWELL_ENABLE;
				}else if(dwellQueueLength == 0){
					// load time offset such that next period is correct
					PITLD0 = (advance - PITCNT0);

					// increment queue length
					dwellQueueLength++;
				}else if(dwellQueueLength > fixedConfigs1.engineSettings.combustionEventsPerEngineCycle){ //TODO sensible figures here for array index OOBE
					// do nothing, or increment a counter or something similar.
				}else{
					unsigned short sumOfDwells = PITLD0;
					// add up the prequeued time periods

					// queue = 1 pitld is all
					// queue = 2 one from 0 index of array AND pitld

					unsigned char index = 0;
					while(index < (dwellQueueLength -1)){
						sumOfDwells += queuedDwellOffsets[index];
						index++;
					}
					//				for(index = 0;index < (dwellQueueLength -1);index++){ // is this right?
					//					sumOfDwells += queuedDwellOffsets[index];
					//				}

					// store time offset in appropriate array location
					queuedDwellOffsets[dwellQueueLength - 1] = advance - (PITCNT0 + sumOfDwells);

					// increment queue length from one or more
					dwellQueueLength++;
				}

				// IGNITION experimental stuff

				// If ignition is not currently enabled, set it all up
				if(!(PITCE & IGNITION_ENABLE)){
					/* Schedule Ignition event (do this first because it comes earliest. */
					// set the channel to fire
					nextIgnitionChannel = ignitionChannel;

					// figure out the time to set the delay reg to
					PITLD1 = advance + injectorMainPulseWidthsRealtime[fuelChannel];
					//				PITLD1 = ignitionAdvances[ignitionChannel + outputBankIgnitionOffset];

					// clear the flags first as they apparently become set any old time whether enabled or not.
					PITTF |= IGNITION_ENABLE;

					// turn on the ints
					PITINTE |= IGNITION_ENABLE;

					// clear the flags first as they apparently become set any old time whether enabled or not.
					PITTF |= IGNITION_ENABLE;

					// enable channels
					PITCE |= IGNITION_ENABLE;
				}else if(ignitionQueueLength == 0){
					// load timer register
					PITLD1 = ((advance + injectorMainPulseWidthsRealtime[fuelChannel]) - PITCNT1);

					// increment to 1
					ignitionQueueLength++;
				}else if(ignitionQueueLength > fixedConfigs1.engineSettings.combustionEventsPerEngineCycle){ //TODO sensible figures here for array index OOBE
					// do nothing, or increment a counter or something similar.
				}else{
					unsigned short sumOfIgnitions = PITLD1;
					// add up the prequeued time periods

					// queue = 1 pitld is all
					// queue = 2 one from 0 index of array AND pitld


					unsigned char index = 0;
					while(index < (ignitionQueueLength - 1)){
						sumOfIgnitions += queuedIgnitionOffsets[index];
						index++;
					}
					//	for(index = 0;index < (ignitionQueueLength -1);index++){ // is this right?
					// 		sumOfIgnitions += queuedIgnitionOffsets[index];
					//	}

					// store time offset in appropriate array location
					queuedIgnitionOffsets[ignitionQueueLength - 1] = advance - (PITCNT1 + sumOfIgnitions);

					// increment from 1 or more
					ignitionQueueLength++;
				}
			}
		}
		RuntimeVars.primaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	}else{
		PORTJ &= 0x7F;
		RuntimeVars.primaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
	}

	Counters.primaryTeethSeen++;
	// suss out rpm and accurate TDC reference

	// if you say it quick, it doesn't sound like much :
	// schedule fuel and ign based on spark cut and fuel cut and timing vars and status vars config vars
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

	// TODO discard narrow ones! test for tooth width and tooth period

	/* Set up edges as per config */
	unsigned char risingEdge;
	if(fixedConfigs1.coreSettingsA & SECONDARY_POLARITY){
		risingEdge = PTITCurrentState & 0x02;
	}else{
		risingEdge = !(PTITCurrentState & 0x02);
	}

	if(risingEdge){
		// echo input condition
		PORTJ |= 0x40;

		// display the crank pulses
		PORTM = (char)primaryPulsesPerSecondaryPulseBuffer;

		primaryPulsesPerSecondaryPulseBuffer = primaryPulsesPerSecondaryPulse;
		primaryPulsesPerSecondaryPulse = 0;

		// if we didn't get the right number of pulses drop sync and start over
		if((primaryPulsesPerSecondaryPulseBuffer != 12) && (coreStatusA & PRIMARY_SYNC)){
			coreStatusA &= CLEAR_PRIMARY_SYNC;
			Counters.crankSyncLosses++;
		}

		LongTime timeStamp;

		/* Install the low word */
		timeStamp.timeShorts[1] = edgeTimeStamp;
		/* Find out what our timer value means and put it in the high word */
		if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
			timeStamp.timeShorts[0] = timerExtensionClock + 1;
		}else{
			timeStamp.timeShorts[0] = timerExtensionClock;
		}

		// get the data we actually want
		engineCyclePeriod = 2 * (timeStamp.timeLong - lastSecondaryOddTimeStamp); // save the engine cycle period
		lastSecondaryOddTimeStamp = timeStamp.timeLong; // save this stamp for next time round

		// Because this is our only reference, each time we get this pulse, we know where we are at (simple mode so far)
		coreStatusA |= PRIMARY_SYNC;
		RuntimeVars.secondaryInputLeadingRuntime = TCNT - codeStartTimeStamp;
	}else{
		PORTJ &= 0xBF;
		RuntimeVars.secondaryInputTrailingRuntime = TCNT - codeStartTimeStamp;
	}

	Counters.secondaryTeethSeen++;
	// suss out phase/engine cycle reference showing which bank we are on

	/* If the flag is not cleared at the beginning then the interrupt gets rescheduled while it is running, hence it can't be done at the end of the ISR */
}
