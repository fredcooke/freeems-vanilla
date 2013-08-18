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
 * @brief A lambda table for a Volvo B21A.
 *
 * Under development
 */

// Approximate AFR to lambda conversion for petrol:
// 16.00, 15.50, 15.00, 14.70, 14.00, 13.50, 13.00, 12.50, 12.25, 12.00, 11.75, 11.50, 11.25, 11.00
//  1.08,  1.05,  1.02,  1.00,  0.96,  0.92,  0.89,  0.86,  0.84,  0.82,  0.80,  0.78,  0.76,  0.74

//  Low RPM                                                                                                     High RPM
//     200       500      1000      1600      2200      2800      3400      4000      4600      5200      5800      6400  // Vacuum
  LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //    15
  LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.01), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //    30
  LR(1.00), LR(0.98), LR(0.97), LR(1.01), LR(1.03), LR(1.03), LR(1.01), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //    45
  LR(0.96), LR(0.96), LR(0.94), LR(0.96), LR(0.97), LR(0.98), LR(0.97), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), //    60

  LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), //    75
  LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), LR(0.89), //    90
  LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), //   105
  LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83)  //   120
//     200       500      1000      1600      2200      2800      3400      4000      4600      5200      5800      6400  // "Boost"
//  Low RPM                                                                                                     High RPM

