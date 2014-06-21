#	FreeEMS - the open source engine management system
#
#	paths.mk
#
#	Copyright 2008-2014 Fred Cooke
#
#	This Makefile is part of the FreeEMS project.
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
#	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
#
#	Thank you for choosing FreeEMS to run your engine!




################################################################################
#                             All Fixed Variables                              #
################################################################################


# Constants
FIRMWARE_VERSION := $(shell git describe --always --dirty=-DEV)
OUTPREFIX := FreeEMS
BUILD_DATE := "$(shell date)"
OS := $(shell uname)
BUILT_BY_NAME := "$(shell git config --global --get user.name)"
SUPPORT_EMAIL := "$(shell git config --global --get user.email)"

# Windows differences
ifdef ComSpec
# Windows uses backslash
PATHSEP = \\
# Windows mkdir does not accept -p
MKDIR = mkdir
# Windows echo repeats " symbols (Q stands for quote...)
Q =
SHASUM = sha1sum
else
PATHSEP = /
MKDIR = mkdir -p
Q = "
SHASUM = shasum
endif

# Mac differences
ifeq ($(OS), Darwin)
MD5SUM = md5 -r
else
# If using this on windows, we're in cygwin, same as Linux
MD5SUM = md5sum
endif

ifdef CLIFLAGS
CLIBUILD = -D CLIFLAGS=1
ifdef XGATE
CLIFLAGSARG = -D $(CLIFLAGS)=1 -D XGATE=1
LABEL := $(OUTPREFIX)-$(FIRMWARE_VERSION)-$(CLIFLAGS)-XGATE
else
CLIFLAGSARG = -D $(CLIFLAGS)=1
LABEL := $(OUTPREFIX)-$(FIRMWARE_VERSION)-$(CLIFLAGS)
endif
else
LABEL := $(OUTPREFIX)-$(FIRMWARE_VERSION)
endif

# Directories here
DISTRIBUTIONDIR = ../../tmp/$(LABEL)
FIRMWAREDISTRIBUTIONDIR = $(DISTRIBUTIONDIR)/$(LABEL)-firmware
DOXYDOCDIR = ../../docs/doxygen-html
MAINDIR = freeems-vanilla
INCDIR = inc
DEPDIR = dependencies
DECDIR = decoders
DATADIR = initialisers
BUGDIR = debug
OUTDIR = output
OBJDIR = objects
ASMDIR = assembly
XGASMDIR = assemblyxgate
HANDASMDIR = assemblyhand
S19DIR = firmware
PPCDIR = preprocessedc
XGOBJDIR = $(OBJDIR)$(PATHSEP)xgate

# Release tag message file
RELTAG = $(OUTDIR)/gitTagMessage.txt
TAGNAME = $(OUTDIR)/gitTagName.txt

# Program prefixes, for the main cpu and for the xgate coprocessor
PREFIX = m68hc11-
XGPREFIX = mc9xgate-

# All of the tools
CP = cp
RM = rm -rf
ZIP = zip
GCC = $(PREFIX)gcc
COPY = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump
NM = $(PREFIX)nm
RE = $(PREFIX)readelf
SIZE = $(PREFIX)size
XGAS = $(XGPREFIX)as
