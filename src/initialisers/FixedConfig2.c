/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
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
		MAPMinimum:    HondaDenso183kPaMin,
		MAPRange:      HondaDenso183kPaRange,
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
#else
		MAPMinimum:    MPX4250AMin,
		MAPRange:      MPX4250ARange,
#endif
// AAP Sensor Configuration
#if CONFIG == SNOTROCKET_ID
		AAPMinimum:    HondaDenso183kPaMin,
		AAPRange:      HondaDenso183kPaRange,
#else
		AAPMinimum:    MPX4100AMin,
		AAPRange:      MPX4100ARange,
#endif
#if CONFIG == SEANKLT1_ID
		EGOMinimum:    AFR1020LambdaMin,
		EGORange:      AFR1020LambdaRange,
#else
		EGOMinimum:    LC1LambdaMin,
		EGORange:      LC1LambdaRange,
#endif
#if CONFIG == HOTEL_ID
		BRVMinimum:    VOLTS(0),
		BRVRange:      VOLTS(25.082),
#elif CONFIG == SNOTROCKET_ID
		BRVMinimum:    VOLTS(0),
		BRVRange:      VOLTS(24.777),
#else
		BRVMinimum:    VOLTS(0),
		BRVRange:      VOLTS(24.5), // Standard 3.9k and 1k values.
#endif
		TPSMinimumADC: 0,
		TPSMaximumADC: ADC_MAX_VALUE
	},
	sensorSettings:{ // Warning, until the following mods are made to ADC use, setting this lower than your cranking rpm will result in a pulsing fuel pump.
		readingTimeout: 500, /** Default to 0.5 of a second 120rpm for a 4 cylinder @todo TODO new method of ADC sampling, Always sample ADC async, If no sync, use async ADC readings, otherwise use synced. Do this with pointer to array set at beginning of math */
		numberOfADCsToRead: 8,
		spare8bitConfig: 0
	},
	algorithmSettings:{
		loadType:      LOAD_MAP,
		algorithmType: ALGO_SPEED_DENSITY
	},
	decoderSettings:{
#if CONFIG == HOTEL_ID
		accelerationInputEventTimeTolerance: ACCEL_TIME_TOL(100), // once started this needs a lot less... fix
		decelerationInputEventTimeTolerance: DECEL_TIME_TOL(100)
#elif CONFIG == SNOTROCKET_ID
		accelerationInputEventTimeTolerance: ACCEL_TIME_TOL(100),
		decelerationInputEventTimeTolerance: DECEL_TIME_TOL(100)
#else
		accelerationInputEventTimeTolerance: ACCEL_TIME_TOL(50),
		decelerationInputEventTimeTolerance: DECEL_TIME_TOL(50)
#endif
	},
	userTextField2:        "Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installed on and relevant to the state of tune and configuration of settings. Lastly, please remember that this field WILL be shrinking in length from it's currently large size to something more reasonable in future. I would like to attempt to keep it at least thirty two characters long though, so writing that much is a non issue, not more!"
};
