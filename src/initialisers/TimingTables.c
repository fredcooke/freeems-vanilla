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
	RPMLength:  MAINTABLE_RPM_LENGTH,
	LoadLength: MAINTABLE_LOAD_LENGTH,
	RPM:{
#ifdef TRUCK
#include "../data/tables/axis/FredsTruck-RPM.h"
#elif HOTEL
#include "../data/tables/axis/HotelHyundai-RPM.h"
#elif PRESTO
#include "../data/tables/axis/FredsTruck-RPM.h"
#elif SEANKLT1
#include "../data/tables/axis/SeansLT1-RPM.h"
#elif SEANKR1
#include "../data/tables/axis/FredsTruck-RPM.h"
#elif SNOTROCKET
#include "../data/tables/axis/SimsVolvo-RPM.h"
#else
#include "../data/tables/axis/FredsTruck-RPM.h"
#endif
	},
	Load: {
#ifdef TRUCK
#include "../data/tables/axis/FredsTruck-Load.h"
#elif HOTEL
#include "../data/tables/axis/HotelHyundai-Load.h"
#elif PRESTO
#include "../data/tables/axis/FredsTruck-Load.h"
#elif SEANKLT1
#include "../data/tables/axis/FredsTruck-Load.h"
#elif SEANKR1
#include "../data/tables/axis/FredsTruck-Load.h"
#elif SNOTROCKET
#include "../data/tables/axis/SimsVolvo-Load.h"
#else
#include "../data/tables/axis/FredsTruck-Load.h"
#endif
	},
	Table: {
// USE FLAT 0 DEGREE TIMING UNTIL YOU CAN VERIFY YOUR DECODER OFFSET!!
#ifdef TRUCK
#include "../data/tables/ign/FredsTruckIgnitionTiming.h"
#elif HOTEL
#include "../data/tables/ign/HotelHyundaiIgnitionTiming.h"
#elif PRESTO
#include "../data/tables/ign/flat15degrees.h"
#elif SEANKLT1
#include "../data/tables/ign/SeansLT1IgnitionTiming.h"
#elif SEANKR1
#include "../data/tables/ign/flat0degrees.h"
#elif JOSHBROWN
#include "../data/tables/ign/HotelHyundaiIgnitionTiming.h"
#elif SNOTROCKET
#include "../data/tables/ign/SimsVolvoIgnitionTiming.h"
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
		#include "../data/tables/axis/mainTable-RPM.h"
	},
	Load:{
		#include "../data/tables/axis/mainTable-Load.h"
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
		#include "../data/tables/axis/mainTable-RPM.h"
	},
	Load:{
		#include "../data/tables/axis/mainTable-Load.h"
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
		#include "../data/tables/axis/mainTable-RPM.h"
	},
	Load:{
		#include "../data/tables/axis/mainTable-Load.h"
	},
	Table:{
		#include "../data/tables/ign/flat15degrees.h"
	}
};
