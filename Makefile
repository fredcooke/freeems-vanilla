# Top level convenience make file

Help:
	@echo
	@echo "######################## Welcome to FreeEMS! ########################"
	@echo
	@echo "To build, choose a target from the below list and type 'make target'!"
	@echo "For example, to build blank unconfigured firmware type 'make BLANK'"
	@echo "Note: For BenchTest to work you MUST build using the BENCHTEST target!"
	@echo "Advanced users can find more options available in the src/main directory!"
	@echo
	@echo "Options:"
	@echo
	@make -qp | awk -F':' '/^[a-zA-Z0-9][^$$#\/\t=]*:([^=]|$$)/ {split($$1,A,/ /);for(i in A)print A[i]}'

TEST_AND_SAVE_ALL:
	cd src/main; ../../bin/testclibuilds.bash

BLANK:
	cd src/main; make clean s19

clean:
	cd src/main; make clean

SPECIAL: # Can use a dependency here instead. 
	cd src/main; make clean EvenTeeth-Distributor-4of6and1


# Other special builds

BENCHTEST:
	cd src/main; CLIFLAGS="DEFAULT" make clean BenchTest
TRUCK:
	cd src/main; CLIFLAGS="$@" make clean MitsiAndMazda-CAS-4and1
HOTEL:
	cd src/main; CLIFLAGS="$@" make clean HallOrOptical-Distributor-4of90
PRESTO:
	cd src/main; CLIFLAGS="$@" make clean EvenTeeth-Cam-24and1
SEANKLT1:
	cd src/main; CLIFLAGS="$@" make clean GM-LT1-CAS-360and8
SNOTROCKET:
	cd src/main; CLIFLAGS="$@" make clean EvenTeeth-Cam-24and1
SPUDMN:
	cd src/main; CLIFLAGS="$@" make clean MissingTeeth-Crank-8minus1
SLATER:
	cd src/main; CLIFLAGS="$@" make clean MissingTeeth-Crank-12minus1
PETERJSERIES:
	cd src/main; CLIFLAGS="$@" make clean JSeries-12CrankWith6-2Cam
DEUCECOUPE:
	cd src/main; CLIFLAGS="$@" make clean EvenTeeth-Cam-6and1
PETERTRUCK:
	cd src/main; CLIFLAGS="$@" make clean MissingTeeth-Cam-12minus1
SCAVENGER:
	cd src/main; CLIFLAGS="$@" make clean MitsiAndMazda-CAS-4and2
DEUCES10:
	cd src/main; CLIFLAGS="$@" make clean EvenTeeth-Cam-4and1
