/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010, 2011 Fred Cooke, Olli Hollmen
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


/**	@file structs.h
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief General struct typedefs
 *
 * This file contains all of the general purpose and smaller struct typedefs.
 *
 * @author Fred Cooke
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
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
 * - char		8 bit (defaults to unsigned, but always specify signed/unsigned anyway)
 * - short		16 bit (defaults to signed, but always specify signed/unsigned anyway)
 * - int		16 bit DO NOT USE! (current compile flags make this 16 bits, but a change of flags could will change your program if you use this because they will all be 32 bit all of a sudden)
 * - long		32 bit (defaults to signed, but always specify signed/unsigned anyway)
 * - long long	64 bit (inefficient, avoid these, if using : defaults to signed, but always specify signed/unsigned anyway)
 * - float		32 bit IEEE floating point numbers (inefficient, avoid these, used fixed point math)
 * - double		64 bit IEEE floating point numbers (inefficient, avoid these, used fixed point math)
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
 * This structure holds:
 * - the size
 * - RAM page and address
 * - flash page and address
 *
 * It is used for looking up the details of a memory block to
 * allow serial operations on RAM and flash data structures.
 */
typedef struct {
	unsigned short flags;    ///< Memory Blocks property flags (elaborate functionality) */
	unsigned short parent;   ///< Parent blocks (?) */
	unsigned char RAMPage;   ///< RAM Page */
	unsigned char FlashPage; ///< Flash Page */
	void* RAMAddress;        ///< RAM Address */
	void* FlashAddress;      ///< Flash Address */
	unsigned short size;     ///< Memory Block Size */
} blockDetails;


/** Use this block to make it easy to manage the derived variables.
 * Calculated from core vars stored in CoreVar .
 */
typedef struct {
	/*  */
	unsigned short LoadMain;		///< Configurable unit of load
//	unsigned short LoadSecondary;

	unsigned short VEMain;			///< Divide by 512 to get %
//	unsigned short VESecondary;

	unsigned short Lambda;			///< Divide by 32768 to get Lamda
	unsigned short AirFlow;			///< Top half of the equation
	unsigned short densityAndFuel;	///< Bottom half of the equation

	unsigned short BasePW;			///< Raw PW before corrections
	unsigned short ETE;				///< Additional PW for ETE correction
	signed short TFCTotal;			///< Transient fuel correction PW (+/-)

	unsigned short EffectivePW;		///< Actual PW of fuel delivery
	unsigned short IDT;				///< Minimum PW before fuel flow begins
	unsigned short RefPW;			///< Reference electrical PW

	unsigned short Advance;         ///< Ignition advance (scaled degrees / oneDegree(currently 50) = degrees)
	unsigned short Dwell;           ///< Dwell Angle (ticks / 1250 = ms)

	// replace highest first to avoid hassles for offset based dave/mtx...
	unsigned short zsp19; /*  */
	unsigned short zsp18; /*  */
	unsigned short zsp17; /*  */
	unsigned short zsp16; /*  */
	unsigned short zsp15; /*  */
	unsigned short zsp14; /*  */
	unsigned short zsp13; /*  */
	unsigned short zsp12; /*  */
	unsigned short zsp11; /*  */
	unsigned short zsp10; /*  */
	unsigned short zsp9;  /*  */
	unsigned short zsp8;  /*  */
	unsigned short zsp7;  /*  */
	unsigned short zsp6;  /*  */
	unsigned short zsp5;  /*  */
	unsigned short zsp4;  /*  */
	unsigned short zsp3;  /*  */
	unsigned short zsp2;  /*  */
	unsigned short zsp1;  /*  */
} DerivedVar;


/** Use this block to manage the execution time of various functions loops and ISRs etc
 */
typedef struct {
	/* Engine position and RPM code runtimes */
	unsigned short primaryInputLeadingRuntime;
	unsigned short primaryInputTrailingRuntime;
	unsigned short secondaryInputLeadingRuntime;
	unsigned short secondaryInputTrailingRuntime;

	/* Mathematics runtimes */
	unsigned short calcsRuntime;
	unsigned short genCoreVarsRuntime;
	unsigned short genDerivedVarsRuntime;
	unsigned short mathTotalRuntime;
	unsigned short mathSumRuntime;

	unsigned short RTCRuntime;

	/*  */
	unsigned short mainLoopRuntime;
	unsigned short logSendingRuntime;
	unsigned short serialISRRuntime;
} RuntimeVar;


/** Use this block to manage the execution time of various functions loops and ISRs etc.
 * - Engine position and RPM code latencies
 * - Injector latencies
 *
 */
typedef struct {
	/* Engine position and RPM code latencies */
	unsigned short primaryInputLatency;
	unsigned short secondaryInputLatency;

	/* Injector latencies */
	unsigned short Injector1Latency;
	unsigned short Injector2Latency;
	unsigned short Injector3Latency;
	unsigned short Injector4Latency;
	unsigned short Injector5Latency;
	unsigned short Injector6Latency;

	unsigned short DwellLatency;
	unsigned short IgniteLatency;

	/* Not an ISR, but important none the less */
	unsigned short mathLatency;
	unsigned short mathSampleTimeStamp0;
	unsigned short mathSampleTimeStamp1;
} ISRLatencyVar;


/** Use this block to make it easy to manage the core variables.
 */
typedef struct {
	/* Calculated and averaged from ADC0 readings */
	unsigned short IAT;			///< Inlet Air Temperature (MAT JS)			: 0.0	-    655.35		(0.01 Kelvin (/100))		*/
	unsigned short CHT;			///< Coolant / Head Temperature (CLT JS)		: 0.0	-    655.35		(0.01 Kelvin (/100))		*/
	unsigned short TPS;			///< Throttle Position Sensor (TPS JS)		: 0.0	-    102.39		(0.001? % (/640))			*/
	unsigned short EGO;			///< Exhaust Gas Oxygen (O2 JS)				: 0.000	-      1.999999	(0.0001? lambda (/32768))	*/
	unsigned short MAP;			///< Manifold Absolute Pressure (5euroh1)		: 0.0	-    655.35		(0.01 kPa (/100))			*/
	unsigned short AAP;			///< Atmospheric Absolute Pressure (6euroh1)	: 0.0	-    655.35		(0.01 kPa (/100))			*/
	unsigned short BRV;			///< Battery Reference Voltage (4euroh1)		: 0.000	-     65.535	(0.001 Volts (/1000))		*/
	unsigned short MAT;			///< Manifold Air Temperature (Spare JS)		: 0.0	-    655.35		(0.01 Kelvin (/100))		*/

	/* Calculated and averaged from ADC1 readings */
	unsigned short EGO2;		///< Exhaust Gas Oxygen (NC)					: 0.000	-      1.999999	(0.0001? lambda (/32768))	*/
	unsigned short IAP;			///< Intercooler Absolute Pressure (NC)		: 0.0	-    655.35		(0.01 kPa (/100))			*/
	unsigned short MAF;			///< Mass Air Flow							: 0.0	-  65535.0		(raw units from lookup)		*/

	/* Calculated from MAP and TPS history */
	unsigned short DMAP;		///< Delta MAP kPa/second or similar */
	unsigned short DTPS;		///< Delta TPS %/second or similar */

	/* Calculated from engine position data */
	unsigned short RPM;			///< Revolutions Per Minute (Calced)			: 0		-  32767.5		(0.5 RPM (/2))				*/
	unsigned short DRPM;		///< Delta RPM (Calced)						: 0		-  32767.5		(0.5 RPM/Second (/2))		*/
	unsigned short DDRPM;		///< Delta Delta RPM (Calced)					: 0		-  32767.5		(0.5 RPM/Second^2 (/2))		*/
} CoreVar;


/** Use this block to ensure that the components are contiguous and we can then reference
 * them via offsets and pointers (NC= Not (likely) connected).
 */
typedef struct {
	/* ADC0 raw readings */
	unsigned short IAT;       ///< Inlet Air Temperature (MAT JS)          */ /* COMPULSORY!                 */
	unsigned short CHT;       ///< Coolant / Head Temperature (CLT JS)     */ /* COMPULSORY!                 */
	unsigned short TPS;       ///< Throttle Position Sensor (TPS JS)       */ /* Reduced performance without */
	unsigned short EGO;       ///< Exhaust Gas Oxygen (O2 JS)              */ /* Recommended                 */
	unsigned short MAP;       ///< Manifold Absolute Pressure (5euroh1)    */ /* COMPULSORY OR TPS OR MAF    */
	unsigned short AAP;       ///< Atmospheric Absolute Pressure (6euroh1) */ /* Recommended                 */
	unsigned short BRV;       ///< Battery Reference Voltage (4euroh1)     */ /* COMPULSORY!                 */
	unsigned short MAT;       ///< Manifold Air Temperature (Spare JS)     */ /* Could help heat soak issues */

	/* ADC1 raw readings */
	unsigned short EGO2;      ///< Exhaust Gas Oxygen (NC)                 */ /* Option for V/boxer engines  */
	unsigned short IAP;       ///< Intercooler Absolute Pressure (NC)      */ /* Option for turbo engines    */
	unsigned short MAF;       ///< Mass Air Flow (NC)                      */ /* Option for OEM engines      */
	unsigned short SpareADC3; ///< Spare ADC1 port 3 (NC)                  */
	unsigned short SpareADC4; ///< Spare ADC1 port 4 (NC)                  */
	unsigned short SpareADC5; ///< Spare ADC1 port 5 (NC)                  */
	unsigned short SpareADC6; ///< Spare ADC1 port 6 (NC)                  */
	unsigned short SpareADC7; ///< Spare ADC1 port 7 (NC)                  */
} ADCArray;


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


#define MAINTABLE_RPM_LENGTH 16 		///< How many cells on the X axis */ //24
#define MAINTABLE_LOAD_LENGTH 16 		///< How many cells on the Y axis */ //19
#define MAINTABLE_MAX_RPM_LENGTH 27		///< How many cells on the X axis max */
#define MAINTABLE_MAX_LOAD_LENGTH 21	///< How many cells on the Y axis max */
#define MAINTABLE_MAX_MAIN_LENGTH 462	///< 924B 462 shorts maximum main table length */

// @struct maintable

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
	unsigned short RPMLength;						///< The length of the RPM axis array */
	unsigned short LoadLength;						///< The length of the Load axis array */
	unsigned short RPM[MAINTABLE_MAX_RPM_LENGTH];		///< The array of RPM (X) axis values */
	unsigned short Load[MAINTABLE_MAX_LOAD_LENGTH];		///< The array of Load (Y) axis values */
	unsigned short Table[MAINTABLE_MAX_MAIN_LENGTH];	///< The table as an array of values */
} mainTable;
CASSERT(sizeof(mainTable) == flashSectorSize, mainTable)


#define TWODTABLEUS_LENGTH 16
/** This block used for various curves */
typedef struct {
	unsigned short Axis[TWODTABLEUS_LENGTH];
	unsigned short Values[TWODTABLEUS_LENGTH];
} twoDTableUS;


#define TWODTABLESS_LENGTH 16
/** This block used for various curves */
typedef struct {
	signed short Axis[TWODTABLESS_LENGTH];
	signed short Values[TWODTABLESS_LENGTH];
} twoDTableSS;


#define TWODTABLEMS_LENGTH 16
/** This block used for various curves */
typedef struct {
	unsigned short Axis[TWODTABLEMS_LENGTH];
	signed short Values[TWODTABLEMS_LENGTH];
} twoDTableMS;


#define TWODTABLEUC_LENGTH 8
/** This block used for various curves */
typedef struct {
	unsigned char Axis[TWODTABLEUC_LENGTH];
	unsigned char Values[TWODTABLEUC_LENGTH];
} twoDTableUC;


/** Use this block to manage the execution count of various functions loops and ISRs etc.
 *
 */
typedef struct {
	// Error conditions
	unsigned char callsToUISRs;                    ///< to ensure we aren't accidentally triggering unused ISRs.
	unsigned char lowVoltageConditions;            ///< low voltage conditions.

	// RPM/Position input
	unsigned char decoderSyncLosses;               ///< lost decoder syncs.
	unsigned char decoderSyncCorrections;          ///< definite decoder syncs found while already synced in a different position.
//	unsigned short RPMValidityLosses;              ///< lost RPM validity events.

	// Scheduling
	unsigned char normalSchedule;                  ///< times events were scheduled normally.
	unsigned char tooFarToSchedule;                ///< times sched wasnt done to prevent excess advance.
	unsigned char dwellStretchedToSchedule;        ///< times sched needed to extend dwell to prevent excess advance.
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

	unsigned short primaryTeethSeen;               ///< Free running counters for number of teeth seen such that... */
	unsigned short secondaryTeethSeen;             ///< ...tooth timing can be used to reconstruct the signal at lower rpm */

	unsigned short syncedADCreadings;              ///< Incremented each time a synchronous ADC reading is taken */
	unsigned short timeoutADCreadings;             ///< Incremented for each ADC reading in RTC because of timeout */

	unsigned short calculationsPerformed;          ///< Incremented for each time the fuel and ign calcs are done */
	unsigned short datalogsSent;                   ///< Incremented for each time we send out a log entry */

	// UART/serial specific counters
	unsigned char serialEscapePairMismatches;      ///< Incremented when an escape is found but not followed by an escapee */
	unsigned char serialStartsInsideAPacket;       ///< Incremented when a start byte is found inside a packet */
	unsigned char serialPacketsOverLength;         ///< Incremented when the buffer fills up before the end */
	unsigned char serialNoiseErrors;               ///< Incremented when noise is detected */
	unsigned char serialOverrunErrors;             ///< Incremented when an overrun occurs */
	unsigned char serialFramingErrors;             ///< Incremented when a framing error occurs */
	unsigned char serialParityErrors;              ///< Incremented when a parity error occurs */

	// Generic com counters
	unsigned char commsChecksumMismatches;         ///< Incremented when calculated checksum did not match the received one */
	unsigned char commsPacketsUnderMinLength;      ///< Incremented when a packet is found that is too short */
	unsigned char commsDebugMessagesNotSent;       ///< Incremented when a debug message can't be sent due to the TX buffer */
	unsigned char commsErrorMessagesNotSent;       ///< Incremented when an error message can't be sent due to the TX buffer */

	// GP use (pad the struct with the number of these)
	unsigned char testUC0;                         ///< General purpose counter, 0 - 255 value, use for debugging new code or problem setups.
	unsigned char testUC1;                         ///< @copydoc testUC0
	unsigned char testUC2;                         ///< @copydoc testUC0
	unsigned char testUC3;                         ///< @copydoc testUC0
	unsigned char testUC4;                         ///< @copydoc testUC0
	unsigned char testUC5;                         ///< @copydoc testUC0
	unsigned char testUC6;                         ///< @copydoc testUC0

	// GP use
	unsigned short testUS0;                        ///< General purpose counter, 0 - 65535 value, use for debugging new code or problem setups.
	unsigned short testUS1;                        ///< @copydoc testUS0
	unsigned short testUS2;                        ///< @copydoc testUS0
	unsigned short testUS3;                        ///< @copydoc testUS0
	unsigned short testUS4;                        ///< @copydoc testUS0
	unsigned short testUS5;                        ///< @copydoc testUS0
} Counter;


/** Use this block to manage the various clocks kept.
 */
typedef struct {
	/* Real Time and other Clocks (all require init to zero) */
	unsigned short realTimeClockMain;					///< Variable to count RTI executions, 0.125ms exactly	*/
	unsigned short realTimeClockMillis;					///< Variable to count milliseconds exactly				*/
	unsigned short realTimeClockTenths;					///< Variable to count tenths of a second exactly		*/
	unsigned short realTimeClockSeconds;				///< Variable to count seconds exactly					*/
	unsigned short realTimeClockMinutes;				///< Variable to count minutes exactly					*/

	unsigned short millisToTenths;						///< Roll-over variable for counting tenths				*/
	unsigned short tenthsToSeconds;						///< Roll-over variable for counting seconds				*/
	unsigned short secondsToMinutes;					///< Roll-over variable for counting minutes				*/

	unsigned short timeoutADCreadingClock;				///< Timeout clock/counter for synced ADC readings		*/
} Clock;


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file STRUCTS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
