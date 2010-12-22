/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010 Fred Cooke
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


/** @file locationIDs.h
 * @ingroup allHeaders
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_LOCATION_IDS_H_SEEN
#define FILE_LOCATION_IDS_H_SEEN


/* Memory block ID section
 *
 * The IDs are arranged into groups such that different actions can be
 * performed on them depending upon their type. The upper most division is one
 * of "verifiable" and "free form". Verifiable blocks contain data that can
 * have a function run over them to check that they are consistent and good
 * before being stored or used in the code. Verifiable blocks should not be
 * edited with arbitrary manipulation of memory, the firmware protects them or
 * their sub-blocks from incorrect alteration by providing specific accessor
 * functions with their own checks. Fields in non-verifiable blocks should
 * usually work with any value stored in them, just not necessarily in a way
 * that the user would like. Range markers are defined for purposes of
 * checking which area something is in.
 */


/* | LOWER  -  UPPER | GETEST <= | < LTTEST | DESCRIPTION
 * | 0x0000 - 0x000F | 0x0000 <= | < 0x0010 | Big tables that need verification to write to
 * |        -        |           |          |
 * | 0x0100 - 0x010D | 0x0100 <= | < 0x0200 | twoDTableUS
 * |        -        |           |          |
 * | 0x3000 - 0x3007 | 0x3000 <= | < 0x4000 | Big blocks of small tables that should be written whole or individually with verification:
 * | 0x4000 - 0x4007 | 0x4000 <= | < 0x5000 | Small table block fillers - OK to access by offset/size but no point so prevented for now (RAM and Flash)
 * |        -        |           |          |
 * | 0x8000 - 0x8003 | 0x8000 <= | < 0x9000 | lookup tables that should only be written as a whole block
 * |        -        |           |          |
 * | UNIMPL - UNIMPL | 0x???? <= | < 0x???? | Small table block configurations - OK to access by offset/size (RAM and Flash)
 * | 0xC000 - 0xFFFF | 0xC000 <= |    N/A   | Big config blocks and sub sections with many small fields - OK to access by offset/size (Flash ONLY)
 */


/* Memory block range limits */
#define MainTableLocationLower                         0x0000
#define MainTableLocationUpper                         0x0010
// gap
#define twoDTableUSLocationLower                       0x0100
#define twoDTableUSLocationUpper                       0x0200
// gap
#define SmallTableBlocksLower                          0x3000
#define SmallTableBlocksUpper                          0x4000
#define SmallTableBlockFillersLower                    0x4000
#define SmallTableBlockFillersUpper                    0x5000
// gap
#define FlashLookupTablesLower                         0x8000
#define FlashLookupTablesUpper                         0x9000
// gap
#define SmallTableBlockConfigsLower                    0x????
#define SmallTableBlockConfigsUpper                    0x????
// gap
#define BigConfigBlocksLower                           0xC000
#define BigConfigBlocksUpper                           0xFFFF+1=? // unusable so ensure it breaks


/* Big main tables */
/* Fueling tables */
#define VETableMainLocationID                          0x0000
#define VETableMain2LocationID                         0x0001
#define VETableSecondaryLocationID                     0x0002
#define VETableSecondary2LocationID                    0x0003
#define VETableTertiaryLocationID                      0x0004
#define VETableTertiary2LocationID                     0x0005
#define LambdaTableLocationID                          0x0006
#define LambdaTable2LocationID                         0x0007
/* Timing tables */
#define IgnitionAdvanceTableMainLocationID             0x0008
#define IgnitionAdvanceTableMain2LocationID            0x0009
#define IgnitionAdvanceTableSecondaryLocationID        0x000A
#define IgnitionAdvanceTableSecondary2LocationID       0x000B
#define InjectionAdvanceTableMainLocationID            0x000C
#define InjectionAdvanceTableMain2LocationID           0x000D
#define InjectionAdvanceTableSecondaryLocationID       0x000E
#define InjectionAdvanceTableSecondary2LocationID      0x000F


/* twoDTableUS tables (TablesA) */
#define dwellDesiredVersusVoltageTableLocationID       0x0100
#define dwellDesiredVersusVoltageTable2LocationID      0x0101
#define injectorDeadTimeTableLocationID                0x0102
#define injectorDeadTimeTable2LocationID               0x0103
#define postStartEnrichmentTableLocationID             0x0104
#define postStartEnrichmentTable2LocationID            0x0105
#define engineTempEnrichmentTableFixedLocationID       0x0106
#define engineTempEnrichmentTableFixed2LocationID      0x0107
#define primingVolumeTableLocationID                   0x0108
#define primingVolumeTable2LocationID                  0x0109
#define engineTempEnrichmentTablePercentLocationID     0x010A
#define engineTempEnrichmentTablePercent2LocationID    0x010B
#define dwellMaxVersusRPMTableLocationID               0x010C
#define dwellMaxVersusRPMTable2LocationID              0x010D


/* TablesB */
/// TODO @todo Claim some RAM back for XGATE use?


/* TablesC */
/// TODO @todo Claim some RAM back for XGATE use?


/* TablesD */
/// TODO @todo Claim some RAM back for XGATE use?


/* Tunable blocks */
#define SmallTablesALocationID                         0x3000
#define SmallTablesA2LocationID                        0x3001
#define SmallTablesBLocationID                         0x3002
#define SmallTablesB2LocationID                        0x3003
#define SmallTablesCLocationID                         0x3004
#define SmallTablesC2LocationID                        0x3005
#define SmallTablesDLocationID                         0x3006
#define SmallTablesD2LocationID                        0x3007


/* Table block fillers */
#define fillerALocationID                              0x4000
#define fillerA2LocationID                             0x4001
#define fillerBLocationID                              0x4002
#define fillerB2LocationID                             0x4003
#define fillerCLocationID                              0x4004
#define fillerC2LocationID                             0x4005
#define fillerDLocationID                              0x4006
#define fillerD2LocationID                             0x4007


/* Flash ONLY lookup tables blocks */
#define IATTransferTableLocationID                     0x8000 /* 2k */
#define CHTTransferTableLocationID                     0x8001 /* 2k */
#define MAFTransferTableLocationID                     0x8002 /* 2k */
#define TestTransferTableLocationID                    0x8003 /* 2k */


/* Flash ONLY fixed config blocks */
/* Fixed config 1 */
#define FixedConfig1LocationID                         0xC000
/* Fixed config 1 sub sections */
#define engineSettingsLocationID                       0xC001
#define serialSettingsLocationID                       0xC002
#define tachoSettingsLocationID                        0xC003
#define coreSettingsALocationID                        0xC004
#define userTextFieldLocationID                        0xC005
/* Fixed config 2 */
#define FixedConfig2LocationID                         0xD000
/* Fixed config 2 sub sections */
#define sensorRangesLocationID                         0xD001
#define sensorPresetsLocationID                        0xD002
#define sensorSettingsLocationID                       0xD003
#define userTextField2LocationID                       0xD004


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file LOCATION_IDS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
