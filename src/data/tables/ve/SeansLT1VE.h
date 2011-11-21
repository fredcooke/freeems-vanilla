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
 * @brief Will eventually contain Sean's pre-canned tune
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
//100     500     900    1300    1800    2250    2700    3150    3600    4050    4500    4950    5400    5850    6300    6750 // Vacuum
25600,  25480,  25360,  25360,  30360,  33360,  36507,  35000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  15
25528,  25408,  25872,  25384,  30000,  33432,  36763,  37355,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  30
25992,  25872,  25360,  25384,  30000,  33944,  36221,  38891,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  45
25480,  25872,  25872,  25432,  30000,  33504,  36293,  39915,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  60

25088,  25016,  25992,  30016,  32040,  33064,  36877,  39427,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  75
29696,  27136,  26112,  30112,  32624,  33160,  36485,  39963,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, //  90
32819,  32768,  32768,  33280,  34280,  33280,  36045,  39987,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 105
41000,  36608,  37069,  36557,  37069,  37581,  38605,  40499,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 120

41000,  40499,  39987,  38963,  39475,  39475,  39475,  40499,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 135
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 150
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 165
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 180

41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 195
41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  41000,  65535,      0, // 210
55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  55555,  56665,      0, // 225
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 226
//100     500     900    1300    1800    2250    2700    3150    3600    4050    4500    4950    5400    5850    6300    6750 //  WOT
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
