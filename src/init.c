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
 *
 * @author Fred Cooke
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
 *
 * @author Fred Cooke
 */
void init(){
	ATOMIC_START();         /* Disable ALL interrupts while we configure the board ready for use */
	initPLL();              /* Set up the PLL and use it */
	initIO();               /* TODO make this config dependent. Set up all the pins and modules to be in low power harmless states */
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


/* used to chop out all the init stuff at compile time for hardware testing. */
//#define NO_INIT


/** @brief Set the PLL clock frequency
 *
 * Set the Phase Locked Loop to our desired frequency (80MHz) and switch to
 * using it for clock (40MHz bus speed).
 *
 * @author Fred Cooke
 */
void initPLL(){
	CLKSEL &= PLLSELOFF;	/* Switches to base external OSCCLK to ensure PLL is not being used (off out of reset, but not sure if the monitor turns it on before passing control or not) */
	PLLCTL &= PLLOFF;		/* Turn the PLL device off to adjust its speed (on by default out of reset) */
	REFDV = PLLDIVISOR;		/* 16MHz / (3 + 1) = 4MHz Bus frequency */
	SYNR = PLLMULTIPLIER;	/* 4MHz * (9 + 1) = 40MHz Bus frequency */
	PLLCTL |= PLLON;		/* Turn the PLL device back on again at 80MHz */

	while (!(CRGFLG & PLLLOCK)){
		/* Do nothing while we wait till the PLL loop locks onto the target frequency. */
		/* Target frequency is given by (2 * (crystal frequency / (REFDV + 1)) * (SYNR + 1)) */
		/* Bus frequency is half PLL frequency and given by ((crystal frequency / (REFDV + 1)) * (SYNR + 1)) */
	}

	CLKSEL = PLLSELON;		/* Switches to PLL clock for internal bus frequency	*/
	/* from MC9S12XDP512V2.pdf Section 2.4.1.1.2 page 101 Third paragraph		*/
	/* "This takes a MAXIMUM of 4 OSCCLK clock cylces PLUS 4 PLL clock cycles"	*/
	/* "During this time ALL clocks freeze, and CPU activity ceases"			*/
	/* Therefore there is no point waiting for this to occur, we already are...	*/
}


/* Configure all the I/O to default values to keep power use down etc */
void initIO(){
	/* for now, hard code all stuff to be outputs as per Freescale documentation,	*/
	/* later what to do will be pulled from flash configuration such that all		*/
	/* things are setup at once, and not messed with thereafter. when the port		*/
	/* something uses is changed via the tuning interface, the confuration will be	*/
	/* done on the fly, and the value burned to flash such that next boot happens	*/
	/* correctly and current running devices are used in that way.					*/

	/* Turn off and on and configure all the modules in an explicit way */
	// TODO set up and turn off all modules (CAN,SCI,SPI,IIC,etc)

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
	ATD0CTL4 = 0x73; /* Set the ADC clock and sample period for best accuracy */
	ATD0CTL5 = 0xB0; /* Sets justification to right, multiplex and scan all channels. Writing to this causes conversions to begin */

#ifndef NO_INIT
	/* Set up the PWM component and initialise its values to off */
	PWME = 0x7F; /* Turn on PWM 0 - 6 (7 is user LED on main board) */
	PWMCLK = ZEROS; /* The fastest we can go for all channels */
	PWMPRCLK = ZEROS; /* The fastest prescaler we can go for all channels */
	PWMSCLA = ZEROS; /* The fastest we can go */
	PWMSCLB = ZEROS; /* The fastest we can go */
	/* TODO PWM channel concatenation for high resolution */
	// join channel pairs together here (needs 16 bit regs enabled too)
	/* TODO Initialise pwm channels with frequency, and initial duty for real use */
	// initial PWM settings for testing
	/* PWM periods */
	PWMPER0 = 0xFF; // 255 for ADC0 testing
	PWMPER1 = 0xFF; // 255 for ADC1 testing
	PWMPER2 = 0xFF; // 255 for ADC1 testing
	PWMPER3 = 0xFF; // 255 for ADC1 testing
	PWMPER4 = 0xFF; // 255 for ADC1 testing
	PWMPER5 = 0xFF; // 255 for ADC1 testing
	PWMPER6 = 0xFF; // 255 for ADC1 testing
	PWMPER7 = 0xFF; // 255 for ADC1 testing
	/* PWM duties */
	PWMDTY0 = 0;
	PWMDTY1 = 0;
	PWMDTY2 = 0;
	PWMDTY3 = 0;
	PWMDTY4 = 0;
	PWMDTY5 = 0;
	PWMDTY6 = 0;
	PWMDTY7 = 0;


	/* Initialise the state of pins configured as output */
	/* Initialise to low such that transistor grounded things are all turned off by default. */
	PORTA = BIT7; /* Set fuel pump on at boot time. The serial monitor pin is on 0x40, and could cause problems if capacitance at the output is large when a reset occurs. */
	PORTB = ZEROS; /* Init the rest of the spark outputs as off */
	PORTE = 0x1F; /* 0b_0001_1111 : when not in use 0b_1001_1111 PE7 should be high PE5 and PE6 should be low, the rest high */
	PORTK = ZEROS;
	PORTS = 0x02; // Set TX0 pin to high between transmissions!
	PORTT = ZEROS; /* All pins in off state at boot up (only matters for 2 - 7) */
	PORTM = ZEROS;
	PORTP = ZEROS; // TODO hook these up to the adc channels such that you can vary the brightness of an led with a pot.
	PORTH = ZEROS;
	PORTJ = ZEROS;
	/* AD0PT1 You are out of your mind if you waste this on digital Inputs */
	/* AD1PT1 You are out of your mind if you waste this on digital Inputs */

	/* Initialise the Data Direction Registers */
	/* To outputs based on the note at the end of chapter 1.2.2 of MC9S12XDP512V2.pdf */
	DDRA = ONES; /* GPIO (8) */
	DDRB = ONES; /* GPIO (8) */
	DDRE = 0xFC; /* 0b_1111_1100 : Clock and mode pins PE0,PE1 are input only pins, the rest are GPIO */
	DDRK = ONES; /* Only 0,1,2,3,4,5,7, NOT 6 (7) */
	DDRS = 0xFE; /* RX0 as input: SCI0 (RX,TX), SCI1 (RX,TX), SPI0 (MISO,MOSI,SCK,SS) (8) */
	DDRT = 0xFC; /* 0b_1111_1100 set ECT pins 0,1 to IC and 2:7 to OC (8) */
	DDRM = ONES; /* CAN 0 - 3 (8) */
	DDRP = ONES; /* PWM pins (8) */
	DDRH = ZEROS; /* All pins configured as input for misc isrs (SPI1, SPI2) (8) */
	DDRJ = ONES; /* Only 0,1,6,7 are brought out on the 112 pin chip (4) */
	/* Configure the non bonded pins to output to avoid current drain (112 pin package) */
	DDRC = ONES; /* NON-bonded external data bus pins */
	DDRD = ONES; /* NON-bonded external data bus pins */
	/* AD0DDR1 You are out of your mind if you waste this on digital Inputs */
	/* AD1DDR1 You are out of your mind if you waste this on digital Inputs */
#endif
}


/** @brief Buffer lookup tables addresses
 *
 * Save pointers to the lookup tables which live in paged flash.
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 *
 * @author Fred Cooke
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
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 *
 * @author Fred Cooke
 */
void initFuelAddresses(){
	/* Setup addresses within the page to avoid warnings */
	VETableMainFlashLocation		= (void*)&VETableMainFlash;
	VETableSecondaryFlashLocation	= (void*)&VETableSecondaryFlash;
	VETableTertiaryFlashLocation	= (void*)&VETableTertiaryFlash;
	LambdaTableFlashLocation		= (void*)&LambdaTableFlash;
	VETableMainFlash2Location		= (void*)&VETableMainFlash2;
	VETableSecondaryFlash2Location	= (void*)&VETableSecondaryFlash2;
	VETableTertiaryFlash2Location	= (void*)&VETableTertiaryFlash2;
	LambdaTableFlash2Location		= (void*)&LambdaTableFlash2;
}


/** @brief Copy fuel tables to RAM
 *
 * Initialises the fuel tables in RAM by copying them up from flash.
 *
 * @author Fred Cooke
 */
void initPagedRAMFuel(void){
	/* Copy the tables from flash to RAM */
	RPAGE = RPAGE_FUEL_ONE;
	memcpy((void*)&TablesA,	VETableMainFlashLocation,		sizeof(mainTable));
	memcpy((void*)&TablesB,	VETableSecondaryFlashLocation,	sizeof(mainTable));
	memcpy((void*)&TablesC,	VETableTertiaryFlashLocation,	sizeof(mainTable));
	memcpy((void*)&TablesD,	LambdaTableFlashLocation,		sizeof(mainTable));
	RPAGE = RPAGE_FUEL_TWO;
	memcpy((void*)&TablesA,	VETableMainFlash2Location,		sizeof(mainTable));
	memcpy((void*)&TablesB,	VETableSecondaryFlash2Location,	sizeof(mainTable));
	memcpy((void*)&TablesC,	VETableTertiaryFlash2Location,	sizeof(mainTable));
	memcpy((void*)&TablesD,	LambdaTableFlash2Location,		sizeof(mainTable));
}


/** @brief Buffer timing tables addresses
 *
 * Save pointers to the timing tables which live in paged flash.
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 *
 * @author Fred Cooke
 */
void initTimingAddresses(){
	/* Setup addresses within the page to avoid warnings */
	IgnitionAdvanceTableMainFlashLocation			= (void*)&IgnitionAdvanceTableMainFlash;
	IgnitionAdvanceTableSecondaryFlashLocation		= (void*)&IgnitionAdvanceTableSecondaryFlash;
	InjectionAdvanceTableMainFlashLocation			= (void*)&InjectionAdvanceTableMainFlash;
	InjectionAdvanceTableSecondaryFlashLocation		= (void*)&InjectionAdvanceTableSecondaryFlash;
	IgnitionAdvanceTableMainFlash2Location			= (void*)&IgnitionAdvanceTableMainFlash2;
	IgnitionAdvanceTableSecondaryFlash2Location		= (void*)&IgnitionAdvanceTableSecondaryFlash2;
	InjectionAdvanceTableMainFlash2Location			= (void*)&InjectionAdvanceTableMainFlash2;
	InjectionAdvanceTableSecondaryFlash2Location	= (void*)&InjectionAdvanceTableSecondaryFlash2;
}


/** @brief Copy timing tables to RAM
 *
 * Initialises the timing tables in RAM by copying them up from flash.
 *
 * @author Fred Cooke
 */
void initPagedRAMTime(){
	/* Copy the tables from flash to RAM */
	RPAGE = RPAGE_TIME_ONE;
	memcpy((void*)&TablesA,	IgnitionAdvanceTableMainFlashLocation,			sizeof(mainTable));
	memcpy((void*)&TablesB,	IgnitionAdvanceTableSecondaryFlashLocation,		sizeof(mainTable));
	memcpy((void*)&TablesC,	InjectionAdvanceTableMainFlashLocation,			sizeof(mainTable));
	memcpy((void*)&TablesD,	InjectionAdvanceTableSecondaryFlashLocation,	sizeof(mainTable));
	RPAGE = RPAGE_TIME_TWO;
	memcpy((void*)&TablesA,	IgnitionAdvanceTableMainFlash2Location,			sizeof(mainTable));
	memcpy((void*)&TablesB,	IgnitionAdvanceTableSecondaryFlash2Location,	sizeof(mainTable));
	memcpy((void*)&TablesC,	InjectionAdvanceTableMainFlash2Location,		sizeof(mainTable));
	memcpy((void*)&TablesD,	InjectionAdvanceTableSecondaryFlash2Location,	sizeof(mainTable));
}


/** @brief Buffer tunable tables addresses
 *
 * Save pointers to the tunable tables which live in paged flash and their
 * sub-sections too.
 *
 * @note Many thanks to Jean Bélanger for the inspiration/idea to do this!
 *
 * @author Fred Cooke
 */
void initTunableAddresses(){
	/* Setup addresses within the page to avoid warnings */
	SmallTablesAFlashLocation 	= (void*)&SmallTablesAFlash;
	SmallTablesBFlashLocation 	= (void*)&SmallTablesBFlash;
	SmallTablesCFlashLocation 	= (void*)&SmallTablesCFlash;
	SmallTablesDFlashLocation 	= (void*)&SmallTablesDFlash;
	SmallTablesAFlash2Location	= (void*)&SmallTablesAFlash2;
	SmallTablesBFlash2Location	= (void*)&SmallTablesBFlash2;
	SmallTablesCFlash2Location	= (void*)&SmallTablesCFlash2;
	SmallTablesDFlash2Location	= (void*)&SmallTablesDFlash2;

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
	dwellMaxVersusRPMTableLocation            = (void*)&SmallTablesAFlash.dwellMaxVersusRPMTable;
	dwellMaxVersusRPMTable2Location           = (void*)&SmallTablesAFlash2.dwellMaxVersusRPMTable;

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
	memcpy((void*)&TablesA,	SmallTablesAFlashLocation,	sizeof(mainTable));
	memcpy((void*)&TablesB,	SmallTablesBFlashLocation,	sizeof(mainTable));
	memcpy((void*)&TablesC,	SmallTablesCFlashLocation,	sizeof(mainTable));
	memcpy((void*)&TablesD,	SmallTablesDFlashLocation,	sizeof(mainTable));
	RPAGE = RPAGE_TUNE_TWO;
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&& WARNING &&&&&&&&&&&&&&&&&&&&&&&&&&&&&& //
	//    You will get garbage if you use table switching at this time!!!    //
	//         XGATE code being run from this region temporarily!!!          //
	//   Writing to these tables WILL corrupt XGATE code/kill your engine!   //
	// &&&&&&&&&&&&&&&&&&&&&&&&&&&&&& WARNING &&&&&&&&&&&&&&&&&&&&&&&&&&&&&& //
	//memcpy(xgateSchedRAMAddress, xgateSchedFlashAddress, (xgateSchedEnd - xgateSched));
	//memcpy(xgateInjectorsOnRAMAddress, xgateInjectorsOnFlashAddress, (xgateInjectorsOnEnd - xgateInjectorsOn));
	//memcpy(xgateInjectorsOffRAMAddress, xgateInjectorsOffFlashAddress, (xgateInjectorsOffEnd - xgateInjectorsOff));
//	memcpy((void*)&TablesA,	SmallTablesAFlash2Location,	sizeof(mainTable));
//	memcpy((void*)&TablesB,	SmallTablesBFlash2Location,	sizeof(mainTable));
//	memcpy((void*)&TablesC,	SmallTablesCFlash2Location,	sizeof(mainTable));
//	memcpy((void*)&TablesD,	SmallTablesDFlash2Location,	sizeof(mainTable));
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
 *
 * @author Fred Cooke
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
 *
 * @author Fred Cooke
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
/* All other variables are initialised to zero by the premain built in code				*/
void initVariables(){
	/* And the opposite for the other halves */
	CoreVars = &CoreVars0;
	DerivedVars = &DerivedVars0;
	ADCBuffers = &ADCBuffers0;
	ADCBuffersRecord = &ADCBuffers1;

	ticksPerDegree = &ticksPerDegree0; // TODO temp, remove, maybe
	ticksPerDegreeRecord = &ticksPerDegree1; // TODO temp, remove, maybe

	/* Setup the pointers to the registers for fueling use, this does NOT work if done in global.c, I still don't know why. */
	injectorMainTimeRegisters[0] = TC2_ADDR;
	injectorMainTimeRegisters[1] = TC3_ADDR;
	injectorMainTimeRegisters[2] = TC4_ADDR;
	injectorMainTimeRegisters[3] = TC5_ADDR;
	injectorMainTimeRegisters[4] = TC6_ADDR;
	injectorMainTimeRegisters[5] = TC7_ADDR;
	injectorMainControlRegisters[0] = TCTL2_ADDR;
	injectorMainControlRegisters[1] = TCTL2_ADDR;
	injectorMainControlRegisters[2] = TCTL1_ADDR;
	injectorMainControlRegisters[3] = TCTL1_ADDR;
	injectorMainControlRegisters[4] = TCTL1_ADDR;
	injectorMainControlRegisters[5] = TCTL1_ADDR;

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
	FCLKDIV = 0x4A;                  	/* Set the flash clock frequency	*/
	FPROT = 0xFF;                    	/* Disable all flash protection 	*/
	FSTAT = FSTAT | (PVIOL | ACCERR);	/* Clear any errors             	*/
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


#ifndef NO_INIT
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
	/* http://www.google.com/search?hl=en&safe=off&q=1+%2F+%2840MHz+%2F+32+%29&btnG=Search */
	/* http://www.google.com/search?hl=en&safe=off&q=1+%2F+%2840MHz+%2F+32+%29+*+2%5E16&btnG=Search */
	/* www.mecheng.adelaide.edu.au/robotics_novell/WWW_Devs/Dragon12/LM4_Timer.pdf */

	/* Initial actions */
	TIOS = 0xFC; /* 0b_1111_1100 0 and 1 are input capture, 2 through 7 are output compare */
	TCTL1 = ZEROS; /* Set disabled at startup time, use these and other flags to switch fueling on and off inside the decoder */
	TCTL2 = ZEROS; /* 0,1 have compare turned off regardless as they are in IC mode. */
	TCTL3 = ZEROS; /* Capture off for 4 - 7 */
	TCTL4 = 0x0F; /* Capture on both edges of two pins for IC (0,1), capture off for 2,3 */

	// TODO setup delay counters on 0 and 1 to filter noise (nice feature!)
	//DLYCT = ??; built in noise filter

//	/* Configurable tachometer output */	PTMCPSR = 0xFF // Precision prescaler - fastest is 1 represented by 0, slowest/longest possible is 256 represented by 255 or 0xFF
//	MCCNT = ONES16; // init to slowest possible, first
//	MCCTL = 0xC4; // turn on and setup the mod down counter
//	MCFLG = 0x80; // clear the flag up front

	decoderInitPreliminary();
#endif
}


/* Configure the PIT timers for their various uses. */
void initPITTimer(){
#ifndef NO_INIT
//	/*  */
//	// set micro periods
//	PITMTLD0 = 0x1F; /* 32 prescaler gives 0.8uS resolution and max period of 52.4288ms measured */
//	PITMTLD1 = 0x1F; /* ditto */
//	/* http://www.google.com/search?hl=en&safe=off&q=1+%2F+%2840MHz+%2F+32+%29 Exactly the same as for ECT */
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
#endif
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
	 *nstant = ((139371764	 * 16384			) / (15053			   * 4096		 ));
	 * OR
	 *nstant = ((masterConst / injectorFlow) * perCylinderVolume) / stoichiometricAFR;
	 *nstant = ((139371764	 / 4096		   ) * 16384			) / 15053			 ;
	 * http://www.google.com/search?hl=en&safe=off&q=((139371764++%2F+4096+++++)+*+16384+++)+%2F+15053++++&btnG=Search */
	bootFuelConst = ((unsigned long)(masterFuelConstant / fixedConfigs1.engineSettings.injectorFlow) * fixedConfigs1.engineSettings.perCylinderVolume) / fixedConfigs1.engineSettings.stoichiometricAFR;

	/* The MAP range used to convert fake TPS from MAP and vice versa */
	TPSMAPRange = fixedConfigs2.sensorRanges.TPSOpenMAP - fixedConfigs2.sensorRanges.TPSClosedMAP;

	/* The ADC range used to generate TPS percentage */
	TPSADCRange = fixedConfigs2.sensorRanges.TPSMaximumADC - fixedConfigs2.sensorRanges.TPSMinimumADC;


	/* Use like flags for now, just add one for each later */
	unsigned char cumulativeConfigErrors = 0;

	/* Check various aspects of config which will cause problems */

	/* BRV max bigger than variable that holds it */
	if(((unsigned long)fixedConfigs2.sensorRanges.BRVMinimum + fixedConfigs2.sensorRanges.BRVRange) > 65535){
		//sendError(BRV_MAX_TOO_LARGE);
		cumulativeConfigErrors++;
	}

	// TODO check all critical variables here!

	/*
	 * check ignition settings for range etc, possibly check some of those on the fly too
	 * check fuel settings for being reasonable
	 * check all variable tables for correct sizing
	 * etc
	 */

	while(cumulativeConfigErrors > 0){
		sleep(1000);
		/// @todo TODO send an async error of some sort here, perhaps upgrade errors to handle args for this purpose, or perhaps send an async error for each error, inc this var, then send a "errors occurred, reset and listen to see what they were" packet?
		//send("There were ");
		//sendUC(cumulativeConfigErrors);
		//send(" config errors, init aborted!");
	} /// @todo TODO ensure that we can recieve config and settings via serial while this is occuring! If not a bad config will lock us out all together.
}


/* Set up all the remaining interrupts */
void initInterrupts(){
	/* IMPORTANT : Set the s12x vector base register (Thanks Karsten!!) */
	IVBR = 0xF7; /* Without this the interrupts will never find your code! */

	/* Set up the Real Time Interrupt */
	RTICTL = 0x81; /* 0b_1000_0001 0.125ms/125us period http://www.google.com/search?hl=en&safe=off&q=1+%2F+%2816MHz+%2F+%282+*+10%5E3%29+%29&btnG=Search */
//	RTICTL = 0xF9; /* 0b_1111_1001 0.125s/125ms period http://www.google.com/search?hl=en&safe=off&q=1+%2F+%2816MHz+%2F+%282*10%5E6%29+%29&btnG=Search */
	CRGINT |= 0x80; /* Enable the RTI */
	CRGFLG = 0x80; /* Clear the RTI flag */

#ifndef NO_INIT
	// set up port H for testing
	PPSH = ZEROS; // falling edge/pull up for all
	PIEH = ONES; // enable all pins interrupts
	PIFH = ONES; // clear all port H interrupt flags
#endif

	// TODO set up irq and xirq for testing
	// IRQCR for IRQ
	//

	/* VReg API setup (only for wait mode? i think so) */
//	VREGAPIR = 0x09C3; /* For 500ms period : (500ms - 0.2ms) / 0.2ms = 0b100111000011 = 2499 */
//	VREGAPICL = 0x02; /* Enable the interrupt */
//	VREGAPICL = 0x04; /* Start the counter running */
	/* Writing a one to the flag will set it if it is unset, so best not to mess with it here as it probably starts off unset */

	/* LVI Low Voltage Interrupt enable */
	VREGCTRL = 0x02; // Counts bad power events for diagnosis reasons
}
