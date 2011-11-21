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
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_COMMS_CORE_H_SEEN
#define FILE_COMMS_CORE_H_SEEN


#ifdef EXTERN
#warning "EXTERN already defined by another header, please sort it out!"
#undef EXTERN /* If fail on warning is off, remove the definition such that we can redefine correctly. */
#endif


#ifdef COMMSCORE_C
#define EXTERN
/* Internal use without check on buffer, purely here to place functions in paged memory. */
void sendErrorInternal(unsigned short) FPAGE_FE;
void sendDebugInternal(unsigned char*) FPAGE_FE;
#else
#define EXTERN extern
#endif


/* Function declarations */
/* This function accesses paged flash and thus must be in linear space. Set explicitly to text. */
EXTERN void decodePacketAndRespond(void) TEXT;

EXTERN void sendErrorIfClear(unsigned short) FPAGE_FE;
EXTERN void sendDebugIfClear(unsigned char*) FPAGE_FE;
//EXTERN void sendErrorBusyWait(unsigned short) FPAGE_FE;
//EXTERN void sendDebugBusyWait(unsigned char*) FPAGE_FE;

EXTERN void resetReceiveState(unsigned char) FPAGE_FE;
EXTERN void finaliseAndSend(unsigned short) FPAGE_FE;

EXTERN void populateBasicDatalog(void) FPAGE_FE;


/* Global variables for TX (one set per interface) */
EXTERN unsigned short	TXPacketLengthToSendCAN0;
EXTERN unsigned short	TXPacketLengthToSendSCI0;
EXTERN unsigned char*	TXBufferCurrentPositionHandler;
EXTERN unsigned char*	TXBufferCurrentPositionCAN0;
EXTERN unsigned char*	TXBufferCurrentPositionSCI0;


/* Buffer use and source IDs/flags */
EXTERN unsigned char	TXBufferInUseFlags;
EXTERN unsigned char	RXBufferContentSourceID;
/* Masks for TXBufferInUseFlags and RXBufferContentSourceID */
#define COM_SET_SCI0_INTERFACE_ID		BIT0
#define COM_SET_CAN0_INTERFACE_ID		BIT1
#define COM_SET_SPARE2_INTERFACE_ID		BIT2
#define COM_SET_SPARE3_INTERFACE_ID		BIT3
#define COM_SET_SPARE4_INTERFACE_ID		BIT4
#define COM_SET_SPARE5_INTERFACE_ID		BIT5
#define COM_SET_SPARE6_INTERFACE_ID		BIT6
#define COM_SET_SPARE7_INTERFACE_ID		BIT7
#define COM_CLEAR_SCI0_INTERFACE_ID		NBIT0
#define COM_CLEAR_CAN0_INTERFACE_ID		NBIT1
#define COM_CLEAR_SPARE2_INTERFACE_ID	NBIT2
#define COM_CLEAR_SPARE3_INTERFACE_ID	NBIT3
#define COM_CLEAR_SPARE4_INTERFACE_ID	NBIT4
#define COM_CLEAR_SPARE5_INTERFACE_ID	NBIT5
#define COM_CLEAR_SPARE6_INTERFACE_ID	NBIT6
#define COM_CLEAR_SPARE7_INTERFACE_ID	NBIT7
#define CLEAR_ALL_SOURCE_ID_FLAGS		ZEROS


/* Global variables for RX (one set for all) */
EXTERN unsigned char	RXStateFlags;
EXTERN unsigned char*	RXBufferCurrentPosition;
EXTERN unsigned short	RXPacketLengthReceived;
EXTERN unsigned short	RXCalculatedPayloadLength; // why global??
/* Masks for SCIRXStateFlags */
//#define RX_BUFFER_IN_USE			BIT0
#define RX_READY_TO_PROCESS			BIT1
#define RX_SCI_ESCAPED_NEXT			BIT2
//#define RX_SCI_INSIDE_PACKET		BIT3
//#define RX_BUFFER_NOT_IN_USE		NBIT0
#define RX_CLEAR_READY_TO_PROCESS	NBIT1
#define RX_SCI_NOT_ESCAPED_NEXT		NBIT2
//#define RX_SCI_NOT_INSIDE_PACKET	NBIT3

/* Global CAN specific variables */
// TODO can id filters routing etc


/* Comms Control Enable and Disable Masks */
/* SCI masks */
#define SCICR2_RX_ENABLE		BIT2
#define SCICR2_TX_ENABLE		BIT3
#define SCICR2_RX_ISR_ENABLE	BIT5
#define SCICR2_TX_ISR_ENABLE	BIT7
#define SCICR2_RX_DISABLE		NBIT2
#define SCICR2_TX_DISABLE		NBIT3
#define SCICR2_RX_ISR_DISABLE	NBIT5
#define SCICR2_TX_ISR_DISABLE	NBIT7
/* CAN masks */
// TODO probably 8 of these too
// TODO probably 8 of these too
// TODO probably 8 of these too
// TODO probably 8 of these too
// TODO probably 8 of these too
// TODO probably 8 of these too
// TODO probably 8 of these too
// TODO probably 8 of these too



/* Header components */
EXTERN unsigned char	RXHeaderFlags;
EXTERN unsigned char*   TXHeaderFlags;
EXTERN unsigned short	RXHeaderPayloadID; /// TODO @todo why global?
EXTERN unsigned short	RXHeaderPayloadLength;


/* Header flag masks */
/* Always has flags (obviously)			*/
/* Always has payload ID so no flag		*/
/* Always has checksum, so no flag		*/
#define HEADER_HAS_LENGTH   BIT0
#define HEADER_IS_NACK      BIT1
#define HEADER_HAS_SEQUENCE BIT2
#define HEADER_RESERVED_E   BIT3
#define HEADER_RESERVED_D   BIT4
#define HEADER_RESERVED_C   BIT5
#define HEADER_RESERVED_B   BIT6
#define HEADER_RESERVED_A   BIT7


#define asyncDatalogOff        0x00 ///< Logs by polling only, reduces CPU load a little but gives much lower data rate
#define asyncDatalogBasic      0x01 ///< Good old default log, always contains the normal stuff, good for most people, most of the time
#define asyncDatalogScratchPad 0x02 ///< User log of anything, any subset of a block allowed, start offset, size, content pointers/flags
#define asyncDatalogStructs    0x03 ///< Key structs, or subsets of them, or chunk to chunk, streamed, more efficient than scratch pad and bigger if needed
#define asyncDatalogPosition   0x04 ///< Record a buffer of position information, send when full: http://forum.diyefi.org/viewtopic.php?f=8&t=1339
#define asyncDatalogBlockBytes 0x05 ///< Populate a large block with bytes as fast as possible, send when full
#define asyncDatalogBlockWords 0x06 ///< Populate a large block with bytes as fast as possible, send when full
#define asyncDatalogBlockLongs 0x07 ///< Populate a large block with bytes as fast as possible, send when full
#define asyncDatalogStreamByte 0x08 ///< Send out a single byte as often as possible, ~1kHz with occasional ~3ms gaps from math running instead
#define asyncDatalogStreamWord 0x09 ///< Send out a single word as often as possible, ~1kHz with occasional ~3ms gaps from math running instead
#define asyncDatalogStreamLong 0x0A ///< Send out a single long as often as possible, ~1kHz with occasional ~3ms gaps from math running instead
#define asyncDatalogLastType   asyncDatalogStreamLong


// Stuff that should only be found in this file.
#include "packetTypes.h"
#include "unitTestIDs.h"


#undef EXTERN


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file COMMS_CORE_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
