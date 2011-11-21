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
 * @brief A default set of RPMs for a B21A engine.
 *
 * This file only contains the data to be hash included into all mainTable RPM sections
 *
 * @author Fred Cooke
 */


/* 27 RPM values starting at 200 and ending at 9100, only the first 24 are used by default */
  400,  1000,  2000,  3200,
 4400,  5600,  6800,  8000,
 9200, 10400, 11600, 13000,
13001, 15200, 16000,  16001,

// spare:
20000,  20001,  20002,  20003,
20004,  20005,  20006,  20007,
20008,  20009,  20010
