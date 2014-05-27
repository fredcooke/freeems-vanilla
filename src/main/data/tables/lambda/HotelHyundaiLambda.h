/* FreeEMS - the open source engine management system
 *
 * Copyright 2010-2014 Fred Cooke
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
 * @brief The Mighty Hotel's Starion TBI manifold naturally aspirated 16x16 lambda curve.
 */


// Low RPM                                                                                                                                            High RPM
//   100       500       700      1300      1700      2100      2500      2900      3300      3700      4100      4500      4900      5300      5800      6300  // Vacuum
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), //  14
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), //  20
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), //  26
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), LR(1.10), //  32

LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.05), LR(1.05), LR(1.05), LR(1.05), LR(1.05), LR(1.05), LR(1.05), LR(1.05), LR(1.05), LR(1.05), LR(1.05), //  38
LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), LR(1.00), //  44
LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), LR(0.99), //  50
LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), LR(0.98), //  56

LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), LR(0.96), //  62
LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), LR(0.94), //  68
LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), LR(0.92), //  74
LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), LR(0.90), //  80

LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), LR(0.88), //  86
LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), LR(0.86), //  92
LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), //  98
LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85), LR(0.85)  // 104
//   100       500       700      1300      1700      2100      2500      2900      3300      3700      4100      4500      4900      5300      5800      6300  // WOT
// Low RPM                                                                                                                                            High RPM
