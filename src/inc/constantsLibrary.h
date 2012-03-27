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
 * @brief Global physical constants and configuration library
 *
 * A convenient set of ready-to-use values for from-source builds.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template    */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual       */
#ifndef FILE_CONSTANTSLIBRARY_H_SEEN
#define FILE_CONSTANTSLIBRARY_H_SEEN


// Densities of various common fuels in grams per litre
#define densityOfOctane FUEL_DENSITY(703)
#define densityOfPetrol FUEL_DENSITY(720)

// Stoichiometric AFRs for various common fuels. Generated with http://www.diyefi.org/calculators.htm#stoich
#define stoichiometricAFRMethane  AFR(17.245)
#define stoichiometricAFRPropane  AFR(15.685)
#define stoichiometricAFRLPG      AFR(15.599)
#define stoichiometricAFRButane   AFR(15.469)
#define stoichiometricAFROctane   AFR(15.137)
#define stoichiometricAFRGasoline AFR(14.700)
#define stoichiometricAFRXylene   AFR(13.681)
#define stoichiometricAFRToluene  AFR(13.512)
#define stoichiometricAFRBenzene  AFR(13.282)
#define stoichiometricAFRE85      AFR( 9.862)
#define stoichiometricAFREthanol  AFR( 9.008)
#define stoichiometricAFRMethanol AFR( 6.475)

// Wide-band input common configuration values
#define LC1LambdaMin                LAMBDA(0.5)
#define LC1LambdaMax                LAMBDA(1.5)
#define LC1LambdaRange              (LC1LambdaMax - LC1LambdaMin) // 1.0
#define AFR1020LambdaMin            LAMBDA(0.68)
#define AFR1020LambdaMax            LAMBDA(1.36)
#define AFR1020LambdaRange          (AFR1020LambdaMax - AFR1020LambdaMin) // 0.68


/* MAP Sensor Data Explanation
 *
 * Motorola/Freescale pressure sensor data obtained from the
 * data sheets by extrapolation of the "typical" line to the
 * borders of the transfer function chart. This gives us the
 * correct values in the middle despite not being able to
 * reach the ends of the scale.
 *
 * By min and max I mean the OV and 5V pressures that aren't
 * attainable, but that give the correct function in between.
 */


/* Honda Denso 1.8bar found on 88 - ?? Honda vehicles. */
#define HondaDenso183kPaMin      KPA( -6.64)    /* Pressure read at lowest ADC reading */
#define HondaDenso183kPaMax      KPA(182.78)    /* Pressure read at highest ADC reading */
#define HondaDenso183kPaRange    (HondaDenso183kPaMax - HondaDenso183kPaMin)

/* Toyota 2.3bar found on some Toyota Cynos 5E-FE cars (and probably many others), em_knaps and Lev8n are responsible for this data! */
#define ToyotaNA227kPaMin        KPA( 25)       /* Pressure read at lowest ADC reading */
#define ToyotaNA227kPaMax        KPA(247)       /* Pressure read at highest ADC reading */
#define ToyotaNA227kPaRange      (ToyotaNA227kPaMax - ToyotaNA227kPaMin)
// NOTE: The accuracy of this calibration is highly questionable. Please use the Honda units which is configured above and known to be accurate

/* GM 2bar found on Cyclone Turbo V6 and probably other cars too. TODO These numbers are probably not that accurate... */
#define GM2BarMin                KPA(  1.5)     /* Pressure read at lowest ADC reading */
#define GM2BarMax                KPA(200.0)     /* Pressure read at highest ADC reading */
#define GM2BarRange              (GM2BarMax - GM2BarMin)

/* www.freescale.com/files/sensors/doc/data_sheet/MPX4100A.pdf */
#define MPX4100AMin              KPA( 14.0)     /* Pressure read at lowest ADC reading */
#define MPX4100AMax              KPA(107.5)     /* Pressure read at highest ADC reading */
#define MPX4100ARange            (MPX4100AMax - MPX4100AMin)

/* www.freescale.com/files/sensors/doc/data_sheet/MPX4250A.pdf */
#define MPX4250AMin              KPA(  8)       /* Pressure read at lowest ADC reading */
#define MPX4250AMax              KPA(260)       /* Pressure read at highest ADC reading */
#define MPX4250ARange            (MPX4250AMax - MPX4250AMin)

#define MPXH6300AMin             KPA( 12)       /* Pressure read at lowest ADC reading */
#define MPXH6300AMax             KPA(320)       /* Pressure read at highest ADC reading */
#define MPXH6300ARange           (MPXH6300AMax - MPXH6300AMin)

#define MPXH6400AMin             KPA( 12)       /* Pressure read at lowest ADC reading */
#define MPXH6400AMax             KPA(420)       /* Pressure read at highest ADC reading */
#define MPXH6400ARange           (MPXH6400AMax - MPXH6400AMin)


#else
    /* let us know if we are being untidy with headers */
    #warning "Header file CONSTANTSLIBRARY_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
