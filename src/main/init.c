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
 * @brief Initialise the devices state
 *
 * Setup, configure and initialise all aspects of the devices state including
 * but not limited to:
 *
 * - Setup the bus clock speed
 * - Configuration based variable initialisation
 * - I/O register behaviour and initial state
 * - Configure and enable interrupts
 * - Copy tunable data up to RAM from flash
 * - Configure peripheral module behaviour
 */


#define INIT_C
#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/utils.h"
#include "inc/commsISRs.h"
#include "inc/pagedLocationBuffers.h"
#include "inc/init.h"
#include "inc/decoderInterface.h"
#include "inc/xgateVectors.h"
#include <string.h>


/** @brief The main top level init
 *
 * The main init function to be called from main.c before entering the main
 * loop. This function is simply a delegator to the finer grained special
 * purpose init functions.
 */
void init(){
	ATOMIC_START();         /* Disable ALL interrupts while we configure the board ready for use */
	initPLL();              /* Set up the PLL and use it */
	initGPIO();
	initPWM();
	initADC();
	initAllPagedRAM();      /* Copy table and config blocks of data from flash to the paged RAM blocks for fast data lookup */
	initVariables();        /* Initialise the rest of the running variables etc */
	initFlash();            /* TODO, finalise this */
	initECTTimer();         /* TODO move this to inside config in an organised way. Set up the timer module and its various aspects */
//	initPITTimer();         /* TODO ditto... */
	initSCIStuff();         /* Setup the sci module(s) that we will use. */
	initConfiguration();    /* TODO Set user/feature/config up here! */
#ifdef XGATE
	initXgate();            /* Fred is a legend, for good reason as of now */
#endif
	initInterrupts();       /* still last, reset timers, enable interrupts here TODO move this to inside config in an organised way. Set up the rest of the individual interrupts */
	ATOMIC_END();           /* Re-enable any configured interrupts */
}


#ifdef XGATE
#include "xgateInit.c"
#endif


/** @brief Set the PLL clock frequency
 *
 * Set the Phase Locked Loop to our desired frequency (80MHz) and enable PLL.
 */
void initPLL(){
	CLKSEL &= PLLSELOFF;  /* Switches to base external OSCCLK to ensure PLL is not being used (off out of reset, but not sure if the monitor turns it on before passing control or not) */
	PLLCTL &= PLLOFF;     /* Turn the PLL device off to adjust its speed (on by default out of reset) */
	REFDV = PLLDIVISOR;   /* 16MHz / (3 + 1) = 4MHz Bus frequency */
	SYNR = PLLMULTIPLIER; /* 4MHz * (9 + 1) = 40MHz Bus frequency */
	PLLCTL |= PLLON;      /* Turn the PLL device back on again at 80MHz */
	enablePLL();
}

/** @brief Switch to using PLL
 *
 * Switch to using PLL for clock (40MHz bus speed). Interrupt is enabled elsewhere.
 *
 * Note: Requires busy wait loop, only for init and emergency use.
 *
 * @todo Should be limited, and have break out with error code and fall back mechanism.
 */
void enablePLL(){
	while (!(CRGFLG & PLLLOCK)){
		/* Do nothing while we wait till the PLL loop locks onto the target frequency. */
		/* Target frequency is given by (2 * (crystal frequency / (REFDV + 1)) * (SYNR + 1)) */
		/* Bus frequency is half PLL frequency and given by ((crystal frequency / (REFDV + 1)) * (SYNR + 1)) */
	}

	CLKSEL = PLLSEL; /* Switches to PLL clock for internal bus frequency        */
	/* from MC9S12XDP512V2.pdf Section 2.4.1.1.2 page 101 Third paragraph       */
	/* "This takes a MAXIMUM of 4 OSCCLK clock cylces PLUS 4 PLL clock cycles"  */
	/* "During this time ALL clocks freeze, and CPU activity ceases"            */
	/* Therefore there is no point waiting for this to occur, we already are... */
}


/// Set up the analogue inputs
void initADC(){
	// Currently not true, and may never be: TODO When the port something uses
	// is changed via the tuning interface, the configuration will be done on
	// the fly, and the value burned to flash such that next boot happens
	// correctly and current running devices are used in that way.

	/* Digital input buffers on the ATD channels are off by default, leave them this way! */
	//ATD0DIEN = ZEROS; /* You are out of your mind if you waste this on digital Inputs */
	//ATD1DIEN0 = ZEROS; /* You are out of your mind if you waste this on digital Inputs (NOT-bonded, can't use) */
	//ATD1DIEN1 = ZEROS; /* You are out of your mind if you waste this on digital Inputs */

	/* And configure them all for analog input */
	//ATD0CTL0 = 0x07/* With mult turned on this is required to be set to cause wrap around, but is correct out of reset */
	//ATD0CTL1 = 0x07/* Trigger and interrupt configuration, unused for now. */
	ATD0CTL2 = 0xC0; /* Turns on the ADC block and sets auto flag clear */
	ATD0CTL3 = 0x40; /* Set sequence length = 8 */
	ATD0CTL4 = 0x73; /* Set the ADC clock and sample period for best accuracy */
	ATD0CTL5 = 0xB0; /* Sets justification to right, multiplex and scan all channels. Writing to this causes conversions to begin */

	/* And configure them all for analog input */
	ATD1CTL0 = 0x07; /* TODO bring this out of config based on chip variant variable. Sets wrap on 8th ADC because we can't use the other 8 on 112 pin version */
	//ATD0CTL1 = 0x07/* Trigger and interrupt configuration, unused for now. */
	ATD1CTL2 = 0xC0; /* Turns on the ADC block and sets auto flag clear */
	ATD1CTL3 = 0x40; /* Set sequence length = 8 */
	ATD1CTL4 = 0x73; /* Set the ADC clock and sample period for best accuracy */
	ATD1CTL5 = 0xB0; /* Sets justification to right, multiplex and scan all channels. Writing to this causes conversions to begin */
}


/// Set up the PWM module from configuration
void initPWM(){
	/* TODO PWM channel concatenation for high resolution */
	// join channel pairs together here (needs 16 bit regs enabled too)
	/* TODO Initialise pwm channels with frequency, and initial duty for real use */
	// initial PWM settings for testing

	PWMPER0 = fixedConfigs2.inputOutputSettings.PWMPeriod0;
	PWMPER1 = fixedConfigs2.inputOutputSettings.PWMPeriod1;
	PWMPER2 = fixedConfigs2.inputOutputSettings.PWMPeriod2;
	PWMPER3 = fixedConfigs2.inputOutputSettings.PWMPeriod3;
	PWMPER4 = fixedConfigs2.inputOutputSettings.PWMPeriod4;
	PWMPER5 = fixedConfigs2.inputOutputSettings.PWMPeriod5;
	PWMPER6 = fixedConfigs2.inputOutputSettings.PWMPeriod6;
	PWMPER7 = fixedConfigs2.inputOutputSettings.PWMPeriod7;

	PWMDTY0 = fixedConfigs2.inputOutputSettings.PWMInitialDuty0;
	PWMDTY1 = fixedConfigs2.inputOutputSettings.PWMInitialDuty1;
	PWMDTY2 = fixedConfigs2.inputOutputSettings.PWMInitialDuty2;
	PWMDTY3 = fixedConfigs2.inputOutputSettings.PWMInitialDuty3;
	PWMDTY4 = fixedConfigs2.inputOutputSettings.PWMInitialDuty4;
	PWMDTY5 = fixedConfigs2.inputOutputSettings.PWMInitialDuty5;
	PWMDTY6 = fixedConfigs2.inputOutputSettings.PWMInitialDuty6;
	PWMDTY7 = fixedConfigs2.inputOutputSettings.PWMInitialDuty7;

	PWMCLK   = fixedConfigs2.inputOutputSettings.PWMClock;
	PWMPRCLK = fixedConfigs2.inputOutputSettings.PWMClockPrescaler;
	PWMSCLA  = fixedConfigs2.inputOutputSettings.PWMScalerA;
	PWMSCLB  = fixedConfigs2.inputOutputSettings.PWMScalerB;
	PWMPOL   = fixedConfigs2.inputOutputSettings.PWMPolarity;
	PWMCAE   = fixedConfigs2.inputOutputSettings.PWMCenterAlign;
	PWMCTL   = fixedConfigs2.inputOutputSettings.PWMControl & 0xF0; // Disallow access to power saving and reserved bits
	PWME     = fixedConfigs2.inputOutputSettings.PWMEnable; // MUST be done after concatenation with PWMCTL
}


/// Set up all the pin states as per configuration, but protect key states.
void initGPIO(){
	// Set the initial pin state of pins configured as output
	PORTA = fixedConfigs2.inputOutputSettings.PortInitialValueA | BIT6 | BIT7; // Mask the fuel pump relay and CEL pins on
	PORTB = fixedConfigs2.inputOutputSettings.PortInitialValueB;
	PORTC = fixedConfigs2.inputOutputSettings.PortInitialValueC;
	PORTD = fixedConfigs2.inputOutputSettings.PortInitialValueD;
	PORTE = (fixedConfigs2.inputOutputSettings.PortInitialValueE | BIT7) & (NBIT5 & NBIT6); // 7 should be high, and 5 and 6 low, to reduce current draw. The rest don't matter. 0 and 1 are not outputs.
	PORTH = fixedConfigs2.inputOutputSettings.PortInitialValueH;
	PORTJ = fixedConfigs2.inputOutputSettings.PortInitialValueJ;
	PORTK = fixedConfigs2.inputOutputSettings.PortInitialValueK;
	PORTM = fixedConfigs2.inputOutputSettings.PortInitialValueM;
	PORTP = fixedConfigs2.inputOutputSettings.PortInitialValueP;
	PORTS = fixedConfigs2.inputOutputSettings.PortInitialValueS | 0x02; // Mask the SCI0 TX pin to high between transmissions!
	PORTT = 0x00; // Set all ECT pins to off state, only matters for 2-7, and only if being used. TODO mask this dynamically based on decoder type and configured channels.
	/* AD0PT1 You are out of your mind if you waste this on digital Inputs */
	/* AD1PT1 You are out of your mind if you waste this on digital Inputs */

	// Initialise the Data Direction Registers
	DDRA = fixedConfigs2.inputOutputSettings.PortDirectionA | BIT6 | BIT7; // Mask the fuel pump relay and CEL pins as outputs
	DDRB = fixedConfigs2.inputOutputSettings.PortDirectionB;
	DDRC = fixedConfigs2.inputOutputSettings.PortDirectionC;
	DDRD = fixedConfigs2.inputOutputSettings.PortDirectionD;
	DDRE = fixedConfigs2.inputOutputSettings.PortDirectionE; // No need to mask off bits 0 and 1, they have no effect and are always inputs.
	DDRH = fixedConfigs2.inputOutputSettings.PortDirectionH;
	DDRJ = fixedConfigs2.inputOutputSettings.PortDirectionJ;
	DDRK = fixedConfigs2.inputOutputSettings.PortDirectionK;
	DDRM = fixedConfigs2.inputOutputSettings.PortDirectionM;
	DDRP = fixedConfigs2.inputOutputSettings.PortDirectionP;
	DDRS = fixedConfigs2.inputOutputSettings.PortDirectionS & 0xFE; // Mask the SCI0 RX pin as input between receiving
	DDRT = 0xFC; // Set ECT pins 0,1 to IC and 2:7 to OC (8) TODO mask this dynamically based on decoder type and configured channels.
	/* AD0DDR1 You are out of your mind if you waste this on digital Inputs */
	/* AD1DDR1 You are out of your mind if you waste this on digital Inputs */
}


/** @brief Buffer lookup tables addresses
 *
 * Save pointers to the lookup tables which live in paged flash.
 */
void initLookupAddresses(){
	IATTransferTableLocation = (void*)&IATTransferTable;
	CHTTransferTableLocation = (void*)&CHTTransferTable;
	MAFTransferTableLocation = (void*)&MAFTransferTable;
	TestTransferTableLocation = (void*)&TestTransferTable;
}


/** @brief Buffer fuel tables addresses
 *
 * Save pointers to the fuel tables which live in paged flash.
 */
void initFuelAddresses(){
	/* Setup addresses within the page to avoid warnings */
	VETableMainFlashLocation       = (void*)&VETableMainFlash;
	VETableSecondaryFlashLocation  = (void*)&VETableSecondaryFlash;
	AirflowTableFlashLocation      = (void*)&AirflowTableFlash;
	LambdaTableFlashLocation       = (void*)&LambdaTableFlash;
	VETableMainFlash2Location      = (void*)&VETableMainFlash2;
	VETableSecondaryFlash2Location = (void*)&VETableSecondaryFlash2;
	AirflowTableFlash2Location     = (void*)&AirflowTableFlash2;
	LambdaTableFlash2Location      = (void*)&LambdaTableFlash2;
}


/** @brief Copy fuel tables to RAM
 *
 * Initialises the fuel tables in RAM by copying them up from flash.
 */
void initPagedRAMFuel(void){
	/* Copy the tables from flash to RAM */
	RPAGE = RPAGE_FUEL_ONE;
	memcpy((void*)&TablesA, VETableMainFlashLocation,       sizeof(mainTable));
	memcpy((void*)&TablesB, VETableSecondaryFlashLocation,  sizeof(mainTable));
	memcpy((void*)&TablesC, AirflowTableFlashLocation,      sizeof(mainTable));
	memcpy((void*)&TablesD, LambdaTableFlashLocation,       sizeof(mainTable));
	RPAGE = RPAGE_FUEL_TWO;
	memcpy((void*)&TablesA, VETableMainFlash2Location,      sizeof(mainTable));
	memcpy((void*)&TablesB, VETableSecondaryFlash2Location, sizeof(mainTable));
	memcpy((void*)&TablesC, AirflowTableFlash2Location,     sizeof(mainTable));
	memcpy((void*)&TablesD, LambdaTableFlash2Location,      sizeof(mainTable));
}


/** @brief Buffer timing tables addresses
 *
 * Save pointers to the timing tables which live in paged flash.
 */
void initTimingAddresses(){
	/* Setup addresses within the page to avoid warnings */
	IgnitionAdvanceTableMainFlashLocation        = (void*)&IgnitionAdvanceTableMainFlash;
	IgnitionAdvanceTableSecondaryFlashLocation   = (void*)&IgnitionAdvanceTableSecondaryFlash;
	InjectionAdvanceTableMainFlashLocation       = (void*)&InjectionAdvanceTableMainFlash;
	InjectionAdvanceTableSecondaryFlashLocation  = (void*)&InjectionAdvanceTableSecondaryFlash;
	IgnitionAdvanceTableMainFlash2Location       = (void*)&IgnitionAdvanceTableMainFlash2;
	IgnitionAdvanceTableSecondaryFlash2Location  = (void*)&IgnitionAdvanceTableSecondaryFlash2;
	InjectionAdvanceTableMainFlash2Location      = (void*)&InjectionAdvanceTableMainFlash2;
	InjectionAdvanceTableSecondaryFlash2Location = (void*)&InjectionAdvanceTableSecondaryFlash2;
}


/** @brief Copy timing tables to RAM
 *
 * Initialises the timing tables in RAM by copying them up from flash.
 */
void initPagedRAMTime(){
	/* Copy the tables from flash to RAM */
	RPAGE = RPAGE_TIME_ONE;
	memcpy((void*)&TablesA, IgnitionAdvanceTableMainFlashLocation,        sizeof(mainTable));
	memcpy((void*)&TablesB, IgnitionAdvanceTableSecondaryFlashLocation,   sizeof(mainTable));
	memcpy((void*)&TablesC, InjectionAdvanceTableMainFlashLocation,       sizeof(mainTable));
	memcpy((void*)&TablesD, InjectionAdvanceTableSecondaryFlashLocation,  sizeof(mainTable));
	RPAGE = RPAGE_TIME_TWO;
	memcpy((void*)&TablesA, IgnitionAdvanceTableMainFlash2Location,       sizeof(mainTable));
	memcpy((void*)&TablesB, IgnitionAdvanceTableSecondaryFlash2Location,  sizeof(mainTable));
	memcpy((void*)&TablesC, InjectionAdvanceTableMainFlash2Location,      sizeof(mainTable));
	memcpy((void*)&TablesD, InjectionAdvanceTableSecondaryFlash2Location, sizeof(mainTable));
}


/** @brief Buffer tunable tables addresses
 *
 * Save pointers to the tunable tables which live in paged flash and their
 * sub-sections too.
 */
void initTunableAddresses(){
	/* Setup addresses within the page to avoid warnings */
	SmallTablesAFlashLocation  = (void*)&SmallTablesAFlash;
	SmallTablesBFlashLocation  = (void*)&SmallTablesBFlash;
	SmallTablesCFlashLocation  = (void*)&SmallTablesCFlash;
	SmallTablesDFlashLocation  = (void*)&SmallTablesDFlash;
	SmallTablesAFlash2Location = (void*)&SmallTablesAFlash2;
	SmallTablesBFlash2Location = (void*)&SmallTablesBFlash2;
	SmallTablesCFlash2Location = (void*)&SmallTablesCFlash2;
	SmallTablesDFlash2Location = (void*)&SmallTablesDFlash2;

	/* TablesA */
	dwellDesiredVersusVoltageTableLocation    = (void*)&SmallTablesAFlash.dwellDesiredVersusVoltageTable;
	dwellDesiredVersusVoltageTable2Location   = (void*)&SmallTablesAFlash2.dwellDesiredVersusVoltageTable;
	injectorDeadTimeTableLocation             = (void*)&SmallTablesAFlash.injectorDeadTimeTable;
	injectorDeadTimeTable2Location            = (void*)&SmallTablesAFlash2.injectorDeadTimeTable;
	postStartEnrichmentTableLocation          = (void*)&SmallTablesAFlash.postStartEnrichmentTable;
	postStartEnrichmentTable2Location         = (void*)&SmallTablesAFlash2.postStartEnrichmentTable;
	engineTempEnrichmentTableFixedLocation    = (void*)&SmallTablesAFlash.engineTempEnrichmentTableFixed;
	engineTempEnrichmentTableFixed2Location   = (void*)&SmallTablesAFlash2.engineTempEnrichmentTableFixed;
	primingVolumeTableLocation                = (void*)&SmallTablesAFlash.primingVolumeTable;
	primingVolumeTable2Location               = (void*)&SmallTablesAFlash2.primingVolumeTable;
	engineTempEnrichmentTablePercentLocation  = (void*)&SmallTablesAFlash.engineTempEnrichmentTablePercent;
	engineTempEnrichmentTablePercent2Location = (void*)&SmallTablesAFlash2.engineTempEnrichmentTablePercent;
	dwellVersusRPMTableLocation               = (void*)&SmallTablesAFlash.dwellVersusRPMTable;
	dwellVersusRPMTable2Location              = (void*)&SmallTablesAFlash2.dwellVersusRPMTable;
	blendVersusRPMTableLocation               = (void*)&SmallTablesAFlash.blendVersusRPMTable;
	blendVersusRPMTable2Location              = (void*)&SmallTablesAFlash2.blendVersusRPMTable;

	/* TablesB */
	loggingSettingsLocation       = (void*)&SmallTablesBFlash.loggingSettings;
	loggingSettings2Location      = (void*)&SmallTablesBFlash2.loggingSettings;
	perCylinderFuelTrimsLocation  = (void*)&SmallTablesBFlash.perCylinderFuelTrims;
	perCylinderFuelTrims2Location = (void*)&SmallTablesBFlash2.perCylinderFuelTrims;

	/* TablesC */
	// TODO

	/* TablesD */
	// TODO

	/* filler defs */
	fillerALocation  = (void*)&SmallTablesAFlash.filler;
	fillerA2Location = (void*)&SmallTablesAFlash2.filler;
	fillerBLocation  = (void*)&SmallTablesBFlash.filler;
	fillerB2Location = (void*)&SmallTablesBFlash2.filler;
	fillerCLocation  = (void*)&SmallTablesCFlash.filler;
	fillerC2Location = (void*)&SmallTablesCFlash2.filler;
	fillerDLocation  = (void*)&SmallTablesDFlash.filler;
	fillerD2Location = (void*)&SmallTablesDFlash2.filler;
}


/**
 *
 */
void initPagedRAMTune(){
	/* Copy the tables from flash to RAM */
	RPAGE = RPAGE_TUNE_ONE;
	memcpy((void*)&TablesA, SmallTablesAFlashLocation, sizeof(mainTable));
	memcpy((void*)&TablesB, SmallTablesBFlashLocation, sizeof(mainTable));
	memcpy((void*)&TablesC, SmallTablesCFlashLocation, sizeof(mainTable));
	memcpy((void*)&TablesD, SmallTablesDFlashLocation, sizeof(mainTable));
	RPAGE = RPAGE_TUNE_TWO;
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&& WARNING &&&&&&&&&&&&&&&&&&&&&&&&&&&&&& //
	//    You will get garbage if you use table switching at this time!!!    //
	//         XGATE code being run from this region temporarily!!!          //
	//   Writing to these tables WILL corrupt XGATE code/kill your engine!   //
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&& WARNING &&&&&&&&&&&&&&&&&&&&&&&&&&&&&& //
	//memcpy(xgateSchedRAMAddress, xgateSchedFlashAddress, (xgateSchedEnd - xgateSched));
	//memcpy(xgateInjectorsOnRAMAddress, xgateInjectorsOnFlashAddress, (xgateInjectorsOnEnd - xgateInjectorsOn));
	//memcpy(xgateInjectorsOffRAMAddress, xgateInjectorsOffFlashAddress, (xgateInjectorsOffEnd - xgateInjectorsOff));
//	memcpy((void*)&TablesA,	SmallTablesAFlash2Location, sizeof(mainTable));
//	memcpy((void*)&TablesB,	SmallTablesBFlash2Location, sizeof(mainTable));
//	memcpy((void*)&TablesC,	SmallTablesCFlash2Location, sizeof(mainTable));
//	memcpy((void*)&TablesD,	SmallTablesDFlash2Location, sizeof(mainTable));
}


/** @brief Buffer addresses of paged data
 *
 * Save the paged memory addresses to variables such that we can access them
 * from another paged block with no warnings.
 *
 * If you try to access paged data from the wrong place you get nasty warnings.
 * These calls to functions that live in the same page that they are addressing
 * prevent those warnings.
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 */
void initAllPagedAddresses(){
	/* Setup pointers to lookup tables */
	initLookupAddresses();
	/* Setup pointers to the main tables */
	initFuelAddresses();
	initTimingAddresses();
	initTunableAddresses();
}


/** @brief Copies paged flash to RAM
 *
 * Take the tables and config from flash up to RAM to allow live tuning.
 *
 * For the main tables and other paged config we need to adjust
 * the RPAGE value to the appropriate one before copying up.
 *
 * This function is simply a delegator to the ones for each flash page. Each
 * one lives in the same paged space as the data it is copying up.
 */
void initAllPagedRAM(){
	/* Setup the flash block pointers before copying flash to RAM using them */
	initAllPagedAddresses();

	/* Copy the tables up to their paged RAM blocks through the window from flash */
	initPagedRAMFuel();
	initPagedRAMTime();
	initPagedRAMTune();

	/* Default to page one for now, perhaps read the configured port straight out of reset in future? TODO */
	setupPagedRAM(TRUE); // probably something like (PORTA & TableSwitchingMask)
}


/* Initialise and set up all running variables that require a non-zero start value here */
/* All other variables are initialised to zero by the premain built in code             */
void initVariables(){
	/* And the opposite for the other halves */
	CoreVars = &CoreVars0;
	DerivedVars = &DerivedVars0;
	ADCBuffers = &ADCBuffers0;
	ADCBuffersRecord = &ADCBuffers1;

	ticksPerDegree = &ticksPerDegree0; // TODO temp, remove, maybe
	ticksPerDegreeRecord = &ticksPerDegree1; // TODO temp, remove, maybe

	/* Setup the pointers to the registers for fueling use, this does NOT work if done in global.c, I still don't know why. */
	ectMainTimeRegisters[0] = TC2_ADDR;
	ectMainTimeRegisters[1] = TC3_ADDR;
	ectMainTimeRegisters[2] = TC4_ADDR;
	ectMainTimeRegisters[3] = TC5_ADDR;
	ectMainTimeRegisters[4] = TC6_ADDR;
	ectMainTimeRegisters[5] = TC7_ADDR;
	ectMainControlRegisters[0] = TCTL2_ADDR;
	ectMainControlRegisters[1] = TCTL2_ADDR;
	ectMainControlRegisters[2] = TCTL1_ADDR;
	ectMainControlRegisters[3] = TCTL1_ADDR;
	ectMainControlRegisters[4] = TCTL1_ADDR;
	ectMainControlRegisters[5] = TCTL1_ADDR;

	coreStatusA |= FUEL_PUMP_PRIME;

	// Initial state is NOT to fire... can be configured by scheduler if required.
	outputEventInputEventNumbers[0] = 0xFF;
	outputEventInputEventNumbers[1] = 0xFF;
	outputEventInputEventNumbers[2] = 0xFF;
	outputEventInputEventNumbers[3] = 0xFF;
	outputEventInputEventNumbers[4] = 0xFF;
	outputEventInputEventNumbers[5] = 0xFF;
	outputEventInputEventNumbers[6] = 0xFF;
	outputEventInputEventNumbers[7] = 0xFF;
	outputEventInputEventNumbers[8] = 0xFF;
	outputEventInputEventNumbers[9] = 0xFF;
	outputEventInputEventNumbers[10] = 0xFF;
	outputEventInputEventNumbers[11] = 0xFF;
	outputEventInputEventNumbers[12] = 0xFF;
	outputEventInputEventNumbers[13] = 0xFF;
	outputEventInputEventNumbers[14] = 0xFF;
	outputEventInputEventNumbers[15] = 0xFF;
	outputEventInputEventNumbers[16] = 0xFF;
	outputEventInputEventNumbers[17] = 0xFF;
	outputEventInputEventNumbers[18] = 0xFF;
	outputEventInputEventNumbers[19] = 0xFF;
	outputEventInputEventNumbers[20] = 0xFF;
	outputEventInputEventNumbers[21] = 0xFF;
	outputEventInputEventNumbers[22] = 0xFF;
	outputEventInputEventNumbers[23] = 0xFF;

	// TODO perhaps read from the ds1302 once at start up and init the values or different ones with the actual time and date then update them in RTI
}


/** @brief Flash module setup
 *
 * Initialise configuration registers for the flash module to allow burning of
 * non-volatile flash memory from within the firmware.
 *
 * The FCLKDIV register can be written once only after reset, thus the lower
 * seven bits and the PRDIV8 bit must be set at the same time.
 *
 * We want to put the flash clock as high as possible between 150kHz and 200kHz
 *
 * The oscillator clock is 16MHz and because that is above 12.8MHz we will set
 * the PRDIV8 bit to further divide by 8 bits as per the manual.
 *
 * 16MHz = 16000KHz which pre-divided by 8 is 2000kHz
 *
 * 2000kHz / 200kHz = 10 thus we want to set the divide register to 10 or 0x0A
 *
 * Combining 0x0A with PRDIV8 gives us 0x4A (0x0A | 0x40 = 0x4A) so we use that
 *
 * @author Sean Keys
 *
 * @note If you use a different crystal lower than 12.8MHz PRDIV8 should not be set.
 *
 * @warning If the frequency you end up with is outside 150kHz - 200kHz you may
 *          damage your flash module or get corrupt data written to it.
 */
void initFlash(){
	FCLKDIV = 0x4A;                   /* Set the flash clock frequency */
	FPROT = 0xFF;                     /* Disable all flash protection  */
	FSTAT = FSTAT | (PVIOL | ACCERR); /* Clear any errors              */
}


/* Set up the timer module and its various interrupts */
void initECTTimer(){
	/** @todo TODO Take the configuration from the decoder (as is) and mask it such that it does not affect the 6 other channels.
	 * Take the the number of output channels required from configuration and configure that many as outputs
	 * Configure the balance in whatever way is specified in the GPIO configuration - allow second input to be reused as GPI only.
	 *
	 * This stuff affects:
	 * - TIE = 0x01 or 0x03, only. OC channels enabled as required and IC only for RPM/position.
	 * - TIOS = nope, always 0xFC for 2 IC and 6 OC
	 * - TCTL (1,2,3,4) 4 = 0x0? mask off high 4 bits and allow low 4 to come from decoder config/init
	 * - PORTT = zeros, with balance from config
	 * - DDRT = 0,1 inputs, or if unused by decoder, from config
	 */



	// TODO rearrange the order of this stuff and pull enable and interrupt enable out to the last function call of init.


	/* Timer channel interrupts */
	TIE = 0x03; /* 0,1 IC interrupts enabled for reading engine position and RPM, 6 OC channels disabled such that no injector switching happens till scheduled */
	TFLG = ONES; /* Clear all the flags such that we are up and running before they first occur */
	TFLGOF = ONES; /* Clear all the flags such that we are up and running before they first occur */

	/* TODO Turn the timer on and set the rate and overflow interrupt */
//	DLYCT = 0xFF; /* max noise filtering as experiment for volvo this will come from flash config */ // just hiding a wiring/circuit issue...
	TSCR1 = 0x88; /* 0b_1000_1000 Timer enabled, and precision timer turned on */
	TSCR2 = 0x87; /* 0b_1000_0111 Overflow interrupt enable, divide by 256 if precision turned off */
//	PTPSR = 0x03; /* 4 prescaler gives .1uS resolution and max period of 7ms measured */
	PTPSR = 0x1F; /* 32 prescaler gives 0.8uS resolution and max period of 52.4288ms measured */
//	PTPSR = 0x3F; /* 64 prescaler gives 1.6uS resolution and max period of 105ms measured */
//	PTPSR = 0xFF; /* 256 prescaler gives 6.4uS resolution and max period of 400ms measured */
//	PTPSR = 0x7F; /* 128 prescaler gives 3.2uS resolution and max period of 200ms measured */
	/* http://duckduckgo.com/?q=1+%2F+%2840MHz+%2F+32+%29 */
	/* http://duckduckgo.com/?q=%281+%2F+%2840MHz+%2F+32+%29%29+*+2^16 */
	/* www.mecheng.adelaide.edu.au/robotics_novell/WWW_Devs/Dragon12/LM4_Timer.pdf */

	/* Initial actions */
	TIOS = 0xFC; /* 0b_1111_1100 0 and 1 are input capture, 2 through 7 are output compare */
	TCTL1 = ZEROS; /* Set disabled at startup time, use these and other flags to switch fueling on and off inside the decoder */
	TCTL2 = ZEROS; /* 0,1 have compare turned off regardless as they are in IC mode. */
	TCTL3 = ZEROS; /* Capture off for 4 - 7 */
	TCTL4 = 0x0F; /* Capture on both edges of two pins for IC (0,1), capture off for 2,3 */

	// TODO setup delay counters on 0 and 1 to filter noise (nice feature!)
	//DLYCT = ??; built in noise filter

//	PTMCPSR = 0xFF // Precision prescaler - fastest is 1 represented by 0, slowest/longest possible is 256 represented by 255 or 0xFF
//	MCCNT = ONES16; // init to slowest possible, first
//	MCCTL = 0xC4; // turn on and setup the mod down counter
//	MCFLG = 0x80; // clear the flag up front

	decoderInitPreliminary();
}


/* Configure the PIT timers for their various uses. */
void initPITTimer(){
//	// set micro periods
//	PITMTLD0 = 0x1F; /* 32 prescaler gives 0.8uS resolution and max period of 52.4288ms measured */
//	PITMTLD1 = 0x1F; /* ditto */
//	/* http://duckduckgo.com/?q=1+%2F+%2840MHz+%2F+32+%29 Exactly the same as for ECT */
//
//	// set timers running
//	PITLD0 = dwellPeriod;
//	// enable module
//	PITCFLMT = 0x80;
//	// enable channels
//	//PITCE = 0x03;
//	// enable interrupt
//	PITINTE = 0x01;
//	// clear flags
//	//PITFLT = ONES;
}

/* Setup the sci module(s) that we need to use. */
void initSCIStuff(){
	/* The alternative register set selector defaults to zero */

	// set the baud/data speed
	SCI0BD = fixedConfigs1.serialSettings.baudDivisor;

	// etc

	/* Switch to alternative register set? */

	// etc

	/* Switch back again? */

	/*
	 * 0 = LOOPS (normal two wire operation)
	 * 0 = SCISWAI (Wait mode on)
	 * 0 = RSRC (if loops=1, int/ext wiring)
	 * 1 = M MODE (9 bit operation)
	 * 0 = WAKE (idle line wakeup)
	 * 0 = ILT (idle line type count start pos)
	 * 1 = PE (parity on)
	 * 1 = PT (odd parity)
	 *
	 * 0x13 = ODD (default)
	 * 0x12 = EVEN
	 * 0x00 = NONE
	 */
	SCI0CR1 = 0x13;

	/*
	 * 0 = TIE (tx data empty isr disabled)
	 * 0 = TCIE (tx complete isr disabled)
	 * 1 = RIE (rx full isr enabled)
	 * 0 = ILIE (idle line isr disabled)
	 * 0 = TE (transmit disabled)
	 * 1 = RE (receive enabled)
	 * 0 = RWU (rx wake up normal)
	 * 0 = SBK (send break off)
	 */
	SCI0CR2 = 0x24;
}

/* TODO Load and calculate all configuration data required to run */
void initConfiguration(){
//	// TODO Calc TPS ADC range on startup or every time? this depends on whether we ensure that things work without a re init or reset or not.


	/* Add in tunable physical parameters at boot time TODO move to init.c TODO duplicate for secondary fuel? or split somehow?
	 *nstant = ((masterConst * perCylinderVolume) / (stoichiometricAFR * injectorFlow));
	 *nstant = ((139371764 * 16384) / (15053 * 4096));
	 * OR
	 *nstant = ((masterConst / injectorFlow) * perCylinderVolume) / stoichiometricAFR;
	 *nstant = ((139371764 /  4096) * 16384) / 15053;
	 * http://duckduckgo.com/?q=%28%28139371764++%2F+4096%29+*+16384%29+%2F+15053 */
	bootFuelConst = ((unsigned long)(masterFuelConstant / fixedConfigs1.engineSettings.injectorFlow) * fixedConfigs1.engineSettings.perCylinderVolume) / fixedConfigs1.engineSettings.stoichiometricAFR;

	/* The ADC range used to generate TPS percentage */
	TPSADCRange = fixedConfigs2.sensorRanges.TPSMaximumADC - fixedConfigs2.sensorRanges.TPSMinimumADC;
}


/* Set up all the remaining interrupts */
void initInterrupts(){
	/* IMPORTANT : Set the s12x vector base register (Thanks Karsten!!) */
	IVBR = 0xF7; /* Without this the interrupts will never find your code! */

	/* Set up the Real Time Interrupt */
	RTICTL = 0x81; /* 0b_1000_0001 0.125ms/125us period http://duckduckgo.com/?q=1+%2F+%2816MHz+%2F+%282+*+10^3%29+%29 */
//	RTICTL = 0xF9; /* 0b_1111_1001 0.125s/125ms period http://duckduckgo.com/?q=1+%2F+%2816MHz+%2F+%282*10^6%29+%29 */
	CRGINT |= (RTIE | PLLLOCKIE | SCMIE); /* Enable the Real Time Interrupt, PLL Lock Interrupt, and Self Clock Mode Interrupt */
	CRGFLG = (RTIF | PLLLOCKIF | SCMIF); /* Clear the RTI, LOCKI, and SCMI flags */
	RAMWPC |= AVIE; // Enable the access protection interrupt for XGATE RAM

	// set up port H for testing
	PPSH = ZEROS; // falling edge/pull up for all
	PIEH = ONES; // enable all pins interrupts
	PIFH = ONES; // clear all port H interrupt flags

	// TODO set up irq and xirq for testing
	// IRQCR for IRQ

	/* VReg API setup (only for wait mode? i think so) */
//	VREGAPIR = 0x09C3; /* For 500ms period : (500ms - 0.2ms) / 0.2ms = 0b100111000011 = 2499 */
//	VREGAPICL = 0x02; /* Enable the interrupt */
//	VREGAPICL = 0x04; /* Start the counter running */
	/* Writing a one to the flag will set it if it is unset, so best not to mess with it here as it probably starts off unset */

	/* LVI Low Voltage Interrupt enable */
	VREGCTRL = 0x02; // Counts bad power events for diagnosis reasons
}
