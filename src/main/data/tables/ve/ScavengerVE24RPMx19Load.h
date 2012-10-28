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
 * @brief Hentai's SD VE, based off of Ben's default
 */


// Low RPM                                                                                                                                                                                                                             High RPM
//    200       700      1200      1500      1800      2100      2400      2700      3000      3300      3600      3900      4200      4500      4800      5100      5400      5700      6000      6300      6600      6900      7200      7500  // Vacuum
   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(43),   VE(44),   VE(45),   VE(47),   VE(49), VE(49.5),   VE(50),   VE(50), VE(49.5),   VE(49),   VE(48),   VE(47),   VE(45),   VE(42),   VE(39),   VE(36), //  20kPa
   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(48),   VE(49),   VE(50),   VE(52),   VE(54), VE(54.5),   VE(55),   VE(55), VE(54.5),   VE(54),   VE(53),   VE(52),   VE(50),   VE(47),   VE(44),   VE(41), //  30kPa
   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(53),   VE(55),   VE(56),   VE(58),   VE(60), VE(60.5),   VE(61),   VE(61), VE(60.5),   VE(60),   VE(58),   VE(57),   VE(55),   VE(52),   VE(49),   VE(46), //  40kPa
   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(59),   VE(61),   VE(63),   VE(65),   VE(67), VE(67.5),   VE(68),   VE(68), VE(67.5),   VE(67),   VE(65),   VE(63),   VE(61),   VE(58),   VE(55),   VE(52), //  50kPa
   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(64),   VE(66),   VE(69),   VE(71),   VE(73), VE(73.5),   VE(74),   VE(74), VE(73.5),   VE(73),   VE(71),   VE(68),   VE(64),   VE(61),   VE(58),   VE(55), //  60kPa

   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(68),   VE(71),   VE(73),   VE(75),   VE(77), VE(77.5),   VE(78),   VE(78), VE(77.5),   VE(77),   VE(74),   VE(71),   VE(67),   VE(64),   VE(61),   VE(58), //  70kPa
   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(72),   VE(74),   VE(76),   VE(78),   VE(80), VE(80.5),   VE(81),   VE(81), VE(80.5),   VE(80),   VE(77),   VE(74),   VE(70),   VE(67),   VE(63),   VE(60), //  80kPa
   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(75),   VE(77),   VE(79),   VE(81),   VE(83), VE(83.5),   VE(84),   VE(84), VE(83.5),   VE(83),   VE(80),   VE(77),   VE(73),   VE(70),   VE(66),   VE(63), //  90kPa
   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(80),   VE(82),   VE(84),   VE(86),   VE(88), VE(88.5),   VE(89),   VE(89), VE(88.5),   VE(88),   VE(84),   VE(81),   VE(77),   VE(74),   VE(70),   VE(67), // 100kPa
   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(70),   VE(84),   VE(86),   VE(88),   VE(90),   VE(92), VE(92.5),   VE(93),   VE(93), VE(92.5),   VE(92),   VE(88),   VE(85),   VE(81),   VE(78),   VE(74),   VE(71), // 115kPa

   VE(70),   VE(65),   VE(67),   VE(70),   VE(75),   VE(78),   VE(81),   VE(85),   VE(88),   VE(91),   VE(93),   VE(96),   VE(97), VE(97.5),   VE(98),   VE(98), VE(97.5),   VE(97),   VE(93),   VE(89),   VE(85),   VE(82),   VE(78),   VE(75), // 130kPa
   VE(70),   VE(68),   VE(70),   VE(74),   VE(79),   VE(82),   VE(85),   VE(89),   VE(93),   VE(97),   VE(99),  VE(101),  VE(102),VE(102.5),  VE(103),  VE(103),VE(102.5),  VE(102),   VE(99),   VE(94),   VE(89),   VE(86),   VE(82),   VE(79), // 145kPa
   VE(70),   VE(71),   VE(74),   VE(78),   VE(83),   VE(86),   VE(89),   VE(93),   VE(98),  VE(102),  VE(104),  VE(106),  VE(107),VE(107.5),  VE(108),  VE(108),VE(107.5),  VE(107),  VE(104),   VE(99),   VE(93),   VE(90),   VE(86),   VE(83), // 160kPa
   VE(71),   VE(74),   VE(77),   VE(81),   VE(86),   VE(89),   VE(93),   VE(97),  VE(102),  VE(106),  VE(108),  VE(110),  VE(111),VE(111.5),  VE(112),  VE(112),VE(111.5),  VE(111),  VE(108),  VE(103),   VE(97),   VE(94),   VE(89),   VE(86), // 175kPa
   VE(73),   VE(76),   VE(79),   VE(83),   VE(89),   VE(92),   VE(96),  VE(100),  VE(105),  VE(109),  VE(111),  VE(113),  VE(114),VE(114.5),  VE(115),  VE(115),VE(114.5),  VE(114),  VE(111),  VE(106),  VE(100),   VE(97),   VE(92),   VE(89), // 190kPa

   VE(74),   VE(78),   VE(81),   VE(85),   VE(91),   VE(94),   VE(98),  VE(102),  VE(107),  VE(111),  VE(113),  VE(115),  VE(116),VE(116.5),  VE(117),  VE(117),VE(116.5),  VE(116),  VE(113),  VE(108),  VE(102),   VE(99),   VE(94),   VE(91), // 205kPa
   VE(75),   VE(79),   VE(82),   VE(86),   VE(92),   VE(95),   VE(99),  VE(103),  VE(108),  VE(112),  VE(114),  VE(116),  VE(117),VE(117.5),  VE(118),  VE(118),VE(117.5),  VE(117),  VE(114),  VE(109),  VE(103),  VE(100),   VE(95),   VE(92), // 220kPa
   VE(76),   VE(80),   VE(83),   VE(87),   VE(93),   VE(96),  VE(100),  VE(104),  VE(109),  VE(113),  VE(115),  VE(117),  VE(118),VE(118.5),  VE(119),  VE(119),VE(118.5),  VE(118),  VE(115),  VE(110),  VE(104),  VE(101),   VE(96),   VE(93), // 235kPa
   VE(77),   VE(81),   VE(84),   VE(88),   VE(94),   VE(97),  VE(101),  VE(105),  VE(110),  VE(114),  VE(116),  VE(118),  VE(119),VE(119.5),  VE(120),  VE(120),VE(119.5),  VE(119),  VE(116),  VE(111),  VE(105),  VE(102),   VE(97),   VE(94)  // 250kPa
//    200       700      1200      1500      1800      2100      2400      2700      3000      3300      3600      3900      4200      4500      4800      5100      5400      5700      6000      6300      6600      6900      7200      7500  // Boost
// Low RPM                                                                                                                                                                                                                             High RPM
