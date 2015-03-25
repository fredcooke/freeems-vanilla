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
 * @brief Injection and ignition timing tables
 *
 * This file contains the definitions of the primary group timing tables. The
 * declaration can be found in the global constants header file.
 *
 * @note At least one Doxygen bug prevents the data structures below being show
 *       correctly in the documentation for this file. Please see the source
 *       code itself for more information.
 */


#include "../inc/freeEMS.h"


#ifndef IgnitionAdvanceTableMainFlashV
#define IgnitionAdvanceTableMainFlashV IgnitionAdvanceTableMainFlash
#define IgnitionAdvanceTableSecondaryFlashV IgnitionAdvanceTableSecondaryFlash
#define InjectionAdvanceTableMainFlashV InjectionAdvanceTableMainFlash
#define InjectionAdvanceTableSecondaryFlashV InjectionAdvanceTableSecondaryFlash
#endif


// See fuelAndIgnitionCalcs.c for more info about CLIFLAGS builds!
/* The main Advance Table */
const volatile mainTable IgnitionAdvanceTableMainFlashV TIMETABLESD = {
#if CONFIG == DEFAULT_ID
	RPMLength:  MAINTABLE_RPM_LENGTH,
	LoadLength: MAINTABLE_LOAD_LENGTH,
#elif CONFIG == SNOTROCKET_ID
	RPMLength:  12,
	LoadLength: 8,
#elif CONFIG == DEUCES10_ID
	RPMLength:  13,
	LoadLength: 10,
#elif CONFIG == SCAVENGER_ID
	RPMLength:  24,
	LoadLength: 19,
#else
	RPMLength:  16,
	LoadLength: 16,
#endif
	RPM:{
#if CONFIG == TRUCK_ID
#include "../data/tables/axis/FredsTruck-RPM.h"
#elif CONFIG == HOTEL_ID
#include "../data/tables/axis/HotelHyundai-RPM.h"
#elif CONFIG == PRESTO_ID
#include "../data/tables/axis/FredsTruck-RPM.h"
#elif CONFIG == SEANKLT1_ID
#include "../data/tables/axis/SeansLT1-RPM.h"
#elif SEANKR1 // No ID assigned yet!
#include "../data/tables/axis/FredsTruck-RPM.h"
#elif CONFIG == SNOTROCKET_ID
#include "../data/tables/axis/SimsVolvo-RPM.h"
#elif CONFIG == SLATER_ID
#include "../data/tables/axis/Slater-RPM.h"
#elif CONFIG == DEUCECOUPE_ID
#include "../data/tables/axis/HotelHyundai-RPM.h"
#elif CONFIG == DEUCES10_ID
#include "../data/tables/axis/Deuces3100-RPM.h"
#elif CONFIG == PETERTRUCK_ID
#include "../data/tables/axis/HotelHyundai-RPM.h"
#elif CONFIG == SCAVENGER_ID
#include "../data/tables/axis/ScavengersMiata-RPM.h"
#elif CONFIG == M2CUPAR_ID
#include "../data/tables/axis/M2cupcar-FE3-RPM.h"
#elif CONFIG == DEFAULT_ID
#include "../data/tables/axis/DefaultWith400Spacing-RPM.h"
#else
#include "../data/tables/axis/FredsTruck-RPM.h"
#endif
	},
	Load: {
#if CONFIG == TRUCK_ID
#include "../data/tables/axis/FredsTruck-Load.h"
#elif CONFIG == HOTEL_ID
#include "../data/tables/axis/HotelHyundai-Load.h"
#elif CONFIG == PRESTO_ID
#include "../data/tables/axis/FredsTruck-Load.h"
#elif CONFIG == SEANKLT1_ID
#include "../data/tables/axis/FredsTruck-Load.h"
#elif SEANKR1 // No ID assigned yet!
#include "../data/tables/axis/FredsTruck-Load.h"
#elif CONFIG == SNOTROCKET_ID
#include "../data/tables/axis/SimsVolvo-Load.h"
#elif CONFIG == SLATER_ID
#include "../data/tables/axis/Slater-Load.h"
#elif CONFIG == DEUCECOUPE_ID
#include "../data/tables/axis/HotelHyundai-Load.h"
#elif CONFIG == DEUCES10_ID
#include "../data/tables/axis/Deuces3100-Load.h"
#elif CONFIG == PETERTRUCK_ID
#include "../data/tables/axis/HotelHyundai-Load.h"
#elif CONFIG == SCAVENGER_ID
#include "../data/tables/axis/ScavengersMiata-Load.h"
#elif CONFIG == M2CUPCAR_ID
#include "../data/tables/axis/M2cupcar-FE3-Load.h"
#elif CONFIG == DEFAULT_ID
#include "../data/tables/axis/DefaultWith10and20SplitSpacing-Load.h"
#else
#include "../data/tables/axis/FredsTruck-Load.h"
#endif
	},
	Table: {
// USE FLAT 0 DEGREE TIMING UNTIL YOU CAN VERIFY YOUR DECODER OFFSET!!
#if CONFIG == TRUCK_ID
#include "../data/tables/ign/FredsTruckIgnitionTiming.h"
#elif CONFIG == HOTEL_ID
#include "../data/tables/ign/HotelHyundaiIgnitionTiming.h"
#elif CONFIG == PRESTO_ID
#include "../data/tables/ign/flat15degrees.h"
#elif CONFIG == SEANKLT1_ID
#include "../data/tables/ign/SeansLT1IgnitionTiming.h"
#elif SEANKR1 // No ID assigned yet!
#include "../data/tables/ign/flat0degrees.h"
#elif CONFIG == SNOTROCKET_ID
#include "../data/tables/ign/SimsVolvoIgnitionTiming.h"
#elif CONFIG == SLATER_ID
#include "../data/tables/ign/SlaterTiming.h"
#elif CONFIG == DEUCECOUPE_ID
//#include "../data/tables/ign/TestDIS.h" // Use for verifying your DIS timing
#include "../data/tables/ign/Deuces3100Timing.h"
#elif CONFIG == DEUCES10_ID
#include "../data/tables/ign/DeucesS10Timing.h"
#elif CONFIG == PETERTRUCK_ID
#include "../data/tables/ign/HotelHyundaiIgnitionTiming.h"
#elif CONFIG == SCAVENGER_ID
#include "../data/tables/ign/ScavengerTiming24RPMx19Load.h"
#elif CONFIG == M2CUPCAR_ID
#include "../data/tables/ign/M2cupcarFE3Timing.h"
#elif CONFIG == DEFAULT_ID
#include "../data/tables/ign/DefaultTiming24RPMx19Load.h"
#else
#include "../data/tables/ign/flat10degrees.h"
#endif
	}
};


/* The secondary Advance Table */
const volatile mainTable IgnitionAdvanceTableSecondaryFlashV TIMETABLESD = {
	RPMLength:  MAINTABLE_RPM_LENGTH,
	LoadLength: MAINTABLE_LOAD_LENGTH,
	RPM:{
		#include "../data/tables/axis/DefaultWith400Spacing-RPM.h"
	},
	Load:{
		#include "../data/tables/axis/DefaultWith10and20SplitSpacing-Load.h"
	},
	Table:{
		#include "../data/tables/ign/flat15degrees.h"
	}
};


/* The main Volumetric Efficiency Table */
const volatile mainTable InjectionAdvanceTableMainFlashV TIMETABLESD = {
	RPMLength:  MAINTABLE_RPM_LENGTH,
	LoadLength: MAINTABLE_LOAD_LENGTH,
	RPM:{
		#include "../data/tables/axis/DefaultWith400Spacing-RPM.h"
	},
	Load:{
		#include "../data/tables/axis/DefaultWith10and20SplitSpacing-Load.h"
	},
	Table:{
		#include "../data/tables/ign/flat15degrees.h"
	}
};


/* The secondary Volumetric Efficiency Table */
const volatile mainTable InjectionAdvanceTableSecondaryFlashV TIMETABLESD = {
	RPMLength:  MAINTABLE_RPM_LENGTH,
	LoadLength: MAINTABLE_LOAD_LENGTH,
	RPM:{
		#include "../data/tables/axis/DefaultWith400Spacing-RPM.h"
	},
	Load:{
		#include "../data/tables/axis/DefaultWith10and20SplitSpacing-Load.h"
	},
	Table:{
		#include "../data/tables/ign/flat15degrees.h"
	}
};
