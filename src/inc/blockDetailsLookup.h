/*	FreeEMS - the open source engine management system

	Copyright 2008, 2009 Fred Cooke

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
	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/

	We ask that if you make any changes to this file you email them upstream to
	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!

	Thank you for choosing FreeEMS to run your engine! */


/** @file blockDetailsLookup.h
 * @ingroup allHeaders
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_BLOCK_DETAILS_LOOKUP_H_SEEN
#define FILE_BLOCK_DETAILS_LOOKUP_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef BLOCK_DETAILS_LOOKUP_C
#define EXTERN
#else
#define EXTERN extern
#endif


EXTERN unsigned short lookupBlockDetails(unsigned short, blockDetails*) FPAGE_FE;


/* Memory block ID section */

/* Fueling blocks */
#define VETableMainLocationID						0
#define VETableMain2LocationID						1
#define VETableSecondaryLocationID					2
#define VETableSecondary2LocationID					3
#define VETableTertiaryLocationID					4
#define VETableTertiary2LocationID					5
#define LambdaTableLocationID						6
#define LambdaTable2LocationID						7
/* Timing blocks */
#define IgnitionAdvanceTableMainLocationID			8
#define IgnitionAdvanceTableMain2LocationID			9
#define IgnitionAdvanceTableSecondaryLocationID		10
#define IgnitionAdvanceTableSecondary2LocationID	11
#define InjectionAdvanceTableMainLocationID			12
#define InjectionAdvanceTableMain2LocationID		13
#define InjectionAdvanceTableSecondaryLocationID	14
#define InjectionAdvanceTableSecondary2LocationID	15
/* Tuable blocks */
#define SmallTablesALocationID						100
#define SmallTablesA2LocationID						101
#define SmallTablesBLocationID						102
#define SmallTablesB2LocationID						103
#define SmallTablesCLocationID						104
#define SmallTablesC2LocationID						105
#define SmallTablesDLocationID						106
#define SmallTablesD2LocationID						107
/* Flash ONLY fixed config blocks */
#define FixedConfig1LocationID						200
#define FixedConfig2LocationID						201
/* Flash ONLY lookup tables blocks */
#define IATTransferTableLocationID					300 /* 2k */
#define CHTTransferTableLocationID					301 /* 2k */
#define MAFTransferTableLocationID					302 /* 2k */
#define TestTransferTableLocationID					303 /* 2k */

/* Individual small chunks of small tables blocks */
/* twoDTableUS		= 400 - 899 */
/* arrays/structs	= 900 - 999 */
/* fillers			= 1000+ */

/* TablesA */
#define dwellDesiredVersusVoltageTableLocationID		400
#define dwellDesiredVersusVoltageTable2LocationID		401
#define injectorDeadTimeTableLocationID					402
#define injectorDeadTimeTable2LocationID				403
#define postStartEnrichmentTableLocationID				404
#define postStartEnrichmentTable2LocationID				405
#define engineTempEnrichmentTableFixedLocationID		406
#define engineTempEnrichmentTableFixed2LocationID		407
#define primingVolumeTableLocationID					408
#define primingVolumeTable2LocationID					409
#define engineTempEnrichmentTablePercentLocationID		410
#define engineTempEnrichmentTablePercent2LocationID		411
#define dwellMaxVersusRPMTableLocationID				412
#define dwellMaxVersusRPMTable2LocationID				413


/* TablesB */
#define perCylinderFuelTrimsLocationID					900
#define perCylinderFuelTrims2LocationID					901

/* TablesC */

/* TablesD */

/* filler defs */
#define fillerALocationID 							1000
#define fillerA2LocationID							1001
#define fillerBLocationID							1002
#define fillerB2LocationID							1003
#define fillerCLocationID							1004
#define fillerC2LocationID							1005
#define fillerDLocationID							1006
#define fillerD2LocationID							1007


/* Individual small chunks of fixed config blocks */
/* Fixed conf 1 */
#define engineSettingsLocationID					2000
#define serialSettingsLocationID					2001
#define tachoSettingsLocationID						2002
#define coreSettingsALocationID						2003
#define userTextFieldLocationID						2004
/* Fixed conf 2 */
#define sensorRangesLocationID						3000
#define sensorPresetsLocationID						3001
#define sensorSettingsLocationID					3002
#define userTextField2LocationID					3003


#undef EXTERN

#else
	/* let us know if we are being untidy with headers */
	#warning "Header file BLOCK_DETAILS_LOOKUP_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
