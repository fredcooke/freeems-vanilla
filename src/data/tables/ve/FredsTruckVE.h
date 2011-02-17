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


/* Laid out to make sense for 26 RPM and 19 Load bins, 8 extras on end to make up size. */
/* 80% flat */
//  vacuum                                                                                                              boost
// 0 0 here
//zero RPM
40000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  55550,      0, // last row as boost cut
41000,  42011,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  55550,      0,
41000,  41000,  43022,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  55550,      0,
41000,  41000,  41000,  44033,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  55550,      0,

41000,  41000,  41000,  41000,  45044,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  55550,      0,
41000,  41000,  41000,  41000,  41000,  46055,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  55550,      0,
41000,  41000,  41000,  41000,  41000,  41000,  47066,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  55550,      0,
41000,  41000,  41000,  41000,  41000,  41000,  41000,  48077,  41000,  41000,  41000,  41000,  41000,  41000,  55550,      0,

41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  49088,  41000,  41000,  41000,  41000,  41000,  55550,      0,
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  50099,  41000,  41000,  41000,  41000,  55550,      0,
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  51110,  41000,  41000,  41000,  55550,      0,
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  52220,  41000,  41000,  55550,      0,

41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  53330,  41000,  55550,      0,
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  54440,  55550,      0,
33333,  33333,  33333,  33333,  33333,  33333,  33333,  33333,  33333,  33333,  41000,  41000,  41000,  41000,  55550,      0,
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // last column as rev limit
// revlimit or beyond
//                                                                                                                      15 15 here

// kpa
// 15,     30.     45.     60.     75.     90.    105,    120,    135,    150,    165,    180,    195,    210,   225,     225.01

// Unused until we get full variable size table tuning, firmware can handle it, tuning currently can't :

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
