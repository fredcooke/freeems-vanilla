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
 * @brief Default load values spaced at 10kPa from 15kPa to 105kPa and 20kPa from 140kPa up.
 */


// 21 load values of which the first 10 are used by default
 KPA(15),
 KPA(25),
 KPA(35),
 KPA(45),
 KPA(55),
 KPA(65),
 KPA(75),
 KPA(85),
 KPA(95),
KPA(105),
KPA(140), // First value not used by default
KPA(160),
KPA(180),
KPA(200),
KPA(220),
KPA(240),
KPA(260),
KPA(280),
KPA(300),
KPA(320),
KPA(340)
