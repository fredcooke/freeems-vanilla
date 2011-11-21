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
 * @brief A default set of RPMs for a typical sohc engine.
 *
 * This file only contains the data to be hash included into all mainTable RPM sections
 *
 * @author Fred Cooke
 */


// 16 RPM values starting at 100 and ending at 6100, only the first 16 are used at the moment
  200,  1000,  1400,  2600,
 3400,  4200,  5000,  5800,
 6600,  7400,  8200,  9000,
 9800, 10600, 11600, 11601,

// spare:
20000,  20001,  20002,  20003,
20004,  20005,  20006,  20007,
20008,  20009,  20010
