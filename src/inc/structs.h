/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2011 Fred Cooke, Olli Hollmen
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


/** @file structs.h
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief General struct typedefs
 *
 * This file contains all of the general purpose and smaller struct typedefs.
 *
 * @author Fred Cooke
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_STRUCTS_H_SEEN
#define FILE_STRUCTS_H_SEEN


/** @section fornoobs Reading For Newcomers
 * - http://www.space.unibe.ch/comp_doc/c_manual/C/SYNTAX/struct.html
 * - http://en.wikipedia.org/wiki/Composite_type
 * - http://www.cs.usfca.edu/~wolber/SoftwareDev/C/CStructs.htm
 * - http://sandbox.mc.edu/~bennet/cs220/codeex/struct_c.html
 */


/* @section naming Naming
 * Naming should be in the singular form such that the instantiation can be the plural
 */


/** @section typesumm Types summary
 *
 * BEWARE : Be explicit!!
 *
 * - char        8 bit (defaults to unsigned, but always specify signed/unsigned anyway)
 * - short      16 bit (defaults to signed, but always specify signed/unsigned anyway)
 * - int        16 bit DO NOT USE! (current compile flags make this 16 bits, but a change of flags could will change your program if you use this because they will all be 32 bit all of a sudden)
 * - long       32 bit (defaults to signed, but always specify signed/unsigned anyway)
 * - long long  64 bit (inefficient, avoid these, if using : defaults to signed, but always specify signed/unsigned anyway)
 * - float      32 bit IEEE floating point numbers (inefficient, avoid these, used fixed point math)
 * - double     64 bit IEEE floating point numbers (inefficient, avoid these, used fixed point math)
 */


// TODO various new structs
// Status struct
// Ignition struct
// Injection struct
// Engine position struct
// Validity flags, or they should be in the status struct?

/* @section blkmask blockDetails Masks
 * block_ prefixed defines have Masks for the flag field in the blockDetails struct.
 *
 */
// TODO: Get previous comment blocks (@section) associate correctly with content.

/** Memory block has parent */
#define block_has_parent           BIT0_16
#define block_is_in_ram            BIT1_16
#define block_is_in_flash          BIT2_16
#define block_is_indexable         BIT3_16
#define block_is_read_only         BIT4_16
#define block_gets_verified        BIT5_16
#define block_for_backup_restore   BIT6_16
#define block_spare_flag_7         BIT7_16
#define block_spare_flag_8         BIT8_16
#define block_spare_flag_9         BIT9_16
#define block_spare_flag_10        BIT10_16
#define block_spare_flag_11        BIT11_16
#define block_is_2dus_table        BIT12_16
#define block_is_main_table        BIT13_16
#define block_is_lookup_data       BIT14_16
#define block_is_configuration     BIT15_16

/** Addressable memory block description.
 *
 * This structure holds all details required to manipulate a particular block.
 *
 * It is used for passing around the details of a memory block to allow serial
 * operations on RAM and flash data structures in a safe and protected way.
 */
typedef struct {
	unsigned short flags;    ///< Property flags, see flag masks above
	unsigned short parent;   ///< Location ID of parent block if sub block
	unsigned char RAMPage;   ///< RAM page number
	unsigned char FlashPage; ///< Flash page number
	void* RAMAddress;        ///< RAM address
	void* FlashAddress;      ///< Flash address
	unsigned short size;     ///< Memory block size
} blockDetails;


/** Use this block to ensure that the components are contiguous and we can then reference
 * them via offsets and pointers (NC= Not (likely) connected).
 */
typedef struct {
	/* ADC0 raw readings */
	unsigned short IAT;       ///< Inlet Air Temperature
	unsigned short CHT;       ///< Coolant / Head Temperature
	unsigned short TPS;       ///< Throttle Position Sensor
	unsigned short EGO;       ///< Exhaust Gas Oxygen
	unsigned short MAP;       ///< Manifold Absolute Pressure
	unsigned short AAP;       ///< Atmospheric Absolute Pressure
	unsigned short BRV;       ///< Battery Reference Voltage
	unsigned short MAT;       ///< Manifold Air Temperature

	/* ADC1 raw readings (Subject to change! http://issues.freeems.org/view.php?id=190) */
	unsigned short EGO2;      ///< Exhaust Gas Oxygen
	unsigned short IAP;       ///< Intercooler Absolute Pressure
	unsigned short MAF;       ///< Mass Air Flow
	unsigned short SpareADC3; ///< Spare ADC1 port 3
	unsigned short SpareADC4; ///< Spare ADC1 port 4
	unsigned short SpareADC5; ///< Spare ADC1 port 5
	unsigned short SpareADC6; ///< Spare ADC1 port 6
	unsigned short SpareADC7; ///< Spare ADC1 port 7
} ADCBuffer;


/// Use this block to make it easy to manage the core variables.
typedef struct {
	/* Calculated and averaged from ADC0 readings */
	unsigned short IAT;   ///< Inlet Air Temperature           : 0.0 -   655.35       (0.01 Kelvin (/100))
	unsigned short CHT;   ///< Coolant / Head Temperature      : 0.0 -   655.35       (0.01 Kelvin (/100))
	unsigned short TPS;   ///< Throttle Position Sensor        : 0.0 -   102.398438   (0.0015625 % (/640))
	unsigned short EGO;   ///< Exhaust Gas Oxygen              : 0.0 -     1.99996948 (0.0000305175781 lambda (/32768))
	unsigned short MAP;   ///< Manifold Absolute Pressure      : 0.0 -   655.35       (0.01 kPa (/100))
	unsigned short AAP;   ///< Atmospheric Absolute Pressure   : 0.0 -   655.35       (0.01 kPa (/100))
	unsigned short BRV;   ///< Battery Reference Voltage       : 0.0 -    65.535      (0.001 Volts (/1000))
	unsigned short MAT;   ///< Manifold Air Temperature        : 0.0 -   655.35       (0.01 Kelvin (/100))

	/* Calculated and averaged from ADC1 readings (Subject to change! http://issues.freeems.org/view.php?id=190) */
	unsigned short EGO2;  ///< Exhaust Gas Oxygen              : 0.0 -     1.99996948 (0.0000305175781 lambda (/32768))
	unsigned short IAP;   ///< Intercooler Absolute Pressure   : 0.0 -   655.35       (0.01 kPa (/100))
	unsigned short MAF;   ///< Mass Air Flow                   : 0.0 - 65535.0        (raw units from lookup)

	/* Calculated from MAP and TPS history */
	unsigned short DMAP;  ///< Delta MAP kPa/second or similar
	unsigned short DTPS;  ///< Delta TPS %/second or similar

	/* Calculated from engine position data */
	unsigned short RPM;   ///< Revolutions Per Minute (Calced) : 0.0 - 32767.5        (0.5 RPM (/2))
	unsigned short DRPM;  ///< Delta RPM (Calced)              : 0.0 - 32767.5        (0.5 RPM/Second (/2))
	unsigned short DDRPM; ///< Delta Delta RPM (Calced)        : 0.0 - 32767.5        (0.5 RPM/Second^2 (/2))
} CoreVar;


/** Use this block to make it easy to manage the derived variables.
 * Calculated from core vars stored in CoreVar .
 */
typedef struct {
	/*  */
	unsigned short LoadMain;       ///< Configurable unit of load, same scale as VE by default
	unsigned short VEMain;         ///< Divide by 512 to get 0 - 128%
	unsigned short Lambda;         ///< Divide by 32768 to get Lamda 0 - 2.0

	// TODO remove these:
	unsigned short AirFlow;        ///< Top half of the equation - intermediate, take this out of derived vars into own special struct with other intermediates
	unsigned short densityAndFuel; ///< Bottom half of the equation - ditto, or, just ditch. This is dev/debug code, really...

	unsigned short BasePW;         ///< Raw PW before corrections divide by 1250 for ms
	unsigned short ETE;            ///< Engine Temperature Enrichment percentage correction divide by 327.68 for 0 - 200%
	signed short TFCTotal;         ///< Transient fuel correction PW (+/-) divide by 1250 for ms

	unsigned short EffectivePW;    ///< Actual PW of fuel delivery, before per channel corrections, divide by 1250 for ms
	unsigned short IDT;            ///< PW duration before fuel flow begins, before per channel corrections, divide by 1250 for ms
	unsigned short RefPW;          ///< Reference electrical PW what each cylinder is based on, used for all general decisions, divide by 1250 for ms

	unsigned short Advance;        ///< Ignition advance (scaled degrees / oneDegree(currently 50) = degrees)
	unsigned short Dwell;          ///< Dwell period, divide by 1250 for ms
} DerivedVar;


/** A compile time assertion check.
 *
 *  Validate at compile time that the predicate is true without
 *  generating code. This can be used at any point in a source file
 *  where typedef is legal.
 *
 *  On success, compilation proceeds normally.
 *
 *  On failure, attempts to typedef an array type of negative size. The
 *  offending line will look like
 *      typedef assertion_failed_file_h_42[-1]
 *  where file is the content of the second parameter which should
 *  typically be related in some obvious way to the containing file
 *  name, 42 is the line number in the file on which the assertion
 *  appears, and -1 is the result of a calculation based on the
 *  predicate failing.
 *
 *  @param predicate The predicate to test. It must evaluate to
 *  something that can be coerced to a normal C boolean.
 *
 *  @param file A sequence of legal identifier characters that should
 *  uniquely identify the source file in which this condition appears.
 */
#define CASSERT(predicate, file) _impl_CASSERT_LINE(predicate,__LINE__,file)
#define _impl_PASTE(a,b) a##b
#define _impl_CASSERT_LINE(predicate, line, file) typedef char _impl_PASTE(assertion_failed_##file##_,line)[2*!!(predicate)-1];


#define MAINTABLE_RPM_LENGTH 16       ///< How many cells on the X axis Should be, will be and was 24
#define MAINTABLE_LOAD_LENGTH 16      ///< How many cells on the Y axis Should be, will be and was 19
#define MAINTABLE_MAX_RPM_LENGTH 27   ///< How many cells on the X axis max
#define MAINTABLE_MAX_LOAD_LENGTH 21  ///< How many cells on the Y axis max
#define MAINTABLE_MAX_MAIN_LENGTH 462 ///< 924B 462 shorts maximum main table length


/**	Main Table Structure definition
 *
 * Use this table descriptor to manage the
 * - main VE table
 * - Lambda table
 * - Timing tables
 *
 * Tables can be made any size from 1x1 to 27x17 or 22x21 provided that the multiple of
 * the two doesn't exceed the max main length and neither axis exceeds it's
 * specified maximum.
 *
 * Currently the following tables use this structure:
 * - VETableMainFlash;
 * - VETableSecondaryFlash;
 * - VETableTertiaryFlash;
 * - LambdaTableFlash;
 * - IgnitionAdvanceTableMainFlash;
 * - IgnitionAdvanceTableSecondaryFlash;
 * - InjectionAdvanceTableMainFlash;
 * - InjectionAdvanceTableSecondaryFlash;
 * - VETableMainFlash2;
 * - VETableSecondaryFlash2;
 * - VETableTertiaryFlash2;
 * - LambdaTableFlash2;
 * - IgnitionAdvanceTableMainFlash2;
 * - IgnitionAdvanceTableSecondaryFlash2;
 * - InjectionAdvanceTableMainFlash2;
 * - InjectionAdvanceTableSecondaryFlash2;
 *
 * For a more detailed discussion of how this structure is actually used...
 *
 * @see lookupPagedMainTableCellValue
 *
 * @author Fred Cooke
 */
typedef struct {
	unsigned short RPMLength;                        ///< The length of the RPM axis array
	unsigned short LoadLength;                       ///< The length of the Load axis array
	unsigned short RPM[MAINTABLE_MAX_RPM_LENGTH];    ///< The array of RPM (X) axis values
	unsigned short Load[MAINTABLE_MAX_LOAD_LENGTH];  ///< The array of Load (Y) axis values
	unsigned short Table[MAINTABLE_MAX_MAIN_LENGTH]; ///< The table as an array of values
} mainTable;
CASSERT(sizeof(mainTable) == flashSectorSize, mainTable)


#define TWODTABLEUS_LENGTH 16
/// This block used for various curves
typedef struct {
	unsigned short Axis[TWODTABLEUS_LENGTH];
	unsigned short Values[TWODTABLEUS_LENGTH];
} twoDTableUS;


#define TWODTABLESS_LENGTH 16
/// This block used for various curves
typedef struct {
	signed short Axis[TWODTABLESS_LENGTH];
	signed short Values[TWODTABLESS_LENGTH];
} twoDTableSS;


#define TWODTABLEMS_LENGTH 16
/// This block used for various curves
typedef struct {
	unsigned short Axis[TWODTABLEMS_LENGTH];
	signed short Values[TWODTABLEMS_LENGTH];
} twoDTableMS;


#define TWODTABLEUC_LENGTH 8
/// This block used for various curves
typedef struct {
	unsigned char Axis[TWODTABLEUC_LENGTH];
	unsigned char Values[TWODTABLEUC_LENGTH];
} twoDTableUC;


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

	unsigned char syncedADCreadings;              ///< Incremented each time a synchronous ADC reading is taken
	unsigned char timeoutADCreadings;             ///< Incremented for each ADC reading in RTC because of timeout
	unsigned char calculationsPerformed;          ///< Incremented for each time the fuel and ign calcs are done

	unsigned char sparePadding;                    ///< Replace with something useful
} Counter;


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


/// Important "always send" stuff for datalogging
typedef struct {
	// To be improved MAJORLY:
	unsigned short tempClock;      ///< Incremented once per log sent, to be moved to a char TODO

	// All flags! Pair keeps things sane for hacky apps that think everything is 16 bit.
	unsigned char coreStatusA;     ///< Duplicated, migrate here, remove global var
	unsigned char decoderFlags;    ///< Various decoder state flags
	unsigned short flaggableFlags; ///< Flags to go with our flaggables struct.
	// counter flags once counter mechanism implemented

	// These things should only exist once in memory, and should be grouped in a struct, perhaps this one
	unsigned char currentEvent;          ///< Which input event was last to come in
	unsigned char syncLostWithThisID;    ///< A unique identifier for the reason behind a loss of sync
	unsigned char syncLostOnThisEvent;   ///< Where in the input pattern it all went very badly wrong
	unsigned char syncCaughtOnThisEvent; ///< Where in the input pattern that things started making sense
	unsigned char syncResetCalls;        ///< Sum of sync losses and state clears
	unsigned char primaryTeethSeen;      ///< Free running counters for number of input events, useful at lower RPM
	unsigned char secondaryTeethSeen;    ///< @copydoc primaryTeethSeen

	// Likewise these too
	unsigned char serialOverrunErrors;         ///< Incremented when an overrun occurs due to high interrupt load, not a fault, just a fact of life at high RPM
	unsigned char serialHardwareErrors;     ///< Sum of noise, parity, and framing errors
	unsigned char serialAndCommsCodeErrors; ///< Sum of checksum, escape mismatches, starts inside, and over/under length
	unsigned short inputEventTimeTolerance;    ///< Required to tune noise rejection over RPM TODO add to LT1 and MissingTeeth

	// replace highest first to avoid hassles for offset based dave/mtx...
	unsigned short zsp10; ///< Spare US variable
	unsigned short zsp9;  ///< Spare US variable

	unsigned short zsp8;  ///< Spare US variable
	unsigned short zsp7;  ///< Spare US variable
	unsigned short zsp6;  ///< Spare US variable
	unsigned short zsp5;  ///< Spare US variable
	unsigned short zsp4;  ///< Spare US variable
	unsigned short zsp3;  ///< Spare US variable
	// Do we want these recorded at log assembly time, or at recording of ADC time, or at calculation of vars (core and/or deriv) or at enabling of scheduling, or all of the above?
	unsigned short clockInMilliSeconds; ///< Migrate to start of all large datalogs once analysed
	unsigned short clockIn8thsOfAMilli; ///< Migrate to start of all large datalogs once analysed
} KeyUserDebug;

// Any changes to the above that don't maintain the same size will change the packet size
#define maxBasicDatalogLength (sizeof(CoreVar) + sizeof(DerivedVar) + sizeof(KeyUserDebug))


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file STRUCTS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
