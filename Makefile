# Top level convenience make file

Help:
	@echo
	@echo "######################## Welcome to FreeEMS! ########################"
	@echo
	@echo "To build, choose a target from the below list and type 'make target'!"
	@echo "For example, to build blank unconfigured firmware type 'make DEFAULT'"
	@echo "Note: For BenchTest to work you MUST build using the DEFAULT target!"
	@echo "Advanced users will find more options available in the src directory!"
	@echo
	@echo "Options:"
	@echo
	@make -qp | awk -F':' '/^[a-zA-Z0-9][^$$#\/\t=]*:([^=]|$$)/ {split($$1,A,/ /);for(i in A)print A[i]}'

TEST_AND_SAVE_ALL:
	cd src; ../bin/testclibuilds.bash

# Special builds

DEFAULT:
	cd src; CLIFLAGS="$@" make clean s19	
TRUCK:
	cd src; CLIFLAGS="$@" make clean s19	
HOTEL:
	cd src; CLIFLAGS="$@" make clean s19	
PRESTO:
	cd src; CLIFLAGS="$@" make clean s19	
SEANKLT1:
	cd src; CLIFLAGS="$@" make clean s19	
SNOTROCKET:
	cd src; CLIFLAGS="$@" make clean s19	
SPUDMN:
	cd src; CLIFLAGS="$@" make clean s19	
SLATER:
	cd src; CLIFLAGS="$@" make clean s19	
PETERJSERIES:
	cd src; CLIFLAGS="$@" make clean s19	
DEUCECOUPE:
	cd src; CLIFLAGS="$@" make clean s19	
PETERTRUCK:
	cd src; CLIFLAGS="$@" make clean s19	

