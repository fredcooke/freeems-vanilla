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
 * @brief Will eventually contain Sean's pre-canned tune
 *
 * For now this will be used to ID that tables are being parsed and rendered
 * correctly in mtx 16 by 16
 *
 * This file only contains the data to be hash included into the VE tables
 * in the fuel table files for car specific builds.
 */


// Low RPM                                                                                                             High RPM
// 100     500     900    1300    1800    2250    2700    3150    3600    4050    4500    4950    5400    5850    6300     6750  // Vacuum
VE(50), VE(50), VE(50), VE(50), VE(59), VE(65), VE(71), VE(68), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  15
VE(50), VE(50), VE(50), VE(50), VE(59), VE(65), VE(71), VE(73), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  30
VE(51), VE(51), VE(50), VE(50), VE(59), VE(66), VE(71), VE(76), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  45
VE(50), VE(51), VE(51), VE(50), VE(59), VE(65), VE(71), VE(78), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  60

VE(49), VE(49), VE(51), VE(59), VE(63), VE(65), VE(72), VE(77), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  75
VE(58), VE(53), VE(51), VE(59), VE(64), VE(65), VE(72), VE(78), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), //  90
VE(64), VE(64), VE(64), VE(65), VE(67), VE(65), VE(72), VE(78), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 105
VE(80), VE(72), VE(72), VE(72), VE(72), VE(73), VE(75), VE(79), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 120

VE(80), VE(79), VE(78), VE(76), VE(77), VE(77), VE(77), VE(79), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 135
VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 150
VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 165
VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 180

VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 195
VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(80), VE(90), VE(100), // 210
VE(90), VE(90), VE(90), VE(90), VE(90), VE(90), VE(90), VE(90), VE(90), VE(90), VE(90), VE(90), VE(90), VE(90), VE(90), VE(100), // 225
VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(99), VE(90), VE(100), // 240
// 100     500     900    1300    1800    2250    2700    3150    3600    4050    4500    4950    5400    5850    6300     6750  // Boost
// Low RPM                                                                                                             High RPM


// The rest are UNUSED until we get full variable size table tuning, firmware can handle it, tuning currently can't :
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0),


VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0), VE(0),
VE(0), VE(0), VE(0), VE(0), VE(0), VE(0)
