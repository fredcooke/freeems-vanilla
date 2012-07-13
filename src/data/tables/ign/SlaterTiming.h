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
 * @brief The slater's rough tuned ignition timing table.
 */


//  Low RPM                                                                                                            High RPM
//  250     700    1200    1500    2000    2500    3000    3500    4000    4500    5000    5500    6000    6500    7000    7500  // Vacuum
  IT(0), IT(12), IT(12), IT(22), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), //  20kPa
  IT(0), IT(12), IT(12), IT(22), IT(30), IT(34), IT(40), IT(40), IT(40), IT(40), IT(40), IT(40), IT(40), IT(40), IT(40), IT(40), //  30kPa
  IT(0), IT(12), IT(12), IT(22), IT(30), IT(34), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), //  40kPa
  IT(0), IT(12), IT(12), IT(22), IT(30), IT(34), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), IT(45), //  50kPa
  IT(0), IT(12), IT(12), IT(22), IT(28), IT(32), IT(42), IT(42), IT(42), IT(42), IT(42), IT(42), IT(42), IT(42), IT(42), IT(42), //  60kPa
  IT(0), IT(12), IT(12), IT(21), IT(26), IT(30), IT(39), IT(39), IT(39), IT(39), IT(39), IT(39), IT(39), IT(39), IT(39), IT(39), //  70kPa
  IT(0), IT(10), IT(10), IT(20), IT(24), IT(28), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), //  80kPa
  IT(0), IT(10), IT(10), IT(20), IT(22), IT(26), IT(33), IT(33), IT(33), IT(33), IT(33), IT(33), IT(33), IT(32), IT(33), IT(33), //  90kPa
  IT(0), IT(10), IT(10), IT(18), IT(20), IT(24), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), IT(30), // 100kPa
  IT(0), IT(10), IT(10), IT(15), IT(18), IT(22), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), IT(28), // 110kpa
  IT(0), IT(10), IT(10), IT(12), IT(15), IT(20), IT(27), IT(27), IT(27), IT(27), IT(27), IT(27), IT(27), IT(27), IT(27), IT(27), // 120kpa
  IT(0), IT(10), IT(10), IT(10), IT(12), IT(15), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), IT(26), // 130kpa
  IT(0), IT(10), IT(10), IT(10), IT(10), IT(12), IT(25), IT(25), IT(25), IT(25), IT(25), IT(25), IT(25), IT(25), IT(25), IT(25), // 140kpa
  IT(0), IT(10), IT(10), IT(10), IT(10), IT(10), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), // 150kpa
  IT(0), IT(10), IT(10), IT(10), IT(10), IT(10), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), // 175kPa
  IT(0), IT(10), IT(10), IT(10), IT(10), IT(10), IT(16), IT(16), IT(16), IT(16), IT(16), IT(16), IT(16), IT(16), IT(16), IT(16)  // 200kPa
//  250     700    1200    1500    2000    2500    3000    3500    4000    4500    5000    5500    6000    6500    7000    7500  // Boost
//  Low RPM                                                                                                            High RPM
