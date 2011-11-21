/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009 Fred Cooke
 *
 * This file is part of the FreeEMS project.
 *
 * FreeEMS software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * FreeEMS software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/
 *
 * We ask that if you make any changes to this file you email them upstream to
 * us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!
 *
 * Thank you for choosing FreeEMS to run your engine!
 */


/** @file
 *
 * @ingroup allHeaders
 *
 * @brief Pointers to paged memory blocks
 *
 * The number of these required is fairly significant and thus is best placed
 * in its own header file. Their only function is to prevent warnings from the
 * linker due to accessing paged addresses in linear space.
 *
 * @author Fred Cooke
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_PAGED_LOCATION_BUFFERS_H_SEEN
#define FILE_PAGED_LOCATION_BUFFERS_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef BLOCK_DETAILS_LOOKUP_C
#define EXTERN
#else
#define EXTERN extern
#endif


/*&&&&&&&&&&&&&&&&&&&&& Large 1k or 2k blocks here only &&&&&&&&&&&&&&&&&&&&&*/

/* Fueling blocks */
EXTERN void* VETableMainFlashLocation;
EXTERN void* VETableMainFlash2Location;
EXTERN void* VETableSecondaryFlashLocation;
EXTERN void* VETableSecondaryFlash2Location;
EXTERN void* VETableTertiaryFlashLocation;
EXTERN void* VETableTertiaryFlash2Location;
EXTERN void* LambdaTableFlashLocation;
EXTERN void* LambdaTableFlash2Location;

/* Timing blocks */
EXTERN void* IgnitionAdvanceTableMainFlashLocation;
EXTERN void* IgnitionAdvanceTableMainFlash2Location;
EXTERN void* IgnitionAdvanceTableSecondaryFlashLocation;
EXTERN void* IgnitionAdvanceTableSecondaryFlash2Location;
EXTERN void* InjectionAdvanceTableMainFlashLocation;
EXTERN void* InjectionAdvanceTableMainFlash2Location;
EXTERN void* InjectionAdvanceTableSecondaryFlashLocation;
EXTERN void* InjectionAdvanceTableSecondaryFlash2Location;

/* Tunable blocks */
EXTERN void* SmallTablesAFlashLocation;
EXTERN void* SmallTablesAFlash2Location;
EXTERN void* SmallTablesBFlashLocation;
EXTERN void* SmallTablesBFlash2Location;
EXTERN void* SmallTablesCFlashLocation;
EXTERN void* SmallTablesCFlash2Location;
EXTERN void* SmallTablesDFlashLocation;
EXTERN void* SmallTablesDFlash2Location;

/* Flash ONLY blocks */
EXTERN void* IATTransferTableLocation;
EXTERN void* CHTTransferTableLocation;
EXTERN void* MAFTransferTableLocation;
EXTERN void* TestTransferTableLocation;


/*&&&&&&&&&&&&&&& Small chunks of the above blocks here only! &&&&&&&&&&&&&&&*/

/* Small chunks of TablesA here */
EXTERN void* dwellDesiredVersusVoltageTableLocation;
EXTERN void* dwellDesiredVersusVoltageTable2Location;
EXTERN void* injectorDeadTimeTableLocation;
EXTERN void* injectorDeadTimeTable2Location;
EXTERN void* postStartEnrichmentTableLocation;
EXTERN void* postStartEnrichmentTable2Location;
EXTERN void* engineTempEnrichmentTableFixedLocation;
EXTERN void* engineTempEnrichmentTableFixed2Location;
EXTERN void* primingVolumeTableLocation;
EXTERN void* primingVolumeTable2Location;
EXTERN void* engineTempEnrichmentTablePercentLocation;
EXTERN void* engineTempEnrichmentTablePercent2Location;
EXTERN void* dwellMaxVersusRPMTableLocation;
EXTERN void* dwellMaxVersusRPMTable2Location;

/* Small chunks of TablesB here */
EXTERN void* loggingSettingsLocation;
EXTERN void* loggingSettings2Location;
EXTERN void* perCylinderFuelTrimsLocation;
EXTERN void* perCylinderFuelTrims2Location;

/* Small chunks of TablesC here */

/* Small chunks of TablesD here */

/* Small chunks of FixedConf1 here */

/* Small chunks of FixedConf2 here */

/* Fillers here */
EXTERN void* fillerALocation;
EXTERN void* fillerA2Location;
EXTERN void* fillerBLocation;
EXTERN void* fillerB2Location;
EXTERN void* fillerCLocation;
EXTERN void* fillerC2Location;
EXTERN void* fillerDLocation;
EXTERN void* fillerD2Location;


#undef EXTERN


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file PAGED_LOCATION_BUFFERS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
