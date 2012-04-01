/* FreeEMS - the open source engine management system
 *
 * Copyright 2010-2012 Fred Cooke
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
 * @brief The lambda table as used on Sean's turbo LT1 Camaro
 *
 * This file only contains the data to be hash included into the lambda tables
 * in the fuel table files for car specific builds.
 */


// Laid out to make sense for 16 RPM and 16 Load bins, many extras on end to make up size.
// Approximate AFR to lambda conversion for petrol:
// 14.70, 14.00, 13.50, 13.00, 12.50, 12.25, 12.00, 11.75, 11.50, 11.25, 11.00
//  1.00,  0.96,  0.92,  0.89,  0.86,  0.84,  0.82,  0.80,  0.78,  0.76,  0.74

// Table is flat in the RPM axis, these are Sean's LT1 RPMs, just for example
// Low RPM                                                                                                                                            High RPM
//   100       500       900      1300      1800      2250      2700      3150      3600      4050      4500      4950      5400      5850      6300      6750  // Vacuum
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  15
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  30
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  45
LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), //  60

LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), //  75
LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), //  90
LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), // 105
LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), // 120

LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), // 135
LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), LR(0.80), // 150
LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), // 165
LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), // 180

LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), // 195
LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), // 210
LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), // 225
LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), LR(0.74), // 240
//   100       500       900      1300      1800      2250      2700      3150      3600      4050      4500      4950      5400      5850      6300      6750  // Boost
// Low RPM                                                                                                                                            High RPM


LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),

LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),

LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),

LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.0),



LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.0),
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00)

