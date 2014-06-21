#	FreeEMS - the open source engine management system
#
#	release.mk
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
#                     Release Procedure Target Definitions                     #
################################################################################


# Debian only :-p
testgit:
	@echo "################################################################################"
	@echo "#                            Checking git status...                            #"
	@echo "################################################################################"
	@echo "Are we on master?"
	test `git symbolic-ref HEAD` = refs/heads/master
	@echo "Is everything checked in?"
	test `git status -s | wc -l` -eq 0
	@echo "Fetching from origin..."
	git fetch
	@echo "Are we behind?"
	test `git rev-list \`git show-ref --hash refs/heads/master\`..\`git show-ref --hash refs/remotes/origin/master\` | wc -l` -eq 0
	@echo "Are we ahead?"
	test `git rev-list \`git show-ref --hash refs/remotes/origin/master\`..\`git show-ref --hash refs/heads/master\` | wc -l` -eq 0


md5sumsmsg:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                            Generating MD5 Sums...                            #$(Q)
	@echo $(Q)################################################################################$(Q)

md5sums: s19 md5sumsmsg $(ALLMD5S)

$(FIRMWAREDISTRIBUTIONDIR)/%.s19.md5: $(S19DIR)/%.s19 distributiondir
	$(MD5SUM) $< > $@


sha1sumsmsg:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                           Generating SHA1 Sums...                            #$(Q)
	@echo $(Q)################################################################################$(Q)

sha1sums: s19 sha1sumsmsg $(ALLSHA1S)

$(FIRMWAREDISTRIBUTIONDIR)/%.s19.sha1: $(S19DIR)/%.s19 distributiondir
	$(SHASUM) $< > $@




s19zipsmsg:
	@echo $(Q)################################################################################$(Q)
	@echo $(Q)#                                Zipping S19s...                               #$(Q)
	@echo $(Q)################################################################################$(Q)

s19zips: s19 s19zipsmsg $(ALLS19ZIPS)

$(FIRMWAREDISTRIBUTIONDIR)/%.s19.zip: $(S19DIR)/%.s19 distributiondir
	zip -j $@ $<


tagmessage:
	vim $(RELTAG)

tagname:
	vim $(TAGNAME)


tagrelease: tagname tagmessage
	git tag -F $(RELTAG) `cat $(TAGNAME)` HEAD


zipmain: distributiondir
	cd ../../ ; git archive --format=zip --prefix=$(LABEL)/ HEAD > ./tmp/$(DISTRIBUTIONDIR)/$(LABEL)-full.zip;cd -

zipdocs: distributiondir
	cd ../../ ; git archive --format=zip --prefix=$(LABEL)- HEAD docs/ > ./tmp/$(DISTRIBUTIONDIR)/$(LABEL)-docs.zip;cd -

gendoxy: clean
	cd ../../ ; ( cat docs/Doxyfile ; echo "PROJECT_NUMBER=$(FIRMWARE_VERSION)" ) | doxygen - | grep Warning > src/doxygen.output;cd -

zipsite: distributiondir gendoxy
	cd ../../docs/ ; zip -r  $(DISTRIBUTIONDIR)/$(LABEL)-doxygen-html.zip doxygen-html/;cd -

zipsrc: distributiondir
	cd ../../ ; git archive --format=zip --prefix=$(LABEL)- HEAD src/ > ./tmp/$(DISTRIBUTIONDIR)/$(LABEL)-src.zip;cd -

deploy: distributiondir
	scp -r $(DISTRIBUTIONDIR) raptor:/home/firmware/releases/

deploydoxy: zipsite
	scp -r $(DISTRIBUTIONDIR)/$(LABEL)-doxygen-html.zip raptor:/home/docs/releases/
	ssh raptor unzip /home/docs/releases/$(LABEL)-doxygen-html.zip -d /home/docs/releases/
	ssh raptor mv /home/docs/releases/doxygen-html/ /home/docs/releases/$(FIRMWARE_VERSION)
