/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010, 2011 Fred Cooke
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


/** @file TimingTables.c
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
 *
 * @author Fred Cooke
 */


#include "../inc/freeEMS.h"


// See fuelAndIgnitionCalcs.c for more info about CLIFLAGS builds!
/* The main Advance Table */
const volatile mainTable IgnitionAdvanceTableMainFlash TIMETABLESD = {
	MAINTABLE_RPM_LENGTH,		/* AdvanceTableMain.RPMLength */
	MAINTABLE_LOAD_LENGTH,		/* AdvanceTableMain.LoadLength */
	/* AdvanceTableMain.RPM */
	{
#ifdef TRUCK
#include "../data/tables/axis/FredsTruck-RPM.h"
#elif HOTEL
#include "../data/tables/axis/HotelHyundai-RPM.h"
#elif PRESTO
#include "../data/tables/axis/FredsTruck-RPM.h"
#elif SEANKLT1
#include "../data/tables/axis/FredsTruck-RPM.h"
#elif SEANKR1
#include "../data/tables/axis/FredsTruck-RPM.h"
#else
#include "../data/tables/axis/FredsTruck-RPM.h"
#endif
	},
	/*AdvanceTableMain.Load */
	{
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
#else
#include "../data/tables/axis/FredsTruck-Load.h"
#endif
	},
	/* AdvanceTableMain.Table */
	{
// USE FLAT 0 DEGREE TIMING UNTIL YOU CAN VERIFY YOUR DECODER OFFSET!!
#ifdef TRUCK
#include "../data/tables/ign/FredsTruckIgnitionTiming.h"
#elif HOTEL
#include "../data/tables/ign/HotelHyundaiIgnitionTiming.h"
#elif PRESTO
#include "../data/tables/ign/flat15degrees.h"
#elif SEANKLT1
#include "../data/tables/ign/flat0degrees.h"
#elif SEANKR1
#include "../data/tables/ign/flat0degrees.h"
#else
#include "../data/tables/ign/flat0degrees.h"
#endif
	}
};


/* The secondary Advance Table */
const volatile mainTable IgnitionAdvanceTableSecondaryFlash TIMETABLESD = {
	MAINTABLE_RPM_LENGTH,		/* AdvanceTableSecondary.RPMLength */
	MAINTABLE_LOAD_LENGTH,		/* AdvanceTableSecondary.LoadLength */
	/* AdvanceTableSecondary.RPM */
	{
		#include "../data/tables/axis/mainTable-RPM.h"
	},
	/*AdvanceTableSecondary.Load */
	{
		#include "../data/tables/axis/mainTable-Load.h"
	},
	/* AdvanceTableSecondary.Table */
	{
		#include "../data/tables/ign/flat15degrees.h"
	}
};


/* The main Volumetric Efficiency Table */
const volatile mainTable InjectionAdvanceTableMainFlash TIMETABLESD = {
	MAINTABLE_RPM_LENGTH,		/* VETableMain.RPMLength */
	MAINTABLE_LOAD_LENGTH,		/* VETableMain.LoadLength */
	/* VETableMain.RPM */
	{
		#include "../data/tables/axis/mainTable-RPM.h"
	},
	/*VETableMain.Load */
	{
		#include "../data/tables/axis/mainTable-Load.h"
	},
	/* VETableMain.Table */
	{
		#include "../data/tables/ign/flat15degrees.h"
	}
};


/* The secondary Volumetric Efficiency Table */
const volatile mainTable InjectionAdvanceTableSecondaryFlash TIMETABLESD = {
	MAINTABLE_RPM_LENGTH,		/* VETableSecondary.RPMLength */
	MAINTABLE_LOAD_LENGTH,		/* VETableSecondary.LoadLength */
	/* VETableSecondary.RPM */
	{
		#include "../data/tables/axis/mainTable-RPM.h"
	},
	/*VETableSecondary.Load */
	{
		#include "../data/tables/axis/mainTable-Load.h"
	},
	/* VETableSecondary.Table */
	{
		#include "../data/tables/ign/flat15degrees.h"
	}
};
