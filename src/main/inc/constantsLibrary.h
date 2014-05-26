/* FreeEMS - the open source engine management system
 *
 * Copyright 2012-2013 Fred Cooke
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
#define stoichiometricAFRMethane  STOICH_AFR(17.245)
#define stoichiometricAFRPropane  STOICH_AFR(15.685)
#define stoichiometricAFRLPG      STOICH_AFR(15.599)
#define stoichiometricAFRButane   STOICH_AFR(15.469)
#define stoichiometricAFROctane   STOICH_AFR(15.137)
#define stoichiometricAFRPetrol   STOICH_AFR(14.700)
#define stoichiometricAFRXylene   STOICH_AFR(13.681)
#define stoichiometricAFRToluene  STOICH_AFR(13.512)
#define stoichiometricAFRBenzene  STOICH_AFR(13.282)
#define stoichiometricAFRE85      STOICH_AFR( 9.862)
#define stoichiometricAFREthanol  STOICH_AFR( 9.008)
#define stoichiometricAFRMethanol STOICH_AFR( 6.475)

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

/* GM 1bar found on naturally aspirated vehicles. Taken from http://www.robietherobot.com/storm/mapsensor.htm */
#define GM1BarMin                KPA( 10.0)     /* Pressure read at lowest ADC reading */
#define GM1BarMax                KPA(105.0)     /* Pressure read at highest ADC reading */
#define GM1BarRange              (GM1BarMax - GM1BarMin)

/* GM 2bar found on Cyclone Turbo V6 and probably other cars too. TODO These numbers are probably not that accurate... */
#define GM2BarMin                KPA(  1.5)     /* Pressure read at lowest ADC reading */
#define GM2BarMax                KPA(200.0)     /* Pressure read at highest ADC reading */
#define GM2BarRange              (GM2BarMax - GM2BarMin)

/* www.freescale.com/files/sensors/doc/data_sheet/MPX4100A.pdf */
#define MPX4100AMin              KPA( 14.0)     /* Pressure read at lowest ADC reading */
#define MPX4100AMax              KPA(107.5)     /* Pressure read at highest ADC reading */
#define MPX4100ARange            (MPX4100AMax - MPX4100AMin)

/* www.freescale.com/files/sensors/doc/data_sheet/MPXA6115A.pdf */
#define MPXA6115AMin             KPA( 10.0)     /* Pressure read at lowest ADC reading */
#define MPXA6115AMax             KPA(120.0)     /* Pressure read at highest ADC reading */
#define MPXA6115ARange           (MPXA6115AMax - MPXA6115AMin)

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


// Tachometer default configuration
#define standardTachoArray {1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2,1,2}
#define standardTachoPorts {(unsigned char*)&PORTE,(unsigned char*)&PORTK,(unsigned char*)&PORTK,(unsigned char*)&PORTK}
#define standardTachoMasks {0x80,0x01,0x02,0x04}


// Voltage based small table default data
#define ARRAY_OF_16_VOLTAGES      {  V(6.0),   V(7.2),   V(8.4),   V(9.0),   V(9.6),  V(10.2),  V(10.8),  V(11.4),  V(12.0),  V(12.6),  V(13.2),  V(13.8),  V(14.4),  V(17.8),  V(21.0),  V(24.5)}
#define ARRAY_OF_16_DEADTIMES     { T(2.91),  T(2.30),  T(1.86),  T(1.70),  T(1.58),  T(1.47),  T(1.39),  T(1.30),  T(1.23),  T(1.15),  T(1.10),  T(1.04),  T(0.99),  T(0.76),  T(0.57),  T(0.40)}
#define ARRAY_OF_16_DWELLS        {T(14.55), T(11.50),  T(9.30),  T(8.50),  T(7.90),  T(7.35),  T(6.95),  T(6.50),  T(6.15),  T(5.75),  T(5.48),  T(5.20),  T(4.95),  T(3.80),  T(2.85),  T(2.00)}

// Temperature based small table default data
#define ARRAY_OF_16_TEMPS         { C(-30),  C(-20),  C(-10),    C(0),   C(10),   C(20),   C(30),   C(40),   C(50),   C(60),   C(70),   C(80),   C(90),  C(100),  C(110),  C(120)}
#define ARRAY_OF_16_PERCENTS      { W(250),  W(235),  W(220),  W(205),  W(190),  W(175),  W(160),  W(145),  W(130),  W(118),  W(108),  W(100),  W(100),  W(110),  W(120),  W(130)}
#define ARRAY_OF_16_PERCENTS_WIDE { W(235),  W(220),  W(205),  W(190),  W(175),  W(160),  W(145),  W(130),  W(118),  W(108),  W(100),  W(100),  W(100),  W(110),  W(120),  W(130)}
#define ARRAY_OF_16_VOLUMES       {T(6.40), T(5.06), T(4.09), T(3.74), T(3.48), T(3.23), T(3.06), T(2.86), T(2.71), T(2.53), T(2.41), T(2.29), T(2.18), T(1.67), T(1.25), T(0.88)} // Time in ms, for now, NOT volume, yet

// RPM based small table default data
#define ARRAY_OF_16_RPMS          {  RPM(500), RPM(1000), RPM(1500), RPM(2000), RPM(2500), RPM(3000), RPM(3500), RPM(4000), RPM(4500), RPM(5000), RPM(5500), RPM(6000), RPM(6500), RPM(7000), RPM(7500), RPM(8000)}
#define ARRAY_OF_16_DIS6_DWELLS   {   T(5.75),   T(5.50),   T(5.25),   T(5.00),   T(4.75),   T(4.50),   T(4.25),   T(4.00),   T(3.75),   T(3.50),   T(3.25),   T(3.00),   T(2.75),   T(2.50),   T(2.25),   T(2.00)}
#define ARRAY_OF_16_BLENDS        {  SHORTMAX,  SHORTMAX,  SHORTMAX,   LR(1.5),   LR(1.0),   LR(0.5),   LR(0.0),   LR(0.0),   LR(0.0),   LR(0.0),   LR(0.0),   LR(0.0),   LR(0.0),   LR(0.0),   LR(0.0),   LR(0.0)} // Hacky... TODO migrate TPS to full range and reuse that here too...

// TODO YAGNI currently unused space fillers
#define ARRAY_OF_16_TIMES         {     0,  4096,  8192, 12288, 16384, 20480, 24576, 28672, 32768, 36864, 40960, 45056, 49152, 53248, 57344, 61440}


#else
    /* let us know if we are being untidy with headers */
    #warning "Header file CONSTANTSLIBRARY_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
