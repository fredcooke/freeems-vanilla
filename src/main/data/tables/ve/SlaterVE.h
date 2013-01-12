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
 * @brief The slater's rough/rich tuned VE table.
 */


//   Low RPM                                                                                                                                          High RPM
//   250       700      1200      1500      2000      2500      3000      3500      4000      4500      5000      5500      6000      6500      7000      7500  // Vacuum
  VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15),   VE(15), //  20kPa
  VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25),   VE(25), //  30kPa
  VE(30),   VE(30),   VE(30), VE(35.5), VE(35.6), VE(35.4), VE(36.5),   VE(35),   VE(35),   VE(37),   VE(39),   VE(35),   VE(30),   VE(30),   VE(30),   VE(30), //  40kPa
  VE(30),   VE(30),   VE(30),   VE(35),   VE(36),   VE(40),   VE(36),   VE(36),   VE(36),   VE(40),   VE(43),   VE(43),   VE(43),   VE(36),   VE(36),   VE(36), //  50kPa
  VE(30),   VE(30),   VE(30),   VE(35),   VE(37),   VE(45),   VE(45),   VE(45),   VE(45),   VE(45),   VE(45),   VE(45),   VE(45),   VE(40),   VE(40),   VE(40), //  60kPa
  VE(33),   VE(31),   VE(40),   VE(40),   VE(40),   VE(50),   VE(50),   VE(50),   VE(50),   VE(50),   VE(50),   VE(50),   VE(50),   VE(50),   VE(50),   VE(50), //  70kPa
  VE(40),   VE(40),   VE(55),   VE(55),   VE(55),   VE(55),   VE(55),   VE(55),   VE(55),   VE(55),   VE(55),   VE(55),   VE(55),   VE(55),   VE(55),   VE(55), //  80kPa
  VE(50),   VE(50),   VE(60),   VE(60),   VE(60),   VE(60),   VE(60),   VE(60),   VE(60),   VE(60),   VE(60),   VE(60),   VE(60),   VE(60),   VE(60),   VE(60), //  90kPa
  VE(60),   VE(60),   VE(60),   VE(65),   VE(65),   VE(65),   VE(65),   VE(65),   VE(65),   VE(65),   VE(65),   VE(65),   VE(65),   VE(65),   VE(65),   VE(65), // 100kPa
  VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70), // 110kPa
  VE(83),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73),   VE(73), // 120kPa
  VE(80),   VE(75),   VE(75),   VE(74),   VE(74),   VE(74),   VE(74),   VE(74),   VE(74),   VE(74),   VE(74),   VE(74),   VE(74),   VE(74),   VE(74),   VE(74), // 130kPa
  VE(80),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78),   VE(78), // 140kPa
  VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80),   VE(80), // 150kPa
  VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90),   VE(90), // 175kPa
 VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105),  VE(105)  // 200kPa
//   250       700      1200      1500      2000      2500      3000      3500      4000      4500      5000      5500      6000      6500      7000      7500  // Boost
//   Low RPM                                                                                                                                          High RPM
