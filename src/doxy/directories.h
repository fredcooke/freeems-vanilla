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


/** @file directories.h
 *
 * @ingroup doxygenDocFiles
 * @brief Doxygen directory documentation definitions
 */


/** @dir src
 *
 * The home of all source files used to build FreeEMS firmware. Groups of related
 * files are stored in sub-directories within this directory and general files
 * such as main.c and init.c etc are stored at this level.
 */


/** @dir src/assembly
 *
 * The very small amount of S12X assembly used in the project lives here, as do
 * all assembly files generated during the build process. Cleaning is done using
 * specific file names so as to not remove the hand written files.
 */


/** @dir src/assembly/xgate
 *
 * Assembly source files for the XGATE coprocessor are stored in this directory.
 * All XGATE assembly source files are hand written as it does not make sense to
 * use a C compiler to generate code for this device.
 */


/** @dir src/data
 *
 * This directory contains no actual code, just data used to initialise various
 * blocks of memory such as structs and arrays etc. These files get pulled into
 * files in src/initialisers/ and built into data objects.
 */


/** @dir src/data/tables
 *
 * This directory contains the various data components that make up tables.
 */


/** @dir src/data/tables/axis
 *
 * This directory has the axis data for the RPM and Load axes in it.
 */


/** @dir src/data/tables/ign
 *
 * This directory has the ignition timing table data in it.
 */


/** @dir src/data/tables/lambda
 *
 * This directory has the integral lambda table data in it.
 */


/** @dir src/data/tables/ve
 *
 * This directory has the volumetric efficiency table data in it.
 */


/** @dir src/data/thermistors
 *
 * This directory contains a library of data files for common combinations of
 * bias resistor and thermistors for three main types of sensor and six commonly
 * used resistor values.
 */


/** @dir src/decoders
 *
 * The RPM/position decoder directory contains ISR code for various types of RPM
 * and position sensor combinations. Buildable files can be found at this level.
 * Files that are included into buildable files are found in sub-directories.
 */


/** @dir src/decoders/code
 *
 * Code that is re-used across multiple build configurations lives here.
 */


/** @dir src/decoders/inc
 *
 * Header files for decoder ISRs are stored here, whether one-off or re-used.
 */


/** @dir src/default
 *
 * When files are often customised, they exist in pairs, the defaults goes here,
 * and the user versions go in src/custom which doxygen doesn't list.
 */


/** @dir src/doxy
 *
 * Files such as the source of this directory documentation which are purely
 * present for Doxygen to parse and display are stored here.
 */


/** @dir src/inc
 *
 * Normal header files of global or single file use nature live here.
 */


/** @dir src/initialisers
 *
 * Files that are purely data initialisers and contain no logic code live here.
 */

