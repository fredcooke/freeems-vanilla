#!/bin/bash

#	FreeEMS - the open source engine management system
#
#       dumpAllFlash3forms.bash
#
#       Copyright 2008, 2009, 2010 Fred Cooke
#
#       This file is part of the FreeEMS project.
#
#       FreeEMS software is free software: you can redistribute it and/or modify
#       it under the terms of the GNU General Public License as published by
#       the Free Software Foundation, either version 3 of the License, or
#       (at your option) any later version.
#
#       FreeEMS software is distributed in the hope that it will be useful,
#       but WITHOUT ANY WARRANTY; without even the implied warranty of
#       MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#       GNU General Public License for more details.
#
#       You should have received a copy of the GNU General Public License
#       along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
#
#       We ask that if you make any changes to this file you email them upstream to
#	us at admin(at)diyefi(dot)org or, even better, fork it on www.github.com!!!
#
#       Thank you for choosing FreeEMS to run your engine!

# These are all we can use now as we are paging flash finally :-)

# Set up the variables
export EXPECTED_ARGS="1"
export NUMBER_OF_ARGS="$#"

# Formalise the error codes
export WRONG_NUMBER_OF_ARGS="-20"

# Test for the correct number of arguments
if [ $EXPECTED_ARGS -ne $NUMBER_OF_ARGS ]
then
	echo "$USAGE"
	echo "Expected $EXPECTED_ARGS parameter(s), got $NUMBER_OF_ARGS, exiting..."
	exit "$WRONG_NUMBER_OF_ARGS"
fi

export SERIAL_DEVICE="$1"


# This only pulls down what has been written.
hcs12mem -b 115200 -i sm -p $SERIAL_DEVICE -t mc9s12xdp512 -a banked-ppage --flash-read freeems.full.dump.ppage.`date +%s`.s19

