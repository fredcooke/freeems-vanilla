#	FreeEMS - the open source engine management system
#
#	Copyright 2008, 2009 Fred Cooke
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
#                                                                              #
#   This Makefile is designed to be run with GNU make! Accept no substitute!   #
#                                                                              #
################################################################################
#                                                                              #
#   Top level targets:                                                         #
#                                                                              #
#   make:                                                                      #
#       Builds all output files in the slow multi stage way with all debugging #
#   make fast:                                                                 #
#       Compiles from C straight to objects, links to elfs and copies to s19s  #
#   make clean:                                                                #
#       Permanently removes all build artifact files and directories           #
#   make release:                                                              #
#       Cleans the project, builds it from scratch, copies the s19 files up to #
#       the firmware directory, zips each s19 separately, zips all of the      #
#       documentation, cleans the project again and lastly zips the entire     #
#       project directory                                                      #
#                                                                              #
################################################################################
#                                                                              #
#   When doing a full build the following steps are taken:                     #
#                                                                              #
#    1) Pre-process all of the C files                                         #
#    2) Compile all preprocessed C files into assembly files                   #
#    3) Assemble all assembly files into object files                          #
#    4) Dump the contents of all object files                                  #
#    5) Link one decoder with garbage collection and reporting turned on       #
#    6) Link each decoder without garbage collection                           #
#    7) Dump the contents of each decoders elf                                 #
#    8) Produce a memory map for each elf                                      #
#    9) Produce a readelf dump for each elf                                    #
#   10) Produce an s19 loadable firmware file for each elf                     #
#                                                                              #
################################################################################




################################################################################
#                             All Fixed Variables                              #
################################################################################


# Constants
VERSION = 0.0.19
OUTPREFIX = freeems

# Directories here
RELEASEDIR = ../firmware
INCDIR = inc
BUGDIR = debug
OUTDIR = output
OBJDIR = objects
ASMDIR = assembly
S19DIR = firmware
PPCDIR = preprocessedc

# Set the windows/non debian path first and then overwrite
# with the debian one so we can grep the deb line out and
# end up with a working windows make file in an automated
# way. Additionally, please ensure you do not add any sets
# of three . . . in a row or the line will be missing from
# the windows version. Likewise sets of ### longer than 6
# or so are also at risk :-)
PREFIX = m6811-elf-
PREFIX = m68hc11-
PATHSEP = \\
PATHSEP = /#...

# All of the tools
CP = cp
RM = rm -rf
MKDIR = mkdir
MKDIR = mkdir -p #...
ZIP = zip
GCC = $(PREFIX)gcc
COPY = $(PREFIX)objcopy
DUMP = $(PREFIX)objdump
NM = $(PREFIX)nm
RE = $(PREFIX)readelf
SIZE = $(PREFIX)size




################################################################################
#                               All Source Files                               #
################################################################################


# Indirect dependencies - any header change means a full
# recompile. This can be improved upon and made more specific.
MAINH = main.h
INITH = init.h
UTILH = utils.h
MFILE = Makefile
ISRH = interrupts.h
CINCS = injectorISR.c
FLASHH = flashWrite.h
ASMH = 9S12XDP512asm.s
LOOKUPH = tableLookup.h
WMFILE = Makefile.windows
ISRSH = commsISRs.h injectionISRs.h
COMMSH = commsCore.h blockDetailsLookup.h
LINKER = memory.x regions.x hc9s12xdp512elfb.x
GLOBALH1 = freeEMS.h 9S12XDP512.h memory.h globalConstants.h structs.h
GLOBALH2 = globalDefines.h errorDefines.h TunableConfigs.h FixedConfigs.h
FUELH = fuelAndIgnitionCalcs.h derivedVarsGenerator.h coreVarsGenerator.h
RPMH = NipponDenso.h LT1-360-8.h Subaru-36-2-2-2.h MissingTeeth.h MiataNB.h

# Let's keep this to a bare minimum! If you write ASM code
# please provide an matching alternate C implementation too.
HANDASMS = flashBurn.s
#RPMHANDASMS = 

# .c files from inc/ should be included here as deps for the parts they are relied on by!!
ALLHEADERS1 = $(GLOBALH1) $(COMMSH) $(ISRSH) $(UTILH) $(RPMH) $(FLASHH)
ALLHEADERS2 = $(GLOBALH2) $(FUELH) $(MAINH) $(INITH) $(ISRH) $(LOOKUPH)
ALLH1 = $(patsubst %.h,$(INCDIR)/%.h,$(ALLHEADERS1))
ALLH2 = $(patsubst %.h,$(INCDIR)/%.h,$(ALLHEADERS2))
ALLH3 = $(patsubst %.c,$(INCDIR)/%.c,$(CINCS))
ALLH4 = $(LINKER) $(MFILE) $(INCDIR)/$(ASMH)
ALLH = $(ALLH1) $(ALLH2) $(ALLH3) $(ALLH4)

# Warning : do not include .c files from inc/ as they are
# included into the other C files and automatically compiled.

# Flash data files
FIXEDCLASSES = FixedConfig1.c FixedConfig2.c
LOOKUPCLASSES1 = IATTransferTable.c CHTTransferTable.c
LOOKUPCLASSES2 = MAFTransferTable.c TestTransferTable.c
FUELCLASSES = FuelTables.c FuelTables2.c
TIMECLASSES = TimingTables.c TimingTables2.c
TUNECLASSES = TunableConfig.c TunableConfig2.c

# Source code files
UTILCLASSES = tableLookup.c init.c utils.c globalConstants.c
MATHCLASSES = coreVarsGenerator.c derivedVarsGenerator.c fuelAndIgnitionCalcs.c
COMCLASSES = flashWrite.c commsCore.c blockDetailsLookup.c
ISRCLASSES = interrupts.c injectionISRs.c ignitionISRs.c commsISRs.c realtimeISRs.c miscISRs.c

# All but the engine position/RPM combined here
SOURCE = freeEMS.c staticInit.c main.c $(UTILCLASSES) $(MATHCLASSES) $(COMCLASSES) $(ISRCLASSES)
DATA = $(FIXEDCLASSES) $(LOOKUPCLASSES1) $(LOOKUPCLASSES2) $(FUELCLASSES) $(TIMECLASSES) $(TUNECLASSES)
CLASSES = $(SOURCE) $(DATA)

# Engine position/RPM here
RPMCLASSES = NipponDenso.c LT1-360-8.c Subaru-36-2-2-2.c MissingTeeth.c MiataNB.c
# future rpm = NissanRB2X.c NissanSR20.c MiataNA.c etc... Insert your file above and get coding!


# Convert extensions
PREPROCESSED = $(patsubst %.c,$(PPCDIR)/%.pp.c,$(CLASSES))
ASSEMBLIES = $(patsubst %.c,$(ASMDIR)/%.s,$(CLASSES))
OBJECTS = $(patsubst %.c,$(OBJDIR)/%.o,$(CLASSES)) $(patsubst %.s,$(OBJDIR)/%.o,$(HANDASMS))
DUMPS = $(patsubst %.c,$(BUGDIR)/%.dmp,$(CLASSES)) $(patsubst %.s,$(BUGDIR)/%.dmp,$(HANDASMS))

# Convert RPM extensions
PREPROCESSEDRPM = $(patsubst %.c,$(PPCDIR)/%.pp.c,$(RPMCLASSES))
ASSEMBLIESRPM = $(patsubst %.c,$(ASMDIR)/%.s,$(RPMCLASSES))
OBJECTSRPM = $(patsubst %.c,$(OBJDIR)/%.o,$(RPMCLASSES)) #$(patsubst %.s,$(OBJDIR)/%.o,$(RPMHANDASMS))
DUMPSRPM = $(patsubst %.c,$(BUGDIR)/%.dmp,$(RPMCLASSES)) #$(patsubst %.s,$(BUGDIR)/%.dmp,$(RPMHANDASMS))

# Convert to output files
ALLELFSC = $(patsubst %.c,$(OUTDIR)/$(OUTPREFIX)-$(VERSION)-%.elf,$(RPMCLASSES))
ALLELFSASM = #$(patsubst %.s,$(OUTDIR)/$(OUTPREFIX)-$(VERSION)-%.elf,$(RPMHANDASMS))
ALLDMPSC = $(patsubst %.c,$(BUGDIR)/$(OUTPREFIX)-$(VERSION)-%.dmp,$(RPMCLASSES))
ALLDMPSASM = #$(patsubst %.s,$(BUGDIR)/$(OUTPREFIX)-$(VERSION)-%.dmp,$(RPMHANDASMS))
ALLMAPSC = $(patsubst %.c,$(BUGDIR)/$(OUTPREFIX)-$(VERSION)-%.map,$(RPMCLASSES))
ALLMAPSASM = #$(patsubst %.s,$(BUGDIR)/$(OUTPREFIX)-$(VERSION)-%.map,$(RPMHANDASMS))
ALLREADC = $(patsubst %.c,$(BUGDIR)/$(OUTPREFIX)-$(VERSION)-%.ree,$(RPMCLASSES))
ALLREADASM = #$(patsubst %.s,$(BUGDIR)/$(OUTPREFIX)-$(VERSION)-%.ree,$(RPMHANDASMS))
ALLS19SC = $(patsubst %.c,$(S19DIR)/$(OUTPREFIX)-$(VERSION)-%.s19,$(RPMCLASSES))
ALLS19SASM = #$(patsubst %.s,$(S19DIR)/$(OUTPREFIX)-$(VERSION)-%.s19,$(RPMHANDASMS))
ALLELFS = $(ALLELFSC) $(ALLELFSASM)
ALLDMPS = $(ALLDMPSC) $(ALLDMPSASM)
ALLMAPS = $(ALLMAPSC) $(ALLMAPSASM)
ALLREAD = $(ALLREADC) $(ALLREADASM)
ALLS19S = $(ALLS19SC) $(ALLS19SASM)

# Convert to output files for GC variants
GCDELFSC = $(patsubst %.c,$(OUTDIR)/$(OUTPREFIX)-$(VERSION)-%.gc.elf,$(RPMCLASSES))
GCDELFSASM = #$(patsubst %.s,$(OUTDIR)/$(OUTPREFIX)-$(VERSION)-%.gc.elf,$(RPMHANDASMS))
GCDS19SC = $(patsubst %.c,$(S19DIR)/$(OUTPREFIX)-$(VERSION)-%.gc.s19,$(RPMCLASSES))
GCDS19SASM = #$(patsubst %.s,$(S19DIR)/$(OUTPREFIX)-$(VERSION)-%.gc.s19,$(RPMHANDASMS))
GCDELFS = $(GCDELFSC) $(GCDELFSASM)
GCDS19S = $(GCDS19SC) $(GCDELFSASM)




################################################################################
#                           All Command Line Options                           #
################################################################################


# M68hc1x GCC Options we may want : -minmax  -mlong-calls

# http://www.gnu.org/software/m68hc11/m68hc11_gcc.html shows code size with different options used
# include debug info, optimise , 16 bit ints, hcs12 platform
GCCOPTS1 = -g -Wall -Werror -Winline -O -m68hcs12 -mshort -ffunction-sections
GCCOPTS2 = -fomit-frame-pointer -msoft-reg-count=8 -mauto-incdec -fsigned-char
GCCOPTS = $(GCCOPTS1) $(GCCOPTS2)
# -ffunction-sections option splits out the functions such that the garbage collection can get
# them on a per section basis. I'm not sure, but this could be harmful to paged code so may
# have to review this at a later date perhaps splitting paged functions from nonpaged ones.

# pass to linker, link for hc12
# The vectors address in the linker options is the VMA address and must be short form 0xF710, not a paged address.
LINKOPTS = -Wl,-defsym,vectors_addr=0xF710,-m,m68hc12elfb,-T,hc9s12xdp512elfb.x
LINKOPTSGC = -Wl,--gc-sections,--print-gc-sections,-defsym,vectors_addr=0xF710,-m,m68hc12elfb,-T,hc9s12xdp512elfb.x
# Use this to get a map dump when the linker fails in a confusing way : --print-map

# If using the below option for paged flash, the ADDRESS_TYPE
# field in the freeEMSloader script should be updated to match.
COPYOPTS =  --output-target=srec \
		--change-section-lma .fixedconf1+0xFD4000 \
		--change-section-lma .fixedconf2+0xFD4000 \
		     --change-section-lma .text1+0xFD4000 \
		      --change-section-lma .text+0xFEC000 \
		      --change-section-lma .data+0xFEC000 \
		   --change-section-lma .vectors+0xFEC000 \
		    --change-section-lma .rodata+0xFEC000 \
		--only-section=.fixedconf1 \
		--only-section=.fixedconf2 \
		--only-section=.text \
		--only-section=.text1 \
		--only-section=.data \
		--only-section=.vectors \
		--only-section=.rodata \
		--change-section-lma .ppageF8=0xF88000 \
		--change-section-lma .fpageF9=0xF98000 \
		--change-section-lma .dpageF9=0xF9A000 \
		--change-section-lma .ppageFE=0xFE8000 \
		--only-section=.ppageF8 \
		--only-section=.fpageF9 \
		--only-section=.dpageF9 \
		--only-section=.ppageFE \
		--change-section-lma .fpageFA=0xFA8000 \
		--change-section-lma .dpageFA=0xFAA000 \
		--change-section-lma .fpageFB=0xFB8000 \
		--change-section-lma .dpageFB1=0xFBA000 \
		--change-section-lma .dpageFB2=0xFBA400 \
		--change-section-lma .dpageFB3=0xFBA800 \
		--change-section-lma .dpageFB4=0xFBAC00 \
		--change-section-lma .dpageFB5=0xFBB000 \
		--change-section-lma .dpageFB6=0xFBB400 \
		--change-section-lma .dpageFB7=0xFBB800 \
		--change-section-lma .dpageFB8=0xFBBC00 \
		--change-section-lma .fpageFC=0xFC8000 \
		--change-section-lma .dpageFC=0xFCA000 \
		--only-section=.dpageFA \
		--only-section=.fpageFA \
		--only-section=.dpageFB1 \
		--only-section=.dpageFB2 \
		--only-section=.dpageFB3 \
		--only-section=.dpageFB4 \
		--only-section=.dpageFB5 \
		--only-section=.dpageFB6 \
		--only-section=.dpageFB7 \
		--only-section=.dpageFB8 \
		--only-section=.fpageFB \
		--only-section=.dpageFC \
		--only-section=.fpageFC
#		--change-section-lma .ppageFD=0xFD8000 \
#		--change-section-lma .ppageFF=0xFF8000 \
#		--only-section=.ppageFD \	This is left here for clarity only (equivalent to text1 but paged)
#		--only-section=.ppageFF		This is left here for clarity only (equivalent to text but paged)
# Changes to the above options should be reflected in memory.x and memory.h also!

# The following flash areas can only be used once Sean has written his loader app :
#		--only-section=.ppageE0 \
#		--only-section=.ppageE1 \
#		--only-section=.ppageE2 \
#		--only-section=.ppageE3 \
#		--only-section=.ppageE4 \
#		--only-section=.ppageE5 \
#		--only-section=.ppageE6 \
#		--only-section=.ppageE7 \
#		--only-section=.ppageE8 \
#		--only-section=.ppageE9 \
#		--only-section=.ppageEA \
#		--only-section=.ppageEB \
#		--only-section=.ppageEC \
#		--only-section=.ppageED \
#		--only-section=.ppageEE \
#		--only-section=.ppageEF \
#		--only-section=.ppageF0 \
#		--only-section=.ppageF1 \
#		--only-section=.ppageF2 \
#		--only-section=.ppageF3 \
#		--only-section=.ppageF4 \
#		--only-section=.ppageF5 \
#		--only-section=.ppageF6 \
#		--only-section=.ppageF7 \
#		--change-section-lma .ppageE0=0xE08000 \
#		--change-section-lma .ppageE1=0xE18000 \
#		--change-section-lma .ppageE2=0xE28000 \
#		--change-section-lma .ppageE3=0xE38000 \
#		--change-section-lma .ppageE4=0xE48000 \
#		--change-section-lma .ppageE5=0xE58000 \
#		--change-section-lma .ppageE6=0xE68000 \
#		--change-section-lma .ppageE7=0xE78000 \
#		--change-section-lma .ppageE8=0xE88000 \
#		--change-section-lma .ppageE9=0xE98000 \
#		--change-section-lma .ppageEA=0xEA8000 \
#		--change-section-lma .ppageEB=0xEB8000 \
#		--change-section-lma .ppageEC=0xEC8000 \
#		--change-section-lma .ppageED=0xED8000 \
#		--change-section-lma .ppageEE=0xEE8000 \
#		--change-section-lma .ppageEF=0xEF8000 \
#		--change-section-lma .ppageF0=0xF08000 \
#		--change-section-lma .ppageF1=0xF18000 \
#		--change-section-lma .ppageF2=0xF28000 \
#		--change-section-lma .ppageF3=0xF38000 \
#		--change-section-lma .ppageF4=0xF48000 \
#		--change-section-lma .ppageF5=0xF58000 \
#		--change-section-lma .ppageF6=0xF68000 \
#		--change-section-lma .ppageF7=0xF78000 \



help:
	################################################################################
	#                        Dependency And Target Summary                         #
	################################################################################
	#                                                                              #
	#   Common targets:                                                            #
	#                                                                              #
	#       1) help - This comment block                                           #
	#       2) all - Executes alldebug, slow, slowgc and size                      #
	#       3) fast - Compiles direct to object code and links once with no debug  #
	#       4) slow - Three stage compilation with assembly retained               #
	#       5) slowgc - As above, but with garbage collection during linking       #
	#       6) alldebug - Generates all debug output files                         #
	#       7) install - Not yet implemented                                       #
	#       8) release - Not yet implemented                                       #
	#       9) clean - Removes all files and directories generated by building     #
	#                                                                              #
	#   Second level targets:                                                      #
	#                                                                              #
	#       Stage one:                                                             #
	#                                                                              #
	#           1) preprocess - run the C preprocessor over the raw C files        #
	#           2) compile - compile the preprocessed C into assembly              #
	#           3) assemble - assemble the assembly files into object files        #
	#                                                                              #
	#       Stage two                                                              #
	#                                                                              #
	#           1) link - Generate ELFs objects                                    #
	#           2) gclink - As above, but with garbage collection                  #
	#           3) s19 - Create s19s from elfs                                     #
	#           4) gcs19 - Create s19s from gc elfs                                #
	#                                                                              #
	#       Stage three:                                                           #
	#                                                                              #
	#           1) maps - Memory map files                                         #
	#           2) rees - Readelf dumps                                            #
	#           3) elfdmps - Classic objdump output for final elfs                 #
	#           4) objdmps - Classic objdump output for each object file           #
	#                                                                              #
	################################################################################




################################################################################
#                           All Target Dependencies                            #
################################################################################


# Build everything the long way
all: alldebug gcs19 s19 size
# Single stage compilation
fast: single s19 size
# Multi stage compilation
slow: s19 size
# Multi stage compilation with garbage collection
slowgc: gcs19 size #...
# Clean all except release
clean: cleanasm cleanobj cleanout cleanppc cleans19 cleandebug
# Generate all debug
alldebug: maps rees elfdmps objdmps
# Load the s19 of your choice
#install: clean fast loader
# Perform a release
#release: clean cleanrelease fast someMoreStuffHere checksums zipping etc




################################################################################
#                           Debug Target Definitions                           #
################################################################################


mapsmsg:
	################################################################################
	#                          Generating memory maps....                          #
	################################################################################

maps: link $(BUGDIR) mapsmsg $(ALLMAPS)

$(ALLMAPS): $(BUGDIR)/%.map: $(OUTDIR)/%.elf
	$(NM) $< | sort > $@


reesmsg:
	################################################################################
	#                           Reading all elf files...                           #
	################################################################################

rees: link $(BUGDIR) reesmsg $(ALLREAD)

$(ALLREAD): $(BUGDIR)/%.ree: $(OUTDIR)/%.elf
	$(RE) -a -W $< > $@


elfdmpsmsg:
	################################################################################
	#                           Dumping all elf files...                           #
	################################################################################

elfdmps: link $(BUGDIR) elfdmpsmsg $(ALLDMPS)

$(ALLDMPS): $(BUGDIR)/%.dmp: $(OUTDIR)/%.elf
	$(DUMP) -spSd $< > $@


objdmpmsg:
	################################################################################
	#                         Dumping all object files....                         #
	################################################################################

objdmps: assemble $(BUGDIR) objdmpmsg $(DUMPS) $(DUMPSRPM)

$(DUMPS) $(DUMPSRPM): $(BUGDIR)/%.dmp: $(OBJDIR)/%.o
	$(DUMP) -spSd $< > $@




################################################################################
#                 Fast Single Stage Compile Target Definition                  #
################################################################################


single:
	# TODO fast compile and figure out overlapping dependencies...




################################################################################
#                       Link and Copy Target Definitions                       #
################################################################################


linkmsg: #...
	################################################################################
	#                      Linking the Objects into an ELF...                      #
	################################################################################

link: assemble $(OUTDIR) linkmsg $(ALLELFS)

# link the object files into an elf executable
$(ALLELFS): $(OUTDIR)/$(OUTPREFIX)-$(VERSION)-%.elf: $(OBJDIR)/%.o $(OBJECTS)
	################################################################################
	#               Linking $@ ...
	################################################################################
	$(GCC) $(GCCOPTS) $(LINKOPTS) -o $@ $< $(OBJECTS)


gclinkmsg: #...
	################################################################################
	#                      Linking the Objects into an ELF...                      #
	################################################################################

gclink: assemble $(OUTDIR) linkmsg $(GCDELFS) #...

# link the object files into an elf executable with gc...
$(GCDELFS): $(OUTDIR)/$(OUTPREFIX)-$(VERSION)-%.gc.elf: $(OBJDIR)/%.o $(OBJECTS) #...
	################################################################################
	#               Linking $@ ...
	################################################################################
	$(GCC) $(GCCOPTS) $(LINKOPTSGC) -o $@ $< $(OBJECTS) # ...
# The links with garbage collection are to ensure that there are no warnings ...
# TODO find out how to stop .tramp from being collected (or inserted)! ...


s19msg: #...
	################################################################################
	#                          Building The S19 Files....                          #
	################################################################################

s19: link $(S19DIR) s19msg $(ALLS19S)
# the gc dependency is temporary until i figure out if the .tramp removal is an issue or not.

# Generate the loadable s19 firmware files
$(ALLS19S): $(S19DIR)/%.s19: $(OUTDIR)/%.elf
	################################################################################
	#               Building $@ ...
	################################################################################
	$(COPY) $(COPYOPTS) $< $@
	################################################################################
	#               Measuring $@ ...
	################################################################################
	echo "Flash image size of $@ is" `echo \`cat $@ | wc -l\` "* 16" | bc -l` "bytes..."


gcs19msg: #...
	################################################################################
	#                          Building The S19 Files....                          #
	################################################################################

gcs19: gclink $(S19DIR) gcs19msg  $(GCDS19S) #...

# Generate the garbage collected s19 files temporarily...
$(GCDS19S): $(S19DIR)/%.s19: $(OUTDIR)/%.elf #...
	################################################################################
	#               Building $@ ...
	################################################################################
	$(COPY) $(COPYOPTS) $< $@ #...
	################################################################################
	#               Measuring $@ ...
	################################################################################
	echo "Flash image size of $@ is" `echo \`cat $@ | wc -l\` "* 16" | bc -l` "bytes..."




################################################################################
#                     Size Measuring Target Definition                         #
################################################################################


size: # TODO this should be run for each s19 target with only the one rpm .o file
	################################################################################
	#                          Measuring The Decoder Binaries...                   #
	################################################################################
	$(SIZE) $(OBJECTSRPM)
	################################################################################
	#                          Measuring All Other Binaries...                     #
	################################################################################
	$(SIZE) -t $(OBJECTS)
	################################################################################
	#                    Add one decoder to the total above and                    #
	#                   subtract the size reported for freeEMS.o                   #
	#                   this will give you the actual image size                   #
	################################################################################
	#                                                                              #
	#                  Thank you for building FreeEMS firmware!!!                  #
	#                                                                              #
	################################################################################




################################################################################
#              Preprocess, Compile and Assemble Target Definitions             #
################################################################################


preprocessmsg: #...
	################################################################################
	#                        Running the C Pre Processor...                        #
	################################################################################

preprocess: $(PPCDIR) preprocessmsg $(PREPROCESSED) $(PREPROCESSEDRPM)

# Generate preprocessed source files to examine
$(PREPROCESSED) $(PREPROCESSEDRPM): $(PPCDIR)/%.pp.c: %.c $(ALLH)
	$(GCC) $(GCCOPTS) -E $< > $@


compilemsg: #...
	################################################################################
	#                         Compiling PPC to Assembly...                         #
	################################################################################

compile: preprocess compilemsg $(ASSEMBLIES) $(ASSEMBLIESRPM)

# Generate assembly files to examine
$(ASSEMBLIES) $(ASSEMBLIESRPM): $(ASMDIR)/%.s: $(PPCDIR)/%.pp.c
	$(GCC) $(GCCOPTS) -x cpp-output -S -o $@ $<


assemblemsg: #...
	################################################################################
	#                          Assembling Object Files...                          #
	################################################################################

assemble: compile $(OBJDIR) assemblemsg $(OBJECTS) $(OBJECTSRPM)

# Generate object files to link
$(OBJECTS) $(OBJECTSRPM): $(OBJDIR)/%.o: $(ASMDIR)/%.s
	$(GCC) $(GCCOPTS) -c -o $@ $<




################################################################################
#                     Release Procedure Target Definitions                     #
################################################################################

### clean all

#check git status for changes, fail build if not fully commited

### build all

#copy s19s up

#md5sum/sha1sum s19s above

### clean all

#git commit s19s

#zip each s19 to parent

#zip docs to parent

#zip without docs to parent

#zip entire directory to parent




################################################################################
#                     Create Directory Target Definitions                      #
################################################################################

# Assembly, release and inc directories don't get removed.

$(BUGDIR):
	################################################################################
	#                       Creating the debug directory....                       #
	################################################################################
	$(MKDIR) $(BUGDIR)$(PATHSEP)hack
	rmdir $(BUGDIR)$(PATHSEP)hack

$(S19DIR):
	################################################################################
	#                      Creating the firmware directory...                      #
	################################################################################
	$(MKDIR) $(S19DIR)$(PATHSEP)hack
	rmdir $(S19DIR)$(PATHSEP)hack

$(PPCDIR):
	################################################################################
	#                   Creating the preprocessedc directory....                   #
	################################################################################
	$(MKDIR) $(PPCDIR)$(PATHSEP)hack
	rmdir $(PPCDIR)$(PATHSEP)hack

$(OUTDIR):
	################################################################################
	#                       Creating the output directory...                       #
	################################################################################
	$(MKDIR) $(OUTDIR)$(PATHSEP)hack
	rmdir $(OUTDIR)$(PATHSEP)hack

$(OBJDIR):
	################################################################################
	#                       Creating the object directory...                       #
	################################################################################
	$(MKDIR) $(OBJDIR)$(PATHSEP)hack
	rmdir $(OBJDIR)$(PATHSEP)hack




################################################################################
#                            Clean Target Definitions                          #
################################################################################

cleanasm:
	################################################################################
	#                     Removing generated assembly files....                    #
	################################################################################
	$(RM) $(ASSEMBLIES) $(ASSEMBLIESRPM)

cleanppc:
	################################################################################
	#                  Removing pre-processed C output directory...                #
	################################################################################
	$(RM) $(PPCDIR)

cleanobj:
	################################################################################
	#                         Removing object directory...                         #
	################################################################################
	$(RM) $(OBJDIR)

cleanout:
	################################################################################
	#                       Removing link output directory...                      #
	################################################################################
	$(RM) $(OUTDIR)

cleans19:
	################################################################################
	#                           Removing s19 directory...                          #
	################################################################################
	$(RM) $(S19DIR)

cleandebug:
	################################################################################
	#                          Removing debug directory...                         #
	################################################################################
	$(RM) $(BUGDIR)

cleanrelease:
	################################################################################
	#                         Removing all release files...                        #
	################################################################################
	$(RM) $(RELEASEDIR)/*.zip
	$(RM) $(RELEASEDIR)/*.s19
	$(RM) $(RELEASEDIR)/*.md5
	$(RM) $(RELEASEDIR)/*.sha1




################################################################################
#                   Declare targets that aren't real files                     #
################################################################################


# Aggregators top level
.PHONY: all fast slow slowgc single help

# Aggregators middle level
.PHONY: preprocess compile assemble link gclink s19 gcs19

# Aggregators debug level
.PHONY: alldebug maps rees objdmps elfdmps

# Messages
.PHONY: mapsmsg reesmsg elfdmpsmsg objdmpmsg linkmsg gclinkmsg
.PHONY: s19msg gcs19msg preprocessmsg compilemsg assemblemsg

# Clean targets
.PHONY: clean cleanasm cleanppc cleanobj cleanout cleans19 cleandebug cleanrelease
