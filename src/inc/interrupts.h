/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010 Fred Cooke, Jared Harvey
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
 * @brief All interrupt handler declarations
 *
 * All of the declarations for ISR functions are done here because they are all
 * used in one place and it doesn't make sense to spread them out over N files
 * for N functions. ISR headers only exist where there is a requirement for
 * local variables and constants etc.
 *
 * @author Fred Cooke
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_INTERRUPTS_H_SEEN
#define FILE_INTERRUPTS_H_SEEN


/* http://www.gnu.org/software/m68hc11/m68hc11_gcc.html Section 1.4.1	*/
/* http://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Function-Attributes.html	*/
/* http://gcc.gnu.org/onlinedocs/gcc-4.0.0/gcc/Variable-Attributes.html	*/

/* Interrupt attribute shortcut */
#define INT __attribute__((interrupt))

/* Start and stop atomic operations (Things that we don't want interrupted half way through) */
/* For certain operations we will need to prevent the process from being interrupted, operations such as */
/* writing all vars to a block ready for reading and logging etc. The link below is for avrs, but goes */
/* into some detail about clearing and setting interrupts during important operations. */
/* http://hubbard.engr.scu.edu/embedded/avr/doc/avr-libc/avr-libc-user-manual/group__avr__interrupts.html */
#define ATOMIC_START() __asm__ __volatile__ ("sei")	/* set global interrupt mask */
#define ATOMIC_END() __asm__ __volatile__ ("cli")	/* clear global interrupt mask */

/* Interrupt vector memory management */
#define VECTORS __attribute__ ((section (".vectors")))
extern void _start(void);

/* Interrupt sub-routine prototypes - assigned to text1 region in linear space */
void UISR(void) INT TEXT1; /* Unimplemented Interrupt Sub Routine */

/** This ISR is expanded from @ref InjectorXISR via include
 * statement, and macro definitions, so are the othe 5 below.
 *
 * @see injectorISR.c
 * @see injectionISRs.c
 */
void Injector1ISR(void) INT TEXT1;
void Injector2ISR(void) INT TEXT1; ///< @copydoc Injector1ISR
void Injector3ISR(void) INT TEXT1; ///< @copydoc Injector1ISR
void Injector4ISR(void) INT TEXT1; ///< @copydoc Injector1ISR
void Injector5ISR(void) INT TEXT1; ///< @copydoc Injector1ISR
void Injector6ISR(void) INT TEXT1; ///< @copydoc Injector1ISR

/** RPM ISRs, IC timer for engine position and RPM.
 *
 * There are multiple copies of this interrupt handler, each is linked with the
 * rest of the code once such that if there are N decoder implementations and/or
 * variants, then there are N loadable binaries produced after a full build.
 *
 * For details on any specific decoder implementation, see the documentation for
 * that specific file.
 *
 * @author Various
 */
void PrimaryRPMISR(void) INT TEXT1;
void SecondaryRPMISR(void) INT TEXT1;  ///< @copydoc PrimaryRPMISR

void TimerOverflow(void) INT TEXT1;    /* IC/OC timer overflow handling */
void ModDownCtrISR(void) INT TEXT1;    /* Modulus Down Counter */

void IgnitionDwellISR(void) INT TEXT1; /* PIT timer 0 for dwell start */
void IgnitionFireISR(void) INT TEXT1;  /* PIT timer 1 for coil firing */
void StagedOnISR(void) INT TEXT1;      /* PIT timer 2 for switching staged injectors on */
void StagedOffISR(void) INT TEXT1;     /* PIT timer 3 for switching staged injectors off */

void PortPISR(void) INT TEXT1;         /* Port P interrupt service routine */
void PortHISR(void) INT TEXT1;         /* Port P interrupt service routine */
void PortJISR(void) INT TEXT1;         /* Port P interrupt service routine */

void IRQISR(void) INT TEXT1;           /* IRQ/PE1 interrupt service routine */
void XIRQISR(void) INT TEXT1;          /* XIRQ/PE0 interrupt service routine */

void RTIISR(void) INT TEXT1;           /* Real Time interrupt service routine */

void SCI0ISR(void) INT TEXT1;          /* Serial 0 interrupt service routine */

void LowVoltageISR(void) INT TEXT1;    /* Low voltage counter ISR */
void VRegAPIISR(void) INT TEXT1;       /* VReg periodic interrupt ISR */

typedef void (* interruptTable)(void);


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file INTERRUPTS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
