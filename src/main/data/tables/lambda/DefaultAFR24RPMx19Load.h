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
 * @brief Default petrol AFR data for a mid-90s performance DOHC cylinder head design with square 500cc cylinders.
 *
 * - Chamber/head: DOHC pentroof 86x86mm (approximately 225 CFM)
 * - Compression: 9.0:1 static
 * - Fuel type: pump 98 RON / 93 AKI
 * - Torque peak: 6100 RPM centre with 1600 RPM wide plateau
 * - Redline: 7000 - 9500 RPM
 *
 * This data has lean idle and conservative lean cruise with 0.88 N/A WOT tapering to 0.82 at 1-bar of boost, richening further with more boost.
 *
 * Do NOT drive on this map as though it was tuned for your particular setup. Destruction is sure to occur. Use this ONLY to get started.
 *
 * @author Ben Fenner
 */


// Low RPM                                                                                                                                                                                                                             High RPM
//    200       700      1100      1500      1900      2300      2700      3100      3500      3900      4300      4700      5100      5500      5900      6300      6700      7100      7500      7900      8300      8700      9100      9500  // Vacuum
 AP(14.7), AP(14.9), AP(14.9), AP(15.0), AP(15.0), AP(15.0), AP(15.0), AP(15.0), AP(15.0), AP(15.0), AP(15.0), AP(15.0), AP(14.9), AP(14.8), AP(14.9), AP(15.0), AP(15.0), AP(14.9), AP(15.0), AP(15.0), AP(15.1), AP(15.1), AP(15.1), AP(15.1), //  20kPa
 AP(14.7), AP(14.9), AP(14.9), AP(15.0), AP(15.3), AP(15.3), AP(15.3), AP(15.3), AP(15.3), AP(15.3), AP(15.3), AP(15.3), AP(15.1), AP(14.8), AP(14.9), AP(15.0), AP(15.0), AP(14.9), AP(15.0), AP(15.0), AP(15.1), AP(15.1), AP(15.1), AP(15.1), //  30kPa
 AP(14.7), AP(14.9), AP(14.9), AP(15.0), AP(15.3), AP(15.6), AP(15.6), AP(15.6), AP(15.6), AP(15.5), AP(15.5), AP(15.4), AP(15.1), AP(14.8), AP(14.9), AP(15.0), AP(15.0), AP(14.9), AP(15.0), AP(15.0), AP(15.1), AP(15.1), AP(15.1), AP(15.1), //  40kPa
 AP(14.7), AP(14.9), AP(14.9), AP(15.0), AP(15.3), AP(15.3), AP(15.3), AP(15.3), AP(15.3), AP(15.3), AP(15.3), AP(15.3), AP(15.1), AP(14.8), AP(14.9), AP(15.0), AP(15.0), AP(14.9), AP(15.0), AP(15.0), AP(15.1), AP(15.1), AP(15.1), AP(15.1), //  50kPa
 AP(14.7), AP(14.7), AP(14.8), AP(14.8), AP(14.8), AP(14.8), AP(14.8), AP(14.8), AP(14.8), AP(14.8), AP(14.8), AP(14.8), AP(14.6), AP(14.5), AP(14.6), AP(14.8), AP(14.8), AP(14.8), AP(14.8), AP(14.9), AP(14.9), AP(14.9), AP(14.9), AP(14.9), //  60kPa

 AP(14.2), AP(14.2), AP(14.2), AP(14.2), AP(14.2), AP(14.2), AP(14.2), AP(14.2), AP(14.2), AP(14.2), AP(14.2), AP(14.2), AP(14.1), AP(14.0), AP(14.1), AP(14.2), AP(14.2), AP(14.3), AP(14.4), AP(14.4), AP(14.5), AP(14.5), AP(14.5), AP(14.6), //  70kPa
 AP(13.7), AP(13.7), AP(13.7), AP(13.7), AP(13.7), AP(13.7), AP(13.7), AP(13.7), AP(13.7), AP(13.7), AP(13.7), AP(13.7), AP(13.6), AP(13.5), AP(13.6), AP(13.7), AP(13.7), AP(13.8), AP(13.8), AP(13.9), AP(14.0), AP(14.0), AP(14.1), AP(14.1), //  80kPa
 AP(13.3), AP(13.3), AP(13.3), AP(13.3), AP(13.3), AP(13.3), AP(13.3), AP(13.3), AP(13.3), AP(13.3), AP(13.3), AP(13.3), AP(13.2), AP(13.2), AP(13.2), AP(13.3), AP(13.3), AP(13.3), AP(13.4), AP(13.4), AP(13.5), AP(13.5), AP(13.7), AP(13.8), //  90kPa
 AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.8), AP(12.9), AP(12.9), AP(13.0), AP(13.0), AP(13.0), AP(13.2), AP(13.4), // 100kPa
 AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.6), AP(12.7), AP(12.8), AP(12.8), AP(12.9), AP(12.9), AP(13.0), AP(13.2), // 120kPa

 AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.5), AP(12.6), AP(12.6), AP(12.7), AP(12.7), AP(12.9), AP(13.1), // 140kPa
 AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.4), AP(12.5), AP(12.5), AP(12.6), AP(12.6), AP(12.7), AP(12.9), // 160kPa
 AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.2), AP(12.3), AP(12.4), AP(12.4), AP(12.4), AP(12.6), AP(12.8), // 180kPa
 AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.0), AP(12.1), AP(12.1), AP(12.2), AP(12.2), AP(12.2), AP(12.4), AP(12.6), // 200kPa
 AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.8), AP(11.9), AP(12.0), AP(12.0), AP(12.1), AP(12.1), AP(12.2), AP(12.3), // 220kPa

 AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.6), AP(11.7), AP(11.7), AP(11.8), AP(11.8), AP(11.8), AP(12.0), AP(12.2), // 240kPa
 AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.4), AP(11.5), AP(11.6), AP(11.6), AP(11.7), AP(11.7), AP(11.8), AP(12.1), // 260kPa
 AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.3), AP(11.5), AP(11.5), AP(11.5), AP(11.6), AP(11.6), AP(11.8), AP(11.9), // 280kPa
 AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.2), AP(11.3), AP(11.3), AP(11.3), AP(11.5), AP(11.5), AP(11.6), AP(11.8), // 300kPa
//    200       700      1100      1500      1900      2300      2700      3100      3500      3900      4300      4700      5100      5500      5900      6300      6700      7100      7500      7900      8300      8700      9100      9500  // Vacuum
// Low RPM                                                                                                                                                                                                                             High RPM
