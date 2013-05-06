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
 * @warning MUST be used with 13x10 axis dimensions!!!
 * @brief Deuce's GM 2200 I4 engine. Updated 01/12/2013
 */

//Low RPM                                                                                                                           High RPM
//   100,       500,       800,      1000,      1500,      2000,      2500,      3000,      3500,      4000,      4500,      5000,      5500  // Vaccum
VE(46.0),  VE(46.0),  VE(48.0),  VE(48.0),  VE(50.0),  VE(52.0),  VE(54.0),  VE(56.0),  VE(58.0),  VE(60.0),  VE(62.0),  VE(64.0),  VE(66.0), //  15 kPa
VE(54.0),  VE(54.0),  VE(58.0),  VE(60.0),  VE(61.0),  VE(60.0),  VE(62.0),  VE(65.0),  VE(68.0),  VE(69.0),  VE(70.0),  VE(72.0),  VE(74.0), //  25 kPa

VE(56.0),  VE(56.0),  VE(60.0),  VE(62.0),  VE(63.0),  VE(63.0),  VE(64.0),  VE(65.0),  VE(65.0),  VE(72.0),  VE(74.0),  VE(76.0),  VE(78.0), //  35 kPa
VE(58.0),  VE(58.0),  VE(61.0),  VE(63.0),  VE(64.0),  VE(90.0),  VE(90.0), VE(100.0), VE(105.0), VE(105.0), VE(110.0), VE(115.0), VE(120.0), //  45 kPa

VE(60.0), VE(100.0), VE(100.0),  VE(64.0),  VE(66.0),  VE(95.0),  VE(95.0),  VE(95.0), VE(105.0), VE(110.0), VE(115.0), VE(120.0), VE(125.0), //  55 kPa
VE(60.0), VE(105.0), VE(105.0), VE(105.0),  VE(90.0),  VE(90.0),  VE(90.0),  VE(90.0), VE(105.0), VE(110.0), VE(115.0), VE(120.0), VE(125.0), //  65 kPa

VE(60.0), VE(100.0), VE(108.0), VE(108.0), VE(100.0), VE(100.0), VE(100.0), VE(100.0), VE(110.0), VE(115.0), VE(120.0), VE(125.0), VE(127.9), //  75 kPa
VE(60.0), VE(100.0), VE(115.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(110.0), VE(115.0), VE(120.0), VE(125.0), VE(127.9), //  85 kPa

VE(60.0),  VE(90.0), VE(115.0), VE(115.0), VE(115.0), VE(115.0), VE(115.0), VE(115.0), VE(115.0), VE(120.0), VE(123.0), VE(125.0), VE(127.9), //  95 kPa
VE(60.0),  VE(90.0), VE(115.0), VE(115.0), VE(115.0), VE(115.0), VE(115.0), VE(115.0), VE(115.0), VE(120.0), VE(123.0), VE(125.0), VE(127.9), // 105 kPa
//   100,       500,       800,      1000,      1500,      2000,      2500,      3000,      3500,      4000,      4500,      5000,      5500  // WOT
//Low RPM                                                                                                                           High RPM

