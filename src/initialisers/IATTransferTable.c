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
 * @ingroup dataInitialisers
 *
 * @brief Inlet Air Temperature Transfer Table
 *
 * This file exists solely to contain the Inlet Air Temperature thermistor
 * transfer function lookup table.
 *
 * @author Fred Cooke
 */


#include "../inc/freeEMS.h"


/** @brief Inlet Air Temperature Transfer Table
 *
 * Using this table it is possible to accurately and quickly convert
 * a raw ADC reading to a scaled temperature value in degrees Kelvin.
 *
 * @author FreeTherm
 */
const volatile unsigned short IATTransferTable[1024] LOOKUPD = {
#if CONFIG == TRUCK_ID
#include "../data/thermistors/Bosch.h"
#elif CONFIG == PRESTO_ID
#include "../data/thermistors/Bosch.h"
#elif CONFIG == SEANKLT1_ID
#include "../data/thermistors/Bosch.h"
#elif SEANKR1 // No ID assigned yet!
#include "../data/thermistors/Bosch.h"
#elif CONFIG == SNOTROCKET_ID
#include "../data/thermistors/GM-2k4Bias.h"
#elif CONFIG == SLATER_ID
#include "../data/thermistors/GM-2k6Bias.h"
#elif CONFIG == DEUCECOUPE_ID
#include "../data/thermistors/GM-2k4Bias.h"
#else // Default to correctly biased Jap sensor.
#include "../data/thermistors/Denso-2k7Bias.h"
#endif
};
