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


/**	@file commsCore.c
 * @ingroup communicationsFiles
 *
 * @brief Core communications functions.
 *
 * This file contains most of the core comms functionality. Currently that is
 * only for UART serial style communication. It is already too big and needs
 * to be split up somewhat. This will happen fairly soon during the serial
 * refactoring and protocol fine tuning.
 *
 * @todo TODO function to setup a packet and send it fn(populateBodyFunctionPointer(), header, other, fields, here, and, use, or, not, within){}
 * @todo TODO factor many things into functions and move the receive delegator to its own file
 *
 * @author Fred Cooke
 */


#define COMMSCORE_C
#include "inc/freeEMS.h"
#include "inc/flashWrite.h"
#include "inc/interrupts.h"
#include "inc/utils.h"
#include "inc/tableLookup.h"
#include "inc/locationIDs.h"
#include "inc/blockDetailsLookup.h"
#include "inc/commsCore.h"
#include <string.h>


/** @brief Populate a basic datalog packet
 *
 * Copies various chunks of data to the transmission buffer and truncates to
 * the configured length. If changing this, update the maxBasicDatalogLength.
 *
 * @author Fred Cooke
 *
 * @warning This function is only a skeleton at this time.
 */
void populateBasicDatalog(){
	/* Save the current position */
	unsigned char* position = TXBufferCurrentPositionHandler;

	DerivedVars->sp5++; // increment as basic log sequence generator

	/* Get core vars */
	memcpy(TXBufferCurrentPositionHandler, CoreVars, sizeof(CoreVar));
	TXBufferCurrentPositionHandler += sizeof(CoreVar);
	/* Get derived vars */
	memcpy(TXBufferCurrentPositionHandler, DerivedVars, sizeof(DerivedVar));
	TXBufferCurrentPositionHandler += sizeof(DerivedVar);
	/* Get raw adc counts */
	memcpy(TXBufferCurrentPositionHandler, ADCArrays, sizeof(ADCArray));
	TXBufferCurrentPositionHandler += sizeof(ADCArray);

	/* Set/Truncate the log to the specified length */
	TXBufferCurrentPositionHandler = position + configuredBasicDatalogLength;
}


//void populateLogicAnalyser(){
//	// get portT rpm input and inj main
//	// get portB ign
//	// get portA ign
//	// get portK inj staged
//}


// All of these require some range checking, eg only some registers, and all RAM, not flash, not other regs
// TODO pointer for one byte
// TODO pointer for one short
// TODO function to log generic memory region by location and size ? requires length!
// Ranges are :
// RAM window
// bss/data region
// IO registers etc that can't be altered simply by reading from.
// NOT :
// flash makes no sense
// some regs are sensitive
// some RAM is unused
// serial buffers make no sense
// eeprom makes no sense
//
// 2k of regs max - user beware for now
// 12k of RAM max
//
//init :
//logaddr = fixed.addr
//loglen = fixed.len
//
//len = loglen OR 1 OR 2
//
//check :
//if((addr < 0x0800) && (length < (0x0800 - addr))){
//	// reg space is OK
//}else if(((0x1000 < addr) && (addr < 0x4000)) && (length < (0x4000 - addr))){
//	// RAM space is OK
//}else{
//	// send an error instead
//}
//
//run check at init and set time, not run time or just not check?? maybe its silly to check at all
//
// /* Just dump the ADC channels as fast as possible */
//void populateScopeLogADCAll(){
//	sampleBlockADC(TXBufferCurrentPositionHandler);
//	TXBufferCurrentPositionHandler += sizeof(ADCArray);
//}


// what does this mean >> ??? TODO Look at the time stamps and where to write them, also whether to function call these simple blocks or write one function that handles all the logic.


/** @brief Finalise a packet and send it
 *
 * This functions job is to finalise the main loop part of the packet sending
 * process. It configures the pos/neg ack header bit, adds the code if neg,
 * runs a checksum over the packet data and tags it to the end before
 * configuring the various ISRs that need to send the data out.
 *
 * @author Fred Cooke
 *
 * @bug http://issues.freeems.org/view.php?id=81
 * @todo TODO fix the double/none start byte bug and remove the hack!
 */
void finaliseAndSend(unsigned short errorID){

	if(errorID != 0){
		RXHeaderFlags |= HEADER_IS_NACK;
		*((unsigned short*)TXBufferCurrentPositionHandler) = errorID;
		TXBufferCurrentPositionHandler += 2;
	}

	/* Get the length from the pointer */
	unsigned short TXPacketLengthToSend = (unsigned short)TXBufferCurrentPositionHandler - (unsigned short)&TXBuffer;

	/* Tag the checksum on the end */
	*TXBufferCurrentPositionHandler = checksum((unsigned char*)&TXBuffer, TXPacketLengthToSend);
	TXPacketLengthToSend++;

	/* Send it out on all the channels required. */

	/* SCI0 - Main serial interface */
	if(TXBufferInUseFlags & COM_SET_SCI0_INTERFACE_ID){
		/* Copy numbers to interface specific vars */
		TXPacketLengthToSendSCI0 = TXPacketLengthToSend;
		TXPacketLengthToSendCAN0 = TXPacketLengthToSend;

		/* Queue preamble by clearing and then setting transmit enable	*/
		/* See section 11.4.5.2 of the xdp512 specification document	*/
		//SCI0CR2 &= SCICR2_TX_DISABLE;
		//SCI0CR2 |= SCICR2_TX_ENABLE;

		/* Initiate transmission */
		SCI0DRL = START_BYTE;
		while(!(SCI0SR1 & 0x80)){/* Wait for ever until able to send then move on */}
		SCI0DRL = START_BYTE; // nasty hack that works... means at least one and most 2 starts are sent so stuff works, but is messy... there must be a better way.

		/* Note : Order Is Important! */
		/* TX empty flag is already set, so we must clear it by writing out before enabling the interrupt */
		SCI0CR2 |= SCICR2_TX_ISR_ENABLE;
	}
	/* CAN0 - Main CAN interface */
	if(TXBufferInUseFlags & COM_SET_CAN0_INTERFACE_ID){
		// just clear up front for now
		TXBufferInUseFlags &= COM_CLEAR_CAN0_INTERFACE_ID;
	}
	/* spare2 */
	if(TXBufferInUseFlags & COM_SET_SPARE2_INTERFACE_ID){
		// just clear up front for now
		TXBufferInUseFlags &= COM_CLEAR_SPARE2_INTERFACE_ID;
	}
	/* spare3 */
	if(TXBufferInUseFlags & COM_SET_SPARE3_INTERFACE_ID){
		// just clear up front for now
		TXBufferInUseFlags &= COM_CLEAR_SPARE3_INTERFACE_ID;
	}
	/* spare4 */
	if(TXBufferInUseFlags & COM_SET_SPARE4_INTERFACE_ID){
		// just clear up front for now
		TXBufferInUseFlags &= COM_CLEAR_SPARE4_INTERFACE_ID;
	}
	/* spare5 */
	if(TXBufferInUseFlags & COM_SET_SPARE5_INTERFACE_ID){
		// just clear up front for now
		TXBufferInUseFlags &= COM_CLEAR_SPARE5_INTERFACE_ID;
	}
	/* spare6 */
	if(TXBufferInUseFlags & COM_SET_SPARE6_INTERFACE_ID){
		// just clear up front for now
		TXBufferInUseFlags &= COM_CLEAR_SPARE6_INTERFACE_ID;
	}
	/* spare7 */
	if(TXBufferInUseFlags & COM_SET_SPARE7_INTERFACE_ID){
		// just clear up front for now
		TXBufferInUseFlags &= COM_CLEAR_SPARE7_INTERFACE_ID;
	}
}


/** @brief Decode a packet and respond
 *
 * This is the core function that controls which functionality is run when a
 * packet is received in full by the ISR code and control is passed back to the
 * main loop code. The vast majority of communications action happens here.
 *
 * @author Fred Cooke
 */
void decodePacketAndRespond(){
	/* Extract and build up the header fields */
	RXBufferCurrentPosition = (unsigned char*)&RXBuffer;
	TXBufferCurrentPositionHandler = (unsigned char*)&TXBuffer;

	/* Initialised here such that override is possible */
	TXBufferCurrentPositionSCI0 = (unsigned char*)&TXBuffer;
	TXBufferCurrentPositionCAN0 = (unsigned char*)&TXBuffer;

	/* Start this off as full packet length and build down to the actual length */
	RXCalculatedPayloadLength = RXPacketLengthReceived;

	/* Grab the RX header flags out of the RX buffer */
	RXHeaderFlags = *RXBufferCurrentPosition;
	RXBufferCurrentPosition++;
	RXCalculatedPayloadLength--;

	/* Flag that we are transmitting! */
	TXBufferInUseFlags |= COM_SET_SCI0_INTERFACE_ID;
	// SCI0 only for now...

	/* Load a blank header into the TX buffer ready for masking */
	unsigned char* TXHeaderFlags = TXBufferCurrentPositionHandler;
	*TXHeaderFlags = 0;
	TXBufferCurrentPositionHandler++;

	/* Grab the payload ID for processing and load the return ID */
	RXHeaderPayloadID = *((unsigned short*)RXBufferCurrentPosition);
	*((unsigned short*)TXBufferCurrentPositionHandler) = RXHeaderPayloadID + 1;
	RXBufferCurrentPosition += 2;
	TXBufferCurrentPositionHandler += 2;
	RXCalculatedPayloadLength -= 2;

	/* Check that the length is sufficient for the fields configured. Packets
	 * that are too long will be caught and rejected on an individual payload
	 * ID basis as the information required to handle that is not available at
	 * this point. Packets that are too short are rejected immediately!
	 */
	if(((RXHeaderFlags & HEADER_HAS_LENGTH) && (RXHeaderFlags & HEADER_HAS_SEQUENCE) && (RXPacketLengthReceived < 7))
		|| ((RXHeaderFlags & HEADER_HAS_LENGTH) && (RXPacketLengthReceived < 6))
		|| ((RXHeaderFlags & HEADER_HAS_SEQUENCE) && (RXPacketLengthReceived < 5))){
		finaliseAndSend(packetTooShortForSpecifiedFields);
		resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
		return;
	}

	/* Subtract checksum to get final length */
	RXCalculatedPayloadLength--;

	if(RXHeaderFlags & HEADER_HAS_SEQUENCE){
		*TXBufferCurrentPositionHandler = *RXBufferCurrentPosition;
		RXBufferCurrentPosition++;
		TXBufferCurrentPositionHandler++;
		RXCalculatedPayloadLength--;
		*TXHeaderFlags |= HEADER_HAS_SEQUENCE;
	}

	if(RXHeaderFlags & HEADER_HAS_LENGTH){
		RXHeaderPayloadLength = *((unsigned short*)RXBufferCurrentPosition);
		RXBufferCurrentPosition += 2;
		RXCalculatedPayloadLength -= 2;
		/* Already subtracted one for checksum */
		if(RXHeaderPayloadLength != RXCalculatedPayloadLength){
			finaliseAndSend(payloadLengthHeaderMismatch);
			resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
			return;
		}
	}

	/* Calculate the position of the end of the stored packet for later use as a buffer */
	void* leftOverBuffer = (void*)((unsigned short)&RXBuffer + RXPacketLengthReceived);

	unsigned short errorID = 0;
	/* This is where all the communication logic resides.
	 *
	 * Please Note: Length and it's flag should be set by each return packet
	 * type handler if required or desired.	If an ack has been requested,
	 * ensure the negative ack flag is set if the operation failed.
	 */
	switch (RXHeaderPayloadID){
		case requestInterfaceVersion:
		{
			if(RXCalculatedPayloadLength != 0){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			/* This type must have a length field, set that up */
			*((unsigned short*)TXBufferCurrentPositionHandler) = sizeof(interfaceVersionAndType);
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			TXBufferCurrentPositionHandler += 2;
			/* Load the body into place */
			memcpy((void*)TXBufferCurrentPositionHandler, (void*)&interfaceVersionAndType, sizeof(interfaceVersionAndType));
			TXBufferCurrentPositionHandler += sizeof(interfaceVersionAndType);
			break;
		}
		case requestFirmwareVersion:
		{
			if(RXCalculatedPayloadLength != 0){
				errorID = payloadLengthTypeMismatch;
				break;
			}
			/* This type must have a length field, set that up */
			*((unsigned short*)TXBufferCurrentPositionHandler) = sizeof(firmwareVersion);
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			TXBufferCurrentPositionHandler += 2;
			/* Load the body into place */
			memcpy((void*)TXBufferCurrentPositionHandler, (void*)&firmwareVersion, sizeof(firmwareVersion));
			TXBufferCurrentPositionHandler += sizeof(firmwareVersion);
			break;
		}
		case requestMaxPacketSize:
		{
			if(RXCalculatedPayloadLength != 0){
				errorID = payloadLengthTypeMismatch;
				break;
			}
			/* Load the size into place */
			*((unsigned short*)TXBufferCurrentPositionHandler) = RX_BUFFER_SIZE;
			TXBufferCurrentPositionHandler += 2;
			break;
		}
		case requestEchoPacketReturn:
		{
			/* This type must have a length field, set that up */
			*((unsigned short*)TXBufferCurrentPositionHandler) = RXPacketLengthReceived;
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			TXBufferCurrentPositionHandler += 2;
			/* Load the body into place */
			memcpy((void*)TXBufferCurrentPositionHandler, (void*)&RXBuffer, RXPacketLengthReceived);
			/* Note, there is no overflow check here because the TX buffer is slightly       */
			/* bigger than the RX buffer and there is overflow checking for receives anyway. */
			TXBufferCurrentPositionHandler += RXPacketLengthReceived;
			break;
		}
		case requestSoftSystemReset:
		{
			if(RXCalculatedPayloadLength != 0){
				errorID = payloadLengthTypeMismatch;
				break;
			}
			/* Perform soft system reset */
			_start();
		}
		case requestHardSystemReset:
		{
			if(RXCalculatedPayloadLength != 0){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			/* This is how the serial monitor does it. */
			COPCTL = 0x01; /* Arm with shortest time */
			ARMCOP = 0xFF; /* Write bad value, should cause immediate reset */
			/* Using _start() only resets the app ignoring the monitor switch. It does not work */
			/* properly because the location of _start is not the master reset vector location. */
		}
		case updateBlockInRAM:
		{
			// Subtract six to allow for the locationID, size, offset
			if(RXCalculatedPayloadLength < 7){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			// Extract the RAM location ID
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Extract the offset to place the data at
			unsigned short offset = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Extract the size of the data to be stored
			unsigned short size = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Look up the memory location details
			blockDetails details;
			lookupBlockDetails(locationID, &details);

			// Subtract six to allow for the locationID, size, offset
			if((RXCalculatedPayloadLength - 6) != size){
				errorID = payloadShorterThanSpecifiedValue;
				break;
			}

			// If either of these is zero then this block is not in RAM!
			if((details.RAMPage == 0) || (details.RAMAddress == 0)){
				errorID = invalidMemoryActionForID;
				break;
			}

			// Check that size and offset describe a region that is not out of bounds
			if((size == 0) || (offset > (details.size - 1)) || (size > (details.size - offset))){
				errorID = invalidSizeOffsetCombination;
				break;
			}

			// Don't allow sub region manipulation where it does not make sense or is unsafe.
			if((size != details.size) && (locationID < FlashLookupTablesUpper) && (locationID >= twoDTableUSLocationUpper)){
				errorID = uncheckedTableManipulationNotAllowed;
				break;
			}

			// Save page values for restore
			unsigned char oldRamPage = RPAGE;
			// Set the viewable RAM page
			RPAGE = details.RAMPage;

			/// TODO @todo factor this out into validation delegation function once the number of types increases somewhat
			//
			if(locationID < twoDTableUSLocationUpper){
				void* bufferToCheck;

				// For sub regions, construct an image for verification
				if(size != details.size){
					// Copy data from destination location to buffer
					memcpy(leftOverBuffer, details.RAMAddress, details.size);

					// Copy data from rx buffer to buffer over writing old data
					memcpy(leftOverBuffer + offset, RXBufferCurrentPosition, size);

					bufferToCheck = leftOverBuffer;
				}else{
					bufferToCheck = RXBufferCurrentPosition;
				}

				// Verify all tables
				if(locationID < MainTableLocationUpper){
					errorID = validateMainTable((mainTable*)bufferToCheck);
				}else if(locationID < twoDTableUSLocationUpper){
					errorID = validateTwoDTable((twoDTableUS*)bufferToCheck);
				}// TODO add other table types here

				// If the validation failed, report it
				if(errorID != 0){
					break;
				}
			}

			// Copy from the RX buffer to the block of RAM
			memcpy((unsigned char*)(details.RAMAddress + offset), RXBufferCurrentPosition, size);

			// Check that the write was successful
			unsigned char index = compare(RXBufferCurrentPosition, (unsigned char*)(details.RAMAddress + offset), size);

			// Restore the original RAM and flash pages
			RPAGE = oldRamPage;

			if(index != 0){
				errorID = MEMORY_WRITE_ERROR;
			}
			break;
		}
		case updateBlockInFlash:
		{
			// Subtract six to allow for the locationID, size, offset
			if(RXCalculatedPayloadLength < 7){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			// Extract the RAM location ID
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Extract the offset to place the data at
			unsigned short offset = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Extract the size of the data to be stored
			unsigned short size = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Look up the memory location details
			blockDetails details;
			lookupBlockDetails(locationID, &details);

			// Subtract six to allow for the locationID, size, offset
			if((RXCalculatedPayloadLength - 6) != size){
				errorID = payloadShorterThanSpecifiedValue;
				break;
			}

			// If either of these is zero then this block is not in flash!
			if((details.FlashPage == 0) || (details.FlashAddress == 0)){
				errorID = invalidMemoryActionForID;
				break;
			}

			// Check that size and offset describe a region that is not out of bounds
			if((size == 0) || (offset > (details.size - 1)) || (size > (details.size - offset))){
				errorID = invalidSizeOffsetCombination;
				break;
			}

			// Don't allow sub region manipulation where it does not make sense or is unsafe.
			if((size != details.size) && (locationID < FlashLookupTablesUpper) && (locationID >= twoDTableUSLocationUpper)){
				errorID = uncheckedTableManipulationNotAllowed;
				break;
			}

			/// TODO @todo factor this out into validation delegation function once the number of types increases somewhat
			//
			if(locationID < twoDTableUSLocationUpper){
				void* bufferToCheck;

				// For sub regions, construct an image for verification
				if(size != details.size){
					/* Save page value for restore and set the visible page */
					unsigned char oldFlashPage = PPAGE;
					PPAGE = details.FlashPage;

					// Copy data from destination location to buffer
					memcpy(leftOverBuffer, details.FlashAddress, details.size);

					/* Restore the original flash page */
					PPAGE = oldFlashPage;

					// Copy data from rx buffer to buffer over writing old data
					memcpy(leftOverBuffer + offset, RXBufferCurrentPosition, size);

					bufferToCheck = leftOverBuffer;
				}else{
					bufferToCheck = RXBufferCurrentPosition;
				}

				// Verify all tables
				if(locationID < MainTableLocationUpper){
					errorID = validateMainTable((mainTable*)bufferToCheck);
				}else if(locationID < twoDTableUSLocationUpper){
					errorID = validateTwoDTable((twoDTableUS*)bufferToCheck);
				}// TODO add other table types here

				// If the validation failed, report it
				if(errorID != 0){
					break;
				}
			}

			/* Copy the flash details and populate the RAM details with the buffer location */
			blockDetails burnDetails;
			burnDetails.FlashPage = details.FlashPage;
			burnDetails.FlashAddress = details.FlashAddress + offset;
			burnDetails.RAMPage = RPAGE;
			burnDetails.RAMAddress = RXBufferCurrentPosition;
			burnDetails.size = size;

			/* Copy from the RX buffer to the block of flash */
			errorID = writeBlock(&burnDetails, leftOverBuffer);
			if(errorID != 0){
				break;
			}

			/* If present in RAM, update that too */
			if((details.RAMPage != 0) && (details.RAMAddress != 0)){
				/* Save page values for restore */
				unsigned char oldRamPage = RPAGE;
				/* Set the viewable RAM page */
				RPAGE = details.RAMPage;

				/* Copy from the RX buffer to the block of RAM */
				memcpy((unsigned char*)(details.RAMAddress + offset), RXBufferCurrentPosition, size);

				/* Check that the write was successful */
				unsigned char index = compare(RXBufferCurrentPosition, (unsigned char*)(details.RAMAddress + offset), size);

				/* Restore the original RAM and flash pages */
				RPAGE = oldRamPage;

				if(index != 0){
					errorID = MEMORY_WRITE_ERROR;
				}
			}

			break;
		}
		case retrieveBlockFromRAM:
		{
			if(RXCalculatedPayloadLength != 6){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			// Extract the RAM location ID
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Extract the offset to place the data at
			unsigned short offset = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Extract the size of the data to be stored
			unsigned short size = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			/* Look up the memory location details */
			blockDetails details;
			lookupBlockDetails(locationID, &details);

			if((details.RAMPage == 0) || (details.RAMAddress == 0)){
				errorID = invalidMemoryActionForID;
				break;
			}

			// Special behaviour for size of zero which returns the whole block
			if((size == 0) && (offset == 0)){
				size = details.size;
			}

			// Check that size and offset describe a region that is not out of bounds
			if((size == 0) || (offset > (details.size - 1)) || (size > (details.size - offset))){
				errorID = invalidSizeOffsetCombination;
				break;
			}

			// Don't allow sub region retrieval where it does not make sense or is unsafe. (keep it symmetric for djandruczyk)
			if((size != details.size) && (locationID < FlashLookupTablesUpper) && (locationID >= twoDTableUSLocationUpper)){
				errorID = doesNotMakeSenseToRetrievePartially;
				break;
			}

			/* Save page value for restore and set the visible page */
			unsigned char oldRamPage = RPAGE;
			RPAGE = details.RAMPage;

			/* Copy the block of RAM to the TX buffer */
			memcpy(TXBufferCurrentPositionHandler, (unsigned char*)(details.RAMAddress + offset), size);
			TXBufferCurrentPositionHandler += size;

			/* Restore the original RAM and flash pages */
			RPAGE = oldRamPage;

			break;
		}
		case retrieveBlockFromFlash:
		{
			if(RXCalculatedPayloadLength != 6){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			// Extract the RAM location ID
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Extract the offset to place the data at
			unsigned short offset = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Extract the size of the data to be stored
			unsigned short size = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			/* Look up the memory location details */
			blockDetails details;
			lookupBlockDetails(locationID, &details);

			if((details.FlashPage == 0) || (details.FlashAddress == 0)){
				errorID = invalidMemoryActionForID;
				break;
			}

			// Special behaviour for size of zero which returns the whole block
			if((size == 0) && (offset == 0)){
				size = details.size;
			}

			// Check that size and offset describe a region that is not out of bounds
			if((size == 0) || (offset > (details.size - 1)) || (size > (details.size - offset))){
				errorID = invalidSizeOffsetCombination;
				break;
			}

			// Don't allow sub region retrieval where it does not make sense or is unsafe. (keep it symmetric for djandruczyk)
			if((size != details.size) && (locationID < FlashLookupTablesUpper) && (locationID >= twoDTableUSLocationUpper)){
				errorID = doesNotMakeSenseToRetrievePartially;
				break;
			}

			/* Save page value for restore and set the visible page */
			unsigned char oldFlashPage = PPAGE;
			PPAGE = details.FlashPage;

			/* Copy the block of flash to the TX buffer */
			memcpy(TXBufferCurrentPositionHandler, (unsigned char*)(details.FlashAddress + offset), size);
			TXBufferCurrentPositionHandler += size;

			/* Restore the original RAM and flash pages */
			PPAGE = oldFlashPage;

			break;
		}
		case burnBlockFromRamToFlash:
		{
			if(RXCalculatedPayloadLength != 6){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			// Extract the RAM location ID
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Extract the offset to place the data at
			unsigned short offset = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Extract the size of the data to be stored
			unsigned short size = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			/* Look up the memory location details */
			blockDetails details;
			lookupBlockDetails(locationID, &details);

			/* Check that all data we need is present */
			if((details.RAMPage == 0) || (details.RAMAddress == 0) || (details.FlashPage == 0) || (details.FlashAddress == 0)){
				errorID = invalidMemoryActionForID;
				break;
			}

			// Check that size and offset describe a region that is not out of bounds
			if((size == 0) || (offset > (details.size - 1)) || (size > (details.size - offset))){
				errorID = invalidSizeOffsetCombination;
				break;
			}

			// Don't allow sub region retrieval where it does not make sense or is unsafe. (keep it symmetric for djandruczyk)
			if((size != details.size) && (locationID < FlashLookupTablesUpper) && (locationID >= twoDTableUSLocationUpper)){
				errorID = doesNotMakeSenseToRetrievePartially;
				break;
			}


			// adjust details block to feed to represent the subsection of ram and flash that we want to burn down.
			details.RAMAddress += offset;
			details.FlashAddress += offset;
			details.size = size;

			/* Write the block down from RAM to Flash */
			errorID = writeBlock(&details, leftOverBuffer);
			break;
		}
		case adjustMainTableCell:
		{
			if(RXCalculatedPayloadLength != 8){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			/* Extract the flash location ID from the received data */
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			/* Check the ID to ensure it is a main table */
			if(locationID >= MainTableLocationUpper){
				errorID = invalidIDForMainTableAction;
				break;
			}

			/* Extract the cell value and coordinates */
			unsigned short RPMIndex = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;
			unsigned short LoadIndex = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;
			unsigned short cellValue = *((unsigned short*)RXBufferCurrentPosition);

			/* Look up the memory location details */
			blockDetails details;
			lookupBlockDetails(locationID, &details);

			/* Attempt to set the value */
			errorID = setPagedMainTableCellValue(details.RAMPage, details.RAMAddress, RPMIndex, LoadIndex, cellValue);
			break;
		}
		case adjustMainTableRPMAxis:
		{
			if(RXCalculatedPayloadLength != 6){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			/* Extract the flash location ID from the received data */
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition -= 2;

			/* Check the ID to ensure it is a main table */
			if(locationID >= MainTableLocationUpper){
				errorID = invalidIDForMainTableAction;
				break;
			}

			/* Extract the cell value and coordinates */
			unsigned short RPMIndex = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition -= 2;
			unsigned short RPMValue = *((unsigned short*)RXBufferCurrentPosition);

			/* Look up the memory location details */
			blockDetails details;
			lookupBlockDetails(locationID, &details);

			/* Attempt to set the value */
			errorID = setPagedMainTableRPMValue(details.RAMPage, details.RAMAddress, RPMIndex, RPMValue);
			break;
		}
		case adjustMainTableLoadAxis:
		{
			if(RXCalculatedPayloadLength != 6){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			/* Extract the flash location ID from the received data */
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition -= 2;

			/* Check the ID to ensure it is a main table */
			if(locationID >= MainTableLocationUpper){
				errorID = invalidIDForMainTableAction;
				break;
			}

			/* Extract the cell value and coordinates */
			unsigned short LoadIndex = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition -= 2;
			unsigned short LoadValue = *((unsigned short*)RXBufferCurrentPosition);

			/* Look up the memory location details */
			blockDetails details;
			lookupBlockDetails(locationID, &details);

			/* Attempt to set the value */
			errorID = setPagedMainTableLoadValue(details.RAMPage, details.RAMAddress, LoadIndex, LoadValue);
			break;
		}
		case adjust2dTableAxis:
		{
			if(RXCalculatedPayloadLength != 6){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			/* Extract the flash location ID from the received data */
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition -= 2;

			/* Check the ID to ensure it is a 2d table */
			if((locationID < twoDTableUSLocationLower) || (locationID >= twoDTableUSLocationUpper)){
				errorID = invalidIDForTwoDTableAction;
				break;
			}

			/* Extract the cell value and coordinates */
			unsigned short axisIndex = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition -= 2;
			unsigned short axisValue = *((unsigned short*)RXBufferCurrentPosition);

			/* Look up the memory location details */
			blockDetails details;
			lookupBlockDetails(locationID, &details);

			/* Attempt to set the value */
			errorID = setPagedTwoDTableAxisValue(details.RAMPage, details.RAMAddress, axisIndex, axisValue);
			break;
		}
		case adjust2dTableCell:
		{
			if(RXCalculatedPayloadLength != 6){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			/* Extract the flash location ID from the received data */
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition -= 2;

			/* Check the ID to ensure it is a 2d table */
			if((locationID < twoDTableUSLocationLower) || (locationID >= twoDTableUSLocationUpper)){
				errorID = invalidIDForTwoDTableAction;
				break;
			}

			/* Extract the cell value and coordinates */
			unsigned short cellIndex = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition -= 2;
			unsigned short cellValue = *((unsigned short*)RXBufferCurrentPosition);

			/* Look up the memory location details */
			blockDetails details;
			lookupBlockDetails(locationID, &details);

			/* Attempt to set the value */
			errorID = setPagedTwoDTableCellValue(details.RAMPage, details.RAMAddress, cellIndex, cellValue);
			break;
		}
		case requestBasicDatalog:
		{
			if((RXCalculatedPayloadLength > 2) || (RXCalculatedPayloadLength == 1)){
				errorID = payloadLengthTypeMismatch;
				break;
			}else if(RXCalculatedPayloadLength == 2){
				unsigned short newConfiguredLength = *((unsigned short*)RXBufferCurrentPosition);
				if(newConfiguredLength > maxBasicDatalogLength){
					errorID = datalogLengthExceedsMax;
					break;
				}else{
					configuredBasicDatalogLength = newConfiguredLength;
				}
			}// fall through to use existing configured length

			/* Set the length field up */
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			*(unsigned short*)TXBufferCurrentPositionHandler = configuredBasicDatalogLength;

			/* Fill out the log and send */
			populateBasicDatalog();
			break;
		}
		case requestConfigurableDatalog:
		{
			/// perform function TODO @todo REWORK review this
			errorID = unimplementedFunction;
			break;
		}
		case setAsyncDatalogType:
		{
			if(RXCalculatedPayloadLength != 1){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			unsigned char newDatalogType = *((unsigned char*)RXBufferCurrentPosition);
			if(newDatalogType > 0x01){
				errorID = noSuchAsyncDatalogType;
				break;
			}

			TablesB.SmallTablesB.datalogStreamType = newDatalogType;
			break;
		}
		case forwardPacketOverCAN:
		{
			/// perform function TODO @todo REWORK review this
			errorID = unimplementedFunction;
			break;
		}
		case forwardPacketOverOtherUART:
		{
			/// perform function TODO @todo REWORK review this
			errorID = unimplementedFunction;
			break;
		}
		case retrieveArbitraryMemory:
		{
			if(RXCalculatedPayloadLength != 6){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			unsigned short length = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;
			// Make sure the buffer can handle the block
			if(length > TX_MAX_PAYLOAD_SIZE){
				errorID = requestedLengthTooLarge;
				break;
			}

			void* address = (void*) *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;
			// Ensure we don't try to read past the end of the address space
			if(((unsigned short)address) <= ((0xFFFF - length) + 1)){
				// TODO Possibly check and limit ranges
				errorID = requestedAddressDisallowed;
				break;
			}

			unsigned char RAMPage = *((unsigned char*)RXBufferCurrentPosition);
			RXBufferCurrentPosition++;
			// Ensure RAM page is valid. Being too high is not possible.
			if(RAMPage < RPAGE_MIN){
				errorID = requestedRAMPageInvalid;
				break;
			}

			unsigned char FlashPage = *((unsigned char*)RXBufferCurrentPosition);
			RXBufferCurrentPosition++;
			// Ensure Flash page is valid. Being too high is not possible.
			if(FlashPage < PPAGE_MIN){
				errorID = requestedFlashPageInvalid;
				break;
			}

			/* This type must have a length field, set that up */
			*((unsigned short*)TXBufferCurrentPositionHandler) = length + 6;
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			TXBufferCurrentPositionHandler += 2;

			/* Put the request payload into the reply */
			*((unsigned short*)TXBufferCurrentPositionHandler) = (unsigned short) address;
			TXBufferCurrentPositionHandler += 2;
			*((unsigned short*)TXBufferCurrentPositionHandler) = length;
			TXBufferCurrentPositionHandler += 2;
			*((unsigned char*)TXBufferCurrentPositionHandler) = RAMPage;
			TXBufferCurrentPositionHandler++;
			*((unsigned char*)TXBufferCurrentPositionHandler) = FlashPage;
			TXBufferCurrentPositionHandler++;

			/* Load the body into place */
			memcpy((void*)TXBufferCurrentPositionHandler, address, length);
			TXBufferCurrentPositionHandler += length;

			break;
		}
		case retrieveListOfLocationIDs:
		{
			if(RXCalculatedPayloadLength != 1){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			// Extract the type of list we want
			unsigned char listType = *((unsigned char*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 1;

			// This type must have a length field, set that up
			unsigned short * listLength = (unsigned short*)TXBufferCurrentPositionHandler;
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			TXBufferCurrentPositionHandler += 2;

			// Zero the counter before we start, woops!
			*listLength = 0;

			#define listOfAllValidLocationIDs   0x00
			switch (listType){
				case listOfAllValidLocationIDs:
				{
					unsigned long locationID;
					blockDetails details;
					for(locationID = 0;locationID < 65536;locationID++){
						unsigned short locationIDDoesntExist;
						locationIDDoesntExist = lookupBlockDetails((unsigned short)locationID, &details);

						if(!locationIDDoesntExist){
							*((unsigned short*)TXBufferCurrentPositionHandler) = (unsigned short)locationID;
							TXBufferCurrentPositionHandler += 2;
							*listLength += 2;
						}
					}

					break;
				}
				default:
				{
					errorID = noSuchLocationIDListType;
					break;
				}
			}

			break;
		}
		case retrieveLocationIDDetails:
		{
			if(RXCalculatedPayloadLength != 2){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			// Extract the RAM location ID
			unsigned short locationID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// Write straight to output buffer to save time/code
			errorID = lookupBlockDetails(locationID, (blockDetails*)TXBufferCurrentPositionHandler);

			if(errorID != 0){
				break;
			}

			// Adjust TX buffer position if successful
			TXBufferCurrentPositionHandler += sizeof(blockDetails);

			break;
		}
		default:
		{
			if((RXHeaderPayloadID % 2) == 1){
				errorID = invalidPayloadID;
			}else{
				errorID = unrecognisedPayloadID;
			}
		}
	}

	// Always reply, if errorID is zero it's just an ack.
	finaliseAndSend(errorID);

	/* Switch reception back on now that we are done with the received data */
	resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
	PORTK |= BIT0;
}


/** @brief Send an error if buffer free
 *
 * This is a wrapper for use outside the communication handler function. The error will only be sent if the buffer is empty and available, if not, it will be discarded.
 *
 * @author Fred Cooke
 *
 * @warning Use of this function signifies that the error you are trying to propagate is not urgent and can be forgotten.
 *
 * @note Consider not throwing an error if it seems appropriate to use this.
 *
 * @todo TODO this is only used in coreVarGen, such errors should be caught at init time, NOT runtime, fix that...
 *
 * @param errorID is the error ID to be passed out to listening devices.
 */
void sendErrorIfClear(unsigned short errorID){
	if(!TXBufferInUseFlags){
		TXBufferInUseFlags = ONES;
		sendErrorInternal(errorID);
	}else{
		Counters.commsErrorMessagesNotSent++;
	}
}


/* not currently used...
 *  @brief Send an error even if we must wait
 *
 * This is a wrapper for use outside the communication handler function. This
 * function will block until the error is able to be sent. This behaviour is
 * not recommended as it will interfere with engine operation somewhat.
 *
 * @author Fred Cooke
 *
 * @warning Use of this function signifies that the error you are trying to propagate is extremely urgent and can not be forgotten.
 *
 * @note Using this function blocks other main loop code from execution. Consider handling the error in another way if it seems appropriate to use this.
 *
 * @param errorID is the error ID to be passed out to listening devices.
 */
//void sendErrorBusyWait(unsigned short errorID){
//	while(TXBufferInUseFlags){} /* Wait till clear to send */
//	TXBufferInUseFlags = ONES;
//	sendErrorInternal(errorID);
//}


/** @brief Send an error
 *
 * This function is only for use inside the communication handling function.
 * Use of it outside this environment is not supported and behaviour when used
 * as such is undefined.
 *
 * @author Fred Cooke
 *
 * @warning ONLY use this function from within the communication handler.
 *
 * @see sendErrorIfClear()
 * @see sendErrorBusyWait()
 *
 * @todo TODO clean up the mess of commented out crap in here!
 * @todo TODO decide on errorCode or errorID and consistencise it everywhere.
 *
 * @param errorCode is the error ID to be passed out to listening devices.
 */
void sendErrorInternal(unsigned short errorID){
//	set buffer in use, consider blocking interrupts to do this cleanly


	//	TXBufferInUseFlags = 0;
	/* No need for atomic block here as one of two conditions will always be */
	/* true when calling this. Either we have been flagged to receive and    */
	/* decode a packet, or we are in an ISR. In either case it is safe to    */
	/* check the flags and initiate the sequence if they are clear.          */
//	if(RXTXSerialStateFlags & TX_IN_PROGRESS){
		/* It's OK to return without resetting as it will be done by */
		/* either of those processes if they are underway. The other */
		/* processes are not overridden because they have priority.  */
//		return;
//	}else{ /* Turn off reception */
		/* It's OK to turn this off if nothing was currently being received */
//		SCI0CR2 &= SCICR2_RX_ISR_DISABLE;
//		SCI0CR2 &= SCICR2_RX_DISABLE;

		/* Build up the packet */
		/* Set the pointer to the start */
		TXBufferCurrentPositionHandler = (unsigned char*)&TXBuffer;
		/* Set the length */
//		TXPacketLengthToSend = 5; /* Flags + Payload ID + Error Code */
		// Flags = empty
		*TXBufferCurrentPositionHandler = 0x00;
		TXBufferCurrentPositionHandler++;
		/* Set the payload ID */
		*((unsigned short*)TXBufferCurrentPositionHandler) = asyncErrorCodePacket;
		TXBufferCurrentPositionHandler += 2;

		finaliseAndSend(errorID);
//	}
}


/** @brief Send a debug message if buffer free
 *
 * This is a wrapper for use outside the communication handler function. The debug message will only be sent if the buffer is empty and available, if not, it will be discarded.
 *
 * @author Fred Cooke
 *
 * @note This function exists as a convenience to developers, do not publish code that calls this function.
 *
 * @param message is a pointer to the null terminated debug message string.
 */
void sendDebugIfClear(unsigned char* message){
	if(!TXBufferInUseFlags){
		TXBufferInUseFlags = ONES;
		sendDebugInternal(message);
	}else{
		Counters.commsDebugMessagesNotSent++;
	}
}


/** Send a debug message even if we must wait
 *
 * This is a wrapper for use outside the communication handler function. This
 * function will block until the debug message is able to be sent.
 *
 * @author Fred Cooke
 *
 * @note This function exists as a convenience to developers, do not publish code that calls this function.
 *
 * @param message is a pointer to the null terminated debug message string.
 */
//void sendDebugBusyWait(unsigned char* message){
//	while(TXBufferInUseFlags){} /* Wait till clear to send */
//	TXBufferInUseFlags = ONES;
//	sendDebugInternal(message);
//}


/** @brief Send a debug message
 *
 * Sends a null terminated debug message out on the broadcast address of all available interfaces.
 *
 * @author Fred Cooke
 *
 * @warning ONLY use this function from within the communication handler.
 *
 * @see sendDebugIfClear()
 * @see sendDebugBusyWait()
 *
 * @note This function exists as a convenience to developers, do not publish code that calls this function.
 *
 * @todo TODO clean up the mess of commented out crap in here!
 *
 * @param message is a pointer to the null terminated debug message string.
 */
void sendDebugInternal(unsigned char* message){

//	set buffer in use, consider blocking interrupts to do this cleanly

//	if(TRUE){
//		Counters.serialDebugUnsentCounter++;
//		return;
//	}
	// wrong :
	/* No need for atomic block here as one of two conditions will always be */
	/* true when calling this. Either we have been flagged to receive and    */
	/* decode a packet, or we are in an ISR. In either case it is safe to    */
	/* check the flags and initiate the sequence if they are clear.          */
	//if(RXTXSerialStateFlags & TX_IN_PROGRESS){
		// wrong :
		/* It's OK to return without resetting as it will be done by */
		/* either of those processes if they are underway. The other */
		/* processes are not overridden because they have priority.  */
		//TXBufferInUseFlags = 0;
		//return;
//	}else{ /* Turn off reception */
		/* It's OK to turn this off if nothing was currently being received */
	//	SCI0CR2 &= SCICR2_RX_ISR_DISABLE;
	//	SCI0CR2 &= SCICR2_RX_DISABLE;

		/* Build up the packet */
		/* Set the pointer to the start and init the length */
		TXBufferCurrentPositionHandler = (unsigned char*)&TXBuffer;

		/* Load a protocol with length header into the TX buffer ready for masking */
		*TXBufferCurrentPositionHandler = 0x11;
		TXBufferCurrentPositionHandler++;

		/* Set the payload ID */
		*((unsigned short*)TXBufferCurrentPositionHandler) = asyncDebugInfoPacket;
		TXBufferCurrentPositionHandler += 2;

		/* Store the length location */
		unsigned short* TXLength = (unsigned short*)TXBufferCurrentPositionHandler;
		TXBufferCurrentPositionHandler += 2;

		/* Copy the string into place and record the length copied */
		unsigned short messageLength = stringCopy(TXBufferCurrentPositionHandler, message);
		*TXLength = messageLength;
		TXBufferCurrentPositionHandler += messageLength;

		finaliseAndSend(0);
	//}
}


/* This function should be period limited to about 10 seconds internally (or by scheduler) */
//void checkCountersAndSendErrors(){
	// compare time stamps  with current time stamps and execute if old enough. (if no scheduler)

	// compare counters with counters cache (from last time) sending an error packet when they differ

	// copy counters to counters cache for next time

	// send errors with busy wait on the basis that all errors should be taken care of and not be sent in fairly short order?

	// or send with isr but just busy wait for it to finish before sending the next?

	// debug messages, busy wait or isr or both, perhaps busy wait till able to send, lock sending (need semaphore for this as well as sending one?) and initiate send, then carry on? investigate timeframes for sends of smallish 100byte packets.

	// need to figure out how to queue received packets for processing when we are currently sending stuff out.

	// above notes don't belong here really.
//}


//void prepareDatalog(){
//	// send data log by default otherwise
//	unsigned char chunksExpected = 8; // based on configuration, yet to determine how to calculate this number
//	unsigned char chunksLoaded = 0;
//	if ((!receiving) && (datalogMask & rawVarsMask)) {
//		//
//		chunksLoaded++;
//	}
//	if ((!receiving) && (datalogMask & Mask)) {
//		//
//		chunksLoaded++;
//	}
//	if ((!receiving) && (datalogMask & Mask)) {
//		//
//		chunksLoaded++;
//	}
//	if ((!receiving) && (datalogMask & Mask)) {
//		//
//		chunksLoaded++;
//	}
//	if ((!receiving) && (datalogMask & Mask)) {
//		//
//		chunksLoaded++;
//	}
//	if ((!receiving) && (datalogMask & Mask)) {
//		//
//		chunksLoaded++;
//	}
//	if ((!receiving) && (datalogMask & Mask)) {
//		//
//		chunksLoaded++;
//	}
//	if ((!receiving) && (datalogMask & Mask)) {
//		//
//		chunksLoaded++;
//	}
//	//	set the length
//	//	the pointer should be correct already
//}

