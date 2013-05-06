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
 * @brief DeuceEFI's GM 2200 I4 standard naturally aspirated 13x10 ignition curve for DIS ignition systems. Updated 01/12/2013
 */

//Low RPM                                                                                                               High RPM
//   100,      500,      800,     1000,     1500,     2000,     2500,     3000,     3500,     4000,     4500,     5000,     5500  // Vaccum
 IT(0.0), IT(10.0), IT(12.0), IT(12.0), IT(17.0), IT(22.0), IT(27.0), IT(32.0), IT(37.0), IT(38.0), IT(38.0), IT(38.0), IT(38.0), //  15 kPa
 IT(0.0), IT(10.0), IT(12.0), IT(12.0), IT(17.0), IT(22.0), IT(27.0), IT(32.0), IT(37.0), IT(38.0), IT(38.0), IT(38.0), IT(38.0), //  25 kPa
 
 IT(0.0), IT(10.0), IT(12.0), IT(12.0), IT(17.0), IT(22.0), IT(27.0), IT(32.0), IT(37.0), IT(37.0), IT(37.0), IT(37.0), IT(37.0), //  35 kPa
 IT(0.0), IT(10.0), IT(12.0), IT(12.0), IT(17.0), IT(22.0), IT(27.0), IT(32.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), IT(36.0), //  45 kPa
 
 IT(0.0), IT(10.0), IT(11.0), IT(12.0), IT(17.0), IT(22.0), IT(27.0), IT(31.0), IT(35.0), IT(35.0), IT(35.0), IT(35.0), IT(35.0), //  55 kPa
 IT(0.0),  IT(9.0), IT(11.0), IT(12.0), IT(16.0), IT(21.0), IT(25.0), IT(29.0), IT(33.0), IT(33.0), IT(33.0), IT(33.0), IT(33.0), //  65 kPa
 
 IT(0.0),  IT(8.0), IT(11.0), IT(12.0), IT(15.0), IT(20.0), IT(24.0), IT(28.0), IT(32.0), IT(32.0), IT(32.0), IT(32.0), IT(32.0), //  75 kPa
 IT(0.0),  IT(6.0), IT(10.0), IT(11.0), IT(13.0), IT(16.0), IT(22.0), IT(26.0), IT(30.0), IT(30.0), IT(30.0), IT(30.0), IT(30.0), //  85 kPa

 IT(0.0),  IT(5.0), IT(10.0), IT(11.0), IT(12.0), IT(14.0), IT(21.0), IT(25.0), IT(29.0), IT(29.0), IT(29.0), IT(29.0), IT(29.0), //  95 kPa
 IT(0.0),  IT(4.0),  IT(9.0), IT(10.0), IT(11.0), IT(12.0), IT(18.0), IT(24.0), IT(28.0), IT(28.0), IT(28.0), IT(28.0), IT(28.0), // 105 kPa
//   100,      500,      800,     1000,     1500,     2000,     2500,     3000,     3500,     4000,     4500,     5000,     5500  // WOT
//Low RPM                                                                                                               High RPM
