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
 */


#include "../inc/freeEMS.h"


/// @copydoc fixedConfig1
const volatile fixedConfig1 fixedConfigs1 FIXEDCONF1 = {
	engineSettings:{
#ifdef TRUCK
		perCylinderVolume:  CYLINDER_VOLUME(500),
		injectorFlow:       CC_PER_MINUTE(550), // RX7 "550" which em_knaps had tested at 650cc
#elif PRESTO
		perCylinderVolume:  CYLINDER_VOLUME(400),
		injectorFlow:       CC_PER_MINUTE(213),
#elif SEANKLT1
		perCylinderVolume:  CYLINDER_VOLUME(727),
		injectorFlow:       CC_PER_MINUTE(525),
#elif SEANKR1
		perCylinderVolume:  CYLINDER_VOLUME(250),
		injectorFlow:       CC_PER_MINUTE(230), // http://www.witchhunter.com/flowdatapix/bcdh210.jpg
#elif JOSHBROWN
		perCylinderVolume:  CYLINDER_VOLUME(575),
		injectorFlow:       CC_PER_MINUTE(1600),
#elif SLATER
		perCylinderVolume:  CYLINDER_VOLUME(324),
		injectorFlow:       CC_PER_MINUTE(320),
#elif DEUCECOUPE
		perCylinderVolume:  CYLINDER_VOLUME(522),
		injectorFlow:       CC_PER_MINUTE(235),
#else
		perCylinderVolume:  CYLINDER_VOLUME(500),
		injectorFlow:       CC_PER_MINUTE(550),
#endif
		stoichiometricAFR:  stoichiometricAFRPetrol,
		densityOfFuelAtSTP: densityOfPetrol
	},
	serialSettings:{
		baudDivisor:        SCI_BAUD_DIVISOR(115200) // 21.7013889 (22) http://duckduckgo.com/?q=40000000+%2F+%2816*115200%29
		// http://duckduckgo.com/?q=40000000+%2F+%2816*22%29 113.636 kHz actual speed
		// http://duckduckgo.com/?q=22+%2F+%28%2840000000%2F16%29%2F115200%29 1.376% error in speed
	},
	coarseBitBangSettings:{
#ifdef SNOTROCKET // 24 events for a 24+1 CAS setup with 4 cylinder tacho
		outputActions:      {1,0,0,2,0,0,1,0,0,2,0,0,1,0,0,2,0,0,1,0,0,2,0,0},
#elif SLATER // 11 events for 12-1 crank setup with 4 cylinder tacho
		outputActions:      {1,0,0,2,0,0,1,0,0,2,0},
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
		anglesOfTDC: {ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540), ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540)},
		outputEventPinNumbers:       {0,1,2,3,4,5,4,5}, // COP and semi-sequential
		schedulingConfigurationBits: {0,0,0,0,1,1,1,1}, // First four ignition, last four fuel
		decoderEngineOffset:              ANGLE(90.00), // FE-DOHC, 4and1 CAS approximately centre
		numberOfConfiguredOutputEvents:              8, // Migrated to new way
		numberOfInjectionsPerEngineCycle:            2  // Used to be batch, dead time being wrong could have affected AFRs

#elif HOTEL // Fred's Hotel Hyundai (Stellar) http://forum.diyefi.org/viewtopic.php?f=55&t=1086
		anglesOfTDC:             {ANGLE(0)}, // Simple dual edge dizzy
		outputEventPinNumbers:          {0}, // First pin
		schedulingConfigurationBits:    {0}, // Ignition only
		decoderEngineOffset:    ANGLE(0.00), // Locked dizzy with timing of TDC on edge, used for static timing during cranking.
		numberOfConfiguredOutputEvents:   1, // One per decoder cycle = 4
		numberOfInjectionsPerEngineCycle: 1  // Ditto

#elif PRESTO // Preston's silver-top-on-a-stand http://forum.diyefi.org/viewtopic.php?f=55&t=1101
		anglesOfTDC: {ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540), ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540)},
		outputEventPinNumbers:       {0,1,0,1,4,5,4,5}, // Wasted spark, semi-sequential TODO migrate this to sequential
		schedulingConfigurationBits: {0,0,0,0,1,1,1,1}, // First four ignition, last four injection
		decoderEngineOffset:      ANGLE(128.52), // Stock silver-top using G? for RPM2 and NE for RPM1, CAS approximately centre, @todo TODO find values for extremes of dizzy placement
		numberOfConfiguredOutputEvents:              8, // See two lines above
		numberOfInjectionsPerEngineCycle:            2  // Semi-sequential, for now.

#elif SEANKLT1 // http://forum.diyefi.org/viewtopic.php?f=55&t=1146
		anglesOfTDC: {ANGLE(0), ANGLE(90), ANGLE(180), ANGLE(270), ANGLE(360), ANGLE(450), ANGLE(540), ANGLE(630), ANGLE(0), ANGLE(90), ANGLE(180), ANGLE(270), ANGLE(360), ANGLE(450), ANGLE(540), ANGLE(630)},
		outputEventPinNumbers:       {0,0,0,0,0,0,0,0,2,3,4,5,2,3,4,5}, // LTCC e-dizzy, semi-sequential injection 1/6, 8/5, 4/7, 3/2, and repeat
		schedulingConfigurationBits: {0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1}, // See below two lines
		decoderEngineOffset:               ANGLE(0.00), // Decoder has a true zero zero mechanically hard coded
		numberOfConfiguredOutputEvents:             16, // First half ignition, second half injection
		numberOfInjectionsPerEngineCycle:            2  // Full sync semi-sequential

#elif JOSHBROWN // Josh's 2.3 turbo volvo with 1600cc injectors making shit loads of power etc. Never ran, but nearly... hw issues
		anglesOfTDC: {ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540), ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540)},
		outputEventPinNumbers:       {0,1,0,1,2,3,4,5}, // Wasted spark setup with full sync AND sequential
		schedulingConfigurationBits: {0,0,0,0,1,1,1,1}, // ignition = 0, injection = 1
		decoderEngineOffset:             ANGLE(570.00), // May not be perfect, had ignitor/Puma issues... Stockish Volvo B230FT with DSM/Miata CAS + 24+1 disk.
		numberOfConfiguredOutputEvents:              8, // First half ignition, second half injection
		numberOfInjectionsPerEngineCycle:            1  // Sequential

//#elif MARCOSFIAT // No config available for this vehicle. http://forum.diyefi.org/viewtopic.php?f=55&t=1303

#elif SNOTROCKET // http://forum.diyefi.org/viewtopic.php?f=3&t=1263 Sim's 2.1 Volvo, carbed with CNP using LS1 coils.
		anglesOfTDC: {ANGLE(0), ANGLE(180), ANGLE(360), ANGLE(540)}, // 1,2,3,4: Firing order: 1-3-4-2 set up in loom
		outputEventPinNumbers:           {0,1,2,3}, // COP/CNP ignition only
		schedulingConfigurationBits:     {0,0,0,0}, // All ignition
		decoderEngineOffset:         ANGLE(482.00), // Volvo B21A with DSM/Miata CAS + 24and1 disk
		numberOfConfiguredOutputEvents:          4, // COP setup
		numberOfInjectionsPerEngineCycle:        1  // Ditto

#elif SPUDMN // http://forum.diyefi.org/viewtopic.php?f=55&t=1507 Spudmn's mk1 racing mini in NZ :-)
		anglesOfTDC: {ANGLE(0), ANGLE(180)}, // 1 and 4, 2 and 3
		outputEventPinNumbers:               {0,1}, // Ignition only
		schedulingConfigurationBits:         {0,0}, // Ditto
		decoderEngineOffset:           ANGLE(0.00), // Yet to be checked with timing light
		numberOfConfiguredOutputEvents:          2, // Wasted spark
		numberOfInjectionsPerEngineCycle:        1  // Ditto

#elif SLATER // http://forum.diyefi.org/viewtopic.php?f=62&t=1336  Citroen with t25 turbo on a flat 4 air cooled engine
		anglesOfTDC: {ANGLE(0), ANGLE(180),(0), ANGLE(180)}, // 1 and 4, 2 and 3, repeat
		outputEventPinNumbers:           {0,1,4,5}, // 2 and 3 are unused in this config, fuel are on 4/5 because he plans to use the same hardware on the V8 Supra with wasted spark and thus 2/3 are required for ignition on that
		schedulingConfigurationBits:     {0,0,1,1}, // 2 ignition 2 injection
		decoderEngineOffset:         ANGLE(120.00), // May need adjusting
		numberOfConfiguredOutputEvents:          4, // Wasted spark, semi-sequential
		numberOfInjectionsPerEngineCycle:        2  // Semi-sequential, crank sync only

#elif PETERJSERIES // Firing order 1-4-2-5-3-6 http://forum.diyefi.org/viewtopic.php?f=62&t=1533
		anglesOfTDC: {ANGLE(0), ANGLE(120), ANGLE(240), ANGLE(360), ANGLE(480), ANGLE(600)},
		outputEventPinNumbers:       {0,3,1,4,2,5}, // An example of wiring your engine with cylinder one on output one, harder to grok
		schedulingConfigurationBits: {1,1,1,1,1,1}, // Ones represent scheduling for injection, zeros represent scheduling for ignition
		decoderEngineOffset:           ANGLE(0.00), // Trim fuel injection END point with this value.
		numberOfConfiguredOutputEvents:          6, // THESE ARE NOT IGN, THEY ARE FUEL
		numberOfInjectionsPerEngineCycle:        1  // Sequential, baby, yeah!

#elif DEUCECOUPE // DeuceEFI's GM 3100 V6, firing order 1-6-5-4-3-2, wasted spark DIS ignition http://forum.diyefi.org/viewtopic.php?f=3&t=1278
		anglesOfTDC: {ANGLE(0), ANGLE(120), ANGLE(240), ANGLE(360), ANGLE(480), ANGLE(600), ANGLE(0), ANGLE(120), ANGLE(240), ANGLE(360), ANGLE(480), ANGLE(600)},
		outputEventPinNumbers:       {0,0,0,0,0,0,2,3,4,2,3,4}, // DIS E-dizzy and semi-sequential, for now.
		schedulingConfigurationBits: {0,0,0,0,0,0,1,1,1,1,1,1}, // Six E-dizzy style DIS ignition outputs and six injection events, two per cycle, semi sequential
		decoderEngineOffset:           ANGLE(0.00), // Nothing for now, so as to be able to figure out what is going on.
		numberOfConfiguredOutputEvents:         12, // See three lines above
		numberOfInjectionsPerEngineCycle:        2  // Semi-sequential, for now.

// Looking forward to there being links to threads here soon! In no particular order:
//#elif LEV8N
//#elif SEANKR1
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
		decoderEngineOffset:              ANGLE(0), // Start with zero, work your way to the correct value
		numberOfConfiguredOutputEvents:          0, // This disables scheduling completely, should match the first, second and third arrays
		numberOfInjectionsPerEngineCycle:        1  // 720 degree decoders with one injection per cycle
#endif
	},
	cutAndLimiterSettings:{
		InjectionRPM:{
#ifdef SLATER
			disableThreshold:  RPM(7000),
			reenableThreshold: RPM(6900)
#else
			disableThreshold:  RPM(5000),
			reenableThreshold: RPM(4900)  // Come back on before ignition does
#endif
		},
		IgnitionRPM:{
#ifdef HOTEL
			disableThreshold:  RPM(5800),
			reenableThreshold: RPM(5700) // Nice and close to save the exhaust
#elif SNOTROCKET
			disableThreshold:  RPM(6300),
			reenableThreshold: RPM(6200)
#elif SLATER
			disableThreshold:  RPM(7000),
			reenableThreshold: RPM(6850)
#else
			disableThreshold:  RPM(5000),
			reenableThreshold: RPM(4800)  // Come back on after injection does
#endif
		},
		OverBoost:{
			disableThreshold:  KPA(250), // Cut close to std sensor max
			reenableThreshold: KPA(100)  // Re enable when boost gone all together (force driver to lift)
		},
		cutsEnabled:{
			InjectionRPM: 1,
			IgnitionRPM:  1,
			InjOverBoost: 1,
			IgnOverBoost: 1,
			Spare0: 1,
			Spare1: 1,
			Spare2: 1,
			Spare3: 1,
			Spare4: 1,
			Spare5: 1,
			Spare6: 1,
			Spare7: 1,
			Spare8: 1,
			Spare9: 1,
			SpareA: 1,
			SpareB: 1
		}
	},
	simpleGPIOSettings:{
		outputConfigs:{
			[0] = {
				variable: &CoreVars0.RPM,
				upperValue: RPM(5000),
				lowerValue: RPM(4000),
				port: (unsigned char*)&PORTK,
				mask: 0x08,
				flags: 0
			},
			[1] = {
				variable: &CoreVars0.CHT,
				upperValue: DEGREES_C(100),
				lowerValue: DEGREES_C(90),
				port: (unsigned char*)&PORTK,
				mask: 0x10,
				flags: 0
			}
		},
		numberConfigured: 2,
		spare: 0
	},
	userTextField:          "Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you kee"
};
