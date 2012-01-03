/* FreeEMS - the open source engine management system
 *
 * Copyright 2011 Fred Cooke
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
 * @brief A flat 0 degree timing table, ONLY for use with mechanical timing as
 * a basis for a trim table or for finding TDC while setting up an engine.
 *
 * @warning DO NOT RUN YOUR CAR ON THIS!
 *
 * This file only contains the data to be hash included into some timing tables
 *
 * @author Fred Cooke
 */


//  Low RPM                                                                                                            High RPM
//  100     500     900    1300    1800    2250    2700    3150    3600    4050    4500    4950    5400    5850    6300    6750  // Vacuum
  IT(0), IT(25), IT(25), IT(25), IT(25), IT(25), IT(29), IT(39), IT(39), IT(39), IT(39), IT(39), IT(39), IT(39), IT(39), IT(39), //  15
  IT(0), IT(25), IT(25), IT(25), IT(25), IT(25), IT(28), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), IT(38), //  30
  IT(0), IT(25), IT(25), IT(25), IT(25), IT(25), IT(28), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), //  45
  IT(0), IT(25), IT(25), IT(25), IT(25), IT(25), IT(27), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), IT(37), //  60

  IT(0), IT(25), IT(25), IT(25), IT(25), IT(25), IT(27), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), IT(36), //  75
  IT(0), IT(25), IT(25), IT(25), IT(25), IT(25), IT(26), IT(28), IT(35), IT(35), IT(35), IT(35), IT(35), IT(35), IT(35), IT(35), //  90
  IT(0), IT(12), IT(12), IT(15), IT(18), IT(20), IT(25), IT(30), IT(34), IT(34), IT(34), IT(34), IT(34), IT(34), IT(34), IT(34), // 105
  IT(0), IT(10), IT(10), IT(10), IT(13), IT(15), IT(20), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), IT(23), // 120

  IT(0), IT(10), IT(10), IT(10), IT(11), IT(12), IT(15), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), IT(18), // 135
  IT(0), IT(10), IT(10), IT(10), IT(10), IT(11), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), IT(15), // 150
  IT(0), IT(10), IT(10), IT(10), IT(10), IT(10), IT(14), IT(14), IT(14), IT(14), IT(14), IT(14), IT(14), IT(14), IT(14), IT(14), // 165
  IT(0),  IT(5), IT(10), IT(10), IT(10), IT(13), IT(13), IT(13), IT(13), IT(13), IT(13), IT(13), IT(13), IT(13), IT(13), IT(13), // 180

  IT(0),  IT(5),  IT(5), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(12), // 195
  IT(0),  IT(5),  IT(5),  IT(5), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), // 210
  IT(0),  IT(5),  IT(5),  IT(5),  IT(5), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), IT(10), // 225
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0), // 225.01
//  100     500     900    1300    1800    2250    2700    3150    3600    4050    4500    4950    5400    5850    6300    6750  //  WOT
//  Low RPM                                                                                                            High RPM


  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),

  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),

  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),

  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),








  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),

  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),
  IT(0),  IT(0),  IT(0),  IT(0),  IT(0),  IT(0)
