/*	structs.h

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
	along with any FreeEMS software.  If not, see <http://www.gnu.org/licenses/>.

	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org

	Thank you for choosing FreeEMS to run your engine! */

/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_STRUCTS_H_SEEN
#define FILE_STRUCTS_H_SEEN


/* For noobs	: http://www.space.unibe.ch/comp_doc/c_manual/C/SYNTAX/struct.html
 *				  http://en.wikipedia.org/wiki/Composite_type
 *				  http://www.cs.usfca.edu/~wolber/SoftwareDev/C/CStructs.htm
 *				  http://sandbox.mc.edu/~bennet/cs220/codeex/struct_c.html
 */


/* Naming should be in the singular form such that the instantiation can be the plural */


/* Types summary
 *
 * BEWARE : Be explicit!!
 *
 * char			8 bit (defaults to unsigned, but always specify signed/unsigned anyway)
 * short		16 bit (defaults to signed, but always specify signed/unsigned anyway)
 * int			16 bit DO NOT USE! (current compile flags make this 16 bits, but a change of flags could will change your program if you use this because they will all be 32 bit all of a sudden)
 * long			32 bit (defaults to signed, but always specify signed/unsigned anyway)
 * long long	64 bit (inefficient, avoid these, if using : defaults to signed, but always specify signed/unsigned anyway)
 * float		32 bit IEEE floating point numbers (inefficient, avoid these, used fixed point math)
 * double		64 bit IEEE floating point numbers (inefficient, avoid these, used fixed point math)
 */


// TODO various new structs
// Status struct
// Ignition struct
// Injection struct
// Engine position struct
// Validity flags, or they should be in the status struct?


typedef struct {
	char byte1;  //8 bit
	short byte23;  // 16 bit
} tribyte;


typedef struct {
	unsigned char RAMPage;
	unsigned char FlashPage;
	void* RAMAddress;
	void* FlashAddress;
	unsigned short size;
} blockDetails;

// memory block addresses description parameters


/* Fixed Configuration - place things that do not    *
 * change after initial setup or during tuning here. */
#define FIXED_CONFIG1_SIZE sizeof(fixedConfig1)
typedef struct {

	/* Settings variables : 0 = false */
	unsigned short coreSettingsA;	/* Each bit represents the state of some core setting, masks below and above where the same one is used */
	/* Bit masks for coreSettingsA */ // TODO needs a rename, as does coreStatusA
	//#define COREA1			BIT1_16		/*  1 */
	#define PRIMARY_POLARITY	BIT2_16		/*  2 1 = high teeth 0 = low teeth */
	#define SECONDARY_POLARITY	BIT3_16		/*  3 1 = high teeth 0 = low teeth */
	//#define COREA4 			BIT4_16		/*  4 */
	//#define FUEL_CUT			BIT5_16		/*  5 Remove injection completely */
	//#define HARD_SPARK_CUT	BIT6_16		/*  6 Remove ignition completely */
	//#define SOFT_SPARK_CUT	BIT7_16		/*  7 Remove ignition events round robin style */
	//#define SPARK_RETARD		BIT8_16		/*  8 Retard ignition in RPM dependent way */
	#define STAGED_ON			BIT9_16		/*  9 Whether we are firing the staged injectors */
	#define STAGED_START		BIT10_16	/* 10 1 = Fixed start 0 = Scheduled start */
	#define STAGED_END			BIT11_16	/* 11 1 = Fixed end 0 = Scheduled end */
	//#define COREA12			BIT12_16	/* 12 */
	//#define COREA13			BIT13_16	/* 13 */
	//#define COREA14			BIT14_16	/* 14 */
	//#define COREA15			BIT15_16	/* 15 */
	//#define COREA16			BIT16_16	/* 16 */


	/* Pre configured value settings for the sensor inputs */
	unsigned short presetIAT;
	unsigned short presetCHT;
	unsigned short presetTPS;
	unsigned short presetEGO;
	unsigned short presetBRV;
	unsigned short presetMAP;
	unsigned short presetAAP;
	unsigned short presetMAT;
	unsigned short presetEGO2;
	unsigned short presetIAP;
	unsigned short presetBPW; /* Base Pulse Width */
	unsigned short presetAF; /* Air Flow */


	/* Fuel injection settings TODO duplication from original temp code below!! */
	unsigned short perCylinderVolume;	/* 500cc = 0.5l 0.5 * 32768 = pcv, so divide by 32768 go get litres */
	unsigned short stoichiometricAFR;	/* 34 for hydrogen, all others less, figure is 14.7 * 1024, divide by 1024 to get AFR */
	unsigned short injectorFlow;		/* Injector flow of 240cc/min / 60 is 4ml/second is multiplied by 1024, so divide by 1024 for ml/second, divide by 1000 for litres/second */
	unsigned short densityOfFuelAtSTP; /* 703gm/litre for Octane. 32 * fuel density = number, divide by 32 for the real figure */

	/* Sensor related settings */
	unsigned short TPSClosedMAP;
	unsigned short TPSOpenMAP;


	/* Sensor input conditioning settings */
	/* These are used to calculate MAP, EGO and TPS from ADC readings. */
	unsigned short MAPMinimum;							/* 0 kPa usually. */
	unsigned short MAPRange;							/* 10000, 11500, 25000, 30000, 40000 etc (/100 for kPa) */
	unsigned short AAPMinimum;							/* 0 kPa usually. */
	unsigned short AAPRange;							/* 10000, 11500, 25000, 30000, 40000 etc (/100 for kPa) */
	unsigned short EGOMinimum;							/* 0.5 lambda ? (0.5 x 32768 = 16384) */
	unsigned short EGORange;							/* 1.5 lambda ? ((1.5 - 0.5) x 32768 = 32768 (max 49152)) */
	unsigned short BRVMinimum;							/* 0 Volts usually. */
	unsigned short BRVRange;							/* 24.5 Volts for 10k and 39k resistors on a 12v vehicle */
	unsigned short TPSMinimumADC;						/* *should* be zero, but often isn't, this value corresponds to 0% TPS */
	unsigned short TPSMaximumADC;						/*  */
	// unsigned short TPSADCRange;						// ?? 100% = how many ADCs ?
	/*efine TPS_MINIMUM 0								** = 0.00%		For clarity ONLY, always zero.	*/
	#define TPS_RANGE_MAX 64000							/* = 100.00%									*/
	unsigned char userTextField[userTextFieldArrayLength1]; /* "Place your personal notes here!!" */
} fixedConfig1;


/* Fixed Configuration - place things that do not    *
 * change after initial setup or during tuning here. */
#define FIXED_CONFIG2_SIZE sizeof(fixedConfig2)
typedef struct {

	/* Setting variables (must be inited with useful values) */
	unsigned short capacityOfAirPerCombustionEvent;		/* How much air it swallows per power producing event	*/
	unsigned short perPrimaryInjectorChannelFlowRate;	/* How much fuel flows per minute per channel			*/
	unsigned short perSecondaryInjectorChannelFlowRate;	/* How much fuel flows per minute per channel			*/
	unsigned short readingTimeout;						/* How often an ADC reading MUST occur					*/
	unsigned char ports;								/* How many groups of injectors we are firing			*/
	unsigned char coils;								/* How many coils we are firing							*/
	unsigned char combustionEventsPerEngineCycle;		/* How many power producing events per engine cycle		*/
	unsigned char revolutionsPerEngineCycle;			/* Rotary = 1, 2 Stroke = 1, 4 Stroke = 2				*/
	unsigned char primaryTeeth;							/* How many teeth are on the crank signal including the missing ones if any (eg. 36-1 primary = 36 not 35) */
	unsigned char missingTeeth;							/* Number sequentially removed from primary teeth (eg. 36-1 missing = 1) */

	/* Serial settings */
	unsigned short baudDivisor;							/* 22 = (40MHz / (16*115.2kHz)) = 21.7013889 */
	unsigned char networkAddress;						/* Default = 1, Default for PC = 10 */

	/* Tacho settings */
	unsigned char tachoTickFactor;
	unsigned short tachoTotalFactor;

	/* User text field for noting which installation the unit is from etc. */
	unsigned char userTextField[userTextFieldArrayLength2]; /* "Place your personal notes here!!" */
} fixedConfig2;


#define DERIVED_VARS_SIZE sizeof(DerivedVar)
#define DERIVED_VARS_WIDTH IN_OUT_BANKS	/* How many elements per array currently 2 at 25/6/08 */
#define DERIVED_VARS_UNIT 2				/* How large each element is in bytes (short = 2 bytes) */
/* Use this block to make it easy to manage the derived variables */
typedef struct {
	/* Calculated from core vars */
	unsigned short LoadMain;			/* Configurable unit of load */
//	unsigned short LoadSecondary;

	unsigned short VEMain;			/* Divide by 512 to get % */
//	unsigned short VESecondary;

	unsigned short Lambda;			/* Divide by 32768 to get Lamda */
	unsigned short AirFlow;			/* top half */
	unsigned short densityAndFuel;	/* bottom half */

	unsigned short BasePW;			/* In timer ticks of 0.8us */
	unsigned short IDT;				/* 0.8us ticks */
	unsigned short ETE;				/* 0.8us ticks */
	signed short TFCTotal;			/* Transient fuel correction */

	unsigned short FinalPW;			/* In timer ticks of 0.8us */
	unsigned short RefPW;			/* In timer ticks of 0.8us */

	unsigned short sp1;		/*  */
	unsigned short sp2;		/*  */
	unsigned short sp3;		/*  */
	unsigned short sp4;		/*  */
	unsigned short sp5;		/*  */

//	unsigned short ;		/*  */
} DerivedVar;


#define RUNTIME_VARS_SIZE sizeof(RuntimeVar)
#define RUNTIME_VARS_LENGTH 13		/* How many runtime vars */
#define RUNTIME_VARS_UNIT 2				/* How large each element is in bytes (short = 2 bytes) */
/* Use this block to manage the execution time of various functions loops and ISRs etc */
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


#define ISR_LATENCY_VARS_SIZE sizeof(ISRLatencyVar)
#define ISR_LATENCY_VARS_LENGTH 2		/* How many latency vars */
#define ISR_LATENCY_VARS_UNIT 2				/* How large each element is in bytes (short = 2 bytes) */
/* Use this block to manage the execution time of various functions loops and ISRs etc */
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


#define CORE_VARS_SIZE sizeof(CoreVar)
#define CORE_VARS_LENGTH 16				/* How many arrays */
#define CORE_VARS_UNIT 2				/* How large each element is in bytes (short = 2 bytes) */
/* Use this block to make it easy to manage the core variables */
typedef struct {
	/* Calculated and averaged from ADC0 readings */
	unsigned short IAT;			/* Inlet Air Temperature (MAT JS)			: 0.0	-    655.35		(0.01 Kelvin (/100))		*/
	unsigned short CHT;			/* Coolant / Head Temperature (CLT JS)		: 0.0	-    655.35		(0.01 Kelvin (/100))		*/
	unsigned short TPS;			/* Throttle Position Sensor (TPS JS)		: 0.0	-    102.39		(0.001? % (/640))			*/
	unsigned short EGO;			/* Exhaust Gas Oxygen (O2 JS)				: 0.000	-      1.999999	(0.0001? lambda (/32768))	*/
	unsigned short MAP;			/* Manifold Absolute Pressure (5euroh1)		: 0.0	-    655.35		(0.01 kPa (/100))			*/
	unsigned short AAP;			/* Atmospheric Absolute Pressure (6euroh1)	: 0.0	-    655.35		(0.01 kPa (/100))			*/
	unsigned short BRV;			/* Battery Reference Voltage (4euroh1)		: 0.000	-     65.535	(0.001 Volts (/1000))		*/
	unsigned short MAT;			/* Manifold Air Temperature (Spare JS)		: 0.0	-    655.35		(0.01 Kelvin (/100))		*/

	/* Calculated and averaged from ADC1 readings */
	unsigned short EGO2;		/* Exhaust Gas Oxygen (NC)					: 0.000	-      1.999999	(0.0001? lambda (/32768))	*/
	unsigned short IAP;			/* Intercooler Absolute Pressure (NC)		: 0.0	-    655.35		(0.01 kPa (/100))			*/
	unsigned short MAF;			/* Mass Air Flow							: 0.0	-  65535.0		(raw units from lookup)		*/

	/* Calculated from MAP and TPS history */
	unsigned short DMAP;		/* Delta MAP kPa/second or similar */
	unsigned short DTPS;		/* Delta TPS %/second or similar */

	/* Calculated from engine position data */
	unsigned short RPM;			/* Revolutions Per Minute (Calced)			: 0		-  32767.5		(0.5 RPM (/2))				*/
	unsigned short DRPM;		/* Delta RPM (Calced)						: 0		-  32767.5		(0.5 RPM/Second (/2))		*/
	unsigned short DDRPM;		/* Delta Delta RPM (Calced)					: 0		-  32767.5		(0.5 RPM/Second^2 (/2))		*/
} CoreVar;


#define ADC_ARRAY_SIZE sizeof(ADCArray)
#define ADC_ARRAY_LENGTH 16				/* How many arrays */
#define ADC_ARRAY_UNIT 2				/* How large each element is in bytes (short = 2 bytes) */
/* Use this block to ensure that the components are contiguous and we can then reference them via offsets and pointers */
typedef struct {
	/* ADC0 raw readings */
	unsigned short IAT;			/* Inlet Air Temperature (MAT JS)			*/ /* COMPULSORY! */
	unsigned short CHT;			/* Coolant / Head Temperature (CLT JS)		*/ /* COMPULSORY! */
	unsigned short TPS;			/* Throttle Position Sensor (TPS JS)		*/ /* Reduced performance without */
	unsigned short EGO;			/* Exhaust Gas Oxygen (O2 JS)				*/ /* Recommended */
	unsigned short BRV;			/* Battery Reference Voltage (4euroh1)		*/ /* COMPULSORY! */
	unsigned short MAP;			/* Manifold Absolute Pressure (5euroh1)		*/ /* COMPULSORY OR TPS OR MAF */
	unsigned short AAP;			/* Atmospheric Absolute Pressure (6euroh1)	*/ /* Recommended */
	unsigned short MAT;			/* Manifold Air Temperature (Spare JS)		*/ /* Could help heat soak issues */

	/* ADC1 raw readings */
	unsigned short EGO2;			/* Exhaust Gas Oxygen (NC)					*/ /* V engine option */
	unsigned short IAP;			/* Intercooler Absolute Pressure (NC)		*/ /* Turbo engine option */
	unsigned short MAF;			/* Mass Air Flow (NC)						*/ /* OEM engine option */
	unsigned short SpareADC3;		/* Spare ADC1 port 3 (NC)					*/
	unsigned short SpareADC4;		/* Spare ADC1 port 4 (NC)					*/
	unsigned short SpareADC5;		/* Spare ADC1 port 5 (NC)					*/
	unsigned short SpareADC6;		/* Spare ADC1 port 6 (NC)					*/
	unsigned short SpareADC7;		/* Spare ADC1 port 7 (NC)					*/
} ADCArray;


#define MAINTABLE_SIZE sizeof(mainTable)
#define MAINTABLE_RPM_LENGTH 24			/* How many cells on the X axis */
#define MAINTABLE_LOAD_LENGTH 19		/* How many cells on the Y axis */
#define MAINTABLE_MAX_RPM_LENGTH 27		/* How many cells on the X axis max */
#define MAINTABLE_MAX_LOAD_LENGTH 21	/* How many cells on the Y axis max */
#define MAINTABLE_MAX_MAIN_LENGTH 462	/* 924B 462 shorts maximum main table length */
/* Main Table Structure definition */
/* Use this block to manage the main VE, Lambda and Timing tables. *
 * Tables can be made any size from 1x1 to 27x17 or 22x21 provided *
 * that the multiple of the two doesn't exceed the max main length *
 * and neither axis exceeds it's specified maximum.                */
typedef struct {
	unsigned short RPMLength;						/* The length of the RPM axis array */
	unsigned short LoadLength;						/* The length of the Load axis array */
	unsigned short RPM[MAINTABLE_MAX_RPM_LENGTH];		/* The array of RPM (X) axis values */
	unsigned short Load[MAINTABLE_MAX_LOAD_LENGTH];		/* The array of Load (Y) axis values */
	unsigned short Table[MAINTABLE_MAX_MAIN_LENGTH];	/* The table as an array of values */
} mainTable;


#define TWODTABLEUS_SIZE sizeof(twoDTableUS)
#define TWODTABLEUS_LENGTH 16
/* This block used for various curves */
typedef struct {
	unsigned short Axis[TWODTABLEUS_LENGTH];
	unsigned short Values[TWODTABLEUS_LENGTH];
} twoDTableUS;


#define TWODTABLESS_SIZE sizeof(twoDTableSS)
#define TWODTABLESS_LENGTH 16
/* This block used for various curves */
typedef struct {
	signed short Axis[TWODTABLESS_LENGTH];
	signed short Values[TWODTABLESS_LENGTH];
} twoDTableSS;


#define TWODTABLEMS_SIZE sizeof(twoDTableMS)
#define TWODTABLEMS_LENGTH 16
/* This block used for various curves */
typedef struct {
	unsigned short Axis[TWODTABLEMS_LENGTH];
	signed short Values[TWODTABLEMS_LENGTH];
} twoDTableMS;


#define TWODTABLEUC_SIZE sizeof(twoDTableUC)
#define TWODTABLEUC_LENGTH 8
/* This block used for various curves */
typedef struct {
	unsigned char Axis[TWODTABLEUC_LENGTH];
	unsigned char Values[TWODTABLEUC_LENGTH];
} twoDTableUC;


#define COUNTER_SIZE sizeof(Counter)
#define COUNTER_LENGTH 21			/* How many counters */
#define COUNTER_UNIT 2				/* How large each element is in bytes (short = 2 bytes) */
/* Use this block to manage the execution count of various functions loops and ISRs etc */
typedef struct {
	/* Event Counters (all require init to zero) */
	unsigned short callsToUISRs;						/* Counter to ensure we aren't accidentally triggering unused ISRs		*/
	unsigned short lowVoltageConditions;				/* Counter for low voltage conditions									*/

	unsigned short crankSyncLosses;						/* Counter for number of lost crank syncs								*/
	unsigned short camSyncLosses;						/* Counter for number of lost cam syncs									*/
	unsigned short RPMValidityLosses;					/* Counter for number of lost RPM validity events						*/
	unsigned short primaryTeethDroppedFromLackOfSync;	/* Counter for number of primary teeth dropped due to no primary sync	*/
// TODO remove the one above this line about teeth dropped???? probably...

	unsigned short primaryTeethSeen;					/* Free running counters for number of teeth seen such that...			*/
	unsigned short secondaryTeethSeen;					/* ...tooth timing can be used to reconstruct the signal at lower rpm	*/

	unsigned short syncedADCreadings;					/* Incremented each time a syncronous ADC reading is taken				*/
	unsigned short timeoutADCreadings;					/* Incremented for each ADC reading in RTC because of timeout			*/

	unsigned short calculationsPerformed;				/* Incremented for each time the fuel and ign calcs are done			*/
	unsigned short datalogsSent;						/* Incremented for each time we send out a log entry					*/

	/* UART/serial specific counters */
	unsigned short serialStartsInsideAPacket;			/* Incremented when a start byte is found inside a packet				*/
	unsigned short serialEscapePairMismatches;			/* Incremented when an escape is found but not followed by an escapee	*/
	unsigned short serialPacketsOverLength;				/* Incremented when the buffer fills up before the end					*/
	unsigned short serialNoiseErrors;					/* Incremented when noise is detected									*/
	unsigned short serialOverrunErrors;					/* Incremented when an overrun occurs									*/
	unsigned short serialFramingErrors;					/* Incremented when a framing error occurs								*/
	unsigned short serialParityErrors;					/* Incremented when a parity error occurs								*/

	/* Generic com counters */
	unsigned short commsChecksumMismatches;			/* Incremented when calculated checksum did not match the received one	*/
	unsigned short commsDebugMessagesNotSent;			/* Incremented when a debug message can't be sent due to the TX buffer  */
	unsigned short commsErrorMessagesNotSent;			/* Incremented when an error message can't be sent due to the TX buffer */
} Counter;


#define CLOCK_SIZE sizeof(Clock)
#define CLOCK_LENGTH 9				/* How many clocks */
#define CLOCK_UNIT 2				/* How large each element is in bytes (short = 2 bytes) */
/* Use this block to manage the various clocks kept */
typedef struct {
	/* Real Time and other Clocks (all require init to zero) */
	unsigned short realTimeClockMain;					/* Variable to count RTI executions, 0.125ms exactly	*/
	unsigned short realTimeClockMillis;					/* Variable to count milliseconds exactly				*/
	unsigned short realTimeClockTenths;					/* Variable to count tenths of a second exactly			*/
	unsigned short realTimeClockSeconds;				/* Variable to count seconds exactly					*/
	unsigned short realTimeClockMinutes;				/* Variable to count minutes exactly					*/

	unsigned short millisToTenths;						/* Rollover variable for counting tenths				*/
	unsigned short tenthsToSeconds;						/* Rollover variable for counting seconds				*/
	unsigned short secondsToMinutes;					/* Rollover variable for counting minutes				*/

	unsigned short timeoutADCreadingClock;				/* Timeout clock/counter for synced ADC readings		*/
} Clock;


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file STRUCTS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
