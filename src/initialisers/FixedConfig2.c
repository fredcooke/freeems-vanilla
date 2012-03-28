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
 *
 * @author Fred Cooke
 */


#include "../inc/freeEMS.h"


/// @todo TODO divide fixedConfig2 into useful chunks
/// @todo TODO create engine hardware config chunk
/// @todo TODO create random stuff chunk
/// @todo TODO add the userTextField2 to the dictionary/address lookup


/** @copydoc fixedConfig1 */
const volatile fixedConfig2 fixedConfigs2 FIXEDCONF2 = {
	sensorPresets:{
		presetIAT:  DEGREES_C(20), // Room temperature
		presetCHT:  DEGREES_C(85), // Running temperature
		presetTPS:  PERCENT(50),   // TODO YAGNI
		presetEGO:  LAMBDA(1.0),   // Stoichiometric
		presetBRV:  VOLTS(14.4),   // Standard alternator charging level for wet cell lead acid
		presetMAP:  KPA(30),       // Idle manifold pressure
		presetAAP:  KPA(100),      // Sea-level
		presetMAT:  DEGREES_C(20), // Room temperature
		presetEGO2: LAMBDA(1.0),   // Stoichiometric
		presetIAP:  KPA(250),      // TODO YAGNI
		presetBPW:  PW_MS(1.6),    // TODO YAGNI
		presetAF:   1500 // TODO YAGNI remove? Number is random...
	},
	sensorRanges:{
		TPSClosedMAP:  KPA(30), // Just above where MAP would be with closed throttle at idle
		TPSOpenMAP:    KPA(95), // Just below where MAP would be at WOT
// MAP Sensor Configuration
#ifdef HOTEL
		MAPMinimum:    HondaDenso183kPaMin,
		MAPRange:      HondaDenso183kPaRange,
#elif PRESTO
		MAPMinimum:    HondaDenso183kPaMin,
		MAPRange:      HondaDenso183kPaRange,
#elif SNOTROCKET
		MAPMinimum:    HondaDenso183kPaMin,
		MAPRange:      HondaDenso183kPaRange,
#elif SEANKLT1
		MAPMinimum:    GM2BarMin,
		MAPRange:      GM2BarRange,
#elif SLATER
		MAPMinimum:    HondaDenso183kPaMin,
		MAPRange:      HondaDenso183kPaRange,
//#elif JOSHBROWN
//		MAPMinimum:    MPXH6400AMin,
//		MAPRange:      MPXH6400ARange,
#else
		MAPMinimum:    MPX4250AMin,
		MAPRange:      MPX4250ARange,
#endif
// AAP Sensor Configuration
#ifdef SNOTROCKET
		AAPMinimum:    HondaDenso183kPaMin,
		AAPRange:      HondaDenso183kPaRange,
#else
		AAPMinimum:    MPX4100AMin,
		AAPRange:      MPX4100ARange,
#endif
#ifdef SEANKLT1
		EGOMinimum:    AFR1020LambdaMin,
		EGORange:      AFR1020LambdaRange,
#else
		EGOMinimum:    LC1LambdaMin,
		EGORange:      LC1LambdaRange,
#endif
#ifdef HOTEL
		BRVMinimum:    VOLTS(0),
		BRVRange:      VOLTS(25.082),
#elif SNOTROCKET
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
	},
	decoderSettings:{
// Should macro these, 45.00,50.00 and 100.00 are percentages
#ifdef HOTEL
		accelerationInputEventTimeTolerance: ((100/(100 + 100.00)) * 1000), // once started this needs a lot less... fix
		decelerationInputEventTimeTolerance: (((100 + 100.00)/100) * 1000)
#elif SNOTROCKET
		accelerationInputEventTimeTolerance: ((100/(100 + 100.00)) * 1000),
		decelerationInputEventTimeTolerance: (((100 + 100.00)/100) * 1000)
#else
		accelerationInputEventTimeTolerance: ((100/(100 + 50.00)) * 1000),
		decelerationInputEventTimeTolerance: (((100 + 50.00)/100) * 1000)
#endif
	},
	userTextField2:        "Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installed on and relevant to the state of tune and configuration of settings. Lastly, please remember that this field WILL be shrinking in length from it's currently large size to something more reasonable in future. I would like to attempt to keep it at least thirty two characters long though, so writing that much is a non issue, but not "
};
