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
 * @brief Container struct typedefs
 *
 * This file contains all of the data container struct typedefs used for calculations.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_CONTAINER_TYPES_H_SEEN
#define FILE_CONTAINER_TYPES_H_SEEN


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


/// Important "always send" stuff for datalogging
typedef struct {
	// To be improved MAJORLY:
	unsigned char tempClock;       ///< Incremented once per log sent
	unsigned char spareChar;       ///< Unused at this time.

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
	unsigned char serialHardwareErrors;        ///< Sum of noise, parity, and framing errors
	unsigned char serialAndCommsCodeErrors;    ///< Sum of checksum, escape mismatches, starts inside, and over/under length
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
	#warning "Header file CONTAINER_TYPES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
