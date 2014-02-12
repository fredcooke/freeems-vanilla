/* FreeEMS - the open source engine management system
 *
 * Copyright 2011-2013 Fred Cooke
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
 * @brief A volumetric efficiency table for a Volvo B21A with a B230F intake manifold.
 *
 * Under development
 */

// With corrections, and changes.

//  Low RPM                                                                                         High RPM
//    200           500          1000          1600          2200          2800          3400          4000          4600          5200          5800          6400  // V
  VE( 35),      VE( 35),      VE( 35),      VE( 35),      VE( 36),      VE( 37),      VE( 39),      VE( 40),      VE( 40),      VE( 40),      VE( 39),      VE( 38),//15 
  //                                                                    36.9    36.7     38.8                             40.4
  //                                                             33.6    35.8   36.2            39.5
  //                                                   31.9  33.4   34.9  35.1           31.8   31.6        31.6     32.5       31.5
  //                                              30.6 33.9                         31.2                                 33.5 33.4
  //                                              31.4               28.2 32.6    30.0 33.2                   34.8                         32.5
  VE( 33),      VE( 32),      VE( 31),      VE( 31),      VE( 32),      VE( 33),      VE( 33),      VE( 34),      VE( 35),      VE( 35),      VE( 34),      VE( 34),//30
  //                                        31.1    31.1             33.1 35.4       32.4                                             35.5
  //                                           34.1 32.9     31.9    31.6
  //                                    29.8                                   33.4   36.1              36.9
  //                                28.7  28.5  30.8             36.4            39.0                         41.9
  //                                        35.9              37.7        42.9   41.0   40.8 41.3                       44.0        42
  VE( 33),      VE( 31),      VE( 30),      VE( 37),      VE( 39),      VE( 42),      VE( 42),      VE( 43),      VE( 44),      VE( 42),      VE( 41),      VE( 40),//45
  //                               27.8             39.5      39.9      41.3       42.8            41.2     44.6
  //                        30.5          29.0    40.5             44.3        44.4                 46.4 44.9           48.0
  //                          30.2                        43.5    44.9      45.8 47.7     49.1     51.1                                               46
  //                                                     33.9           44.3                                              53.1     50.2
  //                             35.9       48.2    44.8    47.7                  50.2     52.3 51.9   54.6
  VE( 32),      VE( 30),      VE( 36),      VE( 44),      VE( 46),      VE( 50),      VE( 53),      VE( 55),      VE( 55),      VE( 54),      VE( 54),      VE( 54),//60
  //                   30.331.8                          46.5       47.0  50.2           54.9    47.5  55.2 54.3
  //                             38.6   42.9      49.5                              54.8 54.9 55.0
  //                        37.8           50.7    47.2                        54.0       53.5
  //                     34.3 37.5        46.8      47.0                       47.1       54.1
  //             36.3  36.9 36.5                        50.6       48.5         54.3
  VE( 36),      VE( 37),      VE( 38),      VE( 48),      VE( 52),      VE( 54),      VE( 55),      VE( 56),      VE( 56),      VE( 57),      VE( 58),      VE( 60),//75
  //                40.0                                             54.6  56.1           56.1                                             58.5
  //                                               57.4                56.3     50.5   55.7                                               59.7
  //                                                                                      57.5       62.4                             62.8
  //                                                                 51.8                    58.4
  //                                                         60.6 54.9         60.5           60.4
  VE( 50),      VE( 50),      VE( 57),      VE( 58),      VE( 59),      VE( 60),      VE( 61),      VE( 63),      VE( 65),      VE( 67),      VE( 65),      VE( 65),//90
  //                                    58.6                       59.5           61.1    61.0                                  67.8
  //                                                                                  61.9      66.8                                                   59.8
  //                               59.8                             63.6          62.7       62.8   68.5           69.1            71.2          60.9
  //                                62.0       60                68.6     66.8       62.564.8           68.3        70.5   72.6                62.3
  //                                                                               65.5                     68.2
  VE( 54),      VE( 56),      VE( 62),      VE( 62),      VE( 64),      VE( 65),      VE( 66),      VE( 69),      VE( 71),      VE( 73),      VE( 71),      VE( 70),//105
  //
  //
  //
  //
  //
  VE( 70),      VE( 70),      VE( 70),      VE( 70),      VE( 75),      VE( 75),      VE( 75),      VE( 80),      VE( 80),      VE( 80),      VE( 80),      VE( 80),//120
//    200           500          1000          1600          2200          2800          3400          4000          4600          5200          5800          6400  // 









