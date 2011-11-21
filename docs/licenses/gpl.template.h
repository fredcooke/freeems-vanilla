/* FreeEMS - the open source engine management system
 *
 * Copyright 2011 Fred Cooke
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
 * @ingroup putMeInSomeGroups
 *
 * no brief description unless global or general purpose
 *
 * Description about what this file is intended to contain and
 * anything else that is unique and/or notable about it here!
 *
 * To add a file to the project :
 * - Copy this file to the source directory with an appropriate name
 * - Change the name to your own at the top of the GPL comment
 * - Change the filename to the correct one at the top of this comment
 * - Change all 4 hash defines to the filename uppercased and underscored
 *
 * @bug THIS DOCUMENTATION IS FAULTY!!
 * @todo REPLACE THIS WITH REAL DOCUMENTATION!!
 * @note SOME LAZY DEVELOPER DIDN'T CUSTOMISE THEIR DOCUMENTATION!!
 * @warning IMAGINE WHAT THEIR CODE MIGHT BE LIKE IF THEIR DOCUMENTATION IS THIS BAD!!
 */

/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_< filename >_H_SEEN
#define FILE_< filename >_H_SEEN

#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif

#ifdef < filename >_C
#define EXTERN
#else
#define EXTERN extern
#endif

// hash defines here

// declarations here

#undef EXTERN

#else
	/* let us know if we are being untidy with headers */
	#warning "Header file < filename >_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
