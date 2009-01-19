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


/** @file main.c
 *
 * @brief The main function!
 *
 * The function main is traditionally an applications starting point. For us
 * it has two jobs. The first is to call init() which initialises everything
 * before any normal code runs. After that main() is simply an infinite loop
 * from which low priority non-realtime code runs. The most important units of
 * code that runs under the main loop umbrella are the injection, ignition and
 * scheduling calculations.
 *
 * @author Fred Cooke
 */


#include "inc/main.h"


/** @brief The main function!
 *
 * The centre of the application is here. From here all non-ISR code is called
 * directly or indirectly. The two coarse blocks are init and the main loop.
 * Init is called first to set everything up and then the main loop is entered
 * where the flow of control continues until the device is switched off or
 * reset (excluding asynchronous ISR code). Currently the main loop only runs
 * the fuel, ignition and scheduling calculation code, and only when actually
 * required. The intention is to maintain a very low latency for calculations
 * such that the behaviour of the device more closely reflects the attached
 * engines rapidly changing requirements. When accessory code is added a new
 * scheduling algorithm will be required to keep the latency low without
 * starving any particular blocks of CPU time.
 *
 * @author Fred Cooke
 */
int  main(){ // TODO maybe move this to paged flash ?
	// Set everything up.
	init();

	//LongNoTime.timeLong = 54;
	// Run forever repeating.
	while(TRUE){
	//	unsigned short start = realTimeClockMillis;
		/* If ADCs require forced sampling, sample now */
		if(coreStatusA & FORCE_READING){
			ATOMIC_START(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
			/* Atomic block to ensure a full set of readings are taken together */

			/* Check to ensure that a reading wasn't take before we entered a non interruptable state */
			if(coreStatusA & FORCE_READING){ // do we still need to do this TODO ?

				sampleEachADC(ADCArraysRecord); // TODO still need to do a pair of loops and clock these two functions for performance.
				//sampleLoopADC(&ADCArrays);
				resetToNonRunningState();
				Counters.timeoutADCreadings++;

				/* Set flag to say calc required */
				coreStatusA |= CALC_FUEL_IGN;

				/* Clear force reading flag */
				coreStatusA &= CLEAR_FORCE_READING;
			}

			ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
		}

		/* If required, do main fuel and ignition calcs first */
		if(coreStatusA & CALC_FUEL_IGN){
			ATOMIC_START(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
			/* Atomic block to ensure that we don't clear the flag for the next data set when things are tight */

			/* Switch input bank so that we have a stable set of the latest data */
			if(ADCArrays == &ADCArrays1){
				RPM = &RPM0; // TODO temp, remove
				RPMRecord = &RPM1; // TODO temp, remove
				ADCArrays = &ADCArrays0;
				ADCArraysRecord = &ADCArrays1;
				mathSampleTimeStamp = &ISRLatencyVars.mathSampleTimeStamp0; // TODO temp, remove
				mathSampleTimeStampRecord = &ISRLatencyVars.mathSampleTimeStamp1; // TODO temp, remove
			}else{
				RPM = &RPM1; // TODO temp, remove
				RPMRecord = &RPM0; // TODO temp, remove
				ADCArrays = &ADCArrays1;
				ADCArraysRecord = &ADCArrays0;
				mathSampleTimeStamp = &ISRLatencyVars.mathSampleTimeStamp1; // TODO temp, remove
				mathSampleTimeStampRecord = &ISRLatencyVars.mathSampleTimeStamp0; // TODO temp, remove
			}

			/* Clear the calc required flag */
			coreStatusA &= CLEAR_CALC_FUEL_IGN;

			ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/

			/* Store the latency from sample time to runtime */
			ISRLatencyVars.mathLatency = TCNT - *mathSampleTimeStamp;
			/* Keep track of how many calcs we are managing per second... */
			Counters.calculationsPerformed++;
			/* ...and how long they take each */
			unsigned short mathStartTime = TCNT;

			/* Generate the core variables from sensor input and recorded tooth timings */
			generateCoreVars();

			RuntimeVars.genCoreVarsRuntime = TCNT - mathStartTime;
			unsigned short derivedStartTime = TCNT;

			/* Generate the derived variables from the core variables based on settings */
			generateDerivedVars();

			RuntimeVars.genDerivedVarsRuntime = TCNT - derivedStartTime;
			unsigned short calcsStartTime = TCNT;

			/* Perform the calculations TODO possibly move this to the software interrupt if it makes sense to do so */
			calculateFuelAndIgnition();

			RuntimeVars.calcsRuntime = TCNT - calcsStartTime;
			/* Record the runtime of all the math total */
			RuntimeVars.mathTotalRuntime = TCNT - mathStartTime;

			RuntimeVars.mathSumRuntime = RuntimeVars.calcsRuntime + RuntimeVars.genCoreVarsRuntime + RuntimeVars.genDerivedVarsRuntime;

			ATOMIC_START(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
			/* Atomic block to ensure that outputBank and outputBank Offsets match */

			/* Switch banks to the latest data */
			if(injectorMainPulseWidthsMath == injectorMainPulseWidths1){
				currentDwellMath = &currentDwell0;
				currentDwellRealtime = &currentDwell1;
				injectorMainPulseWidthsMath = injectorMainPulseWidths0;
				injectorMainPulseWidthsRealtime = injectorMainPulseWidths1;
				injectorStagedPulseWidthsMath = injectorStagedPulseWidths0;
				injectorStagedPulseWidthsRealtime = injectorStagedPulseWidths1;
			}else{
				currentDwellMath = &currentDwell1;
				currentDwellRealtime = &currentDwell0;
				injectorMainPulseWidthsMath = injectorMainPulseWidths1;
				injectorMainPulseWidthsRealtime = injectorMainPulseWidths0;
				injectorStagedPulseWidthsMath = injectorStagedPulseWidths1;
				injectorStagedPulseWidthsRealtime = injectorStagedPulseWidths0;
			}

			ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
		}else{
			/* In the event that no calcs are required, sleep a little before returning to retry. */
			sleepMicro(RuntimeVars.mathTotalRuntime); // not doing this will cause the ISR lockouts to run for too high a proportion of the time
			/* Using 0.8 ticks as micros so it will run for a little longer than the math did */
		}


		if(!(TXBufferInUseFlags)){
		//	unsigned short logTimeBuffer = Clocks.realTimeClockTenths;
			/* If the flag for com packet processing is set and the TX buffer is available process the data! */
			if(RXStateFlags & RX_READY_TO_PROCESS){
				/* Clear the flag */
				RXStateFlags &= RX_CLEAR_READY_TO_PROCESS;

				/* Handle the incoming packet */
				decodePacketAndRespond();
			}else if(ShouldSendLog){//(lastTime != logTimeBuffer) && (lastCalcCount != Counters.calculationsPerformed)){

				/* send asynchronous data log if required */
				if(asyncDatalogType!= asyncDatalogOff){
					switch (asyncDatalogType) {
					case asyncDatalogBasic:
					{
						/* Flag that we are transmitting! */
						TXBufferInUseFlags |= COM_SET_SCI0_INTERFACE_ID;
						// SCI0 only for now...

						// headers including length...						*length = configuredBasicDatalogLength;
						TXBufferCurrentPositionHandler = (unsigned char*)&TXBuffer;

						/* Initialised here such that override is possible */
						TXBufferCurrentPositionSCI0 = (unsigned char*)&TXBuffer;
						TXBufferCurrentPositionCAN0 = (unsigned char*)&TXBuffer;

						/* Set the flags : firmware, no ack, no addrs, has length */
						*TXBufferCurrentPositionHandler = HEADER_HAS_LENGTH;
						TXBufferCurrentPositionHandler++;

						/* Set the payload ID */
						*((unsigned short*)TXBufferCurrentPositionHandler) = responseBasicDatalog;
						TXBufferCurrentPositionHandler += 2;

						/* Set the length */
						*((unsigned short*)TXBufferCurrentPositionHandler) = configuredBasicDatalogLength;
						TXBufferCurrentPositionHandler += 2;

						/* populate data log */
						populateBasicDatalog();
						checksumAndSend();
						break;
					}
					case asyncDatalogConfig:
					{
						// TODO
						break;
					}
					case asyncDatalogTrigger:
					{
						// TODO
						break;
					}
					case asyncDatalogADC:
					{
						// TODO
						break;
					}
					case asyncDatalogCircBuf:
					{
						// TODO
						break;
					}
					case asyncDatalogCircCAS:
					{
						// TODO
						break;
					}
					case asyncDatalogLogic:
					{
						// TODO
						break;
					}
					}
				}
				ShouldSendLog = FALSE;
//				// mechanism to ensure we send once per clock tick without doing it in the RTC section.
//				lastTime = logTimeBuffer;
//				// mechanism to ensure we only send something if the data has been updated
//				lastCalcCount = Counters.calculationsPerformed;
			}
		}
		// on once per cycle for main loop heart beat (J0)
		PORTJ ^= 0x01;


		// debug...
		if(SCI0CR2 & SCICR2_RX_ENABLE){
			PORTK |= BIT2;
		}else{
			PORTK &= NBIT2;
		}

		if(SCI0CR2 & SCICR2_RX_ISR_ENABLE){
			PORTK |= BIT3;
		}else{
			PORTK &= NBIT3;
		}

		// PWM experimentation
		adjustPWM();
	}
}
