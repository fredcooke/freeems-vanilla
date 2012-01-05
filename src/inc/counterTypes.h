/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2011 Fred Cooke
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
 * @ingroup allHeaders
 * @ingroup globalHeaders
 * @ingroup dataStructures
 *
 * @brief Counter struct typedefs
 *
 * This file contains all of the counter and statistic struct typedefs.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_COUNTER_TYPES_H_SEEN
#define FILE_COUNTER_TYPES_H_SEEN


// Some Fred Cooke cunning inspired by EssEss
#define FLAG_AND_INC_FLAGGABLE(OFFSET)         \
(*(((unsigned char*)&Flaggables) + OFFSET))++; \
KeyUserDebugs.flaggableFlags |= (1 << OFFSET);               // End of macro

/// These should all stay at zero, thus they are incremented through a mechanism that also sets a flag in a special variable
typedef struct {
	// Error conditions
	unsigned char callsToUISRs;                    ///< to ensure we aren't accidentally triggering unused ISRs.
	unsigned char lowVoltageConditions;            ///< low voltage conditions.
#define FLAG_CALLS_TO_UISRS_OFFSET                 0
#define FLAG_LOW_VOLTATE_CONDITION_OFFSET          1

	// RPM/Position input
	unsigned char decoderSyncLosses;               ///< Number of times cam, crank or combustion sync is lost.
	unsigned char spare;                           ///< Spare.
	unsigned char decoderSyncStateClears;          ///< Sync loss called when not synced yet, thus discarding data and preventing sync.
#define FLAG_DECODER_SYNC_LOSSES_OFFSET            2
#define FLAG_SPARE_OFFSET                          3
#define FLAG_DECODER_SYNC_STATE_CLEARS_OFFSET      4

	// If you're getting these, then your serial hardware sucks
	unsigned char serialNoiseErrors;               ///< Incremented when noise is detected
	unsigned char serialFramingErrors;             ///< Incremented when a framing error occurs
	unsigned char serialParityErrors;              ///< Incremented when a parity error occurs
#define FLAG_SERIAL_NOISE_ERRORS_OFFSET            5
#define FLAG_SERIAL_FRAMING_ERRORS_OFFSET          6
#define FLAG_SERIAL_PARITY_ERRORS_OFFSET           7

	// This is caused by heavy interrupt load delaying serial servicing, just a fact of life at high RPM.
	unsigned char serialOverrunErrors;             ///< Incremented when overrun occurs (duplicated in KeyUserDebug below)
#define FLAG_SERIAL_OVERRUN_ERRORS_OFFSET          8

	// These can be caused by noise, but if there is no noise, then it's a code issue with the PC side application
	unsigned char serialEscapePairMismatches;      ///< Incremented when an escape is found but not followed by an escapee
	unsigned char serialStartsInsideAPacket;       ///< Incremented when a start byte is found inside a packet
	unsigned char serialPacketsOverLength;         ///< Incremented when the buffer fills up before the end
	unsigned char serialChecksumMismatches;        ///< Incremented when calculated checksum did not match the received one
	unsigned char serialPacketsUnderLength;        ///< Incremented when a packet is found that is too short
#define FLAG_SERIAL_ESCAPE_PAIR_MISMATCHES_OFFSET  9
#define FLAG_SERIAL_STARTS_INSIDE_A_PACKET_OFFSET 10
#define FLAG_SERIAL_PACKETS_OVER_LENGTH_OFFSET    11
#define FLAG_SERIAL_CHECKSUM_MISMATCHES_OFFSET    12
#define FLAG_SERIAL_PACKETS_UNDER_LENGTH_OFFSET   13

	// Not currently used
	unsigned char commsDebugMessagesNotSent;       ///< Incremented when a debug message can't be sent due to the TX buffer
	unsigned char commsErrorMessagesNotSent;       ///< Incremented when an error message can't be sent due to the TX buffer
#define FLAG_COMMS_DEBUG_MESSAGES_NOT_SENT_OFFSET 14
#define FLAG_COMMS_ERROR_MESSAGES_NOT_SENT_OFFSET 15
} Flaggable;


/// Use this block to manage the various clocks kept.
typedef struct {
	/* Real Time and other Clocks (all require init to zero) */
	unsigned short realTimeClockMain;      ///< Variable to count RTI executions, 0.125ms exactly
	unsigned short realTimeClockMillis;    ///< Variable to count milliseconds exactly
	unsigned short realTimeClockTenths;    ///< Variable to count tenths of a second exactly
	unsigned short realTimeClockSeconds;   ///< Variable to count seconds exactly
	unsigned short realTimeClockMinutes;   ///< Variable to count minutes exactly

	unsigned short millisToTenths;         ///< Roll-over variable for counting tenths
	unsigned short tenthsToSeconds;        ///< Roll-over variable for counting seconds
	unsigned short secondsToMinutes;       ///< Roll-over variable for counting minutes

	unsigned short timeoutADCreadingClock; ///< Timeout clock/counter for synced ADC readings
} Clock;


/// Use this block to manage the execution count of various functions loops and ISRs etc. TODO break this up into smaller chunks
typedef struct {
	// Scheduling
	unsigned char normalSchedule;                  ///< times events were scheduled normally.
	unsigned char timerStretchedToSchedule;        ///< times timer needed to be extended to prevent not scheduling.

	// Decoder scheduling
	unsigned char pinScheduledToGoHigh;            ///< Behaviour chosen from decoder based on register and pin state.
	unsigned char pinScheduledAlready;             ///< @copydoc pinScheduledToGoHigh
	unsigned char pinScheduledToSelfSchedule;      ///< @copydoc pinScheduledToGoHigh
	unsigned char pinScheduledAgainToStayOn;       ///< @copydoc pinScheduledToGoHigh

	unsigned char pinScheduledToToggleError;       ///< @copydoc pinScheduledToGoHigh
	unsigned char pinScheduledToDoNothing;         ///< @copydoc pinScheduledToGoHigh
	unsigned char pinScheduledFromCold;            ///< @copydoc pinScheduledToGoHigh
	unsigned char pinScheduledWithTimerExtension;  ///< @copydoc pinScheduledToGoHigh

	// Outputs, refactor to not say "injector" later.
	unsigned char injectorSwitchOns;               ///< number of times the injector switched on
	unsigned char injectorSwitchOffs;              ///< number of times the injector switched off to stay off
	unsigned char injectorTimerExtensions;         ///< number of times the injector ISR fired and rescheduled itself to fire and do nothing again
	unsigned char injectorTimerExtensionFinals;    ///< number of times the injector ISR fired and scheduled the injector to switch on

	unsigned char injectorSelfSchedules;           ///< number of times the injector switched off and scheduled itself again
	unsigned char injectorSelfScheduleExtensions;  ///< number of times the injector switched off and scheduled itself again with timer extension

	unsigned char syncedADCreadings;               ///< Incremented each time a synchronous ADC reading is taken
	unsigned char timeoutADCreadings;              ///< Incremented for each ADC reading in RTC because of timeout
	unsigned char calculationsPerformed;           ///< Incremented for each time the fuel and ign calcs are done

	unsigned char sparePadding;                    ///< Replace with something useful
} Counter;


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file COUNTER_TYPES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
