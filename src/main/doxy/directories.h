/* FreeEMS - the open source engine management system
 *
 * Copyright 2014 Fred Cooke
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


/** @dir src/main
 *
 * The home of all source files used to build FreeEMS firmware. Groups of related
 * files are stored in sub-directories within this directory and general files
 * such as main.c and init.c etc are stored at this level.
 */


/** @dir src/main/assemblyhand
 *
 * The very small amount of hand-written S12X assembly used in the project lives
 * here. All assembly files generated during the build process live in a temporary
 * directory called assembly.
 */


/** @dir src/main/assemblyxgate
 *
 * Assembly source files for the XGATE coprocessor are stored in this directory.
 * All XGATE assembly source files are hand written as it does not make sense to
 * use a C compiler to generate code for this device.
 */


/** @dir src/main/data
 *
 * This directory contains no actual code, just data used to initialise various
 * blocks of memory such as structs and arrays etc. These files get pulled into
 * files in src/initialisers/ and built into data objects.
 */


/** @dir src/main/data/tables
 *
 * This directory contains the various data components that make up tables.
 */


/** @dir src/main/data/tables/axis
 *
 * This directory has the axis data for the RPM and Load axes in it.
 */


/** @dir src/main/data/tables/ign
 *
 * This directory has the ignition timing table data in it.
 */


/** @dir src/main/data/tables/lambda
 *
 * This directory has the integral lambda table data in it.
 */


/** @dir src/main/data/tables/ve
 *
 * This directory has the volumetric efficiency table data in it.
 */


/** @dir src/main/data/thermistors
 *
 * This directory contains a library of data files for common combinations of
 * bias resistor and thermistors for three main types of sensor and six commonly
 * used resistor values.
 */


/** @dir src/main/decoders
 *
 * The RPM/position decoder directory contains ISR code for various types of RPM
 * and position sensor combinations. Buildable files can be found at this level.
 * Files that are included into buildable files are found in sub-directories.
 */


/** @dir src/main/decoders/code
 *
 * Code that is re-used across multiple build configurations lives here.
 */


/** @dir src/main/decoders/inc
 *
 * Header files for decoder ISRs are stored here, whether one-off or re-used.
 */


/** @dir src/main/doxy
 *
 * Files such as the source of this directory documentation which are purely
 * present for Doxygen to parse and display are stored here.
 */


/** @dir src/main/inc
 *
 * Normal header files of global or single file use nature live here.
 */


/** @dir src/main/initialisers
 *
 * Files that are purely data initialisers and contain no logic code live here.
 */
