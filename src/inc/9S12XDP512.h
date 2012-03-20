/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2012 Fred Cooke
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
 * @brief MC9S12XDP512 register definitions
 *
 * This is the device header for the FreeScale MC9S12XDP512 MCU. It contains
 * declarations that allow access to all of the devices control registers.
 *
 * These are the full basic register definitions for the Freescale 9S12XDP512
 * processor as taken from MC9S12XDP512V2.pdf Appendix G
 *
 * @author Fred Cooke
 */


/* see if we've seen this, if not, mark seen and process */
#ifndef FILE_9S12XDP512_H_SEEN
#define FILE_9S12XDP512_H_SEEN


/* shortcuts to speed formatting */
/* www.atmel.com/dyn/resources/prod_documents/avr_3_04.pdf First page, second column */
/* http://www.ee.nmt.edu/~rison/ee308_spr06/homepage.html */
/* extra parentheses for clarity and guarantee of precedence */

/* Dereferenced Volatile Unsigned Char Pointer */
#define DVUCP(address) (*((volatile unsigned char*)(address)))
/* Dereferenced Volatile Unsigned Short Pointer */
#define DVUSP(address) (*((volatile unsigned short*)(address)))

/* Address Volatile Unsigned Char Pointer */
#define AVUCP(address) ((volatile unsigned char*)(address))
/* Address Volatile Unsigned Short Pointer */
#define AVUSP(address) ((volatile unsigned short*)(address))



/* Port Integration Module - Reordered within sections for clarity */
/* PIM information from 5 tables the last of which is spread over three pages */

/* Plain ports output switch, input state registers */
#define PORTS_BA DVUSP(0x0001) /// @todo TODO is this address wrong? Test this... /* Both A and B combined as a 16 bit register for ignition access */
#define PORTA DVUCP(0x0000)
#define PORTB DVUCP(0x0001)
#define PORTE DVUCP(0x0008)
#define PORTK DVUCP(0x0032)
/* #define PORTC DVUCP(0x0004) these pins are not bonded on the 112 pin package */
/* #define PORTD DVUCP(0x0005) these pins are not bonded on the 112 pin package */


/* Plain ports Data Direction Registers */
#define DDRA DVUCP(0x0002)
#define DDRB DVUCP(0x0003)
#define DDRE DVUCP(0x0009)
#define DDRK DVUCP(0x0033)


#define DDRC DVUCP(0x0006) /* these pins are not bonded on the 112 pin package but need switching to output */
#define DDRD DVUCP(0x0007) /* these pins are not bonded on the 112 pin package but need switching to output */


/* 0b1//1//00 */
/* --K//E//BA */
/* TODO NOTE: the sixth bit controls pull up on BKGD and VREGEN pins set this to ???? */
/* NOTE: pull up on port E is for 0-4 and 7, ports 5 and 6 are pulled down during reset and never pulled up. */
#define PUCR DVUCP(0x000C) /* pull up enable when used as an input, 0 = no pull up, 1 = pull up on */


/* 0b1//0//00 */
/* --K//E//BA */
/* NOTE: reduced drive affects all pins of all ports listed above. */
#define RDRIV DVUCP(0x000D) /* reduced drive register when used as output, 0 = full drive, 1 = reduced drive */


#define ECLKCTL DVUCP(0x001C) /* Comes up 0b_1100_0000 = both pins off in normal single chip mode */
#define IRQCR DVUCP(0x001E) /* 0 in bit 7 makes it ultra sensitive, 1 makes it falling edge sensitive. 0 in bit 6 turns interrupts off, 1 in bit 6 turns them on. */


/* Port T registers */
#define PTT DVUCP(0x0240) /* GPIO output register, can not be read from reliably, use PTIT instead */
#define PORTT DVUCP(0x0240) /* Duplicate definition for consistency */
#define PTIT DVUCP(0x0241) /* read only port state bits, always return the state of the pin, can be used to detect overload on outputs */
#define DDRT DVUCP(0x0242) /* TODO configure all IO as outputs until we need it */
#define RDRT DVUCP(0x0243) /* reduced drive register when used as output, 0 = full drive, 1 = reduced drive */
#define PERT DVUCP(0x0244) /* pull up/down enable when used as an input, 0 = no pull up, 1 = pull up on */
#define PPST DVUCP(0x0245) /* 0 = pull up, 1 = pull down */


/* Port S registers */
#define PTS DVUCP(0x0248)
#define PORTS DVUCP(0x0248) /* Duplicate definition for consistency */
#define PTIS DVUCP(0x0249) /* read only port state bits, always return the state of the pin, can be used to detect overload on outputs */
#define DDRS DVUCP(0x024A) /* TODO configure all IO as outputs until we need it */
#define RDRS DVUCP(0x024B) /* reduced drive register when used as output, 0 = full drive, 1 = reduced drive */
#define PERS DVUCP(0x024C) /* pull up enable when used as an input, 0 = no pull up, 1 = pull up on */
#define PPSS DVUCP(0x024D) /* 0 = pull up, 1 = pull down */
#define WOMS DVUCP(0x024E) /* wired OR mode TODO find out what this actually means in real terms. */


/* Port M registers */
#define PTM DVUCP(0x0250)
#define PORTM DVUCP(0x0250) /* Duplicate definition for consistency */
#define PTIM DVUCP(0x0251) /* read only port state bits, always return the state of the pin, can be used to detect overload on outputs */
#define DDRM DVUCP(0x0252) /* TODO configure all IO as outputs until we need it */
#define RDRM DVUCP(0x0253) /* reduced drive register when used as output, 0 = full drive, 1 = reduced drive */
#define PERM DVUCP(0x0254) /* pull up enable when used as an input, 0 = no pull up, 1 = pull up on */
#define PPSM DVUCP(0x0255) /* 0 = pull up, 1 = pull down */
#define WOMM DVUCP(0x0256) /* wired OR mode TODO find out what this actually means in real terms. */


/* this should be set to the following bit mask xx????00 */
#define MODRR DVUCP(0x0257)


/* Port P registers */
#define PTP DVUCP(0x0258)
#define PORTP DVUCP(0x0258) /* Duplicate definition for consistency */
#define PTIP DVUCP(0x0259) /* read only port state bits, always return the state of the pin, can be used to detect overload on outputs */
#define DDRP DVUCP(0x025A) /* TODO configure all IO as outputs until we need it */
#define RDRP DVUCP(0x025B) /* reduced drive register when used as output, 0 = full drive, 1 = reduced drive */
#define PERP DVUCP(0x025C) /* pull up enable when used as an input, 0 = no pull up, 1 = pull up on */
#define PPSP DVUCP(0x025D) /* 0 = pull up, 1 = pull down AND when IE pull down means I on rising edge and pull up means I on falling edge */
#define PIEP DVUCP(0x025E) /* interrupt enable, turns on interrupts */
#define PIFP DVUCP(0x025F) /* interrupt flag, write a 1 to clear it */


/* Port H registers */
#define PTH DVUCP(0x0260)
#define PORTH DVUCP(0x0260) /* Duplicate definition for consistency */
#define PTIH DVUCP(0x0261) /* read only port state bits, always return the state of the pin, can be used to detect overload on outputs */
#define DDRH DVUCP(0x0262) /* TODO configure all IO as outputs until we need it */
#define RDRH DVUCP(0x0263) /* reduced drive register when used as output, 0 = full drive, 1 = reduced drive */
#define PERH DVUCP(0x0264) /* pull up enable when used as an input, 0 = no pull up, 1 = pull up on */
#define PPSH DVUCP(0x0265) /* 0 = pull up, 1 = pull down AND when IE pull down means I on rising edge and pull up means I on falling edge */
#define PIEH DVUCP(0x0266) /* interrupt enable, turns on interrupts */
#define PIFH DVUCP(0x0267) /* interrupt flag, write a 1 to clear it */


/* Port J registers */
#define PTJ DVUCP(0x0268)
#define PORTJ DVUCP(0x0268) /* Duplicate definition for consistency */
#define PTIJ DVUCP(0x0269) /* read only port state bits, always return the state of the pin, can be used to detect overload on outputs */
#define DDRJ DVUCP(0x026A) /* TODO configure all IO as outputs until we need it */
#define RDRJ DVUCP(0x026B) /* reduced drive register when used as output, 0 = full drive, 1 = reduced drive */
#define PERJ DVUCP(0x026C) /* pull up enable when used as an input, 0 = no pull up, 1 = pull up on */
#define PPSJ DVUCP(0x026D) /* 0 = pull up, 1 = pull down AND when IE pull down means I on rising edge and pull up means I on falling edge */
#define PIEJ DVUCP(0x026E) /* interrupt enable, turns on interrupts */
#define PIFJ DVUCP(0x026F) /* interrupt flag, write a 1 to clear it */


/* #define ATD0PT1 DVUCP(0x0271)	we don't want to use valuable ATD pins as normal IO, but if we did, r/w here */
/* #define ATD0DDR1 DVUCP(0x0273) for use as an input, ATD0DIEN has to be set to 1. for use as an output? */
/* #define ATD0RDR1 DVUCP(0x0275) reduced drive register when used as output, 0 = full drive, 1 = reduced drive */
#define ATD0PER1 DVUCP(0x0277) /* pull up enable when used as an input, 0 = no pull up, 1 = pull up on */

/* #define ATD1PT1 DVUCP(0x0279)	we don't want to use valuable ATD pins as normal IO, but if we did, r/w here */
/* #define ATD1DDR1 DVUCP(0x027B)	for use as an input, ATD1DIEN1 has to be set to 1. for use as an output? */
/* #define ATD1RDR1 DVUCP(0x027D)	reduced drive register when used as output, 0 = full drive, 1 = reduced drive */
/* #define ATD1PER1 DVUCP(0x027F)	pull up enable when used as an input, 0 = no pull up, 1 = pull up on */

/* Not available on 112 pin version	*/
/* #define ATD1DDR0 DVUCP(0x027A) */
/* 0x0278 #define ATD1PT0 DVUCP() */
/* 0x027C #define ATD1RDR0 DVUCP() */
/* 0x027E #define ATD1PER0 DVUCP() */


/* Memory Mapping Control registers TODO configure these to suit our application. */
/* MMC 1/4 */
//0x000B MODE DVUCP()
//0x000A MMCCTL0 DVUCP()
//0x0013 MMCCTL1 DVUCP()


/* Page control registers */
#define RPAGE DVUCP(0x0016) /* Used to page table data in and out of visible memory. */
//0x0017 EPAGE DVUCP() /* /* TODO similar to above if we need another 2k of eeprom. what are advantages/disadvantages of eeprom over flash?? */
#define PPAGE DVUCP(0x0030) /* TODO look at the best way to use the flash space in a complete system with a lot of code and data. used by compiler and maybe us to switch flash pages for loading/unloading data. */
//0x0010 GPAGE DVUCP() /* /* Global page register for global instruction addressing. I doubt we will use this. */
//0x0011 DIRECT DVUCP() /* /* Direct addressing mode control register. I doubt we will use this. */


//// MMC 4/4
//0x011C RAMWPC /* RAM Write Protection register, the pdf document appears to be incorrect for this, best not to touch it. */
//0x011D RAMXGU /* XGATE Upper region limit, this defines how much RAM we give the xgate to work with. */
//0x011E RAMSHL /* Shared memory lower boundary register, this defines the lower limit of the overlap between XGATE RAM and CPU RAM */
//0x011F RAMSHU /* Shared memory upper boundary register, this defines the upper limit of the overlap between XGATE RAM and CPU RAM */


//// EBI
//0x000E EBICTL0 DVUCP() /*
//0x000F EBICTL1 DVUCP() /*


//// Misc Peripheral
//0x001A PARTIDH DVUCP() /*
//0x001B PARTIDL DVUCP() /*


/* Clock and Reset Generator */
#define SYNR DVUCP(0x0034) /* Multiplier of result of division by REFDV below, output is new PLL/Bus freqency. */
#define REFDV DVUCP(0x0035) /* Divisor of external clock frequency pre being multiplied by SYNR above. */
//0x0036 CTFLG DVUCP() /*
#define CRGFLG DVUCP(0x0037) /* Clock and Reset Generator flags, we use this to determine when the PLL is stable and ready to use. Also to reset the RTI flag. */
#define CRGINT DVUCP(0x0038) /* Bit 7 is RTIE RTI enable bit. */
#define CLKSEL DVUCP(0x0039) /* Clock select register, choose PLL or external clock with this. */
#define PLLCTL DVUCP(0x003A) /* PLL frequency generator control register, used for setting the bus frequency. */
#define RTICTL DVUCP(0x003B) /* Divider select register */
#define COPCTL DVUCP(0x003C) /* COP watch dog control register */
//0x003D FORBYP DVUCP() /*
#define ARMCOP DVUCP(0x003F) /* Computer operating properly timer, we won't be using this at least until we have profiled the running application. it will just cause headaches otherwise. */


/* Enhanced Capture Timer */
/* see reference document from Huang course overview/notes : http://www.ee.nmt.edu/~rison/ee308_spr06/lectures.html */
/* see this link for a discussion of the old 68hc12 timer http://www.seattlerobotics.org/encoder/nov97/68hc12.html */

#define TCNT DVUSP(0x0044) /* Timer counter 16 bit (0x0044 TCNT (hi), 0x0045 TCNT (lo)) */

/* Behavioural control registers (dual purpose) */
#define TIOS DVUCP(0x0040) /* Selects input capture or output compare mode for each timer pin */
#define TIE DVUCP(0x004C) /* Timer channel interrupt enable register */
#define TSCR1 DVUCP(0x0046) /* Timer System Control Register 1 */
#define TSCR2 DVUCP(0x004D) /* Timer System Control Register 2 */
#define TFLG DVUCP(0x004E) /* Timer channel flags */
#define TFLGOF DVUCP(0x004F) /* Timer over flow flag */
#define PTPSR DVUCP(0x006E) /* Precision prescaler for the main timer */

/* Output compare control registers */
#define TTOV DVUCP(0x0047) /* Timer Toggle on Overflow output compare control */
#define CFORC DVUCP(0x0041) /* Output compare force, write a 1 to make the programmed action occur now */
#define OC7M DVUCP(0x0042) /* Channel 7 output compare other pins control mask */
#define OC7D DVUCP(0x0043) /* Channel 7 output compare other pins states */

/*	Timer output compare action control registers
 *	OMx	OLx	Action
 *	0	0	Timer disconnected from output pin logic
 *	0	1	Toggle OCx output line
 *	1	0	Clear OCx output line to zero
 *	1	1	Set OCx output line to one */
#define TCTL1 DVUCP(0x0048) /* (M,L) 77,66,55,44 */
#define TCTL2 DVUCP(0x0049) /* (M,L) 33,22,11,00 */
#define TCTL1_ADDR AVUCP(0x0048) /* (M,L) 77,66,55,44 */
#define TCTL2_ADDR AVUCP(0x0049) /* (M,L) 33,22,11,00 */


/* Input capture control registers */
#define DLYCT DVUCP(0x0069) /* Delay counter control register (minimum tooth width) */
#define ICSYS DVUCP(0x006B) /* Input capture behaviour control register */
#define ICOVW DVUCP(0x006A) /* Input capture overwrite allow */

/*	Timer input capture edge detection control registers
 *	EDGxB	EDGxA	Configuration
 *	0		0		Capture disabled
 *	0		1		Capture on rising edges only
 *	1		0		Capture on falling edges only
 *	1		1		Capture on any edge (rising or falling) */
#define TCTL3 DVUCP(0x004A) /* (B,A) 77,66,55,44 */
#define TCTL4 DVUCP(0x004B) /* (B,A) 33,22,11,00 */

/* Input capture holding registers for 0 - 3 */
#define TC0H DVUSP(0x0078) /* 16 bit (0x0078 TC0H (hi), 0x0079 TC0H (lo)) */
#define TC1H DVUSP(0x007A) /* 16 bit (0x007A TC1H (hi), 0x007B TC1H (lo)) */
#define TC2H DVUSP(0x007C) /* 16 bit (0x007C TC2H (hi), 0x007D TC2H (lo)) */
#define TC3H DVUSP(0x007E) /* 16 bit (0x007E TC3H (hi), 0x007F TC3H (lo)) */

/* Time value comparison/storage registers for each timer channel */
#define TC0 DVUSP(0x0050) /* 16 bit (0x0050 TC0 (hi), 0x0051 TC0 (lo)) */
#define TC1 DVUSP(0x0052) /* 16 bit (0x0052 TC1 (hi), 0x0053 TC1 (lo)) */
#define TC2 DVUSP(0x0054) /* 16 bit (0x0054 TC2 (hi), 0x0055 TC2 (lo)) */
#define TC3 DVUSP(0x0056) /* 16 bit (0x0056 TC3 (hi), 0x0057 TC3 (lo)) */
#define TC4 DVUSP(0x0058) /* 16 bit (0x0058 TC4 (hi), 0x0059 TC4 (lo)) */
#define TC5 DVUSP(0x005A) /* 16 bit (0x005A TC5 (hi), 0x005B TC5 (lo)) */
#define TC6 DVUSP(0x005C) /* 16 bit (0x005C TC6 (hi), 0x005D TC6 (lo)) */
#define TC7 DVUSP(0x005E) /* 16 bit (0x005E TC7 (hi), 0x005F TC7 (lo)) */

#define TC2_ADDR AVUSP(0x0054) /* 16 bit (0x0054 TC2 (hi), 0x0055 TC2 (lo)) */
#define TC3_ADDR AVUSP(0x0056) /* 16 bit (0x0056 TC3 (hi), 0x0057 TC3 (lo)) */
#define TC4_ADDR AVUSP(0x0058) /* 16 bit (0x0058 TC4 (hi), 0x0059 TC4 (lo)) */
#define TC5_ADDR AVUSP(0x005A) /* 16 bit (0x005A TC5 (hi), 0x005B TC5 (lo)) */
#define TC6_ADDR AVUSP(0x005C) /* 16 bit (0x005C TC6 (hi), 0x005D TC6 (lo)) */
#define TC7_ADDR AVUSP(0x005E) /* 16 bit (0x005E TC7 (hi), 0x005F TC7 (lo)) */



/* Pulse accumulator control registers */
#define ICPAR DVUCP(0x0068)
/*	(PACTL) 7   6    5     4     3    2    1    0
	 		  PAEN PAMOD PEDGE CLK1 CLK0 PAOVI PAI */
#define PACTL DVUCP(0x0060)
#define PAFLG DVUCP(0x0061)
#define PBCTL DVUCP(0x0070)
#define PBFLG DVUCP(0x0071)
/* Pulse accumulator count registers dual access, 8 or 16 bit */
#define PACNUS2 DVUSP(0x0062) /* 16 bit (0x0062 PACN3, 0x0063 PACN2) */
#define PACNUS0 DVUSP(0x0064) /* 16 bit (0x0064 PACN1, 0x0065 PACN0) */
#define PACN3 DVUCP(0x0062) /* high */
#define PACN2 DVUCP(0x0063) /* low */
#define PACN1 DVUCP(0x0064) /* high */
#define PACN0 DVUCP(0x0065) /* low */
/* Pulse accumulator holding registers dual access, 8 or 16 bit */
#define PACHUS2 DVUSP(0x0072) /* 16 bit (0x0072 PACH3, 0x0073 PACH2) */
#define PACHUS0 DVUSP(0x0074) /* 16 bit (0x0074 PACH1, 0x0075 PACH0) */
#define PA3H DVUCP(0x0072) /* high */
#define PA2H DVUCP(0x0073) /* low */
#define PA1H DVUCP(0x0074) /* high */
#define PA0H DVUCP(0x0075) /* low */


/* Modulus down counter control registers */
#define MCCTL DVUCP(0x0066) /* Modulus control register */
#define MCFLG DVUCP(0x0067) /* Modulus flag (high bit) and input edge indicators (low 4 bits) */
#define MCCNT DVUSP(0x0076) /* 16 bit (0x0076 MCCNT (hi), 0x0077 MCCNT (lo)) */
#define PTMCPSR DVUCP(0x006F) /* Precision prescaler for the modulus down counter */


/* Analog To Digital converter 1 */
/* TODO Configure these and disable the non functional 16 - 23 144 pin section! */
#define ATD1CTL0 DVUCP(0x0080) /* 0 - 3 define which ADC channel to wrap on when doing multiple channels */
#define ATD1CTL1 DVUCP(0x0081) /* External trigger select when enabled in other control register */
#define ATD1CTL2 DVUCP(0x0082) /* bit 7 turns the ADC block on. */
#define ATD1CTL3 DVUCP(0x0083) /* bit 6 means conversion length is 8, bit 2 controls how the registers are used, bits 0 - 1 define freeze mode behaviour */
#define ATD1CTL4 DVUCP(0x0084) /* bit 7 should be zero meaning 10bit ADC, bits 6,5 are the sample period, and 4,3,2,1,0 are the sample frequency clock scaler */
#define ATD1CTL5 DVUCP(0x0085) /* bit 7 sets right justify, bit 5 sets scan mode, bit 4 sets multiplex mode */
//0x0086 ATD1STAT0 DVUCP() /*
//0x0088 ATD1TEST0 DVUCP() /*
//0x0089 ATD1TEST1 DVUCP() /*
//0x008A ATD1STAT2 DVUCP() /*
//0x008B ATD1STAT1 DVUCP() /*
#define ATD1DIEN0 DVUCP(0x008C) /* Digital input enable - these pins are not bonded on the 112 pin package */
#define ATD1DIEN1 DVUCP(0x008D) /* Digital input enable */
//0x008E ATD1PTAD0 DVUCP() /* digital use only */
//0x008F ATD1PTAD1 DVUCP() /* digital use only */
// one short for each hi lo par based on hi address. label with WORD for consistency
#define ATD1_BASE 0x0090
#define ATD1DR0 DVUSP(ATD1_BASE + 0x0) /* 16 bit (0x0090 ATD1DR0H, 0x0091 ATD1DR0L) */ /* SpareADC (NC)		*/
#define ATD1DR1 DVUSP(ATD1_BASE + 0x2) /* 16 bit (0x0092 ATD1DR1H, 0x0093 ATD1DR1L) */ /* SpareADC (NC)		*/
#define ATD1DR2 DVUSP(ATD1_BASE + 0x4) /* 16 bit (0x0094 ATD1DR2H, 0x0095 ATD1DR2L) */ /* SpareADC (NC)		*/
#define ATD1DR3 DVUSP(ATD1_BASE + 0x6) /* 16 bit (0x0096 ATD1DR3H, 0x0097 ATD1DR3L) */ /* SpareADC (NC)		*/
#define ATD1DR4 DVUSP(ATD1_BASE + 0x8) /* 16 bit (0x0098 ATD1DR4H, 0x0099 ATD1DR4L) */ /* SpareADC (NC)		*/
#define ATD1DR5 DVUSP(ATD1_BASE + 0xA) /* 16 bit (0x009A ATD1DR5H, 0x009B ATD1DR5L) */ /* SpareADC (NC)		*/
#define ATD1DR6 DVUSP(ATD1_BASE + 0xC) /* 16 bit (0x009C ATD1DR6H, 0x009D ATD1DR6L) */ /* SpareADC (NC)		*/
#define ATD1DR7 DVUSP(ATD1_BASE + 0xE) /* 16 bit (0x009E ATD1DR7H, 0x009F ATD1DR7L) */ /* SpareADC (NC)		*/


/* NOT bonded on the 112 pin package!! Left here in case of 144 pin FreeEMS later on. */
//0x00A0 ATD1DR8H
//0x00A1 ATD1DR8L
//0x00A2 ATD1DR9H
//0x00A3 ATD1DR9L
//0x00A4 ATD1DR10H
//0x00A5 ATD1DR10L
//0x00A6 ATD1DR11H
//0x00A7 ATD1DR11L
//0x00A8 ATD1DR12H
//0x00A9 ATD1DR12L
//0x00AA ATD1DR13H
//0x00AB ATD1DR13L
//0x00AC ATD1DR14H
//0x00AD ATD1DR14L
//0x00AE ATD1DR15H
//0x00AF ATD1DR15L
/* NOT bonded on the 112 pin package!! Left here in case of 144 pin FreeEMS later on. */


/* IIC1 - Inter Intergrated Circuit interface 1 TODO configure and use */
//0x00B0 IBAD DVUCP() /*
//0x00B1 IBFD DVUCP() /*
//0x00B2 IBCR DVUCP() /*
//0x00B3 IBSR DVUCP() /*
//0x00B4 IBDR DVUCP() /*


/* SCI2 */
//0x00B8 SCI2BDH
//0x00B8 SCI2ASR1
//0x00B9 SCI2BDL
//0x00B9 SCI2ACR1
//0x00BA SCI2CR1
//0x00BA SCI2ACR2
//0x00BB SCI2CR2
//0x00BC SCI2SR1
//0x00BD SCI2SR2
//0x00BE SCI2DRH
//0x00BF SCI2DRL


/* SCI3 */
//0x00C0 SCI3BDH
//0x00C0 SCI3ASR1
//0x00C1 SCI3BDL
//0x00C1 SCI3ACR1
//0x00C2 SCI3CR1
//0x00C2 SCI3ACR2
//0x00C3 SCI3CR2
//0x00C4 SCI3SR1
//0x00C5 SCI3SR2
//0x00C6 SCI3DRH
//0x00C7 SCI3DRL


/* SCI0 debug/comms/datalogging TODO this is our primary serial interface for flash loading, setup serial comms software to communicate with MTX or similar for testing. */
#define SCI0_BASE 0x00C8

#define SCI0BD DVUSP(SCI0_BASE + 0x0)		/* #define SCI0BDH DVUCP(0x00C8), #define SCI0BDL DVUCP(0x00C9) (IR and baud control) */
#define SCI0CR1 DVUCP(SCI0_BASE + 0x2)	/* Control reg 1 */

#define SCI0ASR1 DVUCP(SCI0_BASE + 0x0)	/* Status reg 1a (rx flags) */
#define SCI0ACR1 DVUCP(SCI0_BASE + 0x1)	/* Control reg 1a (rx conf) */
#define SCI0ACR2 DVUCP(SCI0_BASE + 0x2)	/* Control reg 2a (rx conf) */

#define SCI0CR2 DVUCP(SCI0_BASE + 0x3)	/* Control reg 2 */
#define SCI0SR1 DVUCP(SCI0_BASE + 0x4)	/* Status reg 1 (isr flags) */
#define SCI0SR2 DVUCP(SCI0_BASE + 0x5)	/* Status reg 2 (config/control) */
#define SCI0DRH DVUCP(SCI0_BASE + 0x6)	/* Data reg high (9th bit bit 7 receive bit 6 send) */
#define SCI0DRL DVUCP(SCI0_BASE + 0x7)	/* Data reg low (read and write for receive and send respectively)*/


/* SCI1 debug/comms/datalogging TODO this is our secondary serial interface, setup serial comms software to communicate with MTX or similar for testing. */
//0x00D0 SCI1BDH
//0x00D1 SCI1BDL
//0x00D2 SCI1CR1

//0x00D0 SCI1ASR1
//0x00D1 SCI1ACR1
//0x00D2 SCI1ACR2

//0x00D3 SCI1CR2
//0x00D4 SCI1SR1
//0x00D5 SCI1SR2
//0x00D6 SCI1DRH
//0x00D7 SCI1DRL


/* SPI0 */
#define SPI0CR1 DVUCP(0x00D8)
#define SPI0CR2 DVUCP(0x00D9)
#define SPI0BR  DVUCP(0x00DA)
#define SPI0SR  DVUCP(0x00DB)
#define SPI0DR  DVUCP(0x00DD)


/* IIC0  */
//0x00E0 IBAD
//0x00E1 IBFD
//0x00E2 IBCR
//0x00E3 IBSR
//0x00E4 IBDR


/* SPI1 */
//0x00F0 SPI1CR1
//0x00F1 SPI1CR2
//0x00F2 SPI1BR
//0x00F3 SPI1SR
//0x00F5 SPI1DR


/* SPI2 */
//0x00F8 SPI2CR1
//0x00F9 SPI2CR2
//0x00FA SPI2BR
//0x00FB SPI2SR
//0x00FD SPI2DR


/* Flash Control Registers */
#define FCLKDIV DVUCP(0x0100)	/* Flash Clock Divider Register R/W		*/
#define FSEC DVUCP(0x0101)		/* Flash Security Register R			*/
#define FCNFG DVUCP(0x0103)		/* Flash Configuration Register R/W		*/
#define FPROT DVUCP(0x0104)		/* Flash Protection Register R/W		*/
#define FSTAT DVUCP(0x0105)		/* Flash Status Register R/W			*/
#define FCMD DVUCP(0x0106)		/* Flash Command Register R/W			*/
#define FCTL DVUCP(0x0107)		/* Flash Control Register R				*/

#define FADDR DVUSP(0x0108)		/* Flash Low Address Register R (0x0108 FADDRHI, 0x0109 FADDRLO)	*/
#define FDATA DVUSP(0x010A)		/* Flash High Data Register R (0x010A FDATAHI, 0x010B FDATALO)		*/


/* EEPROM Control Registers TODO learn how to use these to write data to the eeprom through serial comms. */
//0x0110 ECLKDIV
//0x0113 ECNFG
//0x0114 EPROT
//0x0115 ESTAT
//0x0116 ECMD
//0x0118 EADDRHI
//0x0119 EADDRLO
//0x011A EDATAHI
//0x011B EDATALO


//// IM
#define IVBR DVUCP(0x0121) /* Interrupt vector table base location first byte (second is always 0x00) */
#define INT_XGPRIO DVUCP(0x0126)
#define INT_CFADDR DVUCP(0x0127)
#define INT_CFDATA0 DVUCP(0x0128)
#define INT_CFDATA_ARR AVUCP(0x0128)
#define INT_CFDATA1 DVUCP(0x0129)
#define INT_CFDATA2 DVUCP(0x012A)
#define INT_CFDATA3 DVUCP(0x012B)
#define INT_CFDATA4 DVUCP(0x012C)
#define INT_CFDATA5 DVUCP(0x012D)
#define INT_CFDATA6 DVUCP(0x012E)
#define INT_CFDATA7 DVUCP(0x012F)


/* SCI4 */
//0x0130 SCI4BDH
//0x0130 SCI4ASR1
//0x0131 SCI4BDL
//0x0131 SCI4ACR1
//0x0132 SCI4CR1
//0x0132 SCI4ACR2
//0x0133 SCI4CR2
//0x0134 SCI4SR1
//0x0135 SCI4SR2
//0x0136 SCI4DRH
//0x0137 SCI4DRL


/* SCI5 */
//0x0138 SCI5BDH
//0x0138 SCI5ASR1
//0x0139 SCI5BDL
//0x0139 SCI5ACR1
//0x013A SCI5CR1
//0x013A SCI5ACR2
//0x013B SCI5CR2
//0x013C SCI5SR1
//0x013D SCI5SR2
//0x013E SCI5DRH
//0x013F SCI5DRL


/* CAN0 don't want this for now, leave it disabled too. CAN0CTL1 bit 7 should be set to zero to disable this. */
//0x0140 CAN0CTL0
#define CAN0CTL1 DVUCP(0x0141)
//0x0142 CAN0BTR0
//0x0143 CAN0BTR1
//0x0144 CAN0RFLG
//0x0145 CAN0RIER
//0x0146 CAN0TFLG
//0x0147 CAN0TIER
//0x0148 CAN0TARQ
//0x0149 CAN0TAAK
//0x014A CAN0TBSEL
//0x014B CAN0IDAC
//0x014D CAN0MISC
//0x014E CAN0RXERR
//0x014F CAN0TXERR
//0x0150 – 0x0153 : CAN0IDAR0 – CAN0IDAR3
//0x0154 – 0x0157 : CAN0IDMR0 – CAN0IDMR3
//0x0158 – 0x015B : CAN0IDAR4 – CAN0IDAR7
//0x015C – 0x015F : CAN0IDMR4 – CAN0IDMR7
//0x0160 – 0x016F : CAN0RXFG
//0x0170 – 0x017F : CAN0TXFG


//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&
//this block applies to all can maps!!!
//
//0xXXX0
//Extended ID
//Standard ID
//CANxRIDR0
//0xXXX1
//Extended ID
//Standard ID
//CANxRIDR1
//0xXXX2
//Extended ID
//Standard ID
//CANxRIDR2
//0xXXX3
//Extended ID
//Standard ID
//CANxRIDR3
//
//0xXXX4–
//0xXXXB
//CANxRDSR0–
//CANxRDSR7
//0xXXXC CANRxDLR
//0xXXXD Reserved
//0xXXXE CANxRTSRH
//0xXXXF CANxRTSRL
//0xXX10
//Extended ID
//CANxTIDR0
//Standard ID
//
//0xXX0x
//XX10
//Extended ID
//CANxTIDR1
//Standard ID
//0xXX12
//Extended ID
//CANxTIDR2
//Standard ID
//0xXX13
//Extended ID
//CANxTIDR3
//Standard ID
//
//0xXX14–
//0xXX1B
//CANxTDSR0–
//CANxTDSR7
//
//0xXX1C CANxTDLR
//0xXX1D CANxTTBPR
//0xXX1E CANxTTSRH
//0xXX1F CANxTTSRL

//&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&77


/* CAN1 don't want this for now, leave it disabled too. CAN1CTL1 bit 7 should be set to zero to disable this. */
//0x0180 CAN1CTL0
#define CAN1CTL1 DVUCP(0x0181)
//0x0182 CAN1BTR0
//0x0183 CAN1BTR1
//0x0184 CAN1RFLG
//0x0185 CAN1RIER
//0x0186 CAN1TFLG
//0x0187 CAN1TIER
//0x0188 CAN1TARQ
//0x0189 CAN1TAAK
//0x018A CAN1TBSEL
//0x018B CAN1IDAC
//0x018D CAN1MISC
//0x018E CAN1RXERR
//0x018F CAN1TXERR
//0x0190 CAN1IDAR0
//0x0191 CAN1IDAR1
//0x0192 CAN1IDAR2
//0x0193 CAN1IDAR3
//0x0194 CAN1IDMR0
//0x0195 CAN1IDMR1
//0x0196 CAN1IDMR2
//0x0197 CAN1IDMR3
//0x0198 CAN1IDAR4
//0x0199 CAN1IDAR5
//0x019A CAN1IDAR6
//0x019B CAN1IDAR7
//0x019C CAN1IDMR4
//0x019D CAN1IDMR5
//0x019E CAN1IDMR6
//0x019F CAN1IDMR7
//0x01A0 – 0x01AF : CAN1RXFG
//0x01B0 – 0x01BF : CAN1TXFG


/* CAN2 CAN2CTL1 bit 7 should be set to zero to disable this. */
//0x01C0 CAN2CTL0
//0x01C1 CAN2CTL1
//0x01C2 CAN2BTR0
//0x01C3 CAN2BTR1
//0x01C4 CAN2RFLG
//0x01C5 CAN2RIER
//0x01C6 CAN2TFLG
//0x01C7 CAN2TIER
//0x01C8 CAN2TARQ
//0x01C9 CAN2TAAK
//0x01CA CAN2TBSEL
//0x01CB CAN2IDAC
//0x01CD CAN2MISC
//0x01CE CAN2RXERR
//0x01CF CAN2TXERR
//0x01D0 CAN2IDAR0
//0x01D1 CAN2IDAR1
//0x01D2 CAN2IDAR2
//0x01D3 CAN2IDAR3
//0x01D4 CAN2IDMR0
//0x01D5 CAN2IDMR1
//0x01D6 CAN2IDMR2
//0x01D7 CAN2IDMR3
//0x01D8 CAN2IDAR4
//0x01D9 CAN2IDAR5
//0x01DA CAN2IDAR6
//0x01DB CAN2IDAR7
//0x01DC CAN2IDMR4
//0x01DD CAN2IDMR5
//0x01DE CAN2IDMR6
//0x01DF CAN2IDMR7
//0x01E0 – 0x01EF : CAN2RXFG
//0x01F0 – 0x01FF : CAN2TXFG


/* CAN3 CAN3CTL1 bit 7 should be set to zero to disable this. */
//0x0200 CAN3CTL0
#define CAN3CTL1 DVUCP(0x0201)
//0x0202 CAN3BTR0
//0x0203 CAN3BTR1
//0x0204 CAN3RFLG
//0x0205 CAN3RIER
//0x0206 CAN3TFLG
//0x0207 CAN3TIER
//0x0208 CAN3TARQ
//0x0209 CAN3TAAK
//0x020A CAN3TBSEL
//0x020B CAN3IDAC
//0x020E CAN3RXERR
//0x020F CAN3TXERR
//0x0210 CAN3IDAR0
//0x0211 CAN3IDAR1
//0x0212 CAN3IDAR2
//0x0213 CAN3IDAR3
//0x0214 CAN3IDMR0
//0x0215 CAN3IDMR1
//0x0216 CAN3IDMR2
//0x0217 CAN3IDMR3
//0x0218 CAN3IDAR4
//0x0219 CAN3IDAR5
//0x021A CAN3IDAR6
//0x021B CAN3IDAR7
//0x021C CAN3IDMR4
//0x021D CAN3IDMR5
//0x021E CAN3IDMR6
//0x021F CAN3IDMR7
//0x0220 – 0x022F : CAN3RXFG
//0x0230 – 0x023F : CAN3TXFG


/* CAN4 CAN4CTL1 bit 7 should be set to zero to disable this. */
//0x0280 CAN4CTL0
#define CAN4CTL1 DVUCP(0x0281)
//0x0282 CAN4BTR0
//0x0283 CAN4BTR1
//0x0284 CAN4RFLG
//0x0285 CAN4RIER
//0x0286 CAN4TFLG
//0x0287 CAN4TIER
//0x0288 CAN4TARQ
//0x0289 CAN4TAAK
//0x028A CAN4TBSEL
//0x028B CAN4IDAC
//0x028D CAN4MISC
//0x028E CAN4RXERR
//0x028F CAN4TXERR
//0x0290 CAN4IDAR0
//0x0291 CAN4IDAR1
//0x0292 CAN4IDAR2
//0x0293 CAN4IDAR3
//0x0294 CAN4IDMR0
//0x0295 CAN4IDMR1
//0x0296 CAN4IDMR2
//0x0297 CAN4IDMR3
//0x0298 CAN4IDAR4
//0x0299 CAN4IDAR5
//0x029A CAN4IDAR6
//0x029B CAN4IDAR7
//0x029C CAN4IDMR4
//0x029D CAN4IDMR5
//0x029E CAN4IDMR6
//0x029F CAN4IDMR7
//0x02A0 – 0x02AF : CAN4RXFG
//0x02B0 – 0x02BF : CAN4TXFG


/* ATD0 TODO configure this as ATD inputs and try them out to control rate of flashing of leds etc, or even, which LED's are flashing etc */
#define ATD0CTL0 DVUCP(0x02C0) /* 0 - 2 define which ADC channel to wrap on when doing multiple channels */
#define ATD0CTL1 DVUCP(0x02C1) /* External trigger select when enabled in other control register */
#define ATD0CTL2 DVUCP(0x02C2) /* bit 7 turns the ADC block on. */
#define ATD0CTL3 DVUCP(0x02C3) /* bit 6 means conversion length is 8, bit 2 controls how the registers are used, bits 0 - 1 define freeze mode behaviour */
#define ATD0CTL4 DVUCP(0x02C4) /* bit 7 should be zero meaning 10bit ADC, bits 6,5 are the sample period, and 4,3,2,1,0 are the sample frequency clock scaler */
#define ATD0CTL5 DVUCP(0x02C5) /* bit 7 sets right justify, bit 5 sets scan mode, bit 4 sets multiplex mode */
//0x02C6 ATD0STAT0
//0x02CB ATD0STAT1
#define ATD0DIEN DVUCP(0x02CD) /* Digital input enable */
//0x02CF ATD0PTAD0 digital use only
#define ATD0_BASE 0x02D0 /* Maybe use this with a loop to sample them in a compact way. */
#define ATD0DR0 DVUSP(ATD0_BASE + 0x0) /* 16 bit (0x02D0 ATD0DR0H, 0x02D1 ATD0DR0L) */ /* IAT/MAT on my JimStim setup			*/
#define ATD0DR1 DVUSP(ATD0_BASE + 0x2) /* 16 bit (0x02D2 ATD0DR1H, 0x02D3 ATD0DR1L) */ /* CHT/CLT on my JimStim setup			*/
#define ATD0DR2 DVUSP(ATD0_BASE + 0x4) /* 16 bit (0x02D4 ATD0DR2H, 0x02D5 ATD0DR2L) */ /* TPS/TPS on my JimStim setup			*/
#define ATD0DR3 DVUSP(ATD0_BASE + 0x6) /* 16 bit (0x02D6 ATD0DR3H, 0x02D7 ATD0DR3L) */ /* EGO/O2 on my JimStim setup				*/
#define ATD0DR4 DVUSP(ATD0_BASE + 0x8) /* 16 bit (0x02D8 ATD0DR4H, 0x02D9 ATD0DR4L) */ /* BRV  left of 3 one end of my h1 board	*/
#define ATD0DR5 DVUSP(ATD0_BASE + 0xA) /* 16 bit (0x02DA ATD0DR5H, 0x02DB ATD0DR5L) */ /* MAP   mid of 3 one end of my h1 board	*/
#define ATD0DR6 DVUSP(ATD0_BASE + 0xC) /* 16 bit (0x02DC ATD0DR6H, 0x02DD ATD0DR6L) */ /* AAP right of 3 one end of my h1 board	*/
#define ATD0DR7 DVUSP(ATD0_BASE + 0xE) /* 16 bit (0x02DE ATD0DR7H, 0x02DF ATD0DR7L) */ /* SpareADC/SPARE on my JimStim setup		*/


/* VREG unit, Low Voltage Interrupt and Autonomous Periodical Interrupt */
#define VREGCTRL DVUCP(0x02F1) /* VReg Control Register */
#define VREGAPICL DVUCP(0x02F2) /* Autonomous Periodical Interrupt Control Register */
#define VREGAPITR DVUCP(0x02F3) /* Autonomous Periodical Interrupt Trimming Register */
#define VREGAPIR DVUSP(0x02F4) /* Autonomous Periodical Interrupt Rate High and Low Registers (VREGAPIRH DVUCP(0x02F4), VREGAPIRL DVUCP(0x02F5)) */


#define PWME DVUCP(0x0300) /* PWM enable register */
#define PWMPOL DVUCP(0x0301) /* PWM polarity register */
#define PWMCLK DVUCP(0x0302) /* PWM clock choice register */
#define PWMPRCLK DVUCP(0x0303) /* PWM Clock prescalers (bits 0,1,2 and bits 4,5,6 control 4 pins each) */
#define PWMCAE DVUCP(0x0304) /* PWM Center Align Enable Register */
#define PWMCTL DVUCP(0x0305) /* PWM Concatenate, stop, wait, freeze register */
#define PWMSCLA DVUCP(0x0308) /* PWM Scale A register */
#define PWMSCLB DVUCP(0x0309) /* PWM Scale B register */
#define PWMCNT0 DVUCP(0x030C) /* PWM 8 bit counter	*/
#define PWMCNT1 DVUCP(0x030D) /*					*/
#define PWMCNT2 DVUCP(0x030E) /*					*/
#define PWMCNT3 DVUCP(0x030F) /*					*/
#define PWMCNT4 DVUCP(0x0310) /*					*/
#define PWMCNT5 DVUCP(0x0311) /*					*/
#define PWMCNT6 DVUCP(0x0312) /*					*/
#define PWMCNT7 DVUCP(0x0313) /* PWM 8 bit counter	*/
#define PWMPER0 DVUCP(0x0314) /* PWM period value	*/ /* Ign LED 6 on my JimStim */
#define PWMPER1 DVUCP(0x0315) /*					*/ /* Ign LED 4 on my JimStim */
#define PWMPER2 DVUCP(0x0316) /*					*/ /* Ign LED 2 on my JimStim */
#define PWMPER3 DVUCP(0x0317) /*					*/ /* Ign LED 1 on my JimStim */
#define PWMPER4 DVUCP(0x0318) /*					*/ /* Ign LED 3 on my JimStim */
#define PWMPER5 DVUCP(0x0319) /*					*/ /* Ign LED 5 on my JimStim */
#define PWMPER6 DVUCP(0x031A) /*					*/ /* NC yet */
#define PWMPER7 DVUCP(0x031B) /* PWM period value	*/ /* NC yet */
#define PWMDTY0 DVUCP(0x031C) /* PWM duty cycle value	*/
#define PWMDTY1 DVUCP(0x031D) /*						*/
#define PWMDTY2 DVUCP(0x031E) /*						*/
#define PWMDTY3 DVUCP(0x031F) /*						*/
#define PWMDTY4 DVUCP(0x0320) /*						*/
#define PWMDTY5 DVUCP(0x0321) /*						*/
#define PWMDTY6 DVUCP(0x0322) /*						*/
#define PWMDTY7 DVUCP(0x0323) /* PWM duty cycle value	*/
#define PWMSDN DVUCP(0x0324) /* PWM shutdown behaviour register */


/* Periodic Interupt Timer with down counter */
#define PITCFLMT DVUCP(0x0340)	/* PIT Control and Force Load Micro Timer Register, high bit enables, low 2 bits force load micro timers */
#define PITFLT DVUCP(0x0341)	/* PIT Force Load Timer Register, low 4 bits force load timers */
#define PITCE DVUCP(0x0342)		/* PIT Channel Enable Register, low 4 bits let the channel count */
#define PITMUX DVUCP(0x0343)	/* PIT Multiplex Register, low 4 bits set which micro time base is used */
#define PITINTE DVUCP(0x0344)	/* PIT Interrupt Enable Register, low four bits control the ISRs */
#define PITTF DVUCP(0x0345)		/* PIT Time-Out Flag Register, low 4 bits set when each counter reaches 0 */
#define PITMTLD0 DVUCP(0x0346)	/* PIT Micro Timer Load Register 0, time to start counting from when reaching zero */
#define PITMTLD1 DVUCP(0x0347)	/* PIT Micro Timer Load Register 1, time to start counting from when reaching zero */
#define PITLD0 DVUSP(0x0348)	/* PIT Load Register 0, time to start counting from when reaching zero (0x0348 PITLD0 (hi), 0x0349 PITLD0 (lo)) */
#define PITLD1 DVUSP(0x034C)	/* PIT Load Register 1, time to start counting from when reaching zero (0x034C PITLD1 (hi), 0x034D PITLD1 (lo)) */
#define PITLD2 DVUSP(0x0350)	/* PIT Load Register 2, time to start counting from when reaching zero (0x0350 PITLD2 (hi), 0x0351 PITLD2 (lo)) */
#define PITLD3 DVUSP(0x0354)	/* PIT Load Register 3, time to start counting from when reaching zero (0x0354 PITLD3 (hi), 0x0355 PITLD3 (lo)) */
#define PITCNT0 DVUSP(0x034A)	/* PIT Count Register 0, current value of down counter (0x034A PITCNT0 (hi), 0x034B PITCNT0 (lo)) */
#define PITCNT1 DVUSP(0x034E)	/* PIT Count Register 1, current value of down counter (0x034E PITCNT1 (hi), 0x034F PITCNT1 (lo)) */
#define PITCNT2 DVUSP(0x0352)	/* PIT Count Register 2, current value of down counter (0x0352 PITCNT2 (hi), 0x0353 PITCNT2 (lo)) */
#define PITCNT3 DVUSP(0x0356)	/* PIT Count Register 3, current value of down counter (0x0356 PITCNT3 (hi), 0x0357 PITCNT3 (lo)) */


// TODO XGATE Set up stuff
#define XGMCTL DVUSP(0x0380) /* TODO: 7th bit of this should be set to 0 for now to turn the XGATE off */
#define XGMCTLHI DVUCP(0x0380)
#define XGMCTLLO DVUCP(0x0381) /* TODO: or 7th bit of this should be set to 0 for now to turn the XGATE off */
#define XGCHID DVUCP(0x0382)
// unused on xdp512 #define XGVBR DVUCP(0x0384)
// unused on xdp512 #define XGVBR DVUCP(0x0385)
#define XGVBR DVUSP(0x0386)  /* This is all that is used on the xdp512! 16 bit (0x0386 DVUCP (hi), 0x0387 DVUCP (lo)) */
#define XGIF_0 DVUCP(0x0388)
#define XGIF_1 DVUCP(0x0389)
#define XGIF_2 DVUCP(0x038A)
#define XGIF_3 DVUCP(0x038B)  /* WRONG value 0x023B stated in the manual as being both xgate and can3!!!!! should be 0x038B i believe!!!!! */
#define XGIF_4 DVUCP(0x038C)  /* WRONG value 0x023C stated in the manual as being both xgate and can3!!!!! should be 0x038C i believe!!!!! */
#define XGIF_5 DVUCP(0x038D)
#define XGIF_6 DVUCP(0x038E)
#define XGIF_7 DVUCP(0x038F)
#define XGIF_8 DVUCP(0x0390)
#define XGIF_9 DVUCP(0x0391)
#define XGIF_A DVUCP(0x0392)
#define XGIF_B DVUCP(0x0393)
#define XGIF_C DVUCP(0x0394)
#define XGIF_D DVUCP(0x0395)
#define XGIF_E DVUCP(0x0396)
#define XGIF_F DVUCP(0x0397)
#define XGSWT DVUSP(0x0398)
//#define  DVUCP(0x0399 XGSWT (lo)
#define XGSEM DVUSP(0x039A)
//#define  DVUCP(0x039B XGSEM (lo)
#define XGCCR DVUCP(0x039D)
#define XGPC DVUSP(0x039E)
//#define  DVUCP(0x039F XGPC (lo)
#define XGR1 DVUSP(0x03A2)
//#define  DVUCP(0x03A3 XGR1 (lo)
#define XGR2 DVUSP(0x03A4)
//#define  DVUCP(0x03A5 XGR2 (lo)
#define XGR3 DVUSP(0x03A6)
//#define  DVUCP(0x03A7 XGR3 (lo)
#define XGR4 DVUSP(0x03A8)
//#define  DVUCP(0x03A9 XGR4 (lo)
#define XGR5 DVUSP(0x03AA)
//#define  DVUCP(0x03AB XGR5 (lo)
#define XGR6 DVUSP(0x03AC)
//#define  DVUCP(0x03AD XGR6 (lo)
#define XGR7 DVUSP(0x03AE)
//#define  DVUCP(0x03AF XGR7 (lo)


//// DBG
//0x0020 DBGC1 DVUCP() /*
//0x0021 DBGSR DVUCP() /*
//0x0022 DBGTCR DVUCP() /*
//0x0023 DBGC2 DVUCP() /*
//0x0024 DBGTBH DVUCP() /*
//0x0025 DBGTBL DVUCP() /*
//0x0026 DBGCNT DVUCP() /*
//0x0027 DBGSCRX DVUCP() /*
//COMPA 0x0028 DVUCP() /*
//COMPC 0x0028 DVUCP() /*
//DBGXCTL 0x0028 DVUCP() /*
//COMPB 0x0028 DVUCP() /*
//COMPD 0x0028 DVUCP() /*
//0x0029 DBGXAH DVUCP() /*
//0x002A DBGXAM DVUCP() /*
//0x002B DBGXAL DVUCP() /*
//0x002C DBGXDH DVUCP() /*
//0x002D DBGXDL DVUCP() /*
//0x002E DBGXDHM DVUCP() /*
//0x002F DBGXDLM DVUCP() /*


/* All reserved registers/blocks are listed here for reference */

/* 0x003E CTCTL COP test register */
/* 0x006D TIMTST Timer test register */
/* 0x0102 FTSTMOD Flash test register */
/* 0x02C8 ATD0TEST0 ADC test register */
/* 0x02C9 ATD0TEST1 ADC test register */
/* 0x02F0 VREGHTCL VReg test register */
/* 0x0306 PWMTST PWM test register */
/* 0x0307 PWMPRSC PWM test register 2 */
/* 0x030A PWMSCNTA PWM test register 3 */
/* 0x030B PWMSCNTB PWM test register 4 */


/* 0x001D Reserved				*/
/* 0x001F Reserved				*/
/* 0x0012 Reserved				*/
/* 0x0014 - 0x0015 : Reserved	*/
/* 0x0018 - 0x0019 : Reserved	*/
/* 0x0031 Reserved				*/
/* 0x006C Reserved				*/
/* 0x00B5 - 0x00B7 : Reserved	*/
/* 0x0087 Reserved				*/
/* 0x00DC Reserved				*/
/* 0x00DE - 0x00DF : Reserved	*/
/* 0x00E5 - 0x00EF : Reserved	*/
/* 0x00F4 Reserved				*/
/* 0x00F6 Reserved				*/
/* 0x00F7 Reserved				*/
/* 0x00FC Reserved				*/
/* 0x00FE - 0x00FF : Reserved	*/
/* 0x010C - 0x010F : Reserved	*/
/* 0x0111 Reserved				*/
/* 0x0112 Reserved				*/
/* 0x0117 Reserved				*/
/* 0x0120 Reserved				*/
/* 0x0122 - 0x0125 : Reserved	*/
/* 0x014C Reserved				*/
/* 0x018C Reserved				*/
/* 0x01CC Reserved				*/
/* 0x020C - 0x020D : Reserved	*/
/* 0x0246 - 0x0247 : Reserved	*/
/* 0x024F Reserved				*/
/* 0x0270 Reserved				*/
/* 0x0272 Reserved				*/
/* 0x0274 Reserved				*/
/* 0x0276 Reserved				*/
/* 0x028C Reserved				*/
/* 0x02C7 Reserved				*/
/* 0x02CA Reserved				*/
/* 0x02CC Reserved				*/
/* 0x02CE Reserved				*/
/* 0x02E0 – 0x02EF : Reserved	*/
/* 0x02F6 – 0x02FF : Reserved	*/
/* 0x0325 – 0x033F : Reserved	*/
/* 0x0358 – 0x037F : Reserved	*/
/* 0x0383 Reserved				*/
/* 0x039C Reserved				*/
/* 0x03A0 Reserved				*/
/* 0x03A1 Reserved				*/
/* 0x03B0 – 0x07FF : Reserved	*/


/* Clear any accidental use of Reserved from typing mistakes. */
#ifdef Reserved
	#error "We have accidentally defined reserved as Reserved in here, find it and fix it."
#endif


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file 9S12XDP512_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
