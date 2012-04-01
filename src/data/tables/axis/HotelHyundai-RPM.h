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
 * @brief A default set of RPMs for a typical sohc engine.
 *
 * This file only contains the data to be hash included into all mainTable RPM sections
 */


// 16 RPM values starting at 100 and ending at 6100, only the first 16 are used at the moment
 RPM(100),
 RPM(500),
 RPM(700),
RPM(1300),
RPM(1700),
RPM(2100),
RPM(2500),
RPM(2900),
RPM(3300),
RPM(3700),
RPM(4100),
RPM(4500),
RPM(4900),
RPM(5300),
RPM(5800),
RPM(6300),

// spare:
RPM(9000),
RPM(9001),
RPM(9002),
RPM(9003),
RPM(9004),
RPM(9005),
RPM(9006),
RPM(9007),
RPM(9008),
RPM(9009),
RPM(9010)
