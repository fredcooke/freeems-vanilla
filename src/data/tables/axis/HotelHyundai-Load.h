/* FreeEMS - the open source engine management system
 *
 * Copyright 2011 Fred Cooke
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
 * @brief A 16 long set of loads for my hyundai before mtx supports full tables
 *
 * This file only contains the data to be hash included into all mainTable Load sections
 *
 * @author Fred Cooke
 */


// 16 load values starting at 20kPa and ending at 110kPa, only the first 16 are used at the moment
 2000,	 2600,	 3200,	 3800,
 4400,	 5000,	 5600,	 6200,
 6800,	 7400,	 8000,	 8600,
 9200,	 9800,	10400,	11000,

// spare:
27200,	28800,	30400,	32000,
33600
