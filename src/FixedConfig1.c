/**	@file FixedConfig1.c

	Copyright 2008 Fred Cooke

	This file contains the definition of the first fixed configuration block.
	The declaration can be found in the global constants header file.

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

	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org

	Thank you for choosing FreeEMS to run your engine! */


#include "inc/freeEMS.h"


/// @todo TODO for coreSettingsA masks See definitions in freeEMS.h OR is it in structs.h ???
/// @todo TODO divide fixedConfig1 into useful chunks
/// @todo TODO create presets sensor values struct
/// @todo TODO create engine setup struct
/// @todo TODO create ranges struct
/// @todo TODO add userTextField1 to the dictionary/address lookup


const volatile fixedConfig1 fixedConfigs1 FIXEDCONF1 = {
		0x07F0,                 	/* coreSettingsA */

		roomTemperature,        	/* presetIAT */
		runningTemperature,     	/* presetCHT */
		halfThrottle,           	/* presetTPS */
		stoichiometricLambda,   	/* presetEGO */
		runningVoltage,         	/* presetBRV */
		idleManifoldPressure,   	/* presetMAP */
		seaLevelKPa,            	/* presetAAP */
		roomTemperature,        	/* presetMAT */
		stoichiometricLambda,   	/* presetEGO2 */
		maxExpectedBoost,       	/* presetIAP */
		idlePulseWidth,         	/* presetBPW */
		idleAirFlow,            	/* presetAF */

		typicalCylinderSize,    	/* perCylinderVolume */
		stoichiometricAFROctane,	/* stoichiometricAFR */
		typicalInjectorSize,    	/* injectorFlow */
		densityOfOctane,        	/* densityOfFuelAtSTP */

		offIdleMAP,             	/* TPSClosedMAP */
		nearlyWOTMAP,           	/* TPSOpenMAP */
		MPX4250AMin,            	/* MAPMinimum */
		MPX4250ARange,          	/* MAPRange */
		MPX4100AMin,            	/* AAPMinimum */
		MPX4100ARange,          	/* AAPRange */
		LC1LambdaMin,           	/* EGOMinimum */
		LC1LambdaRange,         	/* EGORange */
		batteryVoltageMin,      	/* BRVMinimum */
		batteryVoltageRange,    	/* BRVRange */
		TPSDefaultMin,          	/* TPSMinimumADC */
		TPSDefaultMax,          	/* TPSMaximumADC */

		{"Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installed on and relevant to the state of tune and configuration of settings. Lastly, please remember that this field WILL be shrinking in length from it's currently large size to something more reasonable in future. I would like to attempt to keep it at least thirty two characters long though, so writing that much is a non issue, but"}	/* userTextField[] */
};
