#	FreeEMS - the open source engine management system
#
#	decoders.mk
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
#                            Single Decoder Builds                             #
################################################################################


Listener: $(S19DIR)/$(LABEL)-Listener.s19
BenchTest: $(S19DIR)/$(LABEL)-BenchTest.s19
EvenTeeth-Cam-24and1: $(S19DIR)/$(LABEL)-EvenTeeth-Cam-24and1.s19
EvenTeeth-Cam-16and1: $(S19DIR)/$(LABEL)-EvenTeeth-Cam-16and1.s19
EvenTeeth-Cam-6and1:  $(S19DIR)/$(LABEL)-EvenTeeth-Cam-6and1.s19
EvenTeeth-Cam-4and1:  $(S19DIR)/$(LABEL)-EvenTeeth-Cam-4and1.s19
MissingTeeth-Crank-8minus1:  $(S19DIR)/$(LABEL)-MissingTeeth-Crank-8minus1.s19
MissingTeeth-Crank-12minus1: $(S19DIR)/$(LABEL)-MissingTeeth-Crank-12minus1.s19
MissingTeeth-Cam-12minus1:   $(S19DIR)/$(LABEL)-MissingTeeth-Cam-12minus1.s19
HallOrOptical-Distributor-4of90: $(S19DIR)/$(LABEL)-HallOrOptical-Distributor-4of90.s19
MitsiAndMazda-CAS-4and1: $(S19DIR)/$(LABEL)-MitsiAndMazda-CAS-4and1.s19
MitsiAndMazda-CAS-4and2: $(S19DIR)/$(LABEL)-MitsiAndMazda-CAS-4and2.s19
GM-LT1-CAS-360and8: $(S19DIR)/$(LABEL)-GM-LT1-CAS-360and8.s19 
JSeries-12CrankWith6-2Cam: $(S19DIR)/$(LABEL)-JSeries-12CrankWith6-2Cam.s19
EvenTeeth-Distributor-4of6and1: $(S19DIR)/$(LABEL)-EvenTeeth-Distributor-4of6and1.s19
MissingTeeth-Crank-36minus2: $(S19DIR)/$(LABEL)-MissingTeeth-Crank-36minus2.s19
R18A1-13CrankWith5Cam: $(S19DIR)/$(LABEL)-R18A1-13CrankWith5Cam.s19
