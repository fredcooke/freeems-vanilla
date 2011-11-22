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
 * @ingroup dataInitialisers
 *
 * @brief First fixed config block
 *
 * This file contains the definition of the first fixed configuration block.
 * The declaration can be found in the global constants header file.
 *
 * Please ensure that all variables added here have good default values.
 *
 * @author Fred Cooke
 */


#include "../inc/freeEMS.h"


/// @todo TODO for coreSettingsA masks See definitions in freeEMS.h
/// @todo TODO divide fixedConfig1 into useful chunks
/// @todo TODO create presets sensor values struct
/// @todo TODO create engine setup struct
/// @todo TODO create ranges struct
/// @todo TODO add userTextField1 to the dictionary/address lookup


/** @copydoc fixedConfig1 */
const volatile fixedConfig1 fixedConfigs1 FIXEDCONF1 = {
	engineSettings:{
#ifdef TRUCK
		perCylinderVolume:  cylinderSize500cc,
		injectorFlow:       injector550cc,
#elif PRESTO
		perCylinderVolume:  cylinderSize400cc,
		injectorFlow:       injector213cc,
#elif SEANKLT1
		perCylinderVolume:  cylinderSize727cc,
		injectorFlow:       injector525cc,
#elif SEANKR1
		perCylinderVolume:  cylinderSize250cc,
		injectorFlow:       injector230cc,
#elif JOSHBROWN
		perCylinderVolume:  cylinderSize575cc,
		injectorFlow:       injector1600cc,
#else
		perCylinderVolume:  cylinderSize500cc,
		injectorFlow:       injector550cc,
#endif
		stoichiometricAFR:  stoichiometricAFRGasoline,
		densityOfFuelAtSTP: densityOfPetrol
	},
	serialSettings:{
		baudDivisor:        divisorFor115200bps
	},
	tachoSettings:{
		tachoTickFactor:    tachoTickFactor4at50,
		tachoTotalFactor:   tachoTotalFactor4at50
	},
	coreSettingsA:          0x07F0,
	userTextField:          "Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installed on and relevant to the state of tune and configuration of settings. Lastly, please remember that this field WILL be shrinking in length from it's currently large size to something more reasonable in future. I would like to attempt to keep it at least thirty two characters long though, so writing that much is a non issue, but more won't be possible later!! Extra Space!"
};
