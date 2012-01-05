/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2011 Fred Cooke
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
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_LOCATION_IDS_H_SEEN
#define FILE_LOCATION_IDS_H_SEEN


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

#ifdef BLOCK_DETAILS_LOOKUP_C // only for here, external stuff should use the flags field for determining what to do/not do.
#define MainTable_TwoDTableUS_Border                   0x0100
#endif

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

#ifdef BLOCK_DETAILS_LOOKUP_C // only for here, external stuff should use the flags field for determining what to do/not do.
#define TwoDTableUS_SmallTableFullBlocks_Border        0x3000
#endif

/// TODO @todo Claim some RAM back for XGATE use?
/* TablesB */
/* TablesC */
/* TablesD */

/* Tunable blocks */
#define SmallTablesALocationID                         0x3000
#define SmallTablesA2LocationID                        0x3001
#define SmallTablesBLocationID                         0x3002
#define SmallTablesB2LocationID                        0x3003
#define SmallTablesCLocationID                         0x3004
#define SmallTablesC2LocationID                        0x3005
#define SmallTablesDLocationID                         0x3006
#define SmallTablesD2LocationID                        0x3007

#ifdef BLOCK_DETAILS_LOOKUP_C // only for here, external stuff should use the flags field for determining what to do/not do.
#define SmallTableFullBlocks_SmallTableFillers_Border  0x4000
#endif

/* Table block fillers */
#define fillerALocationID                              0x4000
#define fillerA2LocationID                             0x4001
#define fillerBLocationID                              0x4002
#define fillerB2LocationID                             0x4003
#define fillerCLocationID                              0x4004
#define fillerC2LocationID                             0x4005
#define fillerDLocationID                              0x4006
#define fillerD2LocationID                             0x4007

#ifdef BLOCK_DETAILS_LOOKUP_C // only for here, external stuff should use the flags field for determining what to do/not do.
#define SmallTableFillers_FlashLookupTables_Border     0x8000
#endif

/* Flash ONLY lookup tables blocks */
#define IATTransferTableLocationID                     0x8000 /* 2k */
#define CHTTransferTableLocationID                     0x8001 /* 2k */
#define MAFTransferTableLocationID                     0x8002 /* 2k */
#define TestTransferTableLocationID                    0x8003 /* 2k */

#ifdef BLOCK_DETAILS_LOOKUP_C // only for here, external stuff should use the flags field for determining what to do/not do.
#define FlashLookupTables_SmallTableConfigs_Border     0x9000
#endif

#define loggingSettingsLocationID                      0x9000
#define loggingSettings2LocationID                     0x9001

#ifdef BLOCK_DETAILS_LOOKUP_C // only for here, external stuff should use the flags field for determining what to do/not do.
#define SmallTableConfigs_FixedConfigBlocks_Border     0xA000
#endif

/* Fixed configs whole */
#define FixedConfig1LocationID                         0xA000
#define FixedConfig2LocationID                         0xA001

#ifdef BLOCK_DETAILS_LOOKUP_C // only for here, external stuff should use the flags field for determining what to do/not do.
#define FixedConfigBlocks_FixedConfigSubBlocks_Border  0xC000
#endif

/* Fixed config 1 sub sections */
#define engineSettingsLocationID                       0xC000
#define serialSettingsLocationID                       0xC001
#define tachoSettingsLocationID                        0xC002
#define userTextFieldLocationID                        0xC004

/* Fixed config 2 sub sections */
#define sensorRangesLocationID                         0xC005
#define sensorPresetsLocationID                        0xC006
#define sensorSettingsLocationID                       0xC007
#define userTextField2LocationID                       0xC008

#ifdef BLOCK_DETAILS_LOOKUP_C // only for here, external stuff should use the flags field for determining what to do/not do.
#define FixedConfigSubBlocks_Border_ReadOnlyVarBlocks  0xF000
#endif

// Internal blocks of variables that are sometimes useful to read out
#define ADCRegistersLocationID                         0xF000
#define coreVarsLocationID                             0xF001
#define DerivedVarsLocationID                          0xF002
#define CountersLocationID                             0xF003
#define ClocksLocationID                               0xF004
#define FlaggablesLocationID                           0xF005


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file LOCATION_IDS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
