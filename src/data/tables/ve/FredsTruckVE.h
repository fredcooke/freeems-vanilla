/* FreeEMS - the open source engine management system
 *
 * Copyright 2010 Fred Cooke
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


/** @file FredsTruckVE.h
 *
 * @ingroup dataInitialisers
 *
 * @brief Will eventually contain my pre-canned tune
 *
 * For now this will be used to ID that tables are being parsed and rendered
 * correctly in mtx 16 by 16
 *
 * This file only contains the data to be hash included into the VE tables
 * in the fuel table files for car specific builds.
 *
 * @author Fred Cooke
 */


//  stalled                                                                                                              revlimit or beyond
50000,  51000,  51000,  51000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  33333,      0,  // Vacuum
51000,  52011,  51000,  51000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  33333,      0, // last row as rev limit
51000,  51000,  53022,  51000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  33333,      0, // last row as rev limit
41000,  41000,  41000,  44033,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  33333,      0, // last row as rev limit

41000,  41000,  41000,  41000,  45044,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  33333,      0, // last row as rev limit
41000,  41000,  41000,  41000,  41000,  46055,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  33333,      0, // last row as rev limit
41000,  41000,  41000,  41000,  41000,  41000,  47066,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  33333,      0, // last row as rev limit
41000,  41000,  41000,  41000,  41000,  41000,  41000,  48077,  41000,  41000,  41000,  41000,  41000,  41000,  33333,      0, // last row as rev limit

41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  49088,  41000,  41000,  41000,  41000,  41000,  33333,      0, // last row as rev limit
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  50099,  41000,  41000,  41000,  41000,  33333,      0, // last row as rev limit
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  51110,  41000,  41000,  41000,  33333,      0, // last row as rev limit
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  52220,  41000,  41000,  33333,      0, // last row as rev limit

41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  53330,  41000,  33333,      0, // last row as rev limit
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  54440,  33333,      0, // last row as rev limit
55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55550,      0, // last row as rev limit
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,  // BOOST
// last column as boost cut



// The rest are UNUSED until we get full variable size table tuning, firmware can handle it, tuning currently can't :

0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,
0,  0,  0,


0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,
0,  0,  0,  0,  0,  0xFFFF /* 6 extras to allow different axis sizes. */
