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
 * @brief Fuel VE and Lambda tables
 *
 * This file contains the definitions of the secondary group VE and lambda
 * tables. The declaration can be found in the global constants header file.
 *
 * @note At least one Doxygen bug prevents the data structures below being show
 *       correctly in the documentation for this file. Please see the source
 *       code itself for more information.
 */


#define VETableMainFlashV VETableMainFlash2
#define VETableSecondaryFlashV VETableSecondaryFlash2
#define VETableTertiaryFlashV VETableTertiaryFlash2
#define LambdaTableFlashV LambdaTableFlash2

#include "FuelTables.c"
