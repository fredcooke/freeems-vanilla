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
 * @brief A reasonable default full-range lambda table that suits any engine well enough.
 *
 * @warning MUST be used with 13x10 axis dimensions!!!
 */


// Laid out to make sense for 13 RPM and 10 Load bins, many extras on end to make up size.
// Approximate AFR to lambda conversion for petrol:
// 14.70, 14.00, 13.50, 13.00, 12.50, 12.25, 12.00, 11.75, 11.50, 11.25, 11.00
//  1.00,  0.96,  0.92,  0.89,  0.86,  0.84,  0.82,  0.80,  0.78,  0.76,  0.74


// Table is flat in the RPM axis, these are DeuceEFI's GM 3100 RPMs, just for example
// Low RPM                                                                                                              High RPM
//   100       500       800      1000      1500      2000      2500      3000      3500      4000      4500      5000      5500  // Vacuum
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  15
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  25

LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  35
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  45

LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), //  55
LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), //  65

LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), //  75
LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), //  85

LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), //  95
LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), // 105
//   100       500       800      1000      1500      2000      2500      3000      3500      4000      4500      5000      5500  // WOT
// Low RPM                                                                                                              High RPM
