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
 * @brief Default ignition timing data for a mid-90s performance DOHC cylinder head design with square 500cc cylinders.
 *
 * - Chamber/head: DOHC pentroof 86x86mm (approximately 225 CFM)
 * - Compression: 9.0:1 static
 * - Fuel type: pump 98 RON / 93 AKI
 * - Torque peak: 6100 RPM centre with 1600 RPM wide plateau
 * - Redline: 7000 - 9500 RPM
 *
 * This data is (supposed to be) conservative for the setup setup described, but is untested. Change according to the usual rules of operating.
 *
 * Do NOT drive on this map as though it was tuned for your particular setup. Destruction is sure to occur. Use this ONLY to get started.
 *
 * @author Ben Fenner
 */


// Low RPM                                                                                                                                                                                                                             High RPM
//    200       700      1100      1500      1900      2300      2700      3100      3500      3900      4300      4700      5100      5500      5900      6300      6700      7100      7500      7900      8300      8700      9100      9500  // Vacuum
  IT(0.0), IT(16.0), IT(16.0), IT(25.5), IT(31.5), IT(37.1), IT(40.7), IT(43.5), IT(44.5), IT(44.5), IT(44.5), IT(44.5), IT(43.8), IT(43.3), IT(42.8), IT(42.8), IT(43.3), IT(43.8), IT(44.5), IT(44.9), IT(45.9), IT(47.0), IT(48.7), IT(50.5), //  20kPa
  IT(0.0), IT(16.0), IT(16.0), IT(25.5), IT(31.5), IT(37.1), IT(40.7), IT(43.5), IT(44.5), IT(44.5), IT(44.5), IT(44.5), IT(43.8), IT(43.3), IT(42.8), IT(42.8), IT(43.3), IT(43.8), IT(44.5), IT(44.9), IT(45.9), IT(47.0), IT(48.7), IT(50.5), //  30kPa
  IT(0.0), IT(16.0), IT(16.0), IT(25.5), IT(31.5), IT(37.1), IT(40.7), IT(43.5), IT(44.5), IT(44.5), IT(44.5), IT(44.5), IT(43.8), IT(43.3), IT(42.8), IT(42.8), IT(43.3), IT(43.8), IT(44.5), IT(44.9), IT(45.9), IT(47.0), IT(48.7), IT(50.5), //  40kPa
  IT(0.0), IT(14.3), IT(15.3), IT(25.2), IT(30.8), IT(36.1), IT(39.6), IT(43.1), IT(44.5), IT(44.5), IT(44.5), IT(44.2), IT(43.8), IT(43.3), IT(42.8), IT(42.8), IT(43.3), IT(43.8), IT(44.5), IT(44.9), IT(45.9), IT(47.0), IT(48.7), IT(50.5), //  50kPa
  IT(0.0), IT(12.5), IT(14.6), IT(23.4), IT(28.7), IT(34.0), IT(37.5), IT(40.7), IT(41.7), IT(41.7), IT(41.7), IT(41.4), IT(41.0), IT(40.5), IT(40.0), IT(40.0), IT(40.5), IT(41.0), IT(41.7), IT(42.1), IT(43.1), IT(44.2), IT(45.9), IT(47.7), //  60kPa

  IT(0.0), IT(11.1), IT(13.9), IT(21.7), IT(26.6), IT(31.5), IT(34.7), IT(37.8), IT(38.9), IT(38.9), IT(38.9), IT(38.5), IT(38.2), IT(37.7), IT(37.1), IT(37.1), IT(37.7), IT(38.2), IT(38.9), IT(39.3), IT(40.3), IT(41.4), IT(43.1), IT(44.9), //  70kPa
  IT(0.0),  IT(9.4), IT(13.6), IT(19.9), IT(24.8), IT(29.4), IT(32.6), IT(35.4), IT(35.7), IT(35.7), IT(35.7), IT(35.7), IT(35.0), IT(34.7), IT(34.3), IT(34.3), IT(34.7), IT(35.0), IT(35.7), IT(36.4), IT(37.1), IT(38.5), IT(40.0), IT(41.7), //  80kPa
  IT(0.0),  IT(7.6), IT(12.9), IT(18.2), IT(22.7), IT(26.9), IT(29.8), IT(32.6), IT(32.9), IT(32.9), IT(32.9), IT(32.9), IT(32.2), IT(31.9), IT(31.5), IT(31.5), IT(31.9), IT(32.2), IT(32.9), IT(33.6), IT(34.3), IT(35.7), IT(37.1), IT(38.9), //  90kPa
  IT(0.0),  IT(5.9), IT(12.2), IT(16.4), IT(20.6), IT(24.8), IT(27.6), IT(30.1), IT(30.1), IT(30.1), IT(30.1), IT(30.1), IT(29.4), IT(29.1), IT(28.7), IT(28.7), IT(29.1), IT(29.4), IT(30.1), IT(30.8), IT(31.5), IT(32.9), IT(34.3), IT(36.1), // 100kPa
  IT(0.0),  IT(5.1), IT(10.8), IT(14.6), IT(18.5), IT(22.4), IT(24.8), IT(27.3), IT(27.3), IT(27.3), IT(27.3), IT(27.3), IT(26.6), IT(26.2), IT(25.9), IT(25.9), IT(26.2), IT(26.6), IT(27.3), IT(27.6), IT(28.4), IT(29.8), IT(31.2), IT(32.9), // 120kPa

  IT(0.0),  IT(4.8),  IT(9.7), IT(13.2), IT(16.4), IT(19.9), IT(22.0), IT(24.1), IT(24.1), IT(24.1), IT(24.1), IT(24.1), IT(23.4), IT(23.1), IT(22.7), IT(22.7), IT(23.1), IT(23.4), IT(24.1), IT(24.8), IT(25.5), IT(26.9), IT(28.4), IT(29.8), // 140kPa
  IT(0.0),  IT(4.1),  IT(8.3), IT(11.5), IT(14.3), IT(17.5), IT(19.6), IT(21.3), IT(21.3), IT(21.3), IT(21.3), IT(21.3), IT(20.6), IT(20.3), IT(19.9), IT(19.9), IT(20.3), IT(20.6), IT(21.3), IT(21.7), IT(22.4), IT(23.8), IT(25.2), IT(26.6), // 160kPa
  IT(0.0),  IT(3.4),  IT(7.3),  IT(9.7), IT(12.5), IT(15.0), IT(16.8), IT(18.2), IT(18.2), IT(18.2), IT(18.2), IT(18.2), IT(17.5), IT(17.1), IT(16.8), IT(16.8), IT(17.1), IT(17.5), IT(18.2), IT(18.9), IT(19.6), IT(20.6), IT(22.0), IT(23.8), // 180kPa
  IT(0.0),  IT(2.7),  IT(5.9),  IT(8.0), IT(10.4), IT(12.5), IT(13.9), IT(15.3), IT(15.3), IT(15.3), IT(15.3), IT(15.3), IT(14.6), IT(14.3), IT(13.9), IT(13.9), IT(14.3), IT(14.6), IT(15.3), IT(15.7), IT(16.4), IT(17.5), IT(18.9), IT(20.6), // 200kPa
  IT(0.0),  IT(2.3),  IT(4.4),  IT(6.6),  IT(8.3), IT(10.1), IT(11.1), IT(12.2), IT(12.2), IT(12.2), IT(12.2), IT(12.2), IT(11.5), IT(11.1), IT(10.8), IT(10.8), IT(11.1), IT(11.5), IT(12.2), IT(12.5), IT(13.2), IT(14.6), IT(16.0), IT(17.5), // 220kPa

  IT(0.0),  IT(1.6),  IT(3.4),  IT(4.8),  IT(6.2),  IT(7.6),  IT(8.7),  IT(9.4),  IT(9.4),  IT(9.4),  IT(9.4),  IT(9.4),  IT(8.7),  IT(8.3),  IT(8.0),  IT(8.0),  IT(8.3),  IT(8.7),  IT(9.4),  IT(9.7), IT(10.4), IT(11.5), IT(12.9), IT(14.3), // 240kPa
  IT(0.0),  IT(0.9),  IT(2.0),  IT(3.0),  IT(4.1),  IT(5.1),  IT(5.9),  IT(6.2),  IT(6.2),  IT(6.2),  IT(6.2),  IT(6.2),  IT(5.5),  IT(5.1),  IT(4.8),  IT(4.8),  IT(5.1),  IT(5.5),  IT(6.2),  IT(6.6),  IT(7.3),  IT(8.3),  IT(9.7), IT(11.1), // 260kPa
  IT(0.0),  IT(0.0),  IT(1.0),  IT(2.0),  IT(3.0),  IT(4.0),  IT(5.0),  IT(5.2),  IT(5.2),  IT(5.2),  IT(5.2),  IT(5.2),  IT(4.5),  IT(4.2),  IT(3.8),  IT(3.8),  IT(4.2),  IT(4.5),  IT(5.2),  IT(5.6),  IT(6.3),  IT(7.3),  IT(8.7), IT(10.1), // 280kPa
  IT(0.0),  IT(0.0),  IT(0.0),  IT(1.0),  IT(2.0),  IT(3.0),  IT(4.0),  IT(4.0),  IT(4.0),  IT(4.0),  IT(4.0),  IT(4.0),  IT(3.5),  IT(3.2),  IT(2.8),  IT(2.8),  IT(3.2),  IT(3.5),  IT(4.2),  IT(4.6),  IT(5.3),  IT(6.3),  IT(7.7),  IT(9.4)  // 300kPa
//    200       700      1100      1500      1900      2300      2700      3100      3500      3900      4300      4700      5100      5500      5900      6300      6700      7100      7500      7900      8300      8700      9100      9500  // Boost
// Low RPM                                                                                                                                                                                                                             High RPM
