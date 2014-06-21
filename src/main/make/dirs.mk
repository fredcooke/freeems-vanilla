#	FreeEMS - the open source engine management system
#
#	dirs.mk
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
#                     Create Directory Target Definitions                      #
################################################################################


# Assembly, release and inc directories don't get removed.

dirs: $(BUGDIR) $(S19DIR) $(PPCDIR) $(OUTDIR) $(OBJDIR) $(XGOBJDIR) $(ASMDIR)

$(BUGDIR):
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                       Creating the debug directory....                       #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(MKDIR) $(BUGDIR)$(PATHSEP)$(DECDIR)$(PATHSEP)hack
	rmdir $(BUGDIR)$(PATHSEP)$(DECDIR)$(PATHSEP)hack
	$(MKDIR) $(BUGDIR)$(PATHSEP)$(DATADIR)$(PATHSEP)hack
	rmdir $(BUGDIR)$(PATHSEP)$(DATADIR)$(PATHSEP)hack

$(S19DIR):
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                      Creating the firmware directory...                      #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(MKDIR) $(S19DIR)$(PATHSEP)hack
	rmdir $(S19DIR)$(PATHSEP)hack

$(PPCDIR):
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                   Creating the preprocessedc directory....                   #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(MKDIR) $(PPCDIR)$(PATHSEP)$(DECDIR)$(PATHSEP)hack
	rmdir $(PPCDIR)$(PATHSEP)$(DECDIR)$(PATHSEP)hack
	$(MKDIR) $(PPCDIR)$(PATHSEP)$(DATADIR)$(PATHSEP)hack
	rmdir $(PPCDIR)$(PATHSEP)$(DATADIR)$(PATHSEP)hack

$(ASMDIR):
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                      Creating the assembly directory...                      #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(MKDIR) $(ASMDIR)$(PATHSEP)$(DECDIR)$(PATHSEP)hack
	rmdir $(ASMDIR)$(PATHSEP)$(DECDIR)$(PATHSEP)hack
	$(MKDIR) $(ASMDIR)$(PATHSEP)$(DATADIR)$(PATHSEP)hack
	rmdir $(ASMDIR)$(PATHSEP)$(DATADIR)$(PATHSEP)hack

$(OUTDIR):
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                       Creating the output directory...                       #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(MKDIR) $(OUTDIR)$(PATHSEP)hack
	rmdir $(OUTDIR)$(PATHSEP)hack

$(OBJDIR):
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                       Creating the object directory...                       #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(MKDIR) $(OBJDIR)$(PATHSEP)$(DECDIR)$(PATHSEP)hack
	rmdir $(OBJDIR)$(PATHSEP)$(DECDIR)$(PATHSEP)hack
	$(MKDIR) $(OBJDIR)$(PATHSEP)$(DATADIR)$(PATHSEP)hack
	rmdir $(OBJDIR)$(PATHSEP)$(DATADIR)$(PATHSEP)hack

$(XGOBJDIR):
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                    Creating the xgate object directory...                    #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(MKDIR) $(XGOBJDIR)$(PATHSEP)hack
	rmdir $(XGOBJDIR)$(PATHSEP)hack

distributiondir:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                    Creating the distribution directory...                    #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(MKDIR) $(FIRMWAREDISTRIBUTIONDIR)$(PATHSEP)hack
	rmdir $(FIRMWAREDISTRIBUTIONDIR)$(PATHSEP)hack
