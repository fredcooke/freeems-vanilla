#	FreeEMS - the open source engine management system
#
#	options.mk
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
#                           All Command Line Options                           #
################################################################################


# M68hc1x GCC Options we may want : -minmax  -mlong-calls

# http://www.gnu.org/software/m68hc11/m68hc11_gcc.html shows code size with different options used
# include debug info, optimise , 16 bit ints, hcs12 platform
GCCOPTS1 = -Wall -Werror -Winline -O -m68hcs12 -mshort -ffunction-sections
GCCOPTS2 = -fomit-frame-pointer -msoft-reg-count=8 -mauto-incdec -fsigned-char
GCCOPTS = $(GCCOPTS1) $(GCCOPTS2) $(CLIBUILD) $(CLIFLAGSARG) -D SUPPORT_EMAIL=\"$(SUPPORT_EMAIL)\" -D BUILT_BY_NAME=\"$(BUILT_BY_NAME)\" -D FIRMWARE_VERSION=\"$(FIRMWARE_VERSION)\" -D FIRMWARE_BUILD_DATE=\"$(BUILD_DATE)\" -D OPERATING_SYSTEM=\"$(OS)\"
# -ffunction-sections option splits out the functions such that the garbage collection can get
# them on a per section basis. I'm not sure, but this could be harmful to paged code so may
# have to review this at a later date perhaps splitting paged functions from nonpaged ones.

# pass to linker, link for hc12
# The vectors address in the linker options is the VMA address and must be short form 0xF710, not a paged address.
LINKOPTS = -no-warn-mismatch,-defsym,vectors_addr=0xF710,-m,m68hc12elfb,-T,hc9s12xdp512elfb.x
LINKOPTSGC = -no-warn-mismatch,--gc-sections,--print-gc-sections,-defsym,vectors_addr=0xF710,-m,m68hc12elfb,-T,hc9s12xdp512elfb.x
# Use this to get a map dump when the linker fails in a confusing way : --print-map

# If using the below option for paged flash, the ADDRESS_TYPE
# field in the freeEMSloader script should be updated to match.
COPYOPTS = --output-target=srec \
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
		--change-section-lma .ppageE0X=0xE08800 \
		--change-section-lma .ppageE1=0xE18000 \
		--only-section=.ppageE0X \
		--only-section=.ppageE1 \
		--set-section-flags .ppageE1=alloc,load \
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

# The following flash areas should only be included if they are used.
#		--only-section=.ppageE0S \
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
#		--change-section-lma .ppageE0S=0xE08000 \
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
