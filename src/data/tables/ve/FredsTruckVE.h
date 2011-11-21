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


/** @file
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


// Low RPM                                                                                                           High RPM
//250     700    1000    1600    2200    2800    3400    4000    4600    5200    5800    6400    7000    7600    8000    8001 // Vacuum
25600,  20480,  15360,  15360,  15360,  15360,  19507,  30000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  15
22528,  17408,  15872,  16384,  17408,  18432,  19763,  34355,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  30
20992,  15872,  15360,  16384,  18432,  18944,  22221,  35891,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  45
20480,  15872,  15872,  18432,  19968,  21504,  25293,  36915,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  60

25088,  22016,  20992,  22016,  23040,  24064,  28877,  37427,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  75
29696,  27136,  26112,  26112,  26624,  28160,  33485,  38963,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  90
32819,  32768,  32768,  33280,  33280,  33280,  36045,  39987,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 105
41000,  36608,  37069,  36557,  37069,  37581,  38605,  40499,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 120

41000,  40499,  39987,  38963,  39475,  39475,  39475,  40499,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 135
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 150
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 165
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 180

41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 195
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 210
55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  56665,      0, // 225
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 226
//250     700    1000    1600    2200    2800    3400    4000    4600    5200    5800    6400    7000    7600    8000    8001 // Boost
// Low RPM                                                                                                           High RPM



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
