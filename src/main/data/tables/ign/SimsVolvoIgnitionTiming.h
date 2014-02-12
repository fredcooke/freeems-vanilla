/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2013 Fred Cooke
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
 * @brief A timing table for a Volvo B21A.
 *
 * Under development
 *
 * Based in part on Fred's truck table and Nick Sayler's research:
 * http://blog.nsfabrication.com/2010/03/10/taking-a-look-at-lh-22-ignition-curves/
 */


//  Low RPM                                                                            High RPM
//  200     500    1000    1600    2200    2800    3400    4000    4600    5200    5800    6400  // Vacuum
  IT(0), IT(10), IT(12), IT(18), IT(30), IT(37), IT(42), IT(43), IT(45), IT(46), IT(46), IT(46), //  15
  IT(0), IT(10), IT(15), IT(19), IT(30), IT(36), IT(40), IT(41), IT(43), IT(45), IT(45), IT(45), //  30
  IT(0), IT(10), IT(15), IT(19), IT(27), IT(33), IT(37), IT(38), IT(40), IT(42), IT(42), IT(42), //  45
  IT(0), IT(10), IT(15), IT(18), IT(25), IT(31), IT(35), IT(36), IT(38), IT(40), IT(40), IT(40), //  60

  IT(0), IT(10), IT(15), IT(18), IT(24), IT(28), IT(31), IT(32), IT(36), IT(37), IT(37), IT(37), //  75
  IT(0), IT(10), IT(15), IT(16), IT(20), IT(23), IT(27), IT(29), IT(33), IT(35), IT(35), IT(35), //  90
  IT(0), IT(10), IT(15), IT(16), IT(20), IT(21), IT(24), IT(27), IT(30), IT(32), IT(32), IT(32), // 105
  IT(0), IT(10), IT(15), IT(16), IT(20), IT(20), IT(22), IT(25), IT(28), IT(30), IT(32), IT(32)  // 120
