/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2013 Fred Cooke
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
 * @brief Struct typedefs for fixed configuration
 *
 * This file contains the struct data type definitions for fixed configuration items.
 *
 * Fixed, in this context means that it typically is not tuned in a live way
 * and therefore should not be cached in RAM while running. Usually these are
 * values that do not change such as cylinder volume, injector size, cylinder
 * count and other constants related to physical aspects of the engine setup.
 * When adding configuration values, please consider adding them here first.
 * If a value doesn't need to be live tunable definitely put it here instead.
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template */
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual    */
#ifndef FILE_FIXED_CONFIGS_H_SEEN
#define FILE_FIXED_CONFIGS_H_SEEN


/// Decoder and scheduling settings
typedef struct {
	unsigned char syncConfirmationsRunning;  ///< Upon losing sync while already running, how many sync points are required to consider resync achieved. This should be a relatively high number.
	unsigned char syncConfirmationsStarting; ///< Upon losing sync while starting, before having gained sync for the first time, how many sync points are required to consider initial sync achieved. This should be a near-zero for fast starts.
	unsigned short accelerationInputEventTimeTolerance; ///< This will be replaced: http://issues.freeems.org/view.php?id=118
	unsigned short decelerationInputEventTimeTolerance; ///< This will be replaced: http://issues.freeems.org/view.php?id=118
	unsigned short missingToothTolerance; ///< The future of this variable is uncertain!
} decoderSetting;


#define SOURCE_NORMAL 0
#define SOURCE_PRESET 1
#define SOURCE_LINEAR 2 ///< Read from the normal ADC pin, but process linearly. For bench use, mainly.

/**
 * Configuration that controls how the values of variables are determined.
 */
typedef struct {
	unsigned char BRV;
	unsigned char CHT;
	unsigned char IAT;
} sensorSource;


/** @brief Preset values for inputs and other variables
 *
 * In some cases you may want to ignore input readings and just use some
 * configured value for a particular sensor. These are the values used when you
 * choose to use a fixed reading instead of the real thing.
 */
typedef struct {
	unsigned short presetIAT;   ///< Preset variable value to override calculated values.
	unsigned short presetCHT;   ///< @copydoc presetIAT
	unsigned short presetBRV;   ///< @copydoc presetIAT

	unsigned short failsafeIATIgnition;  ///< Value to fall back on if a sensor fault is detected
	unsigned short failsafeIATInjection; ///< @copydoc failsafeIATIgnition
	unsigned short failsafeCHT; ///< @copydoc failsafeIATIgnition
	unsigned short failsafeBRV; ///< @copydoc failsafeIATIgnition
	unsigned short failsafeMAP; ///< @copydoc failsafeIATIgnition
	unsigned short failsafeAAP; ///< @copydoc failsafeIATIgnition
	unsigned short failsafeTPS; ///< @copydoc failsafeIATIgnition
} sensorPreset;


/// Ranges for sensors with linear config
typedef struct {
	signed short   MAPMinimum;    ///< Vacuum required to make the sensor reach 0 Volt output. Theoretical only, most do not rail.
	unsigned short MAPRange;      ///< Number of kPa between 0 Volts and 5 Volts.
	unsigned short AAPMinimum;    ///< @copydoc MAPMinimum
	unsigned short AAPRange;      ///< @copydoc MAPRange
	unsigned short EGOMinimum;    ///< Lambda that 0 Volt input corresponds to.
	unsigned short EGORange;      ///< Lambda difference between what 0V and 5V inputs correspond to.
	unsigned short BRVMinimum;    ///< Battery Voltage that 0 Volt input means. 0 Volts usually. TODO YAGNI usually? always? what/why?
	unsigned short BRVRange;      ///< TODO reword when above is fixed. Real world voltage difference between lowest and highest ADC reading (0 to 5V). FreeEMS standard is 24.5 Volts for 1k and 3k9 resistors on a 12v vehicle.
	unsigned short TPSMinimumADC; ///< This should be zero, but often isn't, this value is what the TPS input reads with the throttle fully closed.
	unsigned short TPSMaximumADC; ///< This should be the maximum ADC value, but often isn't. This value is what the TPS input reads with the throttle fully open.
} sensorRange;


/// Fuel injection settings
typedef struct {
	unsigned short perCylinderVolume;  ///< 500cc = 0.5l 0.5 * 32768 = pcv, so divide by 32768 go get litres */
	unsigned short injectorFlow;       ///< Injector flow of 240cc/min / 60 is 4ml/second is multiplied by 1024, so divide by 1024 for ml/second, divide by 1000 for litres/second */
	unsigned short stoichiometricAFR;  ///< 34 for hydrogen, all others less, figure is 14.7 * 1024, divide by 1024 to get AFR */
	unsigned short densityOfFuelAtSTP; ///< 703gm/litre for Octane. 32 * fuel density = number, divide by 32 for the real figure */
} engineSetting;


/// Settings related to serial communications
typedef struct {
	unsigned short baudDivisor; ///< The number used to set the data rate. 22 = (40MHz / (16*115.2kHz)) = 21.7013889
} serialSetting;


/// Settings for coarse bit bang outputs
typedef struct {
	unsigned char outputActions[256]; ///< Nothing, On, Off, Toggle for each input event.
	unsigned char* ports[4];         ///< The addresses of the port control registers.
	unsigned char  masks[4];         ///< The masks to apply to the ports above.
	unsigned char numberConfigured;  ///< How many to loop through, max of 4
} coarseBitBangSetting;


/// Settings for ignition and injection output scheduling
typedef struct {
	unsigned short anglesOfTDC[MAX_NUMBER_OF_OUTPUT_EVENTS];                ///< The effective TDC angle of the event in question.
	unsigned char outputEventPinNumbers[MAX_NUMBER_OF_OUTPUT_EVENTS];       ///< Which of the 6 pins should be associated with this event
	unsigned char schedulingConfigurationBits[MAX_NUMBER_OF_OUTPUT_EVENTS]; ///< 0 = ignition, 1 = injection
	unsigned short decoderEngineOffset;
	/**<
	 * Add decoderEngineOffset to code degrees to find 0/TDC for cyl/output 1
	 * or subtract from real degrees to get code degrees. Make this number
	 * larger to advance the base timing, make it smaller to retard it. IE, if
	 * you have 10btdc in your table, flat, and a timing light shows 5btdc on
	 * the engine, then increase this number by 5 degrees. More here:
	 *
	 * http://forum.diyefi.org/viewtopic.php?f=54&t=1523
	 */
	unsigned char numberOfConfiguredOutputEvents;   ///< Should match the used section of the three arrays above
	unsigned char numberOfInjectionsPerEngineCycle; ///< How much to divide the fuel pulse width by to get the per injection fuel pulse width
} schedulingSetting;


/// Enable flags for each cut
typedef struct {
	unsigned InjectionRPM :1; ///< @todo document this
	unsigned IgnitionRPM  :1; ///< @todo document this
	unsigned InjOverBoost :1; ///< @todo document this
	unsigned IgnOverBoost :1; ///< @todo document this
	unsigned Spare0 :1;
	unsigned Spare1 :1;
	unsigned Spare2 :1;
	unsigned Spare3 :1;
	unsigned Spare4 :1;
	unsigned Spare5 :1;
	unsigned Spare6 :1;
	unsigned Spare7 :1;
	unsigned Spare8 :1;
	unsigned Spare9 :1;
	unsigned SpareA :1;
	unsigned SpareB :1;
} cutEnabled;


/// Single cut/limiter
typedef struct {
	unsigned short disableThreshold;  ///< Level at which to disable outputs
	unsigned short reenableThreshold; ///< Level at which to re-enable outputs
} singleCut;


/// Cuts and limiters
typedef struct { // Comment represents normal and recommended cut type
	singleCut InjectionRPM;       ///< Injection, enabled by default at 5k with both and 200 RPM hysteresis
	singleCut IgnitionRPM;        ///< Ignition, enabled by default at 5k with both and 220 RPM hysteresis to ensure not lean when power comes back on
	singleCut OverBoost;          ///< Ignition, enabled by default, set to rail value for sensor, with large hysteresis, requires time out to operate safely

	// Disabled by default until duties are available, then enabled and fuel duty hard coded, elec duty optional, re enabled by time out not just hysteresis
//	singleCut InjectionFuelDuty;  ///< Both, disabled by default, until duties are available
//	singleCut InjectionElecDuty;  ///< Both, disabled by default, until duties are available

	// These require other logic in addition to the generic logic:
//	singleCut TwoStep;            ///< Ignition only or both, disabled by default
//	singleCut OverHeat;           ///< Ignition only or both, disabled by default
//	singleCut Overrun;            ///< Injection, disabled by default
//	singleCut FloodClear;         ///< Injection, disabled by default
	cutEnabled cutsEnabled;       ///< Override hard code on for desired fuel duty not to exceed 102.4% or similar
} cutAndLimiterSetting;


typedef struct {
	unsigned short* variable;
	unsigned short upperValue;
	unsigned short lowerValue;
	unsigned char* port;
	unsigned char mask;
	unsigned char flags; // for go high or low on success.
} singleSimpleGPOutput;


#define NUMBER_OF_OUTPUT_CONFIGS 8
typedef struct {
	singleSimpleGPOutput outputConfigs[NUMBER_OF_OUTPUT_CONFIGS];
	unsigned char numberConfigured;
	unsigned char spare;
} simpleGPIOSetting;


/// Settings related to sensor reading
typedef struct {
	unsigned short readingTimeout; ///< How often an ADC reading MUST occur.
	unsigned char numberOfADCsToRead;
	unsigned char fuelPumpPrimePeriod;
} sensorSetting;


#define LOAD_MAP 0
#define LOAD_TPS 1
#define LOAD_MAF 2
#define LOAD_AAP 3

#define ALGO_SPEED_DENSITY 0
#define ALGO_ALPHA_N       1
#define ALGO_MAF           2
#define ALGO_SD_AN_BLEND   3

#define DWELL_BRV   0
#define DWELL_RPM   1
#define DWELL_FIXED 2

/// Settings for fueling algorithms
typedef struct {
	unsigned char loadType;
	unsigned char algorithmType;
	unsigned char dwellType;
	unsigned char padding;
	unsigned short dwellFixedPeriod;
} algorithmSetting;


/// Input output pin usage configuration @todo TODO document this better
typedef struct {
//	unsigned char PullUpEnable;      ///< Enables per-port weak (~100k) internal pullups. See section 22.3.2.11 on page 834 of MC9S12XDP512RMV2.pdf
//	unsigned char ReducedDrive;      ///< Do NOT change this! This reduces drive strength and could harm your engine. See section 22.3.2.12 on page 835 of MC9S12XDP512RMV2.pdf
	unsigned char PWMEnable;         ///< Enables the PWM functionality for each pin. Note for 16 bit you the low order bit enabled. See section 8.3.2.1 on page 368 of MC9S12XDP512RMV2.pdf
	unsigned char PWMPolarity;       ///< Inverts the duty of the output. 1 means "duty is high portion", 0 means "duty is low portion". See section 8.3.2.2 on page 370 of MC9S12XDP512RMV2.pdf
	unsigned char PWMClock;          ///< TODO abstract this away
	unsigned char PWMClockPrescaler; ///< TODO abstract this away
	unsigned char PWMCenterAlign;    ///< See section 8.3.2.5 on page 372 of MC9S12XDP512RMV2.pdf
	unsigned char PWMControl;        ///< The high four bits concatenate the 8 bit PWM channels into 4 16 bit channels on a pair by pair basis. 4 joins (0,1), 5 joins (2,3), 6 joins (4,5), 7 joins (6,7).
	unsigned char PWMScalerA;        ///< TODO abstract this away
	unsigned char PWMScalerB;        ///< TODO abstract this away

	unsigned char PWMPeriod0; ///< TODO abstract this away
	unsigned char PWMPeriod1; ///< TODO abstract this away
	unsigned char PWMPeriod2; ///< TODO abstract this away
	unsigned char PWMPeriod3; ///< TODO abstract this away
	unsigned char PWMPeriod4; ///< TODO abstract this away
	unsigned char PWMPeriod5; ///< TODO abstract this away
	unsigned char PWMPeriod6; ///< TODO abstract this away
	unsigned char PWMPeriod7; ///< TODO abstract this away

	unsigned char PWMInitialDuty0; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
	unsigned char PWMInitialDuty1; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
	unsigned char PWMInitialDuty2; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
	unsigned char PWMInitialDuty3; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
	unsigned char PWMInitialDuty4; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
	unsigned char PWMInitialDuty5; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
	unsigned char PWMInitialDuty6; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.
	unsigned char PWMInitialDuty7; ///< The duty cycle at power up. Usually unimportant due to being overwritten by the algorithm involved milliseconds later.

	unsigned char PortInitialValueA; ///< The state of the port at power up. @see PortDirectionA
	unsigned char PortInitialValueB; ///< The state of the port at power up. @see PortDirectionB
	unsigned char PortInitialValueC; ///< The state of the port at power up. @see PortDirectionC
	unsigned char PortInitialValueD; ///< The state of the port at power up. @see PortDirectionD
	unsigned char PortInitialValueE; ///< The state of the port at power up. @see PortDirectionE
	unsigned char PortInitialValueH; ///< The state of the port at power up. @see PortDirectionH
	unsigned char PortInitialValueJ; ///< The state of the port at power up. @see PortDirectionJ
	unsigned char PortInitialValueK; ///< The state of the port at power up. @see PortDirectionK
	unsigned char PortInitialValueM; ///< The state of the port at power up. @see PortDirectionM
	unsigned char PortInitialValueP; ///< The state of the port at power up. @see PortDirectionP
	unsigned char PortInitialValueS; ///< The state of the port at power up. @see PortDirectionS
	unsigned char PortInitialValueT; ///< The state of the port at power up. @see PortDirectionT Currently this setting is ignored. TODO Make it take effect on unused port T pins.

	unsigned char PortDirectionA; ///< @see PortDirectionB Pin 6 is the Firmware Load switch input AND the Check Engine Light output. Pin 7 is the standard fuel pump relay drive pin. These bits are therefore overridden and have no effect.
	unsigned char PortDirectionB; ///< Whether pins act as inputs or outputs, 1 means output, 0 means input. 0 is the default for most pins. Note, peripheral modules which use these pins override this control.
	unsigned char PortDirectionC; ///< @see PortDirectionB
	unsigned char PortDirectionD; ///< @see PortDirectionB
	unsigned char PortDirectionE; ///< @see PortDirectionB This port is associated with various control bits. Extreme care should be taken when using them, regardless of what for. Pins 0 and 1 are always inputs regardless of this setting.
	unsigned char PortDirectionH; ///< @see PortDirectionB This port is associated with the SPI1 (0-3), SPI2 (4-7), SCI4 (4,5), and SCI5 (6,7) modules.
	unsigned char PortDirectionJ; ///< @see PortDirectionB This port is associated with the SCI2 (0,1), I2C0 (6,7), I2C1 (4,5), and CAN4 (6,7) modules.
	unsigned char PortDirectionK; ///< @see PortDirectionB
	unsigned char PortDirectionM; ///< @see PortDirectionB This port is associated with the CAN0 (0,1), CAN1 (2,3), CAN2 (4,5), CAN3 (6,7), and SCI3 (6,7) modules.
	unsigned char PortDirectionP; ///< @see PortDirectionB This port is associated with the PWM (0-7) module.
	unsigned char PortDirectionS; ///< @see PortDirectionB This port is associated with the SCI0 (0,1), SCI1 (2,3), and SPI0 (4-7) modules. Primary communication is over SCI0, therefore the control bits for those pins are overridden to ensure correct operation, and have no effect.
	unsigned char PortDirectionT; ///< @see PortDirectionB This port is associated with the ECT (0-7) module. Currently this setting is ignored. TODO Make it take effect on unused port T pins.
} inputOutputSetting;


#define userTextFieldArrayLength1 (flashSectorSize - (sizeof(engineSetting) + sizeof(serialSetting) + sizeof(coarseBitBangSetting) + sizeof(schedulingSetting) + sizeof(cutAndLimiterSetting) + sizeof(simpleGPIOSetting)))
/**
 * One of two structs of fixed configuration data such as physical parameters etc.
 *
 * If you add something here, please ensure you update all of the following :
 * - Default values in the initial definitions in FixedConfig1.c and FixedConfig2.c
 * - The lookupBlockDetails() function in blockDetailsLookup.c
 * - The JSON data map and other related firmware interface definition files
 */
typedef struct {
	engineSetting engineSettings; ///< @see engineSetting
	serialSetting serialSettings; ///< @see serialSetting
	coarseBitBangSetting coarseBitBangSettings; ///< @see coarseBitBangSetting
	schedulingSetting schedulingSettings;       ///< @see schedulingSetting
	cutAndLimiterSetting cutAndLimiterSettings; ///< @see cutAndLimiterSetting
	simpleGPIOSetting simpleGPIOSettings;       ///< @see simpleGPIOSetting
	unsigned char userTextField[userTextFieldArrayLength1]; ///< For on-board meta-data such as which vehicle the unit is from, put your personal tuning notes here!
} fixedConfig1;


#define userTextFieldArrayLength2 (flashSectorSize - (sizeof(sensorSource) + sizeof(sensorPreset) + sizeof(sensorRange) + sizeof(sensorSetting) + sizeof(algorithmSetting) + sizeof(inputOutputSetting) + sizeof(decoderSetting)))
/** @copydoc fixedConfig1 */
typedef struct {
	sensorSource sensorSources;                              ///< @see sensorSource
	sensorPreset sensorPresets;                              ///< @see sensorPreset
	sensorRange sensorRanges;                                ///< @see sensorRange
	sensorSetting sensorSettings;                            ///< @see sensorSetting
	algorithmSetting algorithmSettings;                      ///< @see algorithmSetting
	inputOutputSetting inputOutputSettings;                  ///< @see inputOutputSetting
	decoderSetting decoderSettings;                          ///< @see decoderSetting
	unsigned char userTextField2[userTextFieldArrayLength2]; ///< For on-board meta-data such as which vehicle the unit is from, put your personal tuning notes here!
} fixedConfig2;


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file FIXED_CONFIGS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
