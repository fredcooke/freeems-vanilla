/**	@file flashConstants.c

	Copyright 2008 Fred Cooke, Sean Keys

	This file was originally for me and Sean to collaborate more easily, possibly redundant now.
	@todo TODO This file should probably be removed and the single value moved elsewhere.

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
	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/

	We ask that if you make any changes to this file you email them upstream to
	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!

	Thank you for choosing FreeEMS to run your engine! */


#include "inc/freeEMS.h"


/// @todo TODO this is a variable, not a constant, should this even be a constant? would a define be better?
unsigned char flashClock = 100;
