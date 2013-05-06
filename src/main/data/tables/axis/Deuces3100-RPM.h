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
 * @brief Default RPM values spaced at 400RPM after the cranking and idling rows.
 */


// 27 RPM values of which the first 13 are used by default
  RPM(100),
  RPM(500),
  RPM(800),
 RPM(1000),
 RPM(1500),
 RPM(2000),
 RPM(2500),
 RPM(3000),
 RPM(3500),
 RPM(4000),
 RPM(4500),
 RPM(5000),
 RPM(5500),
 RPM(5700), // First value not used by default
 RPM(5900),
 RPM(6300),
 RPM(6700),
 RPM(7100),
 RPM(7500),
 RPM(7900),
 RPM(8300),
 RPM(8700),
 RPM(9100),
 RPM(9500),
 RPM(9800),
RPM(10200),
RPM(10600)
