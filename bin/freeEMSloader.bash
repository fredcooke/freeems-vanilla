#!/bin/bash

#	freeEMSloader.bash
#
#	Copyright 2008 Fred Cooke
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
#	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org
#
#	Thank you for choosing FreeEMS to run your engine!


# Set up the variables
export EXPECTED_ARGS="2"
export NUMBER_OF_ARGS="$#"
export SERIAL_DEVICE="$1"
export FIRMWARE_S19_PATH="$2"
export SERIAL_BAUD="115200"
export XDP512="mc9s12xdp512"
export XEP100="mc9s12xep100"
export DEVICE_TYPE=$XDP512
export LOAD_TOOL=`which hcs12mem`
#export ADDRESS_TYPE="non-banked"
export ADDRESS_TYPE="banked-ppage"
#export ADDRESS_TYPE="banked-linear"
# Address type banked linear should be used WITHOUT lma/ppage references in the objcopy section of the Makefile

# Set up the files
export TEMP_BASE="/tmp/"`date +date_%F_time_%Hh%Mm%Ss_%p`
export TEMP_S19_COPY=$TEMP_BASE".freeEMS.firmware.copy.s19"
export TEMP_S19_DIFF=$TEMP_BASE".freeEMS.firmware.s19.diff"

# Set up the messages
export GOODBYE="Thank you for choosing the FreeEMS to run your engine, goodbye."
export USAGE="Usage : freeEMSloader.bash /dev/yourTTY new-firmware.s19"

# Formalise the error codes
export WRONG_EMS="-10"

export WRONG_NUMBER_OF_ARGS="-20"
export SERIAL_DEVICE_DOES_NOT_EXIST="-21"
export SERIAL_DEVICE_NOT_READABLE="-22"
export SERIAL_DEVICE_NOT_WRITABLE="-23"
export SERIAL_DEVICE_NOT_CHARACTER_DEVICE="-24"

export S19_FILE_DOES_NOT_EXIST="-30"
export S19_FILE_NOT_READABLE="-31"
export S19_FILE_NOT_REGULAR_FILE="-32"

export HCS12MEM_EXECUTABLE_DOES_NOT_EXIST="-40"
export HCS12MEM_EXECUTABLE_NOT_READABLE="-41"
export HCS12MEM_EXECUTABLE_NOT_EXECUTABLE="-42"

export ABORT_PRE_ERASE="-50"
export ERASE_FAILED="-51"

export ABORT_PRE_LOAD="-60"
export LOAD_FAILED="-61"

export VERIFY_FAILED="-70"
export ABORT_PRE_DELETE_TMP="-71"
export EXIT_WITHOUT_CLEANING_UP="-72"


# continue() takes three arguments : affirmative meaning continue, negative meaning exit, and exit code
continue ()
{
	while [ true ]
	do
		read ANSWER

		if [ "$ANSWER" == "$1" ]
		then
			break

		elif [ "$ANSWER" == "$2" ]
		then
			echo "$GOODBYE"
			exit "$3"
		else
			echo "'$ANSWER' not recognised, $1 and $2 are valid, please re-enter"
		fi
	done
}


# Display splash screen
welcome ()
{
	echo "Welcome to the FreeEMS firmware loader"
	echo
	echo "This program is released under the GPL V3"
	echo "Please see http://www.gnu.org/licenses/ for details"
	echo
	echo "This version is for $DEVICE_TYPE based FreeEMS's"
	echo
	echo "Do you have a $DEVICE_TYPE based FreeEMS? [ yes | quit ]"

	continue "yes" "quit" "$WRONG_EMS"
}


# Ensure all is in order
check_args ()
{
	echo "Checking configuration and arguments..."

	# Test for the correct number of arguments
	if [ $EXPECTED_ARGS -ne $NUMBER_OF_ARGS ]
	then
		echo "$USAGE"
		echo "Expected $EXPECTED_ARGS parameter(s), got $NUMBER_OF_ARGS, exiting..."
		exit "$WRONG_NUMBER_OF_ARGS"

	# Ensure serial device exists
	elif [ ! -e "$SERIAL_DEVICE" ]
	then
		echo "Serial device $SERIAL_DEVICE does NOT exist! exiting..."
		exit "$SERIAL_DEVICE_DOES_NOT_EXIST"

	# Ensure serial device is readable
	elif [ ! -r "$SERIAL_DEVICE" ]
	then
		echo "Serial device $SERIAL_DEVICE is NOT readable! exiting..."
		exit "$SERIAL_DEVICE_NOT_READABLE"

	# Ensure serial device is writable
	elif [ ! -w "$SERIAL_DEVICE" ]
	then	
		echo "Serial device $SERIAL_DEVICE is NOT writable! exiting..."
		exit "$SERIAL_DEVICE_NOT_WRITABLE"

	# Ensure serial device is a character device or symlink
	elif [ ! -c "$SERIAL_DEVICE" ] && [ ! -L "$SERIAL_DEVICE" ]
	then
		echo "Serial device $SERIAL_DEVICE is NOT a valid character device or symlink! exiting..."
		exit "$SERIAL_DEVICE_NOT_CHARACTER_DEVICE"

	# Ensure the s19 file exists
	elif [ ! -e "$FIRMWARE_S19_PATH" ]
	then
		echo "S19 file $FIRMWARE_S19_PATH does NOT exist! exiting..."
		exit "$S19_FILE_DOES_NOT_EXIST"

	# Ensure the s19 is readable
	elif [ ! -r "$FIRMWARE_S19_PATH" ]
	then
		echo "S19 file $FIRMWARE_S19_PATH is NOT readable! exiting..."
		exit "$S19_FILE_NOT_READABLE"

	# Ensure the s19 is a regular file or symlink
	elif [ ! -f "$FIRMWARE_S19_PATH" ] && [ ! -L "$FIRMWARE_S19_PATH" ]
	then
		echo "S19 file $FIRMWARE_S19_PATH is NOT a regular file or symlink! exiting..."
		exit "$S19_FILE_NOT_REGULAR_FILE"

	# Ensure the hcs12mem tool is available
	elif [ ! -e "$LOAD_TOOL" ]
	then
		echo "hcs12mem does NOT appear to be available in the current path! exiting..."
		exit "$HCS12MEM_EXECUTABLE_DOES_NOT_EXIST"

	# Ensure the hcs12mem tool is readable
	elif [ ! -r "$LOAD_TOOL" ]
	then
		echo "$LOAD_TOOL is NOT readable! exiting..."
		exit "$HCS12MEM_EXECUTABLE_NOT_READABLE"

	# Ensure the hcs12mem tool is executable
	elif [ ! -x "$LOAD_TOOL" ]
	then
		echo "$LOAD_TOOL is NOT executable! exiting..."
		exit "$HCS12MEM_EXECUTABLE_NOT_EXECUTABLE"
	fi

	echo "Everything looks good!"
}


# Erase the flash blocks before trying to write our S19 in (this is required)
erase_flash ()
{
	echo "Erase the flash on your FreeEMS? (This is necessary to load new firmware) [ yes | abort ]"
	continue "yes" "abort" "$ABORT_PRE_ERASE"
	
	echo "Erasing the FreeEMS flash without verification..."
	$LOAD_TOOL -b $SERIAL_BAUD -i sm -p $SERIAL_DEVICE -t $DEVICE_TYPE --flash-erase

	if [ $? -ne 0 ]
	then
		echo "Erasing flash failed! exiting..."
		exit "$ERASE_FAILED"
	fi

	echo "Erasing flash was successful!"
}


# Load the s19 into the FreeEMS without verification (verify unimplemented in hcs12mem)
load_s19 ()
{
	echo "Load the firmware to your FreeEMS? [ yes | abort ]"
	continue "yes" "abort" "$ABORT_PRE_LOAD"
	
	echo "Loading $FIRMWARE_S19_PATH to FreeEMS flash without verification..."
	$LOAD_TOOL -b $SERIAL_BAUD -i sm -p $SERIAL_DEVICE -t $DEVICE_TYPE -a $ADDRESS_TYPE --flash-write "$FIRMWARE_S19_PATH"

	if [ $? -ne 0 ]
	then
		echo "Firmware load failed! exiting..."
		exit "$LOAD_FAILED"
	fi

	echo "Firmware load was successful!"
}


# Verify the load to flash manually
verify_load ()
{
	echo "Verifying firmware loaded to flash correctly..."
	
	echo "Reading contents of FreeEMS flash back to $TEMP_S19_COPY ..."
	$LOAD_TOOL -b $SERIAL_BAUD -i sm -p $SERIAL_DEVICE -t $DEVICE_TYPE -a $ADDRESS_TYPE --flash-read "$TEMP_S19_COPY"

	echo "Comparing $TEMP_S19_COPY with $FIRMWARE_S19_PATH , redirecting output to $TEMP_S19_DIFF ..."
	diff $FIRMWARE_S19_PATH $TEMP_S19_COPY > $TEMP_S19_DIFF

	if [ $? -ne 0 ]
	then
		echo "Verification failure! :-("
		echo "The retrieved S19 can be found here : $TEMP_S19_COPY"
		echo "The difference between that and the original can be found here : $TEMP_S19_DIFF"

	else
		echo "Verification successful!"
		
		echo "Removing $TEMP_S19_COPY ..."
		rm "$TEMP_S19_COPY"

		echo "Removing $TEMP_S19_DIFF ..."
		rm "$TEMP_S19_DIFF"
	fi
}


welcome
check_args
erase_flash
load_s19
# verify currently doesn't work. needs more finesse.
#verify_load
echo "It is strongly recommended that you re-extract the firmware and do a visual diff to confirm that the only change is the serial monitor being included."
echo "$GOODBYE"

