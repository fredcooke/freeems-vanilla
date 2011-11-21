/* FreeEMS - the open source engine management system
 *
 * Copyright 2011 Fred Cooke
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
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Echos the input on the first ignition output
 *
 * This decoder is for unlocked distributor cars such as the MIGHTY Hyundai
 * that I've been living in for 6 months. The mechanical distributor continues
 * to set the timing, the ECU just logs RPM and MAP and any other senors and/or
 * solenoids you hook up and configure.
 *
 * No plugs cranking LA test results:
 *

17302
17346
17451
17498
17600
17646
17751
17795
17900

0
44
149
196
298
344
449
493
598

0
52.98
179.4
235.99
358.8
414.18
540.6
593.58
720

52.98
126.42
56.59
122.81
55.38
126.42
52.98
126.42

54.48
125.52

54,126

 *
 * Approximately 1000 samples per second
 */


#define DECODER_IMPLEMENTATION_C
#define DECODER_MAX_CODE_TIME    100 // To be optimised (shortened)!
#define NUMBER_OF_REAL_EVENTS      2 // TODO  All three of these should migrate to a generic 4 cyl header...
#define NUMBER_OF_VIRTUAL_EVENTS   8 // TODO  All three of these should migrate to a generic 4 cyl header...

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"
#include "../inc/utils.h"

#define E1 (64 * oneDegree)


#include "code/HallOrOptical-Distributor-XofY.c"
