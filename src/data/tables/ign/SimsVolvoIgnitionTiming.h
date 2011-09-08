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


/**	@file SimsVolvoIgnitionTiming.h
 *
 * @ingroup dataInitialisers
 *
 * @brief A timing table for a Volvo B21A.
 *
 * Under development
 *
 * This file only contains the data to be hash included into some timing tables
 * Based in part on Fred's truck table and Nick Sayler's research:
 * http://blog.nsfabrication.com/2010/03/10/taking-a-look-at-lh-22-ignition-curves/
 *
 * @author Fred Cooke
 */


/* Based on divisor of 1024 giving approximately 64 degree range with absurd wasteful accuracy level to be corrected later */
/// TODO @todo this is all wrongly laid out now, due to Dave's whinging, so needs fixing...
/* Laid out to make sense for 24 RPM and 19 Load bins, 8 extras on end to make up size. */

// Low RPM                                                                                                           High RPM
//250     700    1000    1600    2200    2800    3400    4000    4600    5200    5800    6500  6500.5    7600    8000    8001 // Vacuum
10240,  10240,  10240,  14336,  18432,  20480,  27648,  30720,  32768,  33792,  32768,  32768,      0,      0,      0,      0, //  15
10240,  10240,  10240,  26624,  30720,  32768,  39936,  43008,  45056,  47104,  45056,  45056,      0,      0,      0,      0, //  30
10240,  10240,  10240,  29696,  33792,  35840,  44032,  46080,  48128,  50176,  48128,  48128,      0,      0,      0,      0, //  45
10240,  10240,  10240,  28672,  32768,  34816,  41984,  45056,  47104,  49152,  46080,  45056,      0,      0,      0,      0, //  60

10240,  10240,  10240,  23552,  27648,  29696,  36864,  39936,  41984,  43008,  41984,  40960,      0,      0,      0,      0, //  75
10240,  10240,  10240,  16384,  20480,  22528,  29696,  32768,  34816,  36864,  35840,  32768,      0,      0,      0,      0, //  90
10240,  10240,  10240,  14336,  18432,  20480,  27648,  30720,  32768,  34816,  32768,  32768,      0,      0,      0,      0, // 105
10240,  10240,  10240,  14336,  18432,  20480,  27648,  30720,  32768,  34816,  32768,  32768,      0,      0,      0,      0, // 120

    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 135
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 150
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 165
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 180

    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 195
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 210
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 225
    0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0,      0, // 226
//250     700    1000    1600    2200    2800    3400    4000    4600    5200    5800    6500  6500.5    7600    8000    8001 // Boost
// Low RPM                                                                                                           High RPM




15360,  15360,  15360,
15360,  15360,  15360,
15360,  15360,  15360,
15360,  15360,  15360,

15360,  15360,  15360,
15360,  15360,  15360,
15360,  15360,  15360,
15360,  15360,  15360,

15360,  15360,  15360,
15360,  15360,  15360,
15360,  15360,  15360,
15360,  15360,  15360,

15360,  15360,  15360,
15360,  15360,  15360,
15360,  15360,  15360,
15360,  15360,  15360,








15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,
15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,

15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,
15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,
15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,
15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,
15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,
15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,  15360,
15360,  15360,  15360,  15360,  15360,  15360 /* 6 extras to allow different axis sizes. */
