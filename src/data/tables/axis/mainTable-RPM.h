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
 * @brief A default set of RPMs for a typical jap engine.
 *
 * This file only contains the data to be hash included into all mainTable RPM sections
 *
 * @author Fred Cooke
 */


/* 27 RPM values starting at 200 and ending at 9100, only the first 24 are used by default */
   0,	 400,	1400,	2100,
2800,	3500,	4200,	4900,
5600,	6300,	7000,	7700,
8400,	9100,	9800,  10500,
11200,  11900,  12600,  13300,
14000,  14700,  14400,  16100,
16800,  17500,  18200
