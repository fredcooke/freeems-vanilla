#!/bin/bash

#	FreeEMS - the open source engine management system
#
#	Copyright 2010-2014 Fred Cooke
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

if [ $# -ne 1 ]; then 
	echo "Wrong arg count! $#"
	exit 1
fi

if [ ! -e "$1" ]; then
	echo "$1 doesn't exist!"
	exit 1
fi

if [ ! -f "$1" ]; then
	echo "$1 is not a file"
	exit 1
fi


# The following two lines take a file with format <num><space><num><space><path/filename> and look for years that need updating.
for f in $(perl -lne '/^\d+\s+\d+\s+(.*)/ && print $1' $1); do perl -i -lpe 's/-2013/-2014/g' "$f"; done      # Update existing ranges
for f in $(perl -lne '/^\d+\s+\d+\s+(.*)/ && print $1' $1); do perl -i -lpe 's/2013 /2013-2014 /g' "$f"; done # Update singular years to ranges
# Update to yearset before using, list generated with git diff --numstat lasthashpreviousyear lasthashcurrentyear -- src

