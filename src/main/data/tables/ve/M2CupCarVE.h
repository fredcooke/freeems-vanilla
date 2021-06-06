/* FreeEMS - the open source engine management system
 *
 * Copyright 2010-2012 Fred Cooke
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
 * @warning MUST be used with 16x16 axis dimensions!!!
 */


// Low RPM                                                                                                           High RPM
//  250     680    1160    1640    2120    2600    3080    3560    4040    4520    5000    5480    5960    6440    6920    7400  // Vacuum
 VE(50), VE(40), VE(30), VE(30), VE(30), VE(30), VE(38), VE(59), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  15
 VE(44), VE(34), VE(31), VE(32), VE(34), VE(36), VE(39), VE(67), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  30
 VE(41), VE(31), VE(30), VE(32), VE(36), VE(37), VE(43), VE(70), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  45
 VE(40), VE(31), VE(31), VE(36), VE(39), VE(42), VE(49), VE(72), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  60

 VE(49), VE(43), VE(41), VE(43), VE(45), VE(47), VE(56), VE(73), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  75
 VE(58), VE(53), VE(51), VE(51), VE(52), VE(55), VE(65), VE(76), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  90
 VE(64), VE(64), VE(64), VE(65), VE(65), VE(65), VE(70), VE(78), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 105
 VE(80), VE(72), VE(72), VE(71), VE(72), VE(73), VE(75), VE(79), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 120

 VE(80), VE(79), VE(78), VE(76), VE(77), VE(77), VE(77), VE(79), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 135
 VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 150
 VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 165
 VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 180

 VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 195
 VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 210
 VE(89), VE(89), VE(89), VE(89), VE(89), VE(89), VE(89), VE(89), VE(89), VE(89), VE(89), VE(89), VE(89), VE(89), VE(90), VE(100), // 225
 VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(100)  // 240
//  250     680    1160    1640    2120    2600    3080    3560    4040    4520    5000    5480    5960    6440    6920    7400  // Boost
// Low RPM                                                                                                             High RPM
