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
 * @brief A 16 long set of loads for my truck before mtx supports full tables
 *
 * This file only contains the data to be hash included into all mainTable Load sections
 *
 * @author Fred Cooke
 */


/* 16 load values starting at 15kPa and ending at 225kPa, with a boost cut, only the first 16 are used at the moment */
// 15,     30.     45.     60.     75.     90.    105,    120,    135,    150,    165,    180,    195,    210,   225,     225.01

 1500,	 3000,	 4500,	 6000,
 7500,	 9000,	10500,	12000,
13500,	15000,	16500,	18000,
19500,	21000,	22500,	22501,

// spare:
27200,	28800,	30400,	32000,
33600
