/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2013 Fred Cooke
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
 * @ingroup dataInitialisers
 *
 * @brief Second fixed config block
 *
 * This file contains the definition of the second fixed configuration block.
 * The declaration can be found in the global constants header file.
 *
 * Please ensure that all variables added here have good default values.
 */


#include "../inc/freeEMS.h"


/** @copydoc fixedConfig1 */
const volatile fixedConfig2 fixedConfigs2 FIXEDCONF2 = {
	sensorSources:{
		BRV: SOURCE_NORMAL,
		CHT: SOURCE_NORMAL,
		IAT: SOURCE_NORMAL,
	},
	sensorPresets:{
		presetIAT:  DEGREES_C(20), // Room temperature
		presetCHT:  DEGREES_C(85), // Running temperature
		presetBRV:  VOLTS(14.4),   // Standard alternator charging level for wet cell lead acid

		failsafeIATIgnition:  DEGREES_C(40),
		failsafeIATInjection:  DEGREES_C(0),
		failsafeCHT:  DEGREES_C(100),
		failsafeMAP:  KPA(60),
		failsafeBRV:  VOLTS(14.4),
		failsafeAAP:  KPA(100),
		failsafeTPS:  PERCENT(10), // Enough for light throttle and idle in Alpha-N with a fault
	},
	sensorRanges:{
// MAP Sensor Configuration
#if CONFIG == HOTEL_ID
		MAPMinimum:    MPX4250AMin,
		MAPRange:      MPX4250ARange,
#elif CONFIG == PRESTO_ID
		MAPMinimum:    HondaDenso183kPaMin,
		MAPRange:      HondaDenso183kPaRange,
#elif CONFIG == SNOTROCKET_ID
		MAPMinimum:    HondaDenso183kPaMin,
		MAPRange:      HondaDenso183kPaRange,
#elif CONFIG == SEANKLT1_ID
		MAPMinimum:    GM2BarMin,
		MAPRange:      GM2BarRange,
#elif CONFIG == SLATER_ID
		MAPMinimum:    HondaDenso183kPaMin,
		MAPRange:      HondaDenso183kPaRange,
#elif CONFIG == DEUCECOUPE_ID
		MAPMinimum:    MPX4100AMin,
		MAPRange:      MPX4100ARange,
#elif CONFIG == DEUCES10_ID
		MAPMinimum:    GM1BarMin,
		MAPRange:      GM1BarRange,
#else
		MAPMinimum:    MPX4250AMin,
		MAPRange:      MPX4250ARange,
#endif
// AAP Sensor Configuration
#if CONFIG == SNOTROCKET_ID
		AAPMinimum:    HondaDenso183kPaMin,
		AAPRange:      HondaDenso183kPaRange,
#else
		AAPMinimum:    MPXA6115AMin,
		AAPRange:      MPXA6115ARange,
#endif
#if CONFIG == SEANKLT1_ID
		EGOMinimum:    AFR1020LambdaMin,
		EGORange:      AFR1020LambdaRange,
#elif CONFIG == SCAVENGER_ID // http://www.schnitzracing.com/manuals/AEMWBK.pdf
		EGOMinimum:    LAMBDA(0.683),
		EGORange:      (LAMBDA(1.365) - LAMBDA(0.683)),
#else
		EGOMinimum:    LC1LambdaMin,
		EGORange:      LC1LambdaRange,
#endif
#if CONFIG == HOTEL_ID
		BRVMinimum:    VOLTS(0),
		BRVRange:      VOLTS(25.082),
#elif CONFIG == SNOTROCKET_ID
		BRVMinimum:    VOLTS(0),
		BRVRange:      VOLTS(24.5), // Shoebox build value: 24.777, reverted to 24.5 for Jaguar build.
#elif CONFIG == DEUCES10_ID
		BRVMinimum:    VOLTS(0),
		BRVRange:      VOLTS(24.65), // This is calibrated for the Jaguar A2 in the 1997 S10 on 01-12-2013.
#else
		BRVMinimum:    VOLTS(0),
		BRVRange:      VOLTS(24.5), // Standard 3.9k and 1k values.
#endif
#if CONFIG == DEUCECOUPE_ID  // This is calibrated for the Deuce Coupe TPS.
		TPSMinimumADC: 81,  // This is to correct for the TPS reading at closed throttle.
		TPSMaximumADC: 574  // This is to correct for the TPS reading at wide open throttle.

#elif CONFIG == DEUCES10_ID   // This is an estimate for the S10 TPS.
		TPSMinimumADC: 120,  // This is to correct for the TPS reading at closed throttle.
		TPSMaximumADC: 560  // This is to correct for the TPS reading at wide open throttle.
#elif CONFIG == SNOTROCKET_ID
		TPSMinimumADC: 185,
		TPSMaximumADC: 809
#else
		TPSMinimumADC: 0,
		TPSMaximumADC: ADC_MAX_VALUE
#endif
	},
	sensorSettings:{ // Warning, until the following mods are made to ADC use, setting this lower than your cranking rpm will result in a pulsing fuel pump.
		readingTimeout: 500, /** Default to 0.5 of a second 120rpm for a 4 cylinder @todo TODO new method of ADC sampling, Always sample ADC async, If no sync, use async ADC readings, otherwise use synced. Do this with pointer to array set at beginning of math */
		numberOfADCsToRead: 8,
		fuelPumpPrimePeriod: 4 // Currently in seconds, may switch units later. Must be at least 1 and at most 60.
	},
	algorithmSettings:{
		loadType:      LOAD_MAP,
		algorithmType: ALGO_SPEED_DENSITY,
#if CONFIG == DEUCECOUPE_ID
		dwellType:     DWELL_RPM,
#elif CONFIG == DEUCES10_ID
		dwellType:     DWELL_RPM,
#elif CONFIG == SEANKLT1_ID
		dwellType:     DWELL_FIXED,
#else
		dwellType:     DWELL_BRV,
#endif
		padding:       0,
#if CONFIG == SEANKLT1_ID
		dwellFixedPeriod: T(2)
#else
		dwellFixedPeriod: T(3)
#endif
	},
	inputOutputSettings:{
//		PullUpEnable:      0x00, // Unused right now
//		ReducedDrive:      0x00, // Unused right now

		PWMEnable:         0xFF, // Enable all PWM channels by default
		PWMPolarity:       0xFF, // Default to "duty is high portion" for all pins
		PWMClock:          0x00, // The fastest we can go for all channels
		PWMClockPrescaler: 0x00, // The fastest prescaler we can go for all channels
		PWMCenterAlign:    0x00, // Default to left aligned
		PWMControl:        0x00, // Default to all 8 bit channels
		PWMScalerA:        0x00, // 0 = 256, 1 = 1, 255 = 255, 0x00 is the slowest we can go
		PWMScalerB:        0x00, // 0 = 256, 1 = 1, 255 = 255, 0x00 is the slowest we can go

		// Default to ~0.4% granularity
		PWMPeriod0: 0xFF,
		PWMPeriod1: 0xFF,
		PWMPeriod2: 0xFF,
		PWMPeriod3: 0xFF,
		PWMPeriod4: 0xFF,
		PWMPeriod5: 0xFF,
		PWMPeriod6: 0xFF,
		PWMPeriod7: 0xFF,

		// Default to pins all low/off
		PWMInitialDuty0: 0x00,
		PWMInitialDuty1: 0x00,
		PWMInitialDuty2: 0x00,
		PWMInitialDuty3: 0x00,
		PWMInitialDuty4: 0x00,
		PWMInitialDuty5: 0x00,
		PWMInitialDuty6: 0x00,
		PWMInitialDuty7: 0x00,

		// Mostly default to low/off state
		PortInitialValueA: 0x00, // Overridden for fuel pump and CEL outputs
		PortInitialValueB: 0x00,
		PortInitialValueC: 0x00,
		PortInitialValueD: 0x00,
		PortInitialValueE: 0x00, // TODO necessary to override???
		PortInitialValueH: 0x00,
		PortInitialValueJ: 0x00,
		PortInitialValueK: 0x00,
		PortInitialValueM: 0x00,
		PortInitialValueP: 0x00,
		PortInitialValueS: 0x00, // Overridden for main communications on SCI0
		PortInitialValueT: 0x00, // Ignored! TODO: Overridden for precision timed outputs

		// Mostly default to outputs to reduce power consumption and heat. See the note at the end of chapter 1.2.2 of MC9S12XDP512V2.pdf
		PortDirectionA: 0xFF, // Overridden for fuel pump and CEL outputs
		PortDirectionB: 0xFF,
		PortDirectionC: 0xFF,
		PortDirectionD: 0xFF,
		PortDirectionE: 0xFF,
		PortDirectionH: 0x00, // All pins configured as inputs for misc isrs
		PortDirectionJ: 0xFF,
		PortDirectionK: 0xFF,
		PortDirectionM: 0xFF,
		PortDirectionP: 0xFF,
		PortDirectionS: 0xFF, // Overridden for main communications on SCI0
		PortDirectionT: 0xFF  // Ignored! TODO: Overridden for precision timed outputs
	},
	decoderSettings:{
		syncConfirmationsRunning: 10, // This number is arbitrary, add an if block and configure to taste.
		syncConfirmationsStarting: 0, // Most users should leave this zero, however having it set to 1 or 2 could be beneficial
#if CONFIG == HOTEL_ID
		accelerationInputEventTimeTolerance: ACCEL_TIME_TOL(100), // once started this needs a lot less... fix
		decelerationInputEventTimeTolerance: DECEL_TIME_TOL(100),
#elif CONFIG == SNOTROCKET_ID
		accelerationInputEventTimeTolerance: ACCEL_TIME_TOL(100),
		decelerationInputEventTimeTolerance: DECEL_TIME_TOL(100),
#elif CONFIG == SCAVENGER_ID
		accelerationInputEventTimeTolerance: ACCEL_TIME_TOL(100),
		decelerationInputEventTimeTolerance: DECEL_TIME_TOL(100),
#else
		accelerationInputEventTimeTolerance: ACCEL_TIME_TOL(50),
		decelerationInputEventTimeTolerance: DECEL_TIME_TOL(50),
#endif
		missingToothTolerance: 2048 // 2048 is 50% right now...
	},
	userTextField2: "Place your personal notes about whatever you like in here!"
			" Don't hesitate to tell us a story about something interesting."
			" Do keep in mind though that when you upload your settings file to "
			"the forum this message WILL be visible to all and sundry, so don't "
			"be putting too many personal details, bank account numbers, "
			"passwords, PIN numbers, license plates, national insurance numbers, "
			"IRD numbers, social security numbers, phone numbers, email addresses,"
			" love stories and other private information in this field. In fact it"
			" is probably best if you keep the information stored here purely "
			"related to the vehicle that this system is installed on and relevant "
			"to the state of tune and configuration of settings. Lastly, please "
			"remember that this field WILL be shrinking in length from it's "
			"currently large size to something more reasonable in future. I would "
			"like to attempt to keep it at least thirty two characters lon"
};
