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
 * @brief Hentai's SD lambda, based off of Ben's default
 */


// Low RPM                                                                                                                                                                                                                             High RPM
//    200       700      1200      1500      1800      2100      2400      2700      3000      3300      3600      3900      4200      4500      4800      5100      5400      5700      6000      6300      6600      6900      7200      7500  // Vacuum
 LR(1.00), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.01), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.03), LR(1.03), LR(1.03), LR(1.03), LR(1.03), //  20kPa
 LR(1.00), LR(1.02), LR(1.02), LR(1.03), LR(1.04), LR(1.04), LR(1.04), LR(1.04), LR(1.04), LR(1.04), LR(1.04), LR(1.04), LR(1.03), LR(1.01), LR(1.02), LR(1.03), LR(1.02), LR(1.02), LR(1.02), LR(1.03), LR(1.03), LR(1.03), LR(1.03), LR(1.03), //  30kPa
 LR(1.00), LR(1.02), LR(1.02), LR(1.03), LR(1.05), LR(1.06), LR(1.06), LR(1.06), LR(1.06), LR(1.06), LR(1.06), LR(1.05), LR(1.03), LR(1.01), LR(1.02), LR(1.03), LR(1.02), LR(1.02), LR(1.02), LR(1.03), LR(1.03), LR(1.03), LR(1.03), LR(1.03), //  40kPa
 LR(1.00), LR(1.02), LR(1.02), LR(1.03), LR(1.04), LR(1.04), LR(1.04), LR(1.04), LR(1.04), LR(1.04), LR(1.04), LR(1.04), LR(1.03), LR(1.01), LR(1.02), LR(1.03), LR(1.02), LR(1.02), LR(1.02), LR(1.03), LR(1.03), LR(1.03), LR(1.03), LR(1.03), //  50kPa
 LR(1.00), LR(1.00), LR(1.01), LR(1.01), LR(1.01), LR(1.01), LR(1.01), LR(1.01), LR(1.01), LR(1.01), LR(1.01), LR(1.01), LR(1.00), LR(0.99), LR(1.00), LR(1.01), LR(1.01), LR(1.01), LR(1.01), LR(1.02), LR(1.02), LR(1.02), LR(1.02), LR(1.02), //  60kPa

 LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.97), LR(0.96), LR(0.96), LR(0.96), LR(0.97), LR(0.97), LR(0.98), LR(0.98), LR(0.98), LR(0.99), LR(0.99), LR(0.99), LR(0.99), //  70kPa
 LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.93), LR(0.92), LR(0.93), LR(0.94), LR(0.94), LR(0.94), LR(0.95), LR(0.95), LR(0.95), LR(0.95), LR(0.96), LR(0.96), //  80kPa
 LR(0.91), LR(0.91), LR(0.91), LR(0.91), LR(0.91), LR(0.91), LR(0.91), LR(0.91), LR(0.91), LR(0.91), LR(0.91), LR(0.91), LR(0.90), LR(0.90), LR(0.90), LR(0.91), LR(0.91), LR(0.91), LR(0.91), LR(0.92), LR(0.92), LR(0.92), LR(0.93), LR(0.94), //  90kPa
 LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.89), LR(0.89), LR(0.89), LR(0.90), LR(0.91), // 100kPa
 LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.87), LR(0.87), LR(0.88), LR(0.88), LR(0.88), LR(0.89), LR(0.90), // 115kPa

 LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.86), LR(0.86), LR(0.86), LR(0.87), LR(0.87), LR(0.88), LR(0.89), // 130kPa
 LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.84), LR(0.85), LR(0.85), LR(0.86), LR(0.86), LR(0.86), LR(0.87), LR(0.88), // 145kPa
 LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.83), LR(0.84), LR(0.84), LR(0.84), LR(0.85), LR(0.85), LR(0.86), LR(0.87), // 160kPa
 LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.83), LR(0.83), LR(0.84), LR(0.84), LR(0.85), LR(0.86), // 175kPa
 LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.81), LR(0.82), LR(0.82), LR(0.82), LR(0.82), LR(0.83), LR(0.84), // 190kPa

 LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.79), LR(0.80), LR(0.80), LR(0.80), LR(0.81), LR(0.81), LR(0.82), LR(0.83), // 205kPa
 LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.78), LR(0.79), LR(0.79), LR(0.79), LR(0.80), LR(0.80), LR(0.81), LR(0.82), // 220kPa
 LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.77), LR(0.78), LR(0.78), LR(0.78), LR(0.79), LR(0.79), LR(0.80), LR(0.81), // 235kPa
 LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.76), LR(0.77), LR(0.77), LR(0.77), LR(0.78), LR(0.78), LR(0.79), LR(0.80)  // 250kPa
//    200       700      1200      1500      1800      2100      2400      2700      3000      3300      3600      3900      4200      4500      4800      5100      5400      5700      6000      6300      6600      6900      7200      7500  // Vacuum
// Low RPM                                                                                                                                                                                                                             High RPM
