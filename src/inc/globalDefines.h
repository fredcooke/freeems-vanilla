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
 * @ingroup globalHeaders
 *
 * @brief Global hash define literal replacements
 *
 * Currently this holds most hash defined constants and literals.
 *
 * @author Fred Cooke
 *
 * @todo TODO Some investigation as to whether it is best to use consts or defines is required
 * @todo TODO Break this up into smaller chunks that are included into this file
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template    */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual       */
#ifndef FILE_GLOBALDEFINES_H_SEEN
#define FILE_GLOBALDEFINES_H_SEEN


/* TODO perhaps configure various ports and pins etc to have names such that the
 * code can stay untouched when being ported and just the header changed to suit?
 * definitely a good idea, but we'll see what karsten says before putting time
 * into it. something like : #define RPM_IN_MAIN IC0 etc etc
 */


/* Definitions for functions used across the project TODO these are unused! */
/* http://www.seattlerobotics.org/encoder/200109/encoder.htm section Assembly */
#define INLINE_ASSEMBLY(code) __asm__ __volatile__ (code)
#define ALWAYS_INLINE __attribute__((always_inline))

/* Common macro definitions across the project */
/* Booleans from http://c2.com/cgi/wiki?CeePreprocessorStatements */
#define FALSE (0!=0) // Note, this evaluates to 0 on this platform
#define TRUE  !FALSE // Note, this evaluates to 1 on this platform

/* 8 bit values */
#define ZEROS 0x00
#define ONES  0xFF

/* 16 bit values */
#define ZEROS16 0x0000
#define ONES16  0xFFFF

/* Halves and Maxes */
#define LONGHALF  0x80000000UL /* 2147483648 */ // Ned IS awesome! ;-)
#define LONGMAX   0xFFFFFFFFUL /* 4294967295 */
#define SHORTHALF 0x8000       /* 32768 */
#define SHORTMAX  0xFFFF       /* 65535 */

/* Individual bits WARNING, do not not these for notted versions, use the notted ones below instead : http://supp.iar.com/Support/?note=12582&from=search+result */
#define BIT0        0x01      /*  1st bit =     1 */
#define BIT1        0x02      /*  2nd bit =     2 */
#define BIT2        0x04      /*  3rd bit =     4 */
#define BIT3        0x08      /*  4th bit =     8 */
#define BIT4        0x10      /*  5th bit =    16 */
#define BIT5        0x20      /*  6th bit =    32 */
#define BIT6        0x40      /*  7th bit =    64 */
#define BIT7        0x80      /*  8th bit =   128 */

#define BIT0_16     0x0001    /*  1st bit =     1 */
#define BIT1_16     0x0002    /*  2nd bit =     2 */
#define BIT2_16     0x0004    /*  3rd bit =     4 */
#define BIT3_16     0x0008    /*  4th bit =     8 */
#define BIT4_16     0x0010    /*  5th bit =    16 */
#define BIT5_16     0x0020    /*  6th bit =    32 */
#define BIT6_16     0x0040    /*  7th bit =    64 */
#define BIT7_16     0x0080    /*  8th bit =   128 */

#define BIT8_16     0x0100    /*  9th bit =   256 */
#define BIT9_16     0x0200    /* 10th bit =   512 */
#define BIT10_16    0x0400    /* 11th bit =  1024 */
#define BIT11_16    0x0800    /* 12th bit =  2048 */
#define BIT12_16    0x1000    /* 13th bit =  4096 */
#define BIT13_16    0x2000    /* 14th bit =  8192 */
#define BIT14_16    0x4000    /* 15th bit = 16384 */
#define BIT15_16    0x8000    /* 16th bit = 32768 */

/* Individual bits NOTTED : http://supp.iar.com/Support/?note=12582&from=search+result */
#define NBIT0       0xFE      /*  1st bit =     1 */
#define NBIT1       0xFD      /*  2nd bit =     2 */
#define NBIT2       0xFB      /*  3rd bit =     4 */
#define NBIT3       0xF7      /*  4th bit =     8 */
#define NBIT4       0xEF      /*  5th bit =    16 */
#define NBIT5       0xDF      /*  6th bit =    32 */
#define NBIT6       0xBF      /*  7th bit =    64 */
#define NBIT7       0x7F      /*  8th bit =   128 */

#define NBIT0_16    0xFFFE    /*  1st bit =     1 */
#define NBIT1_16    0xFFFD    /*  2nd bit =     2 */
#define NBIT2_16    0xFFFB    /*  3rd bit =     4 */
#define NBIT3_16    0xFFF7    /*  4th bit =     8 */
#define NBIT4_16    0xFFEF    /*  5th bit =    16 */
#define NBIT5_16    0xFFDF    /*  6th bit =    32 */
#define NBIT6_16    0xFFBF    /*  7th bit =    64 */
#define NBIT7_16    0xFF7F    /*  8th bit =   128 */

#define NBIT8_16    0xFEFF    /*  9th bit =   256 */
#define NBIT9_16    0xFDFF    /* 10th bit =   512 */
#define NBIT10_16   0xFBFF    /* 11th bit =  1024 */
#define NBIT11_16   0xF7FF    /* 12th bit =  2048 */
#define NBIT12_16   0xEFFF    /* 13th bit =  4096 */
#define NBIT13_16   0xDFFF    /* 14th bit =  8192 */
#define NBIT14_16   0xBFFF    /* 15th bit = 16384 */
#define NBIT15_16   0x7FFF    /* 16th bit = 32768 */


// Shared serial comms stuff TODO move this to a commsCommon.h header
#define START_BYTE          0xAA
#define ESCAPE_BYTE         0xBB
#define STOP_BYTE           0xCC

#define ESCAPED_START_BYTE  0x55
#define ESCAPED_ESCAPE_BYTE 0x44
#define ESCAPED_STOP_BYTE   0x33

#define flashSectorSize        1024
#define flashSectorSizeInWords  512 /* 512 words to a 1k flash sector */


#define IGNITION_TIMING_FACTOR 1024UL // Warning, to be changed to 8 bit, use this:
#define IT(IGNITION_TIMING_BTDC) (IGNITION_TIMING_BTDC * IGNITION_TIMING_FACTOR)

// TODO unused, make used!
#define RPM_FACTOR      2
#define MAP_FACTOR    100
#define TPS_FACTOR    640
#define BRV_FACTOR   1000
#define TEMP_FACTOR   100
#define EGO_FACTOR  32768


#define idleManifoldPressure         3000       /* 30 kPa */
#define seaLevelKPa                 10000       /* 100 kPa */
#define maxExpectedBoost            30000       /* 300 kPa */

#define freezingPoint               27315       /* 0 Celcius */
#define roomTemperature             29315       /* 20 Celcius */
#define runningTemperature          35815       /* 85 Celcius */

#define halfThrottle                32768       /* 50% throttle */
#define runningVoltage              14400       /* 14.4 Volts */
#define idlePulseWidth               2000       /* ~1.5ms */
#define idleAirFlow                  1500       /* guessed */

// Cylinder volumes, value = (cc / 2000) * 65536
#define cylinderSize727cc           23828       /* 727cc per cylinder for Sean's 355ci LT1 */
#define cylinderSize575cc           18842       /* 575cc per cylinder for B230FT */
#define cylinderSize500cc           16384       /* 500cc per cylinder for my FE-DOHC */
#define cylinderSize450cc           14746       /* 450cc per cylinder for my F8-DOHC */
#define cylinderSize400cc           13107       /* 400cc per cylinder for the Toyota 4age */
#define cylinderSize324cc           10616       /* 324cc per cylinder for the Citroen G13 */
#define cylinderSize250cc            8176       /* 250cc per cylinder for Sean's 998cc R1 */

// Injector flows, value = (cc/min / 60) * 1024
#define injector1600cc              27307       /* 1600cc per minute for some random Bosch injectors :-p */
#define injector550cc                9387       /* 550cc per minute for my RX7 injectors */
#define injector525cc                8960       /* 42lb/hr with higher pressure, 50lb/hr, 10.5 conversion from RC, Sean's LT1 */
#define injector320cc                5461       /* 320cc per minute for bosch injectors in citroen turbo engine*/
#define injector230cc                3925       /* 230cc per minute for Yamaha R1 injectors http://www.witchhunter.com/flowdatapix/bcdh210.jpg */
#define injector213cc                3635       /* 213cc per minute for SilverTop 4age injectors */

#define densityOfOctane             22496       /* 703 grams per litre */
#define densityOfPetrol             23040       /* 720 grams per litre */
#define stoichiometricLambda        32768       /* Lambda = 1.0 */

/* Generated with http://www.diyefi.org/calculators.htm#stoich AFR x stoichiometricAFRDivisor (1024) = value */
#define stoichiometricAFRMethane    17659       /* 17.245 AFR */
#define stoichiometricAFRPropane    16061       /* 15.685 AFR */
#define stoichiometricAFRLPG        15973       /* 15.599 AFR */
#define stoichiometricAFRButane     15840       /* 15.469 AFR */
#define stoichiometricAFROctane     15500       /* 15.137 AFR */
#define stoichiometricAFRGasoline   15053       /* 14.700 AFR */
#define stoichiometricAFRXylene     14009       /* 13.681 AFR */
#define stoichiometricAFRToluene    13836       /* 13.512 AFR */
#define stoichiometricAFRBenzene    13601       /* 13.282 AFR */
#define stoichiometricAFRE85        10099       /*  9.862 AFR */
#define stoichiometricAFREthanol     9224       /*  9.008 AFR */
#define stoichiometricAFRMethanol    6630       /*  6.475 AFR */

#define batteryVoltageMin               0       /* Voltage read at lowest ADC reading */
#define batteryVoltageRange         24500       /* Voltage difference between lowest and highest ADC reading */

// 0.5 - 1.5 Lambda
#define LC1LambdaMin                16384       /* Lambda read at lowest ADC reading */
#define LC1LambdaMax                49152       /* Lambda read at highest ADC reading */
#define LC1LambdaRange              32768       /* Lambda difference between lowest and highest ADC reading */

// 0.68 - 1.36 Lambda
#define AFR1020LambdaMin            22282       /* Lambda read at lowest ADC reading */
#define AFR1020LambdaMax            44564       /* Lambda read at highest ADC reading */
#define AFR1020LambdaRange          22282       /* Lambda difference between lowest and highest ADC reading */


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
#define HondaDenso183kPaMin       -664       /* Pressure read at lowest ADC reading */
#define HondaDenso183kPaMax      18278       /* Pressure read at highest ADC reading */
#define HondaDenso183kPaRange                (HondaDenso183kPaMax - HondaDenso183kPaMin)

/* Toyota 2.3bar found on some Toyota Cynos 5E-FE cars (and probably many others), em_knaps and Lev8n are responsible for this data! */
#define ToyotaNA227kPaMin         2500       /* Pressure read at lowest ADC reading */
#define ToyotaNA227kPaMax        24700       /* Pressure read at highest ADC reading */
#define ToyotaNA227kPaRange                  (ToyotaNA227kPaMax - ToyotaNA227kPaMin)
// NOTE: The accuracy of this calibration is highly questionable. Please use the Honda units which is configured above and known to be accurate

/* GM 2bar found on Cyclone Turbo V6 and probably other cars too. TODO These numbers are probably not that accurate... */
#define GM2BarMin                  150       /* Pressure read at lowest ADC reading */
#define GM2BarMax                20000       /* Pressure read at highest ADC reading */
#define GM2BarRange                          (GM2BarMax - GM2BarMin)

/* www.freescale.com/files/sensors/doc/data_sheet/MPX4100A.pdf */
#define MPX4100AMin               1400       /* Pressure read at lowest ADC reading */
#define MPX4100AMax              10750       /* Pressure read at highest ADC reading */
#define MPX4100ARange                        (MPX4100AMax - MPX4100AMin)

/* www.freescale.com/files/sensors/doc/data_sheet/MPX4250A.pdf */
#define MPX4250AMin                800       /* Pressure read at lowest ADC reading */
#define MPX4250AMax              26000       /* Pressure read at highest ADC reading */
#define MPX4250ARange                        (MPX4250AMax - MPX4250AMin)

#define MPXH6300AMin              1200       /* Pressure read at lowest ADC reading */
#define MPXH6300AMax             32000       /* Pressure read at highest ADC reading */
#define MPXH6300ARange                       (MPXH6300AMax - MPXH6300AMin)

#define MPXH6400AMin              1200       /* Pressure read at lowest ADC reading */
#define MPXH6400AMax             42000       /* Pressure read at highest ADC reading */
#define MPXH6400ARange                       (MPXH6400AMax - MPXH6400AMin)

#define TPSDefaultMin                0       /* ADC reading at lowest throttle position */
#define TPSDefaultMax             1023       /* ADC reading at highest throttle position */

#define offIdleMAP                3000       /* 30kPa just above where MAP would be with closed throttle at idle */
#define nearlyWOTMAP              9500       /* 95kPa just below where MAP would be at WOT */

//#define lookedUpVEDivisor   512
//#define VEpercentageDivisor 100
#define oneHundredPercentVE 51200

//#define densityOfFuelDivisor       32
//#define densityOfFuelUnitDivisor 1000
#define densityOfFuelTotalDivisor 32000

#define divisorFor115200bps 22                  /* (40MHz / (16*115.2kHz)) = 21.7013889 */
/* http://www.google.com/search?hl=en&safe=off&q=22%2F%28%2840000000%2F16%29%2F115200%29&btnG=Search 1.376% error in speed */
/* http://www.google.com/search?hl=en&safe=off&q=40MHz%2F%2816*22%29&btnG=Search 113.636 kHz */

/* Not 1024, the number of gaps between them */
#define ADC_DIVISIONS 1023

#define INJECTION_CHANNELS  6    /* How many injection channels the code should support */

/* Valid RPAGE values :
 *    0xFF - linear
 *    0xFE - linear
 *    0xFD - default
 *    0xFC
 *    0xFB
 *    0xFA
 *    0xF9
 *    0xF8
 */
/* The reset value of RPAGE is 0xFD               */
/* The other 8k of linear RAM space is accessible */
/* through the RPAGE window with 0xFE and 0xFF    */
/* 0xFE refers to the 0x2000 to 0x3000 region     */
/* 0xFF refers to the 0x3000 to 0x4000 region     */
#define RPAGE_TUNE_ONE    0xF8
#define RPAGE_TUNE_TWO    0xF9
#define RPAGE_FUEL_ONE    0xFA
#define RPAGE_FUEL_TWO    0xFB
#define RPAGE_TIME_ONE    0xFC
#define RPAGE_TIME_TWO    0xFD
#define RPAGE_LINEAR      0xFD
#define RPAGE_MIN         0xF8
#define PPAGE_MIN         0xE0
#define EPAGE_MIN         0x?? // TODO

/* The TX and RX buffers are slightly larger than 2k because the RX buffer */
/* needs to also receive a header, checksum and attributes for the data    */
/* involved and the TX buffer needs to handle all of those two fold.       */
#define TX_BUFFER_SIZE      0x0820
#define RX_BUFFER_SIZE      0x0810
#define TransferTableSize     2048
#define TX_MAX_PAYLOAD_SIZE   2048


#else
    /* let us know if we are being untidy with headers */
    #warning "Header file GLOBALDEFINES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
