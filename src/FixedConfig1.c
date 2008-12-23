/*	FixedConfig1.c

	Copyright 2008 Fred Cooke

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
	along with any FreeEMS software.  If not, see <http://www.gnu.org/licenses/>.

	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org

	Thank you for choosing FreeEMS to run your engine! */

#include "inc/freeEMS.h"


const volatile fixedConfig1 fixedConfigs1 FIXEDCONF1 = {
	/* Each bit represents the state of some core setting, masks below and above where the same one is used */
	/* Settings variables : 0 = false */
	/* unsigned short coreSettingsA = */	0x07F0,			/* See definitions in freeems.h */

	/* Pre configured value settings for the sensor inputs */
	/* unsigned short presetIAT = */		roomTemperature,
	/* unsigned short presetCHT = */		runningTemperature,
	/* unsigned short presetTPS = */		halfThrottle,
	/* unsigned short presetEGO = */		stoichiometricLambda,
	/* unsigned short presetBRV = */		runningVoltage,
	/* unsigned short presetMAP = */		idleManifoldPressure,
	/* unsigned short presetAAP = */		seaLevelKPa,
	/* unsigned short presetMAT = */		roomTemperature,
	/* unsigned short presetEGO2 = */		stoichiometricLambda,
	/* unsigned short presetIAP = */		maxExpectedBoost,
	/* unsigned short presetBPW = */		idlePulseWidth,
	/* unsigned short presetAF = */			idleAirFlow,


	/* Fuel injection settings */
	/* unsigned short perCylinderVolume = */	typicalCylinderSize,
	/* unsigned short stoichiometricAFR = */	stoichiometricAFROctane,
	/* unsigned short injectorFlow = */			typicalInjectorSize,
	/* unsigned short densityOfFuelAtSTP = */	densityOfOctane,


	/* Sensor related settings */
	/* unsigned short TPSClosedMAP = */		offIdleMAP,		/* Around 30kPa */
	/* unsigned short TPSOpenMAP = */		nearlyWOTMAP,	/* Around 95kPa */


	/* Sensor input conditioning settings */
	/* These are used to calculate MAP, EGO and TPS from ADC readings. */
	/* unsigned short MAPMinimum = */		MPX4250AMin,			/* Default to MPX4250A 260kPa - 8kPa = 252kPa See the link for the transfer function */
	/* unsigned short MAPRange = */			MPX4250ARange,			/* www.freescale.com/files/sensors/doc/data_sheet/MPX4250A.pdf */
	/* unsigned short AAPMinimum = */		MPX4100AMin,			/* Default to MPX4100A 107.5kPa - 14kPa = 93.5kPa See the link for the transfer function */
	/* unsigned short AAPRange = */			MPX4100ARange,			/* www.freescale.com/files/sensors/doc/data_sheet/MPX4100A.pdf */
	/* unsigned short EGOMinimum = */		LC1LambdaMin,			/* Default to Innovate LC-1 on lambda 0.5 - 1.5 for 0-5V range */
	/* unsigned short EGORange = */			LC1LambdaRange,			/* Range of lambda 1.0 */
	/* unsigned short BRVMinimum = */		batteryVoltageMin,		/* 0 - 24.5 Volt measurement with 10k and 39k resistors */
	/* unsigned short BRVRange = */			batteryVoltageRange,	/* http://www.google.com/search?hl=en&safe=off&q=5+*+(39000+%2B+10000)+%2F+10000&btnG=Search */
	/* unsigned short TPSMinimumADC = */	TPSDefaultMin,			/* 25% of voltage = closed (0%) */
	/* unsigned short TPSMaximumADC = */	TPSDefaultMax,			/* 75% of voltage = open (100%) */
	/* unsigned char userTextField[userTextFieldArrayLength] = */	{"Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installed on and relevant to the state of tune and configuration of settings. Lastly, please remember that this field WILL be shrinking in length from it's currently large size to something more reasonable in future. I would like to attempt to keep it at least thirty two characters long though, so writing that much is a non issue, but "}
//	/* unsigned char userTextField[userTextFieldArrayLength] = */	{"Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installed on and relevant to the state of tune and configuration of settings. Lastly, please remember that this field WILL be shrinking in length from it's currently large size to something more reasonable in future. I would like to attempt to keep it at least thirty two characters long though, so writing that much is a non issue, but "}
};
