#	FreeEMS - the open source engine management system
#
#	phony.mk
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
#                   Declare targets that aren't real files                     #
################################################################################


# Aggregators top level
.PHONY: all slow slowgc single help dirs

# Aggregators middle level
.PHONY: dependencies preprocess compile assemble link gclink s19 gcs19 sizes gcsizes

# Aggregators debug level
.PHONY: alldebug maps rees objdmps elfdmps size

# Release targets
.PHONY: release relpack1 relpack2 package packagenodoxy publish publishnodoxy
.PHONY: rebuildfull rebuildnodoxy relbuildfirmware deploy deploydoxy
.PHONY: md5sums sha1sums s19zips sha1sumsgc s19zips s19zipsgc
.PHONY: testgit tagname tagmessage tagrelease
.PHONY: zipmain zipdocs zipsite zipsrc

# Messages
.PHONY: mapsmsg reesmsg elfdmpsmsg objdmpmsg linkmsg gclinkmsg
.PHONY: s19msg gcs19msg preprocessmsg compilemsg assemblemsg
.PHONY: md5sumsmsg sha1sumsmsg s19zipsmsg

# Clean targets
.PHONY: clean cleandep cleanasm cleanppc cleanobj cleanout cleans19 cleandebug cleandoxy

# Lonely documentation target :-(
.PHONY: gendoxy
