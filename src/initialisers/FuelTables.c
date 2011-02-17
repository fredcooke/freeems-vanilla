/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009 Fred Cooke
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


/**	@file FuelTables.c
 * @ingroup dataInitialisers
 *
 * @brief Fuel VE and Lambda tables
 *
 * This file contains the definitions of the primary group VE and lambda
 * tables. The declaration can be found in the global constants header file.
 *
 * @note At least one Doxygen bug prevents the data structures below being show
 *       correctly in the documentation for this file. Please see the source
 *       code itself for more information.
 *
 * @author Fred Cooke
 */


#include "../inc/freeEMS.h"


const volatile mainTable VETableMainFlash FUELTABLESD = {
	MAINTABLE_RPM_LENGTH,		/* VETableMain.RPMLength */
	MAINTABLE_LOAD_LENGTH,		/* VETableMain.LoadLength */
	/* VETableMain.RPM */
	{
		#include "../data/tables/axis/FredsTruck-RPM.h"
	},
	/* VETableMain.Load */
	{
		#include "../data/tables/axis/FredsTruck-Load.h"
	},
	/* VETableMain.Table */
	{
		#include "../data/tables/ve/FredsTruckVE.h"
	}
};


const volatile mainTable VETableSecondaryFlash FUELTABLESD = {
	MAINTABLE_RPM_LENGTH,		/* VETableSecondary.RPMLength */
	MAINTABLE_LOAD_LENGTH,		/* VETableSecondary.LoadLength */
	/* VETableSecondary.RPM */
	{
		#include "../data/tables/axis/mainTable-RPM.h"
	},
	/* VETableSecondary.Load */
	{
		#include "../data/tables/axis/mainTable-Load.h"
	},
	/* VETableSecondary.Table */
	{
		#include "../data/tables/ve/flat80Percent.h"
	}
};


const volatile mainTable VETableTertiaryFlash FUELTABLESD = {
	MAINTABLE_RPM_LENGTH,		/* VETableTertiary.RPMLength */
	MAINTABLE_LOAD_LENGTH,		/* VETableTertiary.LoadLength */
	/* VETableTertiary.RPM */
	{
		#include "../data/tables/axis/mainTable-RPM.h"
	},
	/* VETableTertiary.Load */
	{
		#include "../data/tables/axis/mainTable-Load.h"
	},
	/* VETableTertiary.Table */
	{
		#include "../data/tables/ve/flat80Percent.h"
	}
};


const volatile mainTable LambdaTableFlash FUELTABLESD = {
	MAINTABLE_RPM_LENGTH,		/* LambdaTable.RPMLength */
	MAINTABLE_LOAD_LENGTH,		/* LambdaTable.LoadLength */
	/* LambdaTable.RPM */
	{
		#include "../data/tables/axis/FredsTruck-RPM.h"
	},
	/* LambdaTable.Load */
	{
		#include "../data/tables/axis/FredsTruck-Load.h"
	},
	/* LambdaTable.Table */
	{
		#include "../data/tables/lambda/flatStoichiometric.h"
	}
};
