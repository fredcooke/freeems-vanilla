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
 * @brief Global scaling values and macros
 *
 * A single source of internally scaled fixed point numbers.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template    */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual       */
#ifndef FILE_SCALERDEFINES_H_SEEN
#define FILE_SCALERDEFINES_H_SEEN


/// Ensures that configuration values are properly rounded and not truncated.
#define ROUND(FLOATING_POINT_VALUE) ((FLOATING_POINT_VALUE) + 0.5) // Note, if integer math is used to generate the argument, it won't work.


// All fixed point configuration values
#define IGNITION_TIMING_FACTOR 1024  ///< Temporary ignition timing table scaling factor. Warning, to be changed to 8 bit!
#define TEMPERATURE_K_FACTOR    100  ///< Scaling factor for temperature fixed point arithmetic
#define PRESSURE_KPA_FACTOR     100  ///< Scaling factor for pressure fixed point arithmetic
#define VOLTAGE_FACTOR         1000  ///< Scaling factor for Voltage fixed point arithmetic
#define LAMBDA_FACTOR         32768  ///< Scaling factor for EGO and Lambda fixed point arithmetic
#define RPM_FACTOR                2  ///< Scaling factor for RPM fixed point arithmetic
#define ANGLE_FACTOR             50U ///< Scaling factor for engine angle scheduling fixed point arithmetic. Suffix is necessary otherwise 8 bit is assumed.
#define VE_FACTOR               512  ///< Scaling factor for Volumetric Efficiency fixed point arithmetic
#define AFR_FACTOR             1024  ///< Scaling factor for Air:Fuel Ratio fixed point arithmetic
#define FUEL_DENSITY_FACTOR      32  ///< Scaling factor for fuel density (grams per litre) fixed point arithmetic
#define PW_TICK_FACTOR         1250  ///< Scaling factor for raw pulse width fixed point arithmetic;
#define PERCENT_FACTOR          640  ///< Scaling factor for percentage fixed point arithmetic
#define CYLINDER_VOLUME_LIMIT  2000  ///< Cylinder volume, in cc, can be anything less than this
#define INJECTOR_FLOW_LIMIT    3840  ///< Injector flow, in cc/min can be anything less than this
#define WARM_UP_LIMIT           400  ///< Warm up enrichment percentage, can be anything less than this

// Convenience values for convenience wrappers
#define TEMPERATURE_C_TO_K_OFFSET  273.15 ///< Offset for human degrees Celsius configuration items
#define FUEL_DENSITY_UNIT_FACTOR  1000    ///< Part of the original speed density mathematics, still in use


// All scaler macros!
// Warning: Surround your argument with brackets to ensure order of operations!
// For table use, choose very short, for config use, choose very clear.
// For configuration only, live code will be bloated by cast to long which is required to prevent configuration overflows wrapping to zero.
#define KPA(PRESSURE)                   (signed long)ROUND((PRESSURE) * (double)PRESSURE_KPA_FACTOR)
#define DEGREES_K(TEMPERATURE)        (unsigned long)ROUND((TEMPERATURE) * (double)TEMPERATURE_K_FACTOR)
#define CC_PER_MINUTE(FLOW_RATE)      (unsigned long)ROUND(((FLOW_RATE) / (double)INJECTOR_FLOW_LIMIT) * 65536)
#define CYLINDER_VOLUME(VOLUME_IN_CC) (unsigned long)ROUND(((VOLUME_IN_CC) / (double)CYLINDER_VOLUME_LIMIT) * 65536)
#define VOLTS(VOLTAGE)                (unsigned long)ROUND((VOLTAGE) * (double)VOLTAGE_FACTOR)
#define LAMBDA(LAMBDA_VALUE)          (unsigned long)ROUND((LAMBDA_VALUE) * (double)LAMBDA_FACTOR)
#define RPM(ENGINE_SPEED)             (unsigned long)ROUND((ENGINE_SPEED) * (double)RPM_FACTOR)
#define ANGLE(CRANK_DEGREES)          (unsigned long)ROUND((CRANK_DEGREES) * (double)ANGLE_FACTOR)
#define STOICH_AFR(AIR_FUEL_RATIO)    (unsigned long)ROUND((AIR_FUEL_RATIO) * (double)AFR_FACTOR)
#define FUEL_DENSITY(DENSITY)         (unsigned long)ROUND((DENSITY) * (double)FUEL_DENSITY_FACTOR)
#define PW_MS(PW_MILLISECONDS)        (unsigned long)ROUND((PW_MILLISECONDS) * (double)PW_TICK_FACTOR)
#define PERCENT(PERCENTAGE)           (unsigned long)ROUND((PERCENTAGE) * (double)PERCENT_FACTOR)
#define ACCEL_TIME_TOL(PERCENTAGE)    (unsigned long)((100/(100 + (double)PERCENTAGE)) * 1000) // This code is getting changed a lot, hence literals
#define DECEL_TIME_TOL(PERCENTAGE)    (unsigned long)(((100 + (double)PERCENTAGE)/100) * 1000) // This code is getting changed a lot, hence literals

// One-off configuration stuff
#define SCI_BAUD_DIVISOR(BAUD)        (unsigned long)ROUND(40000000 / ((double)(BAUD) * 16)) // 40MHz / (16*115.2kHz) TODO pull 40MHz out of clock rate stuff

// For table data
#define IT(TIMING_BTDC)               (unsigned long)ROUND((TIMING_BTDC) * (double)IGNITION_TIMING_FACTOR)
#define VE(VOLUMETRIC_EFFICIENCY)     (unsigned long)ROUND((VOLUMETRIC_EFFICIENCY) * (double)VE_FACTOR)
#define LR(LAMBDA_RATIO)              LAMBDA(LAMBDA_RATIO)   // Shortcut for table use, same as above
#define PC(PERCENTAGE)                PERCENT(PERCENTAGE)    // Shortcut for table use, same as above
#define C(TEMPERATURE)                DEGREES_C(TEMPERATURE) // Shortcut for table use, same as below
#define V(VOLTAGE)                    VOLTS(VOLTAGE)         // Shortcut for table use, same as above
#define W(PERCENTAGE)                 (unsigned long)ROUND(((PERCENTAGE) / (double)WARM_UP_LIMIT) * 65536)
#define T(PW_MILLISECONDS)            PW_MS(PW_MILLISECONDS) // Shortcut for table use, same as above

// Convenience wrappers for various non-native units
#define CC_PER_MINUTE_85(FLOW_RATE)   CC_PER_MINUTE((FLOW_RATE) * (100 / 85.0))
#define DEGREES_C(TEMPERATURE)        DEGREES_K((TEMPERATURE) + TEMPERATURE_C_TO_K_OFFSET)


#else
    /* let us know if we are being untidy with headers */
    #warning "Header file SCALERDEFINES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
