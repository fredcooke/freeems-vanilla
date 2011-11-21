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
    0,  25360,  25360,  25360,  25360,  25360,  29712,  39712,  39712,  39712,  39712,  39712,  39712,  39712,  39712,  39712, //  15
    0,  25360,  25360,  25360,  25360,  25360,  28860,  38860,  38860,  38860,  38860,  38860,  38860,  38860,  38860,  38860, //  30
    0,  25360,  25360,  25360,  25360,  25360,  28010,  38010,  38010,  38010,  38010,  38010,  38010,  38010,  38010,  38010, //  45
    0,  25360,  25360,  25360,  25360,  25360,  27160,  37160,  37160,  37160,  37160,  37160,  37160,  37160,  37160,  37160, //  60

    0,  25360,  25360,  25360,  25360,  25360,  27310,  36310,  36310,  36310,  36310,  36310,  36310,  36310,  36310,  36310, //  75
    0,  25360,  25360,  25360,  25360,  25360,  26460,  28460,  35460,  35460,  35460,  35460,  35460,  35460,  35460,  35460, //  90
    0,  12000,  12360,  15360,  18776,  20192,  25610,  30610,  34610,  34610,  34610,  34610,  34610,  34610,  34610,  34610, // 105
    0,  10360,  10360,  10360,  13493,  15626,  20760,  23760,  23760,  23760,  23760,  23760,  23760,  23760,  23760,  23760, // 120

    0,  10360,  10360,  10360,  11210,  12060,  15910,  18910,  18910,  18910,  18910,  18910,  18910,  18910,  18910,  18910, // 135
    0,  10360,  10360,  10360,  10360,  11210,  15060,  15060,  15060,  15060,  15060,  15060,  15060,  15060,  15060,  15060, // 150
    0,  10360,  10360,  10360,  10360,  10360,  14210,  14210,  14210,  14210,  14210,  14210,  14210,  14210,  14210,  14210, // 165
    0,   5180,  10360,  10360,  10360,  13360,  13360,  13360,  13360,  13360,  13360,  13360,  13360,  13360,  13360,  13360, // 180

    0,   5180,   5180,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  10360,  12360, // 195
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
