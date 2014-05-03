/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2014 Fred Cooke
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
 * @brief The Mighty Hotel's Starion TBI manifold naturally aspirated 16x16 VE curve.
 */

//  Low RPM                                                                                                            High RPM
//  100     500     700    1300    1700    2100    2500    2900    3300    3700    4100    4500    4900    5300    5800    6300  // Vacuum
 VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), //  20
 VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), //  26
 VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), VE(19), //  32
 VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), VE(25), //  38

 VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), VE(30), //  44
 VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), VE(33), //  50
 VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), VE(36), //  56
 VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), VE(40), //  62

 VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), VE(45), //  68
 VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), VE(50), //  74
 VE(50), VE(50), VE(50), VE(55), VE(55), VE(55), VE(55), VE(55), VE(55), VE(55), VE(55), VE(55), VE(55), VE(55), VE(55), VE(55), //  80
 VE(50), VE(50), VE(50), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), VE(60), //  86

 VE(50), VE(50), VE(50), VE(70), VE(69), VE(63), VE(65), VE(68), VE(76), VE(74), VE(71), VE(66), VE(66), VE(66), VE(66), VE(66), //  92
 VE(55), VE(55), VE(55), VE(70), VE(69), VE(63), VE(65), VE(67), VE(75), VE(73), VE(70), VE(64), VE(64), VE(64), VE(64), VE(64), //  98
 VE(60), VE(60), VE(60), VE(70), VE(69), VE(63), VE(65), VE(66), VE(74), VE(72), VE(69), VE(63), VE(63), VE(63), VE(63), VE(63), // 104
 VE(60), VE(60), VE(60), VE(70), VE(69), VE(63), VE(65), VE(66), VE(74), VE(72), VE(69), VE(63), VE(63), VE(63), VE(63), VE(63)  // 110
//  100     500     700    1300    1700    2100    2500    2900    3300    3700    4100    4500    4900    5300    5800    6300  // WOT
//  Low RPM                                                                                                            High RPM
