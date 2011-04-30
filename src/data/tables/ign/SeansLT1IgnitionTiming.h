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


/**	@file SeansLT1IgnitionTiming.h
 *
 * @ingroup dataInitialisers
 *
 * @brief A flat 0 degree timing table, ONLY for use with mechanical timing as
 * a basis for a trim table or for finding TDC while setting up an engine.
 *
 * @warning DO NOT RUN YOUR CAR ON THIS!
 *
 * This file only contains the data to be hash included into some timing tables
 *
 * @author Fred Cooke
 */


// Low RPM                                                                                                           High RPM
//100     500     900    1300    1800    2250    2700    3150    3600    4050    4500    4950    5400    5850    6300    6750 // Vacuum
    0,  10360,  10360,  10360,  13477,  16594,  19712,  19712,  19712,  19712,  19712,  19712,  19712,  19712,  19712,  19712, //  15
    0,  10360,  10360,  10360,  13193,  16026,  18860,  18860,  18860,  18860,  18860,  18860,  18860,  18860,  18860,  18860, //  30
    0,  10360,  10360,  10360,  12910,  15460,  18010,  18010,  18010,  18010,  18010,  18010,  18010,  18010,  18010,  18010, //  45
    0,  10360,  10360,  10360,  12626,  14892,  17160,  17160,  17160,  17160,  17160,  17160,  17160,  17160,  17160,  17160, //  60

    0,  10360,  10360,  10360,  12343,  14326,  16310,  16310,  16310,  16310,  16310,  16310,  16310,  16310,  16310,  16310, //  75
    0,  10360,  10360,  10360,  12060,  13760,  15460,  15460,  15460,  15460,  15460,  15460,  15460,  15460,  15460,  15460, //  90
    0,  10360,  10360,  10360,  11776,  13192,  14610,  14610,  14610,  14610,  14610,  14610,  14610,  14610,  14610,  14610, // 105
    0,  10360,  10360,  10360,  11493,  12626,  13760,  13760,  13760,  13760,  13760,  13760,  13760,  13760,  13760,  13760, // 120

    0,  10360,  10360,  10360,  11210,  12060,  12910,  12910,  12910,  12910,  12910,  12910,  12910,  12910,  12910,  12910, // 135
    0,  10360,  10360,  10360,  10360,  11210,  12060,  12060,  12060,  12060,  12060,  12060,  12060,  12060,  12060,  12060, // 150
    0,  10360,  10360,  10360,  10360,  10360,  11210,  11210,  11210,  11210,  11210,  11210,  11210,  11210,  11210,  11210, // 165
    0,   5180,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360, // 180

    0,   5180,   5180,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360, // 195
    0,   5180,   5180,   5180,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360, // 210
    0,   5180,   5180,   5180,   5180,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360, // 225
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 225.01
//100     500     900    1300    1800    2250    2700    3150    3600    4050    4500    4950    5400    5850    6300    6750 //  WOT
// Low RPM                                                                                                           High RPM


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
0,  0,  0,  0,  0,  0
