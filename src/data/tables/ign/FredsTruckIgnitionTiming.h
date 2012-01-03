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
 * @brief A flat 15 degree timing table, good enough for cranking, and
 * conservative enough for anything powerful, but will bake your exhaust
 * manifold/turbo in minutes if driven on.
 *
 * This file only contains the data to be hash included into some timing tables
 *
 * @author Fred Cooke
 */


/* Based on divisor of 1024 giving approximately 64 degree range with absurd wasteful accuracy level to be corrected later */
/// TODO @todo this is all wrongly laid out now, due to Dave's whinging, so needs fixing...
/* Laid out to make sense for 24 RPM and 19 Load bins, 8 extras on end to make up size. */

//  Low RPM                                                                                                            High RPM
//  250     700    1000    1600    2200    2800    3400    4000    4600    5200    5800    6400    7000    7600    8000    8001  // Vacuum
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32),  IT(0), //  15
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32),  IT(0), //  30
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32),  IT(0), //  45
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32),  IT(0), //  60

 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32),  IT(0), //  75
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32),  IT(0), //  90
 IT(10), IT(15), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32),  IT(0), // 105
 IT(10), IT(15), IT(15), IT(17), IT(21), IT(26), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30),  IT(0), // 120

 IT(10), IT(15), IT(15), IT(15), IT(19), IT(23), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28),  IT(0), // 135
 IT(10), IT(15), IT(15), IT(15), IT(17), IT(21), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26),  IT(0), // 150
 IT(10), IT(15), IT(15), IT(15), IT(15), IT(19), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23),  IT(0), // 165
 IT(10), IT(15), IT(15), IT(15), IT(15), IT(17), IT(21), IT(21), IT(21), IT(21), IT(21), IT(21), IT(21), IT(21), IT(21),  IT(0), // 180

 IT(10), IT(15), IT(15), IT(15), IT(15), IT(15), IT(19), IT(19), IT(19), IT(19), IT(19), IT(19), IT(19), IT(19), IT(19),  IT(0), // 195
 IT(10), IT(15), IT(15), IT(15), IT(15), IT(15), IT(17), IT(17), IT(17), IT(17), IT(17), IT(17), IT(17), IT(17), IT(17),  IT(0), // 210
 IT(10), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15),  IT(0), // 225
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0), // 226
//  250     700    1000    1600    2200    2800    3400    4000    4600    5200    5800    6400    7000    7600    8000    8001  // Boost
//  Low RPM                                                                                                            High RPM




 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),

 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),

 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),

 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15),








 IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15),

 IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15),
 IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), /* 6 extras to allow different axis sizes. */
