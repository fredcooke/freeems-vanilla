/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010, 2011 Fred Cooke, Jared Harvey
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
 * @brief Injector ISR shared code
 *
 * This code is identical between all 6 channels, and thus we only want one
 * copy of it. The X in each macro will be replaced with the number that is
 * appropriate for the channel it is being used for at the time.
 *
 * Each channel performs the following actions
 *
 * - 1	Clear its interrupt flag
 * - 2	Record its start time
 * - 3	Measure and record its latency
 * - 4	Check to see if its just turned on
 *   - 4.1	Copy the channels pulse width to a local variable
 *   - 4.2	Determine the minimum pulse width based on code run time const and latency
 *   - 4.3	Clamp used pulsewidth inside min and max
 *   - 4.4	If used pulse width is larger than the current period of the engines cycle flag as always on
 *   - 4.5	Set the action to turn off
 *   - 4.6	Increment the time by pulse width
 *   - 4.7	If staging required, either, switch them on and sched to turn off, or sched to turn on
 * - 5	Else it has just turned off
 *   - 5.1	If staged channel is still on, turn it off
 *   - 5.2	If(self schedule flagged) schedule the next start
 *   - 5.3	Else disable itself
 * - 6	Calculate and record code run time
 * - 7	Return
 *
 * @see injectionISRs.c
 */


// Courtesy of Dave Cramer
#define INJECTOR_MAIN_ON_MASK (BIT2<<INJECTOR_CHANNEL_NUMBER)

/** A template function for ECT injector/coil operation.
 *
 * Note, this function does not exist in the binary, only in source and the
 * Doxygen docs. In contrast the 6 real ones only exist in binary and not the
 * source or Doxygen docs, hence if you want to look at the source, this is the
 * place to do so.
 */
void InjectorXISR(){
	/* Clear the interrupt flag for this channel */
	TFLG = INJECTOR_MAIN_ON_MASK;

	/* Record the current time as start time */
	unsigned short TCNTStart = TCNT;

	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT2, PORTB);

	/* Record the edge time stamp from the IC register */
	unsigned short edgeTimeStamp = *injectorMainTimeRegisters[INJECTOR_CHANNEL_NUMBER];

	/* If rising edge triggered this */
	if(PTIT & INJECTOR_MAIN_ON_MASK){ // Stuff for switch on time

		/* Find out what max and min for pulse width are */
		unsigned short localPulseWidth = outputEventPulseWidthsRealtime[INJECTOR_CHANNEL_NUMBER];
		unsigned short localMinimumPulseWidth = injectorSwitchOnCodeTime + injectorCodeLatencies[INJECTOR_CHANNEL_NUMBER];

		/** @todo TODO *maybe* instead of checking min and increasing pulse, just force it straight off if diff between start and now+const is greater than desired pulsewidth */

		/* Ensure we dont go under minimum pulsewidth */
		if(localPulseWidth < localMinimumPulseWidth){
			localPulseWidth = localMinimumPulseWidth;
		}/* else{ just use the value } */

		LongTime timeStamp;

		/* Install the low word */
		timeStamp.timeShorts[1] = edgeTimeStamp;
		/* Find out what our timer value means and put it in the high word */
		if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
			timeStamp.timeShorts[0] = timerExtensionClock + 1;
		}else{
			timeStamp.timeShorts[0] = timerExtensionClock;
		}

		// store the end time for use in the scheduler
		injectorMainEndTimes[INJECTOR_CHANNEL_NUMBER] = timeStamp.timeLong + localPulseWidth;

		/* Set the action for compare to switch off FIRST or it might inadvertently PWM the injector during opening... */
		*injectorMainControlRegisters[INJECTOR_CHANNEL_NUMBER] &= injectorMainGoLowMasks[INJECTOR_CHANNEL_NUMBER];

		/* Set the time to turn off again */
		*injectorMainTimeRegisters[INJECTOR_CHANNEL_NUMBER] += localPulseWidth;

		/* This is the point we actually want the time to, but because the code is so simple, it can't help but be a nice short time */

		Counters.injectorSwitchOns++;

		/* Calculate and store code run time */
		injectorCodeOpenRuntimes[INJECTOR_CHANNEL_NUMBER] = TCNT - TCNTStart;
	}else{ // Stuff for switch off time and repeat timer time.
		if(!(*injectorMainControlRegisters[INJECTOR_CHANNEL_NUMBER] & injectorMainEnableMasks[INJECTOR_CHANNEL_NUMBER])){ // set to no action
			if(outputEventExtendNumberOfRepeatsRealtime[INJECTOR_CHANNEL_NUMBER] > 0){
				*injectorMainTimeRegisters[INJECTOR_CHANNEL_NUMBER] += outputEventExtendRepeatPeriodRealtime[INJECTOR_CHANNEL_NUMBER];
				outputEventExtendNumberOfRepeatsRealtime[INJECTOR_CHANNEL_NUMBER]--;
				Counters.injectorTimerExtensions++;
			}else{
				*injectorMainControlRegisters[INJECTOR_CHANNEL_NUMBER] |= injectorMainEnableMasks[INJECTOR_CHANNEL_NUMBER];
				*injectorMainTimeRegisters[INJECTOR_CHANNEL_NUMBER] += outputEventDelayFinalPeriodRealtime[INJECTOR_CHANNEL_NUMBER];
				// this is already set from the decoder, we're just delaying use of it: outputEventPulseWidthsRealtime[INJECTOR_CHANNEL_NUMBER]
				Counters.injectorTimerExtensionFinals++;
			}
		}else{ // if set to off action (implicit)
			/* Set the action for compare to switch on and the time to next start time, clear the self timer flag */
			if(selfSetTimer & INJECTOR_MAIN_ON_MASK){
				if(outputEventExtendNumberOfRepeatsHolding[INJECTOR_CHANNEL_NUMBER] > 0){
					*injectorMainControlRegisters[INJECTOR_CHANNEL_NUMBER] &= injectorMainDisableMasks[INJECTOR_CHANNEL_NUMBER];
					outputEventExtendNumberOfRepeatsRealtime[INJECTOR_CHANNEL_NUMBER] = outputEventExtendNumberOfRepeatsHolding[INJECTOR_CHANNEL_NUMBER];
					outputEventExtendRepeatPeriodRealtime[INJECTOR_CHANNEL_NUMBER] = outputEventExtendRepeatPeriodHolding[INJECTOR_CHANNEL_NUMBER];
					outputEventDelayFinalPeriodRealtime[INJECTOR_CHANNEL_NUMBER] = outputEventDelayFinalPeriodHolding[INJECTOR_CHANNEL_NUMBER];
					Counters.injectorSelfScheduleExtensions++;
				}else{
					*injectorMainControlRegisters[INJECTOR_CHANNEL_NUMBER] |= injectorMainGoHighMasks[INJECTOR_CHANNEL_NUMBER];
					Counters.injectorSelfSchedules++;
				}
				*injectorMainTimeRegisters[INJECTOR_CHANNEL_NUMBER] += injectorMainStartOffsetHolding[INJECTOR_CHANNEL_NUMBER];
				outputEventPulseWidthsRealtime[INJECTOR_CHANNEL_NUMBER] = outputEventPulseWidthsHolding[INJECTOR_CHANNEL_NUMBER];
				selfSetTimer &= injectorMainOffMasks[INJECTOR_CHANNEL_NUMBER];
			}else{
				// Disable interrupts and actions incase the period from this end to the next start is long (saves cpu)
				TIE &= injectorMainOffMasks[INJECTOR_CHANNEL_NUMBER];
				*injectorMainControlRegisters[INJECTOR_CHANNEL_NUMBER] &= injectorMainDisableMasks[INJECTOR_CHANNEL_NUMBER];
				Counters.injectorSwitchOffs++;
			}
		}
		/* Calculate and store code run time */
		injectorCodeCloseRuntimes[INJECTOR_CHANNEL_NUMBER] = TCNT - TCNTStart;
	}
	/* Calculate and store the latency based on compare time and start time */
	injectorCodeLatencies[INJECTOR_CHANNEL_NUMBER] = TCNTStart - edgeTimeStamp;

	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT2, PORTB);
}
