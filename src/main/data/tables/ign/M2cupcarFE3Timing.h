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
 * @M2cupcar ignition timing table based on prior tune
 */


//  Low RPM                                                                                                            High RPM
//  250     680    1160    1640    2120    2600    3080    3560    4040    4520    5000    5480    5960    6440    6920    7400  // Vacuum
 IT(10), IT(14), IT(15), IT(19), IT(23), IT(28), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), IT(32), //  15
 IT(10), IT(14), IT(15), IT(19), IT(23), IT(28), IT(32), IT(34), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), //  30
 IT(10), IT(14), IT(16), IT(19), IT(23), IT(28), IT(32), IT(34), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), //  45
 IT(10), IT(14), IT(18), IT(19), IT(25), IT(30), IT(32), IT(34), IT(30), IT(32), IT(34), IT(36), IT(38), IT(38), IT(38), IT(38), //  60

 IT(10), IT(12), IT(16), IT(19), IT(28), IT(32), IT(30), IT(28), IT(26), IT(28), IT(30), IT(32), IT(35), IT(38), IT(38), IT(38), //  75
 IT(11), IT(13), IT(17), IT(21), IT(30), IT(30), IT(28), IT(26), IT(23), IT(23), IT(25), IT(27), IT(30), IT(32), IT(34), IT(35), //  90
 IT(11), IT(14), IT(19), IT(23), IT(29), IT(29), IT(27), IT(24), IT(22), IT(22), IT(23), IT(26), IT(28), IT(30), IT(33), IT(34), // 105
 IT(11), IT(14), IT(19), IT(25), IT(27), IT(27), IT(24), IT(21), IT(19), IT(18), IT(19), IT(22), IT(25), IT(27), IT(29), IT(30), // 120

 IT(11), IT(14), IT(19), IT(24), IT(26), IT(26), IT(23), IT(20), IT(17), IT(16), IT(18), IT(20), IT(23), IT(25), IT(28), IT(29), // 135
 IT(11), IT(14), IT(19), IT(23), IT(25), IT(25), IT(22), IT(19), IT(15), IT(15), IT(16), IT(18), IT(21), IT(24), IT(26), IT(27), // 150
 IT(11), IT(14), IT(18), IT(22), IT(23), IT(22), IT(20), IT(17), IT(14), IT(14), IT(15), IT(17), IT(20), IT(22), IT(24), IT(25), // 165
 IT(11), IT(14), IT(17), IT(20), IT(21), IT(20), IT(17), IT(15), IT(13), IT(13), IT(14), IT(17), IT(19), IT(21), IT(23), IT(24), // 180

 IT(11), IT(13), IT(16), IT(19), IT(19), IT(17), IT(15), IT(13), IT(12), IT(12), IT(13), IT(16), IT(18), IT(20), IT(21), IT(22), // 195
 IT(11), IT(13), IT(16), IT(18), IT(18), IT(16), IT(14), IT(13), IT(11), IT(11), IT(12), IT(14), IT(17), IT(19), IT(21), IT(21), // 210
 IT(11), IT(12), IT(15), IT(17), IT(16), IT(15), IT(13), IT(12), IT(11), IT(10), IT(11), IT(13), IT(15), IT(18), IT(20), IT(21), // 225
 IT(11), IT(12), IT(14), IT(16), IT(15), IT(14), IT(13), IT(12), IT(10), IT(9), IT(10), IT(12), IT(14), IT(17), IT(19), IT(20)  // 240
//  250     680    1160    1640    2120    2600    3080    3560    4040    4520    5000    5480    5960    6440    6920    7400  // Boost
//  Low RPM                                                                                                            High RPM
