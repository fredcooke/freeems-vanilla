/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009 Fred Cooke
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
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_COMMS_ISRS_H_SEEN
#define FILE_COMMS_ISRS_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef COMMSISRS_C
#define EXTERN
#else
#define EXTERN extern
#endif


/* SCISR1 register fields
 *
 * From left most/most significant to right most/least significant.
 *
 * Abrev  Description					  Actions/Meaning
 * TRDE - Transmit Data Register Empty	- Load with more data if there is any			- Main Flag
 * TC   - Transmit Complete				- Nothing being sent and nothing loaded ready	- unused
 * RDRF - Receive Data Register Full	- Store data in buffer until packet complete	- Main Flag
 * IDLE - Idle Line						- Receive line is quiet							- unused
 * OR   - Overrun						- Discard partial data received and increment counter
 * NF   - Noise Flag					- Discard partial data received and increment counter
 * FE   - Framing Error					- Discard partial data received and increment counter
 * PF   - Parity Error					- Discard partial data received and increment counter
 *
 * SCISR1 flag masks */
#define SCISR1_TX_REGISTER_EMPTY	BIT7
#define SCISR1_TX_COMPLETE			BIT6
#define SCISR1_RX_REGISTER_FULL		BIT5
#define SCISR1_RX_IDLE_LINE			BIT4
#define SCISR1_RX_OVERRUN			BIT3
#define SCISR1_RX_NOISE				BIT2
#define SCISR1_RX_FRAMING			BIT1
#define SCISR1_RX_PARITY			BIT0


/* TX/RX state variables */
EXTERN unsigned char	TXByteEscaped;
EXTERN unsigned char	RXCalculatedChecksum;


#undef EXTERN

#else
	/* let us know if we are being untidy with headers */
	#warning "Header file COMMS_ISRS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
