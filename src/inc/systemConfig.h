/* FreeEMS - the open source engine management system
 *
 * Copyright 2012 Fred Cooke
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
 *
 * @brief System configuration defines
 *
 * This holds various hash defined configuration constants and literals.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template    */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual       */
#ifndef FILE_SYSTEM_CONFIG_H_SEEN
#define FILE_SYSTEM_CONFIG_H_SEEN


// Scheduling stuff used in configuration and scheduler
#define MAX_NUMBER_OF_OUTPUT_EVENTS 24
#define INJECTION_CHANNELS  6    /* How many injection channels the code should support */

/* The TX and RX buffers are slightly larger than 2k because the RX buffer */
/* needs to also receive a header, checksum and attributes for the data    */
/* involved and the TX buffer needs to handle all of those two fold.       */
#define TX_BUFFER_SIZE       0x0820 ///< 2k of data plus double maximum header overhead for echo
#define RX_BUFFER_SIZE       0x0810 ///< 2k of data plus maximum header overhead

// ADC values
#define ADC_NUMBER_OF_VALUES                1024 ///< Number of distinct values in 10 bit ADC units
#define ADC_DIVISIONS (ADC_NUMBER_OF_VALUES - 1) ///< The number of gaps between the values
#define ADC_MAX_VALUE (ADC_NUMBER_OF_VALUES - 1) ///< The highest value used in our mode


#else
    /* let us know if we are being untidy with headers */
    #warning "Header file SYSTEM_CONFIG_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
