/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
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
 * @ingroup globalHeaders
 * @ingroup dataStructures
 *
 * @brief Struct typedefs for tunable configuration
 *
 * This file contains both the struct data type definitions and the arrays of
 * default values for small tables. Place reusable definitions of default table
 * values in here such that they can be used in multiple tunable table definitions.
 *
 * You should add your configuration item here if it is best that it is adjusted with
 * instant results on a running engine. For everything else, please consider placing
 * it in one of the fixed configuration structs.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_TUNABLE_CONFIGS_H_SEEN
#define FILE_TUNABLE_CONFIGS_H_SEEN


/** Holds all configuration for logging.
 *
 * These are in tunable config such that the system can pick up where it left
 * off if reset with settings burned to flash, or simply switch back to default
 * if changed in ram and not burned and then reset.
 */
typedef struct {
	unsigned char datalogStreamType;            ///< Which type of datalog to pump out as fast as we can. @see commsCore.h
	unsigned char datalogPollingType;           ///< Which type of datalog to pump out as fast as we can. @see commsCore.h
	unsigned short basicDatalogLength;          ///< How much of the basic datalog to send, cuts off the trailing end.
	void* datalogByteStreamSourceAddress;       ///< Where to grab our data from.
	void* datalogWordStreamSourceAddress;       ///< Where to grab our data from.
	void* datalogLongStreamSourceAddressFirst;  ///< Where to grab our data from. If the second address is set to zero, get 4 bytes from this address.
	void* datalogLongStreamSourceAddressSecond; ///< Where to grab our data from. If this is non-zero, get 2 bytes from the first address and 2 from this address.
	// TODO scratch pad configs
	// TODO structs configs
	// Note, position type has no config and "just works"
} loggingSetting;


#define SMALL_TABLES_1_FILLER_SIZE (flashSectorSize - (sizeof(twoDTableUS) * 8))  // Update this if adding another table!
/**
 * One of four structs of live tunable data such as small tables and fuel trims
 * etc. If you add something here, please ensure you update all of the following :
 * - Default values in the initial definitions in TunableConfig.c and TunableConfig2.c
 * - The address values within the initPagedRAMTune() function in init.c
 * - The lookupBlockDetails() function in blockDetailsLookup.c
 * - The JSON data map and other related firmware interface definition files
 *
 */
typedef struct {
	twoDTableUS dwellDesiredVersusVoltageTable;   ///< Standard dwell curve dependent on voltage.
	twoDTableUS injectorDeadTimeTable;            ///< Injector dead time curve dependent on voltage.
	twoDTableUS postStartEnrichmentTable;         ///< Unused at this time.
	twoDTableUS postStartTaperTimeTable;          ///< Unused at this time.
	twoDTableUS engineTempEnrichmentTableFixed;   ///< Unused at this time.
	twoDTableUS primingVolumeTable;               ///< @todo TODO define units. perhaps micro litres (cubic milli meters) would be good, 5 - 100 seem to be the norm 327.68 = 65535/200
	twoDTableUS engineTempEnrichmentTablePercent; ///< Engine temperature enrichment by percent, AKA warmup curve.
	twoDTableUS dwellMaxVersusRPMTable;           ///< Unused at this time.
	unsigned char filler[SMALL_TABLES_1_FILLER_SIZE];
} SmallTables1;


#define SMALL_TABLES_2_FILLER_SIZE (flashSectorSize - (sizeof(loggingSetting) + 12)) // Update this if adding another table/struct!
/** @copydoc SmallTables1 */
typedef struct {
	loggingSetting loggingSettings;                          ///< @copydoc loggingSetting
	unsigned short perCylinderFuelTrims[INJECTION_CHANNELS]; ///< Trims for injection, from 0% to 200% of base.
	unsigned char filler[SMALL_TABLES_2_FILLER_SIZE];        ///< Padding data.
} SmallTables2;


#define SMALL_TABLES_3_FILLER_SIZE flashSectorSize // Update this if adding a table!
/** @copydoc SmallTables1 */
typedef struct {
	unsigned char filler[SMALL_TABLES_3_FILLER_SIZE]; ///< Padding data.
} SmallTables3;


#define SMALL_TABLES_4_FILLER_SIZE flashSectorSize // Update this if adding a table!
/** @copydoc SmallTables1 */
typedef struct {
	unsigned char filler[SMALL_TABLES_4_FILLER_SIZE]; ///< Padding data.
} SmallTables4;


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file TUNABLE_CONFIGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
