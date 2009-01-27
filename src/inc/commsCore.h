/*	FreeEMS - the open source engine management system

	Copyright 2008 Fred Cooke

	This file is part of the FreeEMS project.

	FreeEMS software is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	FreeEMS software is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/

	We ask that if you make any changes to this file you email them upstream to
	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!

	Thank you for choosing FreeEMS to run your engine! */


/** @file commsCore.h
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
EXTERN void sendErrorBusyWait(unsigned short) FPAGE_FE;
EXTERN void sendDebugBusyWait(unsigned char*) FPAGE_FE;

EXTERN void resetReceiveState(unsigned char) FPAGE_FE;
EXTERN void sendAckIfRequired(void) FPAGE_FE;
EXTERN void checksumAndSend(void) FPAGE_FE;

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
EXTERN unsigned short	RXHeaderPayloadID; // why glob
EXTERN unsigned char	RXHeaderSourceAddress;
EXTERN unsigned short	RXHeaderPayloadLength;


/* Header flag masks */
/* Always has flags (obviously)			*/
/* Always has payload ID so no flag		*/
/* Always has checksum, so no flag		*/
#define HEADER_IS_PROTO		BIT0
#define HEADER_HAS_ACK		BIT1
#define HEADER_IS_NACK		BIT2
#define HEADER_HAS_ADDRS	BIT3
#define HEADER_HAS_LENGTH	BIT4
#define HEADER_USER_BIT_A	BIT5
#define HEADER_USER_BIT_B	BIT6
#define HEADER_USER_BIT_C	BIT7


/*&&&&&&&&&&&&&&&&&&&&  Payload Type ID Name Value Pairs  &&&&&&&&&&&&&&&&&&&&*/

/* Please note, requests use even ID numbers and their matching responses use */
/* the odd number immediately above the original request ID. There are a few  */
/* examples where either a request is not required or a response not sent. In */
/* such cases the odd ID may be used for an packet asyncronously sent from    */
/* the EMS to the PC. These will be well commented when present.			  */


/*&&&&&&&&&&&&&&&&&&&&&&&&  Protocol Payload Type IDs  &&&&&&&&&&&&&&&&&&&&&&&*/

/* Firmware Independent functions */
#define requestInterfaceVersion		  0
#define requestFirmwareVersion		  2
#define requestMaxPacketSize		  4
#define requestEchoPacketReturn		  6
#define requestSoftSystemReset		  8	/* System comes up fresh, so no response */
//efine replytoSoftSystemReset		  9	/* This is reserved */
#define requestHardSystemReset		 10	/* System comes up fresh, so no response */
//efine replytoHardSystemReset		 11	/* This is reserved */


//efine requestAsyncErrorCode		 12	/* This is reserved */
#define asyncErrorCodePacket		 13	/* NOTE : Unrequested error event code packet */
//efine requestAsyncDebugInfo		 14	/* This is reserved */
#define asyncDebugInfoPacket		 15	/* NOTE : Unrequested debug information packet */


/*&&&&&&&&&&&&&&&&&&&&&&&&  Firmware Payload Type IDs  &&&&&&&&&&&&&&&&&&&&&&&*/

/* Whole block manipulation */
#define replaceBlockInRAM			  0
#define replaceBlockInFlash			  2
#define retrieveBlockFromRAM		  4
#define retrieveBlockFromFlash		  6
#define burnBlockFromRamToFlash 	  8
#define eraseAllBlocksFromFlash 	 10
#define burnAllBlocksOfFlash 		 12

/* Main table manipulation */
#define adjustMainTableCell			100
#define adjustMainTableRPMAxis		102
#define	adjustMainTableLoadAxis		104

/* 2d table manipulation */
#define adjust2dTableAxis			200
#define adjust2dTableCell			202

/* Datalog request packets */
#define requestBasicDatalog			300
#define responseBasicDatalog		301
#define requestConfigurableDatalog	302
#define responseConfigurableDatalog	303
#define setAsyncDatalogType			304

/* Special function */
#define forwardPacketOverCAN		400
#define forwardPacketOverOtherUART	402
#define invalidRAMLocationID		404
#define invalidFlashLocationID		406

/* 8 payload IDs for testing purposes */
#define testPayloadIDPacketType0	65520
#define testPayloadIDPacketType1	65522
#define testPayloadIDPacketType2	65524
#define testPayloadIDPacketType3	65526
#define testPayloadIDPacketType4	65528
#define testPayloadIDPacketType5	65530
#define testPayloadIDPacketType6	65532
#define testPayloadIDPacketType7	65534


#undef EXTERN


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file COMMS_CORE_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
