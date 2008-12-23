/*	tunables.h

	Copyright 2008 Fred Cooke

	This file is part of the FreeEMS project.

	FreeEMS software is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FreeEMS software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with any FreeEMS software.  If not, see <http://www.gnu.org/licenses/>.

	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org

	Thank you for choosing FreeEMS to run your engine! */

/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_TUNABLES_H_SEEN
#define FILE_TUNABLES_H_SEEN


typedef struct {
	twoDTableUS dwellDesiredVersusVoltageTable;
	twoDTableUS injectorDeadTimeTable;
	twoDTableUS postStartEnrichmentTable;
	twoDTableUS engineTempEnrichmentTableFixed;
	twoDTableUS primingVolumeTable; // perhaps micro litres (cubic milli meters) would be good, 5 - 100 seem to be the norm 327.68 = 65535/200
	twoDTableUS engineTempEnrichmentTablePercent;
	twoDTableUS dwellMaxVersusRPMTable;
	unsigned char filler[576];
} SmallTables1;


typedef struct {
	unsigned short perCylinderFuelTrims[INJECTION_CHANNELS]; /* Trims for injection, from 0% to 200% of base */
	unsigned char filler[1012];
} SmallTables2;


typedef struct {
	unsigned char filler[1024];
} SmallTables3;


typedef struct {
	unsigned char filler[1024];
} SmallTables4;


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file TUNABLES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
