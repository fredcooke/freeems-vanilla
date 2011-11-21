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
 * @brief A default set of loads for a boosted engine.
 *
 * This file only contains the data to be hash included into all mainTable Load sections
 *
 * @author Fred Cooke
 */


/* 21 load values starting at 16kPa and ending at 336kPa, only the first 19 are used by default */
 1600,	 3200,	 4800,	 6400,
 8000,	 9600,	11200,	12800,
14400,	16000,	17600,	19200,
20800,	22400,	24000,	25600,
27200,	28800,	30400,	32000,
33600
