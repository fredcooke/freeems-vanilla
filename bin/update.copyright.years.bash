#!/bin/bash

#	FreeEMS - the open source engine management system
#
#	filename here
#
#	Copyright 2010 Fred Cooke
#
#	This file is part of the FreeEMS project.
#
#	FreeEMS software is free software: you can redistribute it and/or modify
#	it under the terms of the GNU General Public License as published by
#	the Free Software Foundation, either version 3 of the License, or
#	(at your option) any later version.
#
#	FreeEMS software is distributed in the hope that it will be useful,
#	but WITHOUT ANY WARRANTY; without even the implied warranty of
#	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#	GNU General Public License for more details.
#
#	You should have received a copy of the GNU General Public License
#	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
#
#	We ask that if you make any changes to this file you email them upstream to
#	us at admin(at)diyefi(dot)org or, even better, fork it on www.github.com!!!
#
#	Thank you for choosing FreeEMS to run your engine!


# The following line takes a file with the formate <num><space><num><space><filename/path> and looks for years that need updating.
#for f in $(perl -lne '/^\d+\s+\d+\s+(.*)/ && print $1' files.2009); do perl -i.bkp -lpe 's/2008 /2008, 2009 /g unless /2009/' "$f"; done
# update to new fliename, yearset etc before using, hence commented out. list generated with git diff --numstat hash1 hash2

