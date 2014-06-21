#	FreeEMS - the open source engine management system
#
#	groups.mk
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
#                               Processed Groups                               #
################################################################################


# Convert extensions
DEPENDENCIES = $(patsubst %.c,$(DEPDIR)/%.d,$(CLASSES))
DDEPENDENCIES = $(patsubst %.c,$(DEPDIR)/%.dd,$(CLASSES))
PREPROCESSED = $(patsubst %.c,$(PPCDIR)/%.pp.c,$(CLASSES))
ASSEMBLIES = $(patsubst %.c,$(ASMDIR)/%.s,$(CLASSES))
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(CLASSES))
HANDOBJECTS = $(patsubst %.s,$(OBJDIR)/%.o,$(HANDASMS))
DUMPS = $(patsubst %.c,$(BUGDIR)/%.dmp,$(CLASSES)) $(patsubst %.s,$(BUGDIR)/%.dmp,$(HANDASMS))
XGOBJECTS = $(patsubst %.s,$(XGOBJDIR)/%.o,$(XGASMSRCS))

# Convert RPM extensions
DEPENDENCIESRPM = $(patsubst %.c,$(DEPDIR)/%.d,$(RPMCLASSES))
DDEPENDENCIESRPM = $(patsubst %.c,$(DEPDIR)/%.dd,$(RPMCLASSES))
PREPROCESSEDRPM = $(patsubst %.c,$(PPCDIR)/%.pp.c,$(RPMCLASSES))
ASSEMBLIESRPM = $(patsubst %.c,$(ASMDIR)/%.s,$(RPMCLASSES))
OBJECTSRPM = $(patsubst %.c,$(OBJDIR)/%.o,$(RPMCLASSES)) #$(patsubst $(DECDIR???)%.s,$(OBJDIR)/%.o,$(RPMHANDASMS))
DUMPSRPM = $(patsubst %.c,$(BUGDIR)/%.dmp,$(RPMCLASSES)) #$(patsubst $(DECDIR???)%.s,$(BUGDIR)/%.dmp,$(RPMHANDASMS))

# Convert to output files for source
ALLELFSC = $(patsubst $(DECDIR)/%.c,$(OUTDIR)/$(LABEL)-%.elf,$(RPMCLASSES))
ALLELFSASM = #$(patsubst %.s,$(OUTDIR)/$(LABEL)-%.elf,$(RPMHANDASMS))
ALLDMPSC = $(patsubst $(DECDIR)/%.c,$(BUGDIR)/$(LABEL)-%.dmp,$(RPMCLASSES))
ALLDMPSASM = #$(patsubst %.s,$(BUGDIR)/$(LABEL)-%.dmp,$(RPMHANDASMS))
ALLMAPSC = $(patsubst $(DECDIR)/%.c,$(BUGDIR)/$(LABEL)-%.map,$(RPMCLASSES))
ALLMAPSASM = #$(patsubst %.s,$(BUGDIR)/$(LABEL)-%.map,$(RPMHANDASMS))
ALLREADC = $(patsubst $(DECDIR)/%.c,$(BUGDIR)/$(LABEL)-%.ree,$(RPMCLASSES))
ALLREADASM = #$(patsubst %.s,$(BUGDIR)/$(LABEL)-%.ree,$(RPMHANDASMS))
ALLS19SC = $(patsubst $(DECDIR)/%.c,$(S19DIR)/$(LABEL)-%.s19,$(RPMCLASSES))
ALLS19SASM = #$(patsubst %.s,$(S19DIR)/$(LABEL)-%.s19,$(RPMHANDASMS))

# Convert to output files for as-is variants
ALLELFS = $(ALLELFSC) $(ALLELFSASM)
ALLDMPS = $(ALLDMPSC) $(ALLDMPSASM)
ALLMAPS = $(ALLMAPSC) $(ALLMAPSASM)
ALLREAD = $(ALLREADC) $(ALLREADASM)
ALLS19S = $(ALLS19SC) $(ALLS19SASM)
ALLSIZES = $(patsubst $(S19DIR)/%,$(OUTDIR)/%.txt,$(ALLS19S))
ALLDUMMY = $(patsubst $(S19DIR)/%,$(OUTDIR)/%.txt.dummy,$(ALLS19S))
ALLMD5S = $(patsubst $(S19DIR)/%,$(FIRMWAREDISTRIBUTIONDIR)/%.md5,$(ALLS19S))
ALLSHA1S = $(patsubst $(S19DIR)/%,$(FIRMWAREDISTRIBUTIONDIR)/%.sha1,$(ALLS19S))
ALLS19ZIPS = $(patsubst $(S19DIR)/%,$(FIRMWAREDISTRIBUTIONDIR)/%.zip,$(ALLS19S))


# Convert to output files for GC variants
GCDELFSC = $(patsubst $(DECDIR)/%.c,$(OUTDIR)/$(LABEL)-%.gc.elf,$(RPMCLASSES))
GCDELFSASM = #$(patsubst %.s,$(OUTDIR)/$(LABEL)-%.gc.elf,$(RPMHANDASMS))
GCDS19SC = $(patsubst $(DECDIR)/%.c,$(S19DIR)/$(LABEL)-%.gc.s19,$(RPMCLASSES))
GCDS19SASM = #$(patsubst %.s,$(S19DIR)/$(LABEL)-%.gc.s19,$(RPMHANDASMS))
GCDELFS = $(GCDELFSC) $(GCDELFSASM)
GCDS19S = $(GCDS19SC) $(GCDELFSASM)
GCDSIZES = $(patsubst $(S19DIR)/%,$(OUTDIR)/%.txt,$(GCDS19S))
GCDDUMMY = $(patsubst $(S19DIR)/%,$(OUTDIR)/%.txt.dummy,$(GCDS19S))
