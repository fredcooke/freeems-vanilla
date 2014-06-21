#	FreeEMS - the open source engine management system
#
#	clean.mk
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
#                            Clean Target Definitions                          #
################################################################################

cleanasm:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                     Removing generated assembly files....                    #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(RM) $(ASMDIR)

cleandep:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                  Removing pre-processed C output directory...                #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(RM) $(DEPDIR)$(PATHSEP)*.d $(DEPDIR)$(PATHSEP)*.dd
	$(RM) $(DEPDIR)$(PATHSEP)$(DECDIR)$(PATHSEP)*.d $(DEPDIR)$(PATHSEP)$(DECDIR)$(PATHSEP)*.dd
	$(RM) $(DEPDIR)$(PATHSEP)$(DATADIR)$(PATHSEP)*.d $(DEPDIR)$(PATHSEP)$(DATADIR)$(PATHSEP)*.dd

cleanppc:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                  Removing pre-processed C output directory...                #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(RM) $(PPCDIR)

cleanobj:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                         Removing object directory...                         #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(RM) $(OBJDIR)

cleanout:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                       Removing link output directory...                      #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(RM) $(OUTDIR)

cleans19:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                           Removing s19 directory...                          #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(RM) $(S19DIR)

cleandebug:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                          Removing debug directory...                         #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(RM) $(BUGDIR)

cleandoxy:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                            Removing Doxygen HTML...                          #$(Q)
	@echo $(Q)################################################################################$(Q)
	$(RM) ../../docs/doxygen-html/
