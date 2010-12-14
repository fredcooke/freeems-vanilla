/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010 Fred Cooke
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


/** @file packetTypes.h
 * @ingroup allHeaders
 */


/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_PACKET_TYPES_H_SEEN
#define FILE_PACKET_TYPES_H_SEEN


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
#define replaceBlockInRAM			256
#define replaceBlockInFlash			258
#define retrieveBlockFromRAM		260
#define retrieveBlockFromFlash		262
#define burnBlockFromRamToFlash 	264
#define eraseAllBlocksFromFlash 	266
#define burnAllBlocksOfFlash 		268

/* Main table manipulation */
#define adjustMainTableCell			300
#define adjustMainTableRPMAxis		302
#define	adjustMainTableLoadAxis		304

/* 2d table manipulation */
#define adjust2dTableAxis			306
#define adjust2dTableCell			308

/* Datalog request packets */
#define requestBasicDatalog			400
#define responseBasicDatalog		401 /* Defined because it can be used both synchronously and asynchronously */
#define requestConfigurableDatalog	402
#define responseConfigurableDatalog	403 /* Defined because it can be used both synchronously and asynchronously */
#define setAsyncDatalogType			404

/* Special function */
#define forwardPacketOverCAN		500
#define forwardPacketOverOtherUART	502

/* Generic memory grabber for debugging */
#define retrieveArbitraryMemory		600


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file PACKET_TYPES_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
