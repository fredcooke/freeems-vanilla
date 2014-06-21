#	FreeEMS - the open source engine management system
#
#	sources.mk
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
#                               All Source Files                               #
################################################################################


# Indirect dependencies that can affect everything and cause a full rebuild
MFILE = Makefile make/*
ASMH = 9S12XDP512asm.s
LINKER = memory.x regions.x hc9s12xdp512elfb.x


# Let's keep this to a bare minimum! If you write ASM code
# please provide a matching alternate C implementation too.
HANDASMS = flashBurn.s
#RPMHANDASMS = 

ALLH = $(LINKER) $(MFILE) $(INCDIR)/$(ASMH)

# Warning : do not include .c files from inc/ as they are
# included into the other C files and automatically compiled.

# Flash data files
FIXEDCLASSES = FixedConfig1.c FixedConfig2.c
LOOKUPCLASSES1 = IATTransferTable.c CHTTransferTable.c
LOOKUPCLASSES2 = MAFTransferTable.c TestTransferTable.c
FUELCLASSES = FuelTables.c FuelTables2.c
TIMECLASSES = TimingTables.c TimingTables2.c
TUNECLASSES = TunableConfig.c TunableConfig2.c
# Combined data files
DATARAW = $(FIXEDCLASSES) $(LOOKUPCLASSES1) $(LOOKUPCLASSES2) $(FUELCLASSES) $(TIMECLASSES) $(TUNECLASSES)
DATA = $(patsubst %.c,$(DATADIR)/%.c,$(DATARAW))

# Source code files
UTILCLASSES = tableLookup.c init.c utils.c globalConstants.c StaticBenchTest.c simpleGPIO.c
MATHCLASSES = coreVarsGenerator.c derivedVarsGenerator.c fuelAndIgnitionCalcs.c outputScheduler.c decoderInterface.c
COMCLASSES = flashWrite.c commsCore.c blockDetailsLookup.c
ISRCLASSES = interrupts.c injectionISRs.c commsISRs.c realtimeISRs.c miscISRs.c xgateVectors.c
# Combined source code files
SOURCE = freeEMS.c staticInit.c main.c $(UTILCLASSES) $(MATHCLASSES) $(COMCLASSES) $(ISRCLASSES)

# All but the engine position/RPM combined here
CLASSES = $(SOURCE) $(DATA)

# Engine position/RPM here
# Special decoders are not for use running an engine
RPMSPECIAL = Listener.c BenchTest.c
# TODO: Automate file naming for the following 4 lines
RPMEVENTEETH = EvenTeeth-Cam-24and1.c EvenTeeth-Cam-16and1.c EvenTeeth-Cam-6and1.c EvenTeeth-Distributor-4of6and1.c EvenTeeth-Cam-4and1.c
RPMMISSINGTEETH = MissingTeeth-TestFile.c MissingTeeth-Cam-24minus1.c MissingTeeth-Crank-8minus1.c MissingTeeth-Crank-12minus1.c MissingTeeth-Crank-36minus1.c MissingTeeth-Crank-60minus2.c MissingTeeth-Cam-6minus2.c MissingTeeth-Crank-30minus2.c MissingTeeth-Cam-12minus1.c MissingTeeth-Crank-36minus2.c
RPMHALLOROPTICAL = HallOrOptical-Distributor-4of64.c HallOrOptical-Distributor-4of90.c
RPMVRDISTRIBUTOR = 
# Specific purpose per engine stuff here
RPMMITSISTYLE = MitsiAndMazda-CAS-4and1.c MitsiAndMazda-CAS-4and2.c
RPMHONDASTYLE = JSeries-12CrankWith6-2Cam.c R18A1-13CrankWith5Cam.c
RPMNISSANSTYLE = GM-LT1-CAS-360and8.c
# Insert your file above and get coding!
RPMSPECIFICENGINES = $(RPMMITSISTYLE) $(RPMHONDASTYLE) $(RPMNISSANSTYLE)
RPMCLASSESRAW = $(RPMSPECIAL) $(RPMEVENTEETH) $(RPMMISSINGTEETH) $(RPMHALLOROPTICAL) $(RPMVRDISTRIBUTOR) $(RPMSPECIFICENGINES)
RPMCLASSES = $(patsubst %.c,$(DECDIR)/%.c,$(RPMCLASSESRAW))

# XGATE stuff here!
XGASMSRCS = xgate.s
