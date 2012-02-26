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
#elif SLATER
		perCylinderVolume:  cylinderSize324cc,
		injectorFlow:       injector320cc,
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
	coarseBitBangSettings:{
#ifdef SNOTROCKET
		outputActions:      simisTachoArray,
#elif SLATER
		outputActions:      slaterTachoArray,
#else
		outputActions:      standardTachoArray,
#endif
		ports:              standardTachoPorts,
		masks:              standardTachoMasks,
		numberConfigured:   1
	},
	schedulingSettings:{
// Sadly, FreeEMS car numero uno is gone, RIP Volvo! http://forum.diyefi.org/viewtopic.php?f=55&t=1068

#ifdef TRUCK // Fred's Ford Courier http://forum.diyefi.org/viewtopic.php?f=55&t=1069
		anglesOfTDC: {(0 * oneDegree), (180 * oneDegree), (360 * oneDegree), (540 * oneDegree), (0 * oneDegree), (360 * oneDegree)},
		outputEventPinNumbers:       {0,1,2,3,4,5,4,5}, // COP and semi-sequential
		schedulingConfigurationBits: {0,0,0,0,1,1,1,1}, // First four ignition, last four fuel
		decoderEngineOffset:       (90.00 * oneDegree), // FE-DOHC, 4and1 CAS approximately centre
		numberOfConfiguredOutputEvents:              8, // Migrated to new way
		numberOfInjectionsPerEngineCycle:            2  // Used to be batch, dead time being wrong could have affected AFRs

#elif HOTEL // Fred's Hotel Hyundai (Stellar) http://forum.diyefi.org/viewtopic.php?f=55&t=1086
		anglesOfTDC:           {(0 * oneDegree)}, // Simple dual edge dizzy
		outputEventPinNumbers:               {0}, // First pin
		schedulingConfigurationBits:         {0}, // Ignition only
		decoderEngineOffset: (20.00 * oneDegree), // Distributor fully retarded? Is this true? I don't think so?
		numberOfConfiguredOutputEvents:        1, // One per decoder cycle = 4
		numberOfInjectionsPerEngineCycle:      1  // Ditto

#elif PRESTO // Preston's silver-top-on-a-stand http://forum.diyefi.org/viewtopic.php?f=55&t=1101
		anglesOfTDC: {(0 * oneDegree), (180 * oneDegree), (360 * oneDegree), (540 * oneDegree), (0 * oneDegree), (180 * oneDegree), (360 * oneDegree), (540 * oneDegree)},
		outputEventPinNumbers:       {0,1,0,1,4,5,4,5}, // Wasted spark, semi-sequential TODO migrate this to sequential
		schedulingConfigurationBits: {0,0,0,0,1,1,1,1}, // First four ignition, last four injection
		decoderEngineOffset:      (128.52 * oneDegree), // Stock silver-top using G? for RPM2 and NE for RPM1, CAS approximately centre, @todo TODO find values for extremes of dizzy placement
		numberOfConfiguredOutputEvents:              8, // See two lines above
		numberOfInjectionsPerEngineCycle:            2  // Semi-sequential, for now.

#elif SEANKLT1 // http://forum.diyefi.org/viewtopic.php?f=55&t=1146
		anglesOfTDC: {(0 * oneDegree), (90 * oneDegree), (180 * oneDegree), (270 * oneDegree), (360 * oneDegree), (450 * oneDegree), (540 * oneDegree), (630 * oneDegree), (0 * oneDegree), (90 * oneDegree), (180 * oneDegree), (270 * oneDegree), (360 * oneDegree), (450 * oneDegree), (540 * oneDegree), (630 * oneDegree)},
		outputEventPinNumbers:       {0,0,0,0,0,0,0,0,2,3,4,5,2,3,4,5}, // LTCC e-dizzy, semi-sequential injection 1/6, 8/5, 4/7, 3/2, and repeat
		schedulingConfigurationBits: {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1}, // See below two lines
		decoderEngineOffset:        (0.00 * oneDegree), // Decoder has a true zero zero mechanically hard coded
		numberOfConfiguredOutputEvents:             16, // First half ignition, second half injection
		numberOfInjectionsPerEngineCycle:            2  // Full sync semi-sequential

#elif JOSHBROWN // Josh's 2.3 turbo volvo with 1600cc injectors making shit loads of power etc. Never ran, but nearly... hw issues
		anglesOfTDC: {(0 * oneDegree), (180 * oneDegree), (360 * oneDegree), (540 * oneDegree), (0 * oneDegree), (180 * oneDegree), (360 * oneDegree), (540 * oneDegree)},
		outputEventPinNumbers:       {0,1,0,1,2,3,4,5}, // Wasted spark setup with full sync AND sequential
		schedulingConfigurationBits: {0,0,0,0,1,1,1,1}, // ignition = 0, injection = 1
		decoderEngineOffset:      (570.00 * oneDegree), // May not be perfect, had ignitor/Puma issues... Stockish Volvo B230FT with DSM/Miata CAS + 24+1 disk.
		numberOfConfiguredOutputEvents:              8, // First half ignition, second half injection
		numberOfInjectionsPerEngineCycle:            1  // Sequential

//#elif MARCOSFIAT // No config available for this vehicle. http://forum.diyefi.org/viewtopic.php?f=55&t=1303

#elif SNOTROCKET // http://forum.diyefi.org/viewtopic.php?f=3&t=1263 Sim's 2.1 Volvo, carbed with CNP using LS1 coils.
		anglesOfTDC: {(0 * oneDegree), (180 * oneDegree), (360 * oneDegree), (540 * oneDegree)}, // 1,2,3,4: Firing order: 1-3-4-2 set up in loom
		outputEventPinNumbers:           {0,1,2,3}, // COP/CNP ignition only
		schedulingConfigurationBits:     {0,0,0,0}, // All ignition
		decoderEngineOffset:  (482.00 * oneDegree), // Volvo B21A with DSM/Miata CAS + 24and1 disk
		numberOfConfiguredOutputEvents:          4, // COP setup
		numberOfInjectionsPerEngineCycle:        1  // Ditto

#elif SPUDMN // http://forum.diyefi.org/viewtopic.php?f=55&t=1507 Spudmn's mk1 racing mini in NZ :-)
		anglesOfTDC: {(0 * oneDegree), (180 * oneDegree)}, // 1 and 4, 2 and 3
		outputEventPinNumbers:               {0,1}, // Ignition only
		schedulingConfigurationBits:         {0,0}, // Ditto
		decoderEngineOffset:    (0.00 * oneDegree), // Yet to be checked with timing light
		numberOfConfiguredOutputEvents:          2, // Wasted spark
		numberOfInjectionsPerEngineCycle:        1  // Ditto

#elif SLATER // http://forum.diyefi.org/viewtopic.php?f=62&t=1336  Citroen with t25 turbo on a flat 4 air cooled engine
		anglesOfTDC: {(0 * oneDegree), (180 * oneDegree),(0 * oneDegree), (180 * oneDegree)}, // 1 and 4, 2 and 3, repeat
		outputEventPinNumbers:           {0,1,4,5}, // 2 and 3 are unused in this config, fuel are on 4/5 because he plans to use the same hardware on the V8 Supra with wasted spark and thus 2/3 are required for ignition on that
		schedulingConfigurationBits:     {0,0,1,1}, // 2 ignition 2 injection
		decoderEngineOffset:  (120.00 * oneDegree), // May need adjusting
		numberOfConfiguredOutputEvents:          4, // Wasted spark, semi-sequential
		numberOfInjectionsPerEngineCycle:        2  // Semi-sequential, crank sync only

#elif PETERJSERIES // Firing order 1-4-2-5-3-6 http://forum.diyefi.org/viewtopic.php?f=62&t=1533
		anglesOfTDC: {(0 * oneDegree), (120 * oneDegree), (240 * oneDegree), (360 * oneDegree), (480 * oneDegree), (600 * oneDegree)},
		outputEventPinNumbers:       {0,3,1,4,2,5}, // An example of wiring your engine with cylinder one on output one, harder to grok
		schedulingConfigurationBits: {1,1,1,1,1,1}, // Ones represent scheduling for injection, zeros represent scheduling for ignition
		decoderEngineOffset:    (0.00 * oneDegree), // Trim fuel injection END point with this value.
		numberOfConfiguredOutputEvents:          6, // THESE ARE NOT IGN, THEY ARE FUEL
		numberOfInjectionsPerEngineCycle:        1  // Sequential, baby, yeah!

// Looking forward to there being links to threads here soon! In no particular order:
//#elif LEV8N
//#elif SEANKR1
//#elif DEUCECOUPE
//#elif TTV8SUPRA
//#elif SECRETSQUIRREL // Shhhhhh! :-p
//#elif HOTCAT
//#elif MICROTECHSUCKS // Yes, that's you, John "I love MicroTech" Tramp
//#elif QUAKE86 // Yep, this one too! :-)
//#elif CRAIGB2200
//#elif DAILYRAVAGE // No pun intended!
//#elif QUICKRAVAGE // No pun intended here either!
// No pressure guys! <cough, cough> :-)

#else // Nothing scheduled by default, no sensible default for all possible vehicle setups.
		anglesOfTDC:                            {}, // Depends on cylinder count and other variables
		outputEventPinNumbers:       {0,1,2,3,4,5}, // Default to a variety of pins for testing purposes. Note: Won't do anything without
		schedulingConfigurationBits:            {}, // All ignition by guarantee of C, configured explicitly for real setups.
		decoderEngineOffset:    (0.00 * oneDegree), // Start with zero, work your way to the correct value
		numberOfConfiguredOutputEvents:          0, // This disables scheduling completely, should match the first, second and third arrays
		numberOfInjectionsPerEngineCycle:        1  // 720 degree decoders with one injection per cycle
#endif
	},
	userTextField:          "Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installe"
};
