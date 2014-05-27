/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2012 Fred Cooke
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
 * @brief A fairly standard naturally aspirated 16x16 ignition curve.
 */

//  Low RPM                                                                                                            High RPM
//  100     500     700    1300    1700    2100    2500    2900    3300    3700    4100    4500    4900    5300    5800    6300  // Vacuum
  IT(0), IT(10), IT(17), IT(17), IT(17), IT(27), IT(35), IT(40), IT(55), IT(55), IT(55), IT(55), IT(55), IT(55), IT(55), IT(55), //  14
  IT(0), IT(10), IT(17), IT(17), IT(17), IT(25), IT(30), IT(35), IT(50), IT(50), IT(50), IT(50), IT(50), IT(50), IT(50), IT(50), //  20
  IT(0), IT(10), IT(17), IT(12), IT(17), IT(22), IT(27), IT(32), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), //  26
  IT(0), IT(10), IT(17), IT(12), IT(17), IT(22), IT(27), IT(32), IT(40), IT(40), IT(40), IT(40), IT(40), IT(40), IT(40), IT(40), //  32

  IT(0), IT(10), IT(17), IT(12), IT(17), IT(22), IT(27), IT(32), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), //  38
  IT(0), IT(10), IT(17), IT(12), IT(17), IT(22), IT(27), IT(32), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), //  44
  IT(0), IT(10), IT(17), IT(12), IT(17), IT(22), IT(27), IT(32), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), //  50
  IT(0), IT(10), IT(11), IT(12), IT(17), IT(22), IT(27), IT(31), IT(35), IT(35), IT(35), IT(35), IT(35), IT(35), IT(35), IT(35), //  56

  IT(0), IT(10), IT(10), IT(12), IT(16), IT(21), IT(25), IT(29), IT(34), IT(34), IT(34), IT(34), IT(34), IT(34), IT(34), IT(34), //  62
  IT(0),  IT(9),  IT(9), IT(12), IT(16), IT(21), IT(25), IT(29), IT(33), IT(33), IT(33), IT(33), IT(33), IT(33), IT(33), IT(33), //  68
  IT(0),  IT(8),  IT(8), IT(12), IT(15), IT(20), IT(24), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), //  74
  IT(0),  IT(7),  IT(7), IT(11), IT(14), IT(18), IT(23), IT(27), IT(31), IT(31), IT(31), IT(31), IT(31), IT(31), IT(31), IT(31), //  80

  IT(0),  IT(6),  IT(6), IT(10), IT(13), IT(16), IT(22), IT(26), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), //  86
  IT(0),  IT(5),  IT(5),  IT(9), IT(12), IT(14), IT(21), IT(25), IT(29), IT(29), IT(29), IT(29), IT(29), IT(29), IT(29), IT(29), //  92
  IT(0),  IT(4),  IT(4),  IT(7), IT(10), IT(13), IT(19), IT(24), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), //  98
  IT(0),  IT(4),  IT(4),  IT(6),  IT(8), IT(12), IT(18), IT(24), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28)  // 104
//  100     500     700    1300    1700    2100    2500    2900    3300    3700    4100    4500    4900    5300    5800    6300  // WOT
//  Low RPM                                                                                                            High RPM
