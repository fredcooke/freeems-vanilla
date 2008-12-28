/*	freeEMS.c

	Copyright 2008 Fred Cooke

	This file is part of the FreeEMS project.

	FreeEMS software is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FreeEMS software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with any FreeEMS software.  If not, see <http://www.gnu.org/licenses/>.

	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org

	Thank you for choosing FreeEMS to run your engine! */


#define MAIN_OR_GLOBALS
#include "inc/freeEMS.h"
#include "inc/pagedLocationBuffers.h"


/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */
/* &&&&&&&&&&& THIS FILE IS SUPPOSED TO HAVE NO CODE!!! &&&&&&&&&&& */
/* &&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&& */


/* This file creates the symbols for all of the variables. It is	*/
/* separated to clarify how much memory is actually being used by	*/
/* various parts of the program. This is required because the RX/TX */
/* buffers and main paged RAM unions show up as occupied data space */
/* even though they are actually in RAM and not flash. Additionally */
/* it serves as a good place to keep the Doxygen main page comment.	*/


/** @mainpage FreeEMS
 *  @anchor Doxygen_Home_top
 *
 * Welcome to the FreeEMS project!
 *
 * FreeEMS is a free and open source Engine Management System. It
 * includes both software and hardware designs under free software
 * licenses that you can download. FreeEMS firmware is intended to
 * be clean and modular with an emphasis on readability and quality.
 *
 * A log of the work done between this release and the last one can be found here:
 * @ref changeLog
 *
 * A summary of important information about this release can be found here:
 * @ref releaseNotes
 *
 * Specific aspects of the firmware are documented, one aspect per page in
 * the <a href="pages.html">related pages tab</a>.
 *
 * See also :
 *
 * - <a href="http://www.diyefi.org">DIYEFI.org</a>
 * - <a href="https://sourceforge.net/projects/freeems/">Sourceforge location</a>
 * - <a href="http://freeems.aaronb.info/wiki/doku.php?id=start">Wiki location</a>
 * - <a href="http://www.diyefi.org/forum/index.php">DIYEFI.org forums</a>
 *
 * http://github.com/fredcooke/freeems-vanilla/tree/master
 * https://www.ohloh.net/p/freeems
 * http://freeems.aaronb.info/tracker/
 * http://freeems.aaronb.info/wiki/
 * http://freeems.sourceforge.net/doxygen/ (online version)
 * https://sourceforge.net/project/showfiles.php?group_id=214452&package_id=258422
 * diyefi home
 * diyefi forum
 *
 * Further documentation is available in Open Document Format
 * files in the docs directory of the firmware source tree.
 * This documentation includes at least the following items :
 *
 * Change log in text file format
 * CommsTestMatrix.ods
 * dwellTime.ods
 * EMS-Side-Serial-Implementation.odt
 * FreeEMS-Data-Map-Structure.odg
 * FreeEMS-Hardware-Standards.odt
 * FreeEMS-Hardware-Standards.pdf
 * FreeEMS-MemoryManagement.odt
 * FreeEMS-MemoryManagement.pdf
 * FreeEMS.mm
 * FreeEMS_Serial_Protocol_Core_Specification.odt
 * FreeEMS_Serial_Protocol_Core_Specification.pdf
 * FreeEMS-Tuning-Interface-Overview.odt
 * injectorDeadTime.ods
 * licenses/
 * MainTablePossibleSizes16x16up.ods
 * release.procedure.txt
 * serial.imp.issues.txt
 * tasks.txt
 * TestPacketIdeas.odt
 * tests.txt
 * Wheel-Algorithm-Analysis.ods
 * WHY.txt
 * XDP512-freeEMS-pin-assignment.ods
 *
 * change log in each code release instead of separate file? yes!
 *
 */

/** @page codingStyle Coding Style
 *
 * Use doxygen style comments
 * Document all parameters
 * Document return object details
 * use @ instead of \
 * to start a function comment block use ** instead of *!
 * when declaring a pointer make it (type* name) not (type *name)
 * use // style comments for temporary work/documentation and block comments for permanent stuff.
 * order for doc tags : author, param(s), return
 * tabs should be used for indentation
 * braces should be positioned as follows :
 *
 * void function(){
 *     // stuff
 * }
 *
 * case statements should always use braces :
 *
 * switch(var){
 * case 666:
 * {
 *     // stuff
 * }
 *
 * generally, two blank lines between functions, one blank line between logical blocks
 *
 */

/** @page generalStrategies General Strategies
 *
 * Reading/Writing from/to a specific page :
 *
 * Save the page value to a variable, change the page value, read the table, change the page back and return the value
 *
 * TBC
 *
 */

/** @page changeLog Change Log
 *
 * Some change
 * Another change
 *
 */

/** @page releaseNotes Release Notes
 *
 * An awesome feature
 * Another awesome feature
 *
 */
