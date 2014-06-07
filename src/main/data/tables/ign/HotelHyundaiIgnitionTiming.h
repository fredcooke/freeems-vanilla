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
//  100,    500,    700,   1300,   1700,   2100,   2500,   2900,   3300,   3700,   4100,   4500,   4900,   5300,   5800,   6300  // Vacuum
  IT(0), IT(10), IT(17), IT(17), IT(38), IT(44), IT(55), IT(58), IT(63), IT(63), IT(63), IT(63), IT(63), IT(63), IT(63), IT(63), //  14kPa
  IT(0), IT(10), IT(17), IT(17), IT(38), IT(44), IT(55), IT(58), IT(63), IT(63), IT(63), IT(63), IT(63), IT(63), IT(63), IT(63), //  20kPa
  IT(0), IT(10), IT(17), IT(12), IT(36), IT(42), IT(50), IT(55), IT(59), IT(59), IT(59), IT(59), IT(59), IT(59), IT(59), IT(59), //  26kPa
  IT(0), IT(10), IT(17), IT(12), IT(34), IT(40), IT(47), IT(52), IT(54), IT(54), IT(54), IT(54), IT(54), IT(54), IT(54), IT(54), //  32kPa

  IT(0), IT(10), IT(17), IT(12), IT(32), IT(38), IT(45), IT(48), IT(50), IT(50), IT(50), IT(50), IT(50), IT(50), IT(50), IT(50), //  38kPa
  IT(0), IT(10), IT(17), IT(12), IT(30), IT(36), IT(38), IT(42), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), //  44kPa
  IT(0), IT(10), IT(17), IT(12), IT(28), IT(33), IT(36), IT(38), IT(41), IT(41), IT(41), IT(41), IT(41), IT(41), IT(41), IT(41), //  50kPa
  IT(0), IT(10), IT(11), IT(12), IT(26), IT(30), IT(33), IT(34), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), //  56kPa

  IT(0), IT(10), IT(10), IT(12), IT(24), IT(28), IT(31), IT(32), IT(35), IT(35), IT(35), IT(35), IT(35), IT(35), IT(35), IT(35), //  62kPa
  IT(0),  IT(9),  IT(9), IT(12), IT(22), IT(26), IT(29), IT(31), IT(33), IT(33), IT(33), IT(33), IT(33), IT(33), IT(33), IT(33), //  68kPa
  IT(0),  IT(8),  IT(8), IT(12), IT(20), IT(24), IT(26), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), //  74kPa
  IT(0),  IT(7),  IT(7), IT(11), IT(17), IT(20), IT(23), IT(27), IT(31), IT(31), IT(31), IT(31), IT(31), IT(31), IT(31), IT(31), //  80kPa

  IT(0),  IT(6),  IT(6), IT(10), IT(13), IT(16), IT(22), IT(26), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), //  86kPa
  IT(0),  IT(5),  IT(5),  IT(9), IT(12), IT(14), IT(21), IT(25), IT(28), IT(29), IT(29), IT(29), IT(29), IT(29), IT(29), IT(29), //  92kPa
  IT(0),  IT(4),  IT(4),  IT(7), IT(10), IT(13), IT(19), IT(24), IT(27), IT(27), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), //  98kPa
  IT(0),  IT(4),  IT(4),  IT(6),  IT(8), IT(12), IT(18), IT(24), IT(27), IT(27), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28)  // 104kPa
//  100,    500,    700,   1300,   1700,   2100,   2500,   2900,   3300,   3700,   4100,   4500,   4900,   5300,   5800,   6300  // WOT
//  Low RPM                                                                                                            High RPM
