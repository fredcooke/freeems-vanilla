/*	FixedConfig2.c

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


const volatile fixedConfig2 fixedConfigs2 FIXEDCONF2 = {
	/* Setting variables (must be inited with useful values) */
	/* unsigned short capacityOfAirPerCombustionEvent = */		500,	/* Default to TODO duplicated above */
	/* unsigned short perPrimaryInjectorChannelFlowRate = */	550,	/* Default to  */
	/* unsigned short perSecondaryInjectorChannelFlowRate = */	550,	/* Default to  */
	/* unsigned short readingTimeout = */						500,	/* Default to half a second 60rpm for a 4 cylinder */
	/* unsigned char ports = */									6,		/* Default to maximum */
	/* unsigned char coils = */									6,		/* Default to  */
	/* unsigned char combustionEventsPerEngineCycle = */		6,		/* Default to  */
	/* unsigned char revolutionsPerEngineCycle = */				2,		/* Default to  */
	/* unsigned char primaryTeeth = */							24,		/* Default to  */
	/* unsigned char missingTeeth = */							0,		/* Default to  */

	/* unsigned short baudDivisor = */		baudDivisor115p2,		/* Used to create the serial clock */
	/* unsigned char networkAddress = */	1,						/* Unique identifier on the network */

	/* unsigned char tachoTickFactor = */						tachoTickFactor4at50,
	/* unsigned short tachoTotalFactor = */						tachoTotalFactor4at50,

	/* temporary contents for notes etc								 "0123456789012345678901234567890n" null terminated */
	/* unsigned char userTextField[userTextFieldArrayLength] = */	{"Place your personal notes about whatever you like in here! Don't hesitate to tell us a story about something interesting. Do keep in mind though that when you upload your settings file to the forum this message WILL be visible to all and sundry, so don't be putting too many personal details, bank account numbers, passwords, PIN numbers, license plates, national insurance numbers, IRD numbers, social security numbers, phone numbers, email addresses, love stories and other private information in this field. In fact it is probably best if you keep the information stored here purely related to the vehicle that this system is installed on and relevant to the state of tune and configuration of settings. Lastly, please remember that this field WILL be shrinking in length from it's currently large size to something more reasonable in future. I would like to attempt to keep it at least thirty two characters long though, so writing that much is a non issue, but if you wish to remain compatible......"}
};
