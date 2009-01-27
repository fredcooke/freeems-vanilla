/*	FreeEMS - the open source engine management system

	Copyright 2008, 2009 Fred Cooke

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


/**	@file FixedConfig2.c
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


#include "inc/freeEMS.h"


/// @todo TODO divide fixedConfig2 into useful chunks
/// @todo TODO create engine hardware config chunk
/// @todo TODO create random stuff chunk
/// @todo TODO add the userTextField2 to the dictionary/address lookup


/** @copydoc fixedConfig1 */
const volatile fixedConfig2 fixedConfigs2 FIXEDCONF2 = {
		{
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
		idleAirFlow          		/* presetAF */
		},

		{
		offIdleMAP,         		/* TPSClosedMAP */
		nearlyWOTMAP,       		/* TPSOpenMAP */
		MPX4250AMin,        		/* MAPMinimum */
		MPX4250ARange,      		/* MAPRange */
		MPX4100AMin,        		/* AAPMinimum */
		MPX4100ARange,      		/* AAPRange */
		LC1LambdaMin,       		/* EGOMinimum */
		LC1LambdaRange,     		/* EGORange */
		batteryVoltageMin,  		/* BRVMinimum */
		batteryVoltageRange,		/* BRVRange */
		TPSDefaultMin,      		/* TPSMinimumADC */
		TPSDefaultMax       		/* TPSMaximumADC */
		},

		{
		500,                  	/* readingTimeout */ /** Default to half a second 60rpm for a 4 cylinder @todo TODO new method of ADC sampling, Always sample ADC async, If no sync, use async ADC readings, otherwise use synced. Do this with pointer to array set at beginning of math */
		},

		{"Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installed on and relevant to the state of tune and configuration of settings. Lastly, please remember that this field WILL be shrinking in length from it's currently large size to something more reasonable in future. I would like to attempt to keep it at least thirty two characters long though, so writing that much is a non issue, but not more"}
};
