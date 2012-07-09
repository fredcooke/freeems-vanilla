/* FreeEMS - the open source engine management system
 *
 * Copyright 2012 Fred Cooke
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
 * @brief Peter's rough tune on his Honda J Series V6
 */


//    Low RPM                                                                                                                                                         High RPM
//    200        800       1200       1600       2000       2400       2800       3200       3600       4000       4400       4800       5200       5600       6000       6400  // Vacuum
 VE(60.0),  VE(60.0),  VE(40.0),  VE(42.5),  VE(45.0),  VE(47.5),  VE(50.0),  VE(52.5),  VE(55.0),  VE(57.5),  VE(60.0),  VE(60.0),  VE(60.0),  VE(60.0), VE(127.9), VE(127.9), //  15kPa
 VE(60.0),  VE(60.0),  VE(60.0),  VE(60.0),  VE(60.0),  VE(55.0),  VE(57.5),  VE(60.0),  VE(60.0),  VE(60.0),  VE(60.0),  VE(60.0),  VE(60.0),  VE(60.0), VE(127.9), VE(127.9), //  30kPa
 VE(60.0),  VE(60.0),  VE(57.5),  VE(60.0),  VE(62.5),  VE(67.5),  VE(70.0),  VE(72.5),  VE(72.5),  VE(72.5),  VE(72.5),  VE(72.5),  VE(72.5),  VE(72.5), VE(127.9), VE(127.9), //  45kPa
 VE(60.0),  VE(60.0),  VE(60.0),  VE(62.5),  VE(70.0),  VE(75.0),  VE(77.5),  VE(80.0),  VE(80.0),  VE(80.0),  VE(80.0),  VE(80.0),  VE(80.0),  VE(80.0), VE(127.9), VE(127.9), //  60kPa
 VE(60.0),  VE(60.0),  VE(62.5),  VE(67.5),  VE(72.5),  VE(70.0),  VE(85.0),  VE(90.0),  VE(90.0),  VE(90.0),  VE(90.0),  VE(90.0),  VE(90.0),  VE(90.0), VE(127.9), VE(127.9), //  75kPa
 VE(60.0),  VE(60.0),  VE(65.0),  VE(70.0),  VE(75.0),  VE(85.0),  VE(90.0),  VE(95.0),  VE(95.0),  VE(95.0),  VE(95.0),  VE(95.0),  VE(95.0),  VE(95.0), VE(127.9), VE(127.9), //  90kPa
 VE(60.0),  VE(62.5),  VE(67.5),  VE(72.5),  VE(77.5),  VE(77.5),  VE(95.0), VE(100.0), VE(100.0), VE(100.0), VE(100.0), VE(100.0), VE(100.0), VE(100.0), VE(127.9), VE(127.9), // 105kPa
 VE(57.5),  VE(70.0),  VE(72.5),  VE(75.0),  VE(80.0),  VE(95.0), VE(100.0), VE(105.0), VE(105.0), VE(105.0), VE(105.0), VE(105.0), VE(105.0), VE(105.0), VE(127.9), VE(127.9), // 120kPa
 VE(57.5),  VE(70.0),  VE(72.5),  VE(75.0),  VE(85.0), VE(100.0), VE(105.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(127.9), VE(127.9), // 135kPa
 VE(57.5),  VE(70.0),  VE(72.5),  VE(75.0),  VE(85.0), VE(100.0), VE(105.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(127.9), VE(127.9), // 150kPa
 VE(57.5),  VE(70.0),  VE(72.5),  VE(75.0),  VE(85.0), VE(100.0), VE(105.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(127.9), VE(127.9), // 165kPa
 VE(57.5),  VE(70.0),  VE(72.5),  VE(75.0),  VE(85.0), VE(100.0), VE(105.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(127.9), VE(127.9), // 180kPa
 VE(57.5),  VE(70.0),  VE(72.5),  VE(75.0),  VE(85.0), VE(100.0), VE(105.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(127.9), VE(127.9), // 195kPa
 VE(57.5),  VE(70.0),  VE(72.5),  VE(75.0),  VE(85.0), VE(100.0), VE(105.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(127.9), VE(127.9), // 210kPa
VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), // 225kPa
VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), VE(127.9), // 240kPa
//    200        800       1200       1600       2000       2400       2800       3200       3600       4000       4400       4800       5200       5600       6000       6400  // Boost
//    Low RPM                                                                                                                                                         High RPM
