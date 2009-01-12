/*	Copyright 2008 Fred Cooke

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


/**	@file freeEMS.h
 * @ingroup allHeaders
 * @ingroup globalHeaders
 *
 * @brief The main project header file
 *
 * The central header for all source files to include. This pulls in the
 * device header, all other shared headers, all global defines, all global
 * constant declarations, all type definitions and all global variables. Other
 * variables that are actually in global space but only shared between a few
 * select files should be placed in the header for the main file that uses them.
 *
 * @author Fred Cooke
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_FREEEMS_H_SEEN
#define FILE_FREEEMS_H_SEEN


/* Include top level files that everything else relies on */
#include "memory.h"
#include "9S12XDP512.h"
#include "flashGlobals.h" /// @todo TODO For Sean to integrate back in
///include "registerMasks.h @todo TODO we should define the register masks that we use in one place, but probably not in the main device header.

/* Include define files at the top here as other includes use them */
#include "errorDefines.h"
#include "globalDefines.h"

/* Include data types at the top as other includes use them */
#include "structs.h" /// @todo TODO split this out into more chunks as it's too big.
#include "FixedConfigs.h"
#include "TunableConfigs.h"

/* Global constant declarations */
#include "globalConstants.h"


/* Where extern is used instead of EXTERN it indicates that   	*/
/* the variable is initialised in staticInit.c, if someone    	*/
/* attempts to use extern and doesn't initialise the variable 	*/
/* statically then the linker should error on undefined symbol	*/


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef FREEEMS_C
#define EXTERN
#else
#define EXTERN extern
#endif


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


/* GLOBAL Variables */
// TODO change any of these that need it to volatile!!!


// temporary test vars
EXTERN unsigned short RPM0; // to be replaced with logging scheme for teeth.
EXTERN unsigned short RPM1; // to be replaced with logging scheme for teeth.
extern unsigned short tachoPeriod;
EXTERN unsigned char portHDebounce;

// these should not be here... TODO move to a comms header
extern unsigned char asyncDatalogType;
#define asyncDatalogOff			0x00
#define asyncDatalogBasic		0x01
#define asyncDatalogConfig		0x02
#define asyncDatalogLogic		0x03
#define asyncDatalogADC			0x04
#define asyncDatalogCircBuf		0x05
#define asyncDatalogCircCAS		0x06
#define asyncDatalogTrigger		0x07 // what is this
EXTERN unsigned short configuredBasicDatalogLength;


// temporary test vars
EXTERN void* memdumpaddr;
EXTERN unsigned char ShouldSendLog;

/* Declare instances of variable structs for use */
EXTERN Clock Clocks;					/* Timer Clocks for various functions */
EXTERN Counter Counters;				/* Execution count for various blocks of code */
EXTERN RuntimeVar RuntimeVars;			/* Execution times for various blocks of code */
EXTERN ISRLatencyVar ISRLatencyVars;	/* Delay in execution start for various blocks of code */


/** @page bankedRunningVariables Banked Running Variables
 *
 * This page is to document and explain the operation of the banked running variable system and structure.
 *
 * The program running variables are divided into three broad groups: inputs, working
 * and outputs. For both the input and output groups there are two copies of each set
 * of variables, whereas there is only one copy of each set in the working group. This
 * is required to allow both the inputs and outputs to be safely written and read at
 * the same time. To facilitate this all sets of variables within the input and output
 * groups are referenced with two pointers each. For the input group, the copy pointed
 * to is swapped when fresh data is both available to and required by the mathematics
 * function. For the output group the copy pointed to is swapped when the mathematics
 * function has produced new output data. The input data is supplied by the engine
 * position interrupt service routines as ADC readings and RPM values. The output data
 * consists of pulse widths, timing angles, dwell periods and scheduling information.
 *
 * Accessory functions (Idle, Boost, etc)
 *
 * In order to achieve minimal latency and maximum frequency of execution of the
 * main mathematics code the accessory functions must run asynchronously. Although
 * we can guarantee that these functions will base their calculations on a matched
 * set of data, we can not guarantee that it will be the same set of data presented
 * along side the accessory data in the data log. Thus, where it is required to see
 * the inputs that an accessory functions calculations were based on, those values
 * should be cached for logging on a per function basis.
 *
 * Although it seems like a lot of trouble to go to, it is critical to transient
 * performance that the environmental conditions the engine is operating under are
 * tracked and reacted to as quickly as possible. Having the less important stuff
 * run asynchronously will result in an order of magnitude improvement of parameter
 * tracking and is well worth the extra memory expense and complication.
 */

EXTERN CoreVar* CoreVars;			/** Pointer to the core running variables */
EXTERN CoreVar CoreVars0;			/** Bank 0 core running variables */
/* If we move to xgate or isr driven logging, add bank 1 back in */

EXTERN DerivedVar* DerivedVars;		/** Pointer to the secondary running variables */
EXTERN DerivedVar DerivedVars0;		/** Bank 0 secondary running variables */
/* If we move to xgate or isr driven logging, add bank 1 back in */

EXTERN ADCArray* ADCArrays;			/** main adc storage area for syncronous sampling in the engine position ISR or injection ISR or ignition ISR etc. */
EXTERN ADCArray* ADCArraysRecord;	/** main adc storage area for syncronous sampling in the engine position ISR or injection ISR or ignition ISR etc. */
EXTERN ADCArray ADCArrays0;			/** main adc storage area for syncronous sampling in the engine position ISR or injection ISR or ignition ISR etc. */
EXTERN ADCArray ADCArrays1;			/** main adc storage area for syncronous sampling in the engine position ISR or injection ISR or ignition ISR etc. */

EXTERN ADCArray* asyncADCArrays;		/** secondary adc storage area for asynchronously sampling in the RTC/RTI ISR */
EXTERN ADCArray* asyncADCArraysRecord;	/** secondary adc storage area for asynchronously sampling in the RTC/RTI ISR */
EXTERN ADCArray asyncADCArrays0;		/** secondary adc storage area for asynchronously sampling in the RTC/RTI ISR */
EXTERN ADCArray asyncADCArrays1;		/** secondary adc storage area for asynchronously sampling in the RTC/RTI ISR */

EXTERN unsigned short* mathSampleTimeStamp; // TODO temp, remove
EXTERN unsigned short* mathSampleTimeStampRecord; // TODO temp, remove
EXTERN unsigned short* RPM; // TODO temp, remove
EXTERN unsigned short* RPMRecord; // TODO temp, remove
EXTERN unsigned short* currentDwellMath; // TODO temp, remove
EXTERN unsigned short* currentDwellRealtime; // TODO temp, remove
EXTERN unsigned short currentDwell0; // TODO temp, remove
EXTERN unsigned short currentDwell1; // TODO temp, remove

/*break this on purpose so i fix it later
#define VETablereference (*((volatile mainTable*)(0x1000)))
EXTERN const mainTable *VETableRef;
PLUS
const volatile mainTable *VETableRef = (volatile mainTable*)0x1000;
broken too, need to research how to do this.

see line 80 or so from inc/injectorISR.c for array of pointer use. the above may not be possible... TODO */


/* Potentially pointers for data in ram depending on how it gets implemented */
// volatile ??
//EXTERN tunableConfig tunableConfigs;

/* Layout the tunable copies and buffers in ram space */



/* TODO explanation of paged ram operation Unions for paged large table access using RPAGE */
typedef union {
	mainTable VETableMain;
	mainTable IgnitionAdvanceTableMain;
	SmallTables1 SmallTablesA;
} Tables1;

typedef union {
	mainTable VETableSecondary;
	mainTable IgnitionAdvanceTableSecondary;
	SmallTables2 SmallTablesB;
} Tables2;

typedef union {
	mainTable VETableMainTertiary;
	mainTable InjectionAdvanceTableMain;
	SmallTables3 SmallTablesC;
} Tables3;

typedef union {
	mainTable LambdaTable;
	mainTable InjectionAdvanceTableSecondary;
	SmallTables4 SmallTablesD;
} Tables4;


/* Large blocks */
EXTERN unsigned char TXBuffer[TX_BUFFER_SIZE] TXBUF;
EXTERN unsigned char RXBuffer[RX_BUFFER_SIZE] RXBUF;
EXTERN Tables1 TablesA RWINDOW;
EXTERN Tables2 TablesB RWINDOW;
EXTERN Tables3 TablesC RWINDOW;
EXTERN Tables4 TablesD RWINDOW;


/* RAM page variables */
EXTERN unsigned char currentFuelRPage;
EXTERN unsigned char currentTuneRPage;
EXTERN unsigned char currentTimeRPage;


//union { /* Declare Union http://www.esacademy.com/faq/docs/cpointers/structures.htm */
//    unsigned long timeLong;
//    unsigned short timeShorts[2];
//} LongNoTime RWINDOW ;

/* These are inited once and remain the same, rpage switches change meaning. */

///* Pointers to main tables to aid readability */
//EXTERN mainTable* VETableMain;
//EXTERN mainTable* VETableSecondary;
//EXTERN mainTable* VETableTertiary;
//EXTERN mainTable* LambdaTable;
//
//EXTERN mainTable* IgnitionAdvanceTableMain;
//EXTERN mainTable* IgnitionAdvanceTableSecondary;
//EXTERN mainTable* InjectionAdvanceTableMain;
//EXTERN mainTable* InjectionAdvanceTableSecondary;
//
///* Pointers to SmallTablesA */
//EXTERN twoDTableUS* dwellDesiredVersusVoltageTable;
//EXTERN twoDTableUS* injectorDeadTimeTable;
//EXTERN twoDTableUS* postStartEnrichmentTable;
//EXTERN twoDTableUS* engineTempEnrichmentTableFixed;
//EXTERN twoDTableUS* primingVolumeTable;
//EXTERN twoDTableUS* engineTempEnrichmentTablePercent;
//EXTERN twoDTableUS* dwellMaxVersusRPMTable;
//
///* Pointers to SmallTablesB */
//EXTERN unsigned short* perCylinderFuelTrims;


/* Pointers to SmallTablesC */


/* Pointers to SmallTablesD */




/* Output variables (init not required) TODO ditch this in favour of the real vars in the calcs function and struct */
extern unsigned short masterPulseWidth;
EXTERN unsigned short totalDwell;
extern unsigned short totalAngleAfterReferenceInjection;
extern unsigned short totalAngleAfterReferenceIgnition;

EXTERN unsigned long bootFuelConst;	/* constant derived from configurable constants */
EXTERN unsigned short TPSMAPRange;	/* The MAP range used to convert fake TPS from MAP and vice versa */
EXTERN unsigned short TPSADCRange;	/* The ADC range used to generate TPS percentage */
EXTERN unsigned short boundedTPSADC; // temp to view to debug

EXTERN unsigned short bootTimeAAP; /* TODO populate this at switch on time depending on a few things. */

/* ALL STATUS STUFF HERE */

// TODO these flags are used for coreSettingsA and it is not clear that they are dual purpose, fix this...
/* State variables : 0 = false (don't forget to change the init mask to suit!) */
EXTERN unsigned short coreStatusA;	/* Each bit represents the state of some core parameter, masks below */
/* Bit masks for coreStatusA */ // TODO needs a rename as does coresetingsA
#define COREA01			BIT1_16		/*  1 this was RPM_VALID Whether we are sure rpm is what the variable says (used to inject fuel without ignition below the threshold rpm) */
#define PRIMARY_SYNC	BIT2_16		/*  2 Wasted spark/Semi sequential */
#define SECONDARY_SYNC	BIT3_16		/*  3 COP/Full sequential */
#define ENGINE_PHASE	BIT4_16		/*  4 For COP/Sequential, which revolution we are in, first or second */
#define FUEL_CUT		BIT5_16		/*  5 Remove injection completely */
#define HARD_SPARK_CUT	BIT6_16		/*  6 Remove ignition completely */
#define SOFT_SPARK_CUT	BIT7_16		/*  7 Remove ignition events round robin style */
#define SPARK_RETARD	BIT8_16		/*  8 Retard ignition in RPM dependent way */
#define STAGED_REQUIRED	BIT9_16		/*  9 Fire the staged injectors */
#define CALC_FUEL_IGN	BIT10_16	/* 10 Fuel and ignition require calculation (i.e. variables have been updated) */
#define FORCE_READING	BIT11_16	/* 11 Flag to force ADC sampling at low rpm/stall */
#define COREA12			BIT12_16	/* 12 */
#define COREA13			BIT13_16	/* 13 */
#define COREA14			BIT14_16	/* 14 */
#define COREA15			BIT15_16	/* 15 */
#define COREA16			BIT16_16	/* 16 */

#define CLEAR_PRIMARY_SYNC	NBIT2_16	/* */
#define STAGED_NOT_REQUIRED	NBIT9_16	/*  9 Do not fire the staged injectors */
#define CLEAR_CALC_FUEL_IGN	NBIT10_16	/* 10 Fuel and ignition don't require calculation */
#define CLEAR_FORCE_READING	NBIT11_16	/* 11 Clear flag to force ADC sampling at low rpm/stall */


//TODO make this volatile?
/* ECT IC extension variable (init not required, don't care where it is, only differences between figures) */
unsigned short timerExtensionClock;						/* Increment for each overflow of the main timer, allows finer resolution and longer time period */
/* section 10.3.5 page 290 68hc11 reference manual e.g. groups.csail.mit.edu/drl/courses/cs54-2001s/pdf/M68HC11RM.pdf */


/* For extracting 32 bit long time stamps from the overflow counter and timer registers */
typedef union { /* Declare Union http://www.esacademy.com/faq/docs/cpointers/structures.htm */
    unsigned long timeLong;
    unsigned short timeShorts[2];
} LongTime;


/* Flag registers, init to zero required */
EXTERN unsigned char mainOn;				/* Keep track of where we are at for possible use as multi interrupt per injection */
EXTERN unsigned short dwellOn;				/* Keep track of ignition output state */
EXTERN unsigned char stagedOn;				/* Ensure we turn an injector off again if we turn it on. */
EXTERN unsigned char selfSetTimer;			/* Set the start time of injection at the end of the last one in the channels ISR instead of the input ISR */
EXTERN unsigned char rescheduleFuelFlags;	/* Pulse width is probably longer than engine cycle so schedule a restart at the next start time */


/* Engine Position and RPM reading variables */

/* Engine runtime properties (inits???) TODO */
EXTERN unsigned short primaryPulsesPerSecondaryPulse; /* Type short because of nissan style cam wheels (char would do for other types) */
EXTERN unsigned short primaryPulsesPerSecondaryPulseBuffer; /* Type short because of nissan style cam wheels (char would do for other types) */
EXTERN unsigned short primaryLeadingEdgeTimeStamp; /* Store the timestamp of the leading edge during a pulse */
EXTERN unsigned short primaryTrailingEdgeTimeStamp; /* Store the timestamp of the leading edge during a pulse */
EXTERN unsigned short timeBetweenSuccessivePrimaryPulses; /* This number equates to the speed of the engine */
EXTERN unsigned short timeBetweenSuccessivePrimaryPulsesBuffer; /* This number equates to the speed of the engine */
EXTERN unsigned short lastPrimaryPulseTimeStamp; /* Store the timer value of the each pulse here before exiting the ISR */
extern unsigned long engineCyclePeriod; /* Timer units between engine cycle starts */
EXTERN unsigned long lastSecondaryOddTimeStamp;
EXTERN unsigned short primaryTeethDroppedFromLackOfSync;

/* Ignition stuff */

// ignition experimentation stuff
EXTERN unsigned char dwellQueueLength;				/* 0 = no dwell pending start, 1 = single event scheduled, 2 = one scheduled, and one in the queue, etc */
EXTERN unsigned char ignitionQueueLength;			/* 0 = no spark event pending, 1 = single event scheduled, 2 = one scheduled, and one in the queue, etc */
EXTERN unsigned char nextDwellChannel;				/* Which one to bang off next */
EXTERN unsigned char nextIgnitionChannel;			/* Which one to bang off next */
EXTERN unsigned short ignitionAdvances[IGNITION_CHANNELS * 2]; // Uses channel + offset to have two values at any time
EXTERN unsigned short queuedDwellOffsets[IGNITION_CHANNELS]; // Uses next channel as index
EXTERN unsigned short queuedIgnitionOffsets[IGNITION_CHANNELS]; // Uses next channel as index


/* Injection stuff */

/* Register addresses */
EXTERN volatile unsigned short * volatile injectorMainTimeRegisters[INJECTION_CHANNELS];
EXTERN volatile unsigned char * volatile injectorMainControlRegisters[INJECTION_CHANNELS];

/* Timer holding vars (init not required) */
EXTERN unsigned short injectorMainStartTimesHolding[INJECTION_CHANNELS];
EXTERN unsigned long injectorMainEndTimes[INJECTION_CHANNELS];

// TODO make these names consistent
/* Code time to run variables (init not required) */
EXTERN unsigned short injectorCodeOpenRuntimes[INJECTION_CHANNELS];
EXTERN unsigned short injectorCodeCloseRuntimes[INJECTION_CHANNELS];

/* individual channel pulsewidths (init not required) */
EXTERN unsigned short* injectorMainPulseWidthsMath;
EXTERN unsigned short* injectorStagedPulseWidthsMath;
EXTERN unsigned short* injectorMainPulseWidthsRealtime;
EXTERN unsigned short* injectorStagedPulseWidthsRealtime;
EXTERN unsigned short injectorMainPulseWidths0[INJECTION_CHANNELS];
EXTERN unsigned short injectorMainPulseWidths1[INJECTION_CHANNELS];
EXTERN unsigned short injectorStagedPulseWidths0[INJECTION_CHANNELS];
EXTERN unsigned short injectorStagedPulseWidths1[INJECTION_CHANNELS];

/* Channel latencies (init not required) */
EXTERN unsigned short injectorCodeLatencies[INJECTION_CHANNELS];


#undef EXTERN


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file FREEEMS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
