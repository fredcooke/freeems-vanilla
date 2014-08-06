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
 * @brief Small tables and other live tunable data
 *
 * This file contains the definition of the secondary set of tunable
 * configuration data.The declaration can be found in the global
 * constants header file.
 *
 * Please ensure that any items added to the struct type definition
 * have appropriate defaults added here also. See the documentation
 * for SmallTables1 for more details.
 *
 * For more information, please see the @ref tuneSwitching page.
 */


#define SmallTablesAFlashV SmallTablesAFlash2
#define SmallTablesBFlashV SmallTablesBFlash2
#define SmallTablesCFlashV SmallTablesCFlash2
#define SmallTablesDFlashV SmallTablesDFlash2
#define TUNETABLESDV1 TUNETABLESD5
#define TUNETABLESDV2 TUNETABLESD6
#define TUNETABLESDV3 TUNETABLESD7
#define TUNETABLESDV4 TUNETABLESD8

#include "TunableConfig.c"
