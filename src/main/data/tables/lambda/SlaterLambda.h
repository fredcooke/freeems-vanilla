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
 * @brief The slater's rough tuned lambda table.
 */


//   Low RPM                                                                                                                                          High RPM
//   250       700      1200      1500      2000      2500      3000      3500      4000      4500      5000      5500      6000      6500      7000      7500  // Vacuum
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  20kPa
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  30kPa
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  40kPa
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  50kPa
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  60kPa
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  70kPa
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  80kPa
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  90kPa
LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), // 100kPa
LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.95), // 110kPa
LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), // 120kPa
LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), // 130kPa
LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), // 140kPa
LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), // 150kPa
LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), // 175kPa
LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85)  // 200kPa
//   250       700      1200      1500      2000      2500      3000      3500      4000      4500      5000      5500      6000      6500      7000      7500  // Boost
//   Low RPM                                                                                                                                          High RPM
