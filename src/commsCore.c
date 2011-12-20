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
#include "inc/decoderInterface.h"
#include "inc/commsCore.h"
#include "inc/init.h"
#include <string.h> /// @todo TODO this is pulling in the system string.h not the m68hc1x version, and functions other than memcpy do not work because they are not in crt1.o or other included-by-default libs
#include <datalogPopulator.c>
#include "decoders/inc/BenchTest.h"


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

	/// @todo TODO setup proper sequence and clock with some sort of differential measurement log to log. insert in front of actual data because these are part of the log itself.

	// By default, default values are populated, but if you drop code into the custom directory, that replaces the defaults.
	populateCustomDatalog();
	// Done here to overwrite cheeky custom users data:
	KeyUserDebugs.coreStatusA = coreStatusA;
	KeyUserDebugs.tempClock++;
	KeyUserDebugs.clockIn8thsOfAMilli = Clocks.realTimeClockMain;
	KeyUserDebugs.clockInMilliSeconds = Clocks.realTimeClockMillis;

	/* Get core vars */
	memcpy(TXBufferCurrentPositionHandler, CoreVars, sizeof(CoreVar));
	TXBufferCurrentPositionHandler += sizeof(CoreVar);
	/* Get derived vars */
	memcpy(TXBufferCurrentPositionHandler, DerivedVars, sizeof(DerivedVar));
	TXBufferCurrentPositionHandler += sizeof(DerivedVar);
	/* Get raw adc counts */
	memcpy(TXBufferCurrentPositionHandler, &KeyUserDebugs, sizeof(KeyUserDebug));
	TXBufferCurrentPositionHandler += sizeof(KeyUserDebug);

	/* Set/Truncate the log to the specified length */
	TXBufferCurrentPositionHandler = position + TablesB.SmallTablesB.loggingSettings.basicDatalogLength;
}


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
//	TXBufferCurrentPositionHandler += sizeof(ADCBuffer);
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
		*TXHeaderFlags |= HEADER_IS_NACK;
		*((unsigned short*)TXBufferCurrentPositionHandler) = errorID;
		TXBufferCurrentPositionHandler += 2;
	}

	/* Tag the checksum on the end */
	*TXBufferCurrentPositionHandler = checksum((unsigned char*)&TXBuffer, ((unsigned short)TXBufferCurrentPositionHandler - (unsigned short)&TXBuffer));

	/* Send it out on all the channels required. */

	/* SCI0 - Main serial interface */
	if(TXBufferInUseFlags & COM_SET_SCI0_INTERFACE_ID){
		/* Initiate transmission */
		SCI0DRL = START_BYTE;

		/* Note : Order Is Important! */
		/* TX empty flag is already set, so we must clear it by writing out before enabling the interrupt */
		SCI0CR2 |= (SCICR2_TX_ENABLE | SCICR2_TX_ISR_ENABLE);
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
	TXBufferCurrentPositionHandler = (unsigned char*)&TXBuffer;

	/* Initialised here such that override is possible */
	TXBufferCurrentPositionSCI0 = (unsigned char*)&TXBuffer;
	TXBufferCurrentPositionCAN0 = (unsigned char*)&TXBuffer;

	// How big was the packet that we got back
	unsigned short RXPacketLengthReceived = (unsigned short)RXBufferCurrentPosition - (unsigned short)&RXBuffer;

	/* Check that the packet is big enough for header,ID,checksum */
	if(RXPacketLengthReceived < 4){
		resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
		FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_PACKETS_UNDER_LENGTH_OFFSET);
		KeyUserDebugs.serialAndCommsCodeErrors++;
		return;
	}

	/* Pull out the received checksum and calculate the real one, then check */
	unsigned char RXReceivedChecksum = (unsigned char)*(RXBufferCurrentPosition - 1);
	unsigned char RXCalculatedChecksum = checksum((unsigned char*)&RXBuffer, RXPacketLengthReceived - 1);
	if(RXCalculatedChecksum != RXReceivedChecksum){
		resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
		FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_CHECKSUM_MISMATCHES_OFFSET);
		KeyUserDebugs.serialAndCommsCodeErrors++;
		return;
	}

	/* Start this off as full packet length and build down to the actual length */
	RXCalculatedPayloadLength = RXPacketLengthReceived;

	/* Grab the RX header flags out of the RX buffer */
	RXBufferCurrentPosition = (unsigned char*)&RXBuffer;
	RXHeaderFlags = *RXBufferCurrentPosition;
	RXBufferCurrentPosition++;
	RXCalculatedPayloadLength--;

	/* Flag that we are transmitting! */
	TXBufferInUseFlags |= COM_SET_SCI0_INTERFACE_ID;
	// SCI0 only for now...

	/* Load a blank header into the TX buffer ready for masking */
	TXHeaderFlags = TXBufferCurrentPositionHandler;
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
	// FreeEMS Core Comms Interface cases
		case requestInterfaceVersion:
		{
			if(RXCalculatedPayloadLength != 0){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			/* This type must have a length field, set that up */
			*((unsigned short*)TXBufferCurrentPositionHandler) = sizeof(interfaceVersion);
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			TXBufferCurrentPositionHandler += 2;
			/* Load the body into place */
			memcpy((void*)TXBufferCurrentPositionHandler, (void*)&interfaceVersion, sizeof(interfaceVersion));
			TXBufferCurrentPositionHandler += sizeof(interfaceVersion);
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
		case requestReInitOfSystem:
		{
			if(RXCalculatedPayloadLength != 0){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			init();
			break;
		}
	// FreeEMS Vanilla Firmware Specific cases
		case clearCountersAndFlagsToZero:
		{
			if(RXCalculatedPayloadLength != 0){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			unsigned short zeroCounter;
			unsigned char* counterPointer = (char*) &Counters;
			for(zeroCounter = 0;zeroCounter < sizeof(Counter);zeroCounter++){
				*counterPointer = 0;
				counterPointer++;
			}
			KeyUserDebugs.flaggableFlags = 0;
			unsigned char* flaggablePointer = (char*) &Flaggables;
			for(zeroCounter = 0;zeroCounter < sizeof(Flaggable);zeroCounter++){
				*flaggablePointer = 0;
				flaggablePointer++;
			}
			break;
		}
		case requestDecoderName:
		case requestFirmwareBuildDate:
		case requestCompilerVersion:
		case requestOperatingSystem:
		{
			if(RXCalculatedPayloadLength != 0){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			unsigned char* stringToSend = 0;
			switch (RXHeaderPayloadID) {
				case requestDecoderName:
					stringToSend = (unsigned char*)decoderName;
					break;
				case requestFirmwareBuildDate:
					stringToSend = (unsigned char*)buildTimeAndDate;
					break;
				case requestCompilerVersion:
					stringToSend = (unsigned char*)compilerVersion;
					break;
				case requestOperatingSystem:
					stringToSend = (unsigned char*)operatingSystem;
					break;
			}
			/* This type must have a length field, set that up and load the body into place at the same time */
			*((unsigned short*)TXBufferCurrentPositionHandler) = stringCopy((TXBufferCurrentPositionHandler + 2), stringToSend);
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			// Update with length field and string length.
			TXBufferCurrentPositionHandler += 2 + *((unsigned short*)TXBufferCurrentPositionHandler);
			break;
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

			// Don't let anyone write to running variables unless we are running BenchTest firmware!
			if((details.flags & block_is_read_only) && !(compare((char*)&decoderName, BENCH_TEST_NAME, sizeof(BENCH_TEST_NAME)))){
				errorID = attemptToWriteToReadOnlyBlock;
				break;
			}

			// Subtract six to allow for the locationID, size, offset
			if((RXCalculatedPayloadLength - 6) != size){
				errorID = payloadNotEqualToSpecifiedValue;
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
			if((size != details.size) && !(details.flags & block_is_indexable)){
				errorID = uncheckedTableManipulationNotAllowed;
				break;
			}

			// Save page values for restore
			unsigned char oldRamPage = RPAGE;
			// Set the viewable RAM page
			RPAGE = details.RAMPage;

			/// TODO @todo factor this out into validation delegation function once the number of types increases somewhat
			//
			if((details.flags & block_is_main_table) || (details.flags & block_is_2dus_table)){
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
				if(details.flags & block_is_main_table){
					errorID = validateMainTable((mainTable*)bufferToCheck);
				}else if(details.flags & block_is_2dus_table){
					errorID = validateTwoDTable((twoDTableUS*)bufferToCheck);
				}// TODO add other table types here

				// If the validation failed, report it
				if(errorID != 0){
					RPAGE = oldRamPage; // Restore the original RAM page, even when getting an error condition.
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
				errorID = payloadNotEqualToSpecifiedValue;
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
			if((size != details.size) && !(details.flags & block_is_indexable)){
				errorID = uncheckedTableManipulationNotAllowed;
				break;
			}

			/// TODO @todo factor this out into validation delegation function once the number of types increases somewhat
			//
			if((details.flags & block_is_main_table) || (details.flags & block_is_2dus_table)){
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
				if(details.flags & block_is_main_table){
					errorID = validateMainTable((mainTable*)bufferToCheck);
				}else if(details.flags & block_is_2dus_table){
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
			if((size != details.size) && !(details.flags & block_is_indexable)){
				errorID = doesNotMakeSenseToRetrievePartially;
				break;
			}

			// This type must have a length field, set that up
			*((unsigned short*)TXBufferCurrentPositionHandler) = size;
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			TXBufferCurrentPositionHandler += 2;

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
			if((size != details.size) && !(details.flags & block_is_indexable)){
				errorID = doesNotMakeSenseToRetrievePartially;
				break;
			}

			// This type must have a length field, set that up
			*((unsigned short*)TXBufferCurrentPositionHandler) = size;
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			TXBufferCurrentPositionHandler += 2;

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
			if((size != details.size) && !(details.flags & block_is_indexable)){
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
		case requestDatalogPacket: // Set type through standard configuration methods
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
					TablesB.SmallTablesB.loggingSettings.basicDatalogLength = newConfiguredLength;
				}
			}// fall through to use existing configured length

			/* Set the length field up */
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			*(unsigned short*)TXBufferCurrentPositionHandler = TablesB.SmallTablesB.loggingSettings.basicDatalogLength;
			TXBufferCurrentPositionHandler += 2;

			/* Fill out the log and send */
			populateBasicDatalog(); // TODO change this to pull type from settings and call generic populator which populates with passed in type
			break;
		}
		case setAsyncDatalogType:
		{
			if(RXCalculatedPayloadLength != 1){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			unsigned char newDatalogType = *((unsigned char*)RXBufferCurrentPosition);
			if(newDatalogType > asyncDatalogLastType){
				errorID = noSuchAsyncDatalogType;
				break;
			}

			TablesB.SmallTablesB.loggingSettings.datalogStreamType = newDatalogType;
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
			if(RXCalculatedPayloadLength != 3){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			// Extract the type of list that we want
			unsigned char listType = *((unsigned char*)RXBufferCurrentPosition);
			RXBufferCurrentPosition++;

			// Extract the mask for the qualities that we want
			unsigned short blockDetailsMask = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			// This type must have a length field, set that up
			unsigned short * listLength = (unsigned short*)TXBufferCurrentPositionHandler;
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			TXBufferCurrentPositionHandler += 2;

			// Zero the counter before we start, woops!
			*listLength = 0;

			unsigned long locationID;
			blockDetails details;
			for(locationID = 0;locationID < 65536;locationID++){
				unsigned short locationIDDoesntExist;
				locationIDDoesntExist = lookupBlockDetails((unsigned short)locationID, &details);

				if(!locationIDDoesntExist){
					if((listType == 0x00) || // get all
							((listType == 0x01) && (details.flags & blockDetailsMask)) || // get OR of bits
							((listType == 0x02) && (!(~(details.flags) & blockDetailsMask)))){ // get AND of bits
						*((unsigned short*)TXBufferCurrentPositionHandler) = (unsigned short)locationID;
						TXBufferCurrentPositionHandler += 2;
						*listLength += 2;
					}
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

			// This type must have a length field, set that up
			*((unsigned short*)TXBufferCurrentPositionHandler) = sizeof(blockDetails);
			*TXHeaderFlags |= HEADER_HAS_LENGTH;
			TXBufferCurrentPositionHandler += 2;

			// Write straight to output buffer to save time/code
			errorID = lookupBlockDetails(locationID, (blockDetails*)TXBufferCurrentPositionHandler);

			if(errorID != 0){
				break;
			}

			// Adjust TX buffer position if successful
			TXBufferCurrentPositionHandler += sizeof(blockDetails);

			break;
		}
		case requestUnitTestOverSerial:
		{
			/*
			 * The idea here is to call this function with arguments, and data
			 * and have the result sent back for comparison with an expected
			 * result that isn't divulged to the firmware.
			 *
			 * It is intended that all testable functions be callable through
			 * this mechanism and that any number of test executions can be
			 * performed by an external suite using different parameters and
			 * data sets and matching expected results.
			 *
			 * The usual error mechanism shall be used to indicate some sort of
			 * either internal or test failure and returned errors shall be
			 * suitably descriptive to allow diagnosis and fixing of issues.
			 */

			// Must at least have test ID
			if(RXCalculatedPayloadLength < 2){
				errorID = payloadLengthTypeMismatch;
				break;
			}

			// grab unit test ID from payload
			unsigned short unitTestID = *((unsigned short*)RXBufferCurrentPosition);
			RXBufferCurrentPosition += 2;

			switch(unitTestID){
				case testEmptyTest:
				{
					// Must be only the ID
					if(RXCalculatedPayloadLength != 2){
						errorID = payloadShorterThanRequiredForTest;
						break;
					}

					*((unsigned short*)TXBufferCurrentPositionHandler) = unitTestID;
					TXBufferCurrentPositionHandler +=2;

					break;
				}
				case testTwoDTableUSLookup:
				{
					// ID + Value + Table
					if(RXCalculatedPayloadLength != (2 + 2 + sizeof(twoDTableUS))){
						errorID = payloadShorterThanRequiredForTest;
						break;
					}

					unsigned short Value = *((unsigned short*)RXBufferCurrentPosition);
					RXBufferCurrentPosition += 2;

					twoDTableUS* Table = ((twoDTableUS*)RXBufferCurrentPosition);
					RXBufferCurrentPosition += sizeof(twoDTableUS);

					unsigned short result = lookupTwoDTableUS(Table, Value);

					*((unsigned short*)TXBufferCurrentPositionHandler) = result;
					TXBufferCurrentPositionHandler +=2;

					break;
				}
				// http://issues.freeems.org/view.php?id=156
				//
				/// TODO @todo test all things listed below:
				// lookupPagedMainTableCellValue - pass this RPAGE so that it remains unchanged
				// validateMainTable
				// validateTwoDTable
				// set table values - leave this till last, currently unused by mtx, likely to be removed anyway
				// generateDerivedVars - convert to pointers, remove headers, privatise a lot of data!
				// calculateFuelAndIgnition - ditto
				// scheduling algorithm - ditto
				// safeAdd
				// safeTrim
				// safeScale
				// sleep (milliseconds)
				// sleepMicro (microseconds)
				// checksum
				// stringCopy
				// compare
				// utils that can't be checked: sampleLoopADC sampleBlockADC sampleEachADC - can check for how long each takes! adjustPWM (test only anyway), resetToNonRunningState and setupPagedRAM (would interfere with functioning of device)
				// init code may be able to be partially checked
				// most other code at this stage is ISR code, flash writing code, or could interfere with the running of the engine
				// more testable code will appear with time, such as the HAL layer, and most accessory functions.
				default:
				{
					errorID = noSuchUnitTestID;
				}

			// each case:
				// checks length, fails if wrong
				// parses data into args
				// calls function on data/args
				// assembles response OR sets error
				// breaks
			}
			break;
		}
		case startBenchTestSequence:
		{
			// see TODO on include at top and modify this line appropriately
			if(!(compare((char*)&decoderName, BENCH_TEST_NAME, sizeof(BENCH_TEST_NAME)))){
				if(RXCalculatedPayloadLength < 1){
					errorID = payloadLengthTypeMismatch;
					break;
				}

				unsigned char localTestMode = *((unsigned char*)RXBufferCurrentPosition); //1; // The only mode, for now.
				RXBufferCurrentPosition++;
				if(localTestMode > TEST_MODE_BUMP_UP_CYCLES){
					errorID = unimplementedTestMode;
					break;
				}else if((localTestMode == TEST_MODE_STOP) && (RXCalculatedPayloadLength == 1)){
					if(!(coreStatusA & BENCH_TEST_ON)){
						errorID = benchTestNotRunningToStop;
						break;
					}

					// Ensure we succeed at stopping it as quickly as possible.
					ATOMIC_START();
					KeyUserDebugs.currentEvent = testEventsPerCycle - 1; // Gets incremented then compared with testEventsPerCycle
					testNumberOfCycles = 1;                              // Gets decremented then compared with zero
					ATOMIC_END();

					// eventually save and return where it got to
					break;
				}else if((localTestMode == TEST_MODE_BUMP_UP_CYCLES) && (RXCalculatedPayloadLength == 2)){
					if(!(coreStatusA & BENCH_TEST_ON)){
						errorID = benchTestNotRunningToBump;
						break;
					}

					// Get bump value from payload
					unsigned char bumpCycles = *((unsigned char*)RXBufferCurrentPosition); //1; // The only mode, for now.
					RXBufferCurrentPosition++;

					if(bumpCycles == 0){
						errorID = bumpingByZeroMakesNoSense;
						break;
					}

					// Bump count by value from payload
					testNumberOfCycles += bumpCycles;
					// Given that this function is only for situations when A it's getting near to
					// zero and B the user is watching, not checking for overflow is reasonable.
					break;
				}else if((localTestMode == TEST_MODE_ITERATIONS) && (RXCalculatedPayloadLength == 24)){
					testMode = localTestMode;
					// do nothing to fall through, or move other code into here
				}else{
					errorID = packetSizeWrongForTestMode;
					break;
				}

				if(coreStatusA & BENCH_TEST_ON){
					errorID = benchTestAlreadyRunning;
					break;
				}

				testEventsPerCycle = *((unsigned char*)RXBufferCurrentPosition); //100;  // @ 10ms  =  1s
				RXBufferCurrentPosition++;
				if(testEventsPerCycle == 0){
					errorID = invalidEventsPerCycle;
					break;
				}

				testNumberOfCycles = *((unsigned short*)RXBufferCurrentPosition); //20;   // @ 1s    = 20s
				RXBufferCurrentPosition += 2;
				if(testNumberOfCycles == 0){
					errorID = invalidNumberOfCycles;
					break;
				}

				testTicksPerEvent = *((unsigned short*)RXBufferCurrentPosition); //12500; // @ 0.8us = 10ms
				RXBufferCurrentPosition += 2;
				if(testTicksPerEvent < decoderMaxCodeTime){
					errorID = tooShortOfAnEventPeriod;
					break;
				}

				// Pluck the arrays out of the packet for the loop below
				unsigned char* testEventNumbers = RXBufferCurrentPosition;
				RXBufferCurrentPosition += 6;
				unsigned short* testPulseWidths = (unsigned short*)RXBufferCurrentPosition;
				RXBufferCurrentPosition += 12;

				// Reset the clock for reading timeout
				Clocks.timeoutADCreadingClock = 0; // make this optional, such that we can use real inputs to determine pw and/or dwell.

				// Validate and transfer the per-channel data
				unsigned char channel;
				unsigned char configuredChannels = 6;
				for(channel = 0;channel < 6;channel++){
					if(testPulseWidths[channel] > injectorSwitchOnCodeTime){ // See next block for warning.
						// use as-is
						outputEventPinNumbers[channel] = channel;
						outputEventDelayFinalPeriod[channel] = decoderMaxCodeTime;
						outputEventPulseWidthsMath[channel] = testPulseWidths[channel];
						outputEventInputEventNumbers[channel] = testEventNumbers[channel];
					}else if(testPulseWidths[channel] > 3){
						// less than the code time, and not special, error!
						errorID = tooShortOfAPulseWidthToTest;
						// Warning, PWs close to this could be slightly longer than requested, that will change in later revisions.
						break;
					}else if(testPulseWidths[channel] == 3){
						testMode++; // Dirty hack to avoid dealing with Dave for the time being.
					}else if(testPulseWidths[channel] == 2){
						// use the dwell from the core maths and input vars.
						outputEventPinNumbers[channel] = channel;
						outputEventDelayFinalPeriod[channel] = decoderMaxCodeTime;
						outputEventPulseWidthsMath[channel] = DerivedVars->Dwell;
						outputEventInputEventNumbers[channel] = testEventNumbers[channel];
					}else if(testPulseWidths[channel] == 1){
						// use the reference pulse width from the core maths and input vars.
						outputEventPinNumbers[channel] = channel;
						outputEventDelayFinalPeriod[channel] = decoderMaxCodeTime;
						outputEventPulseWidthsMath[channel] = DerivedVars->RefPW;
						outputEventInputEventNumbers[channel] = testEventNumbers[channel];
					}else{ // is zero
						// Set this channel to zero for and therefore off, don't set this channel.
						outputEventInputEventNumbers[channel] = 0xFF; // Off.
						configuredChannels--;
					}
				}

				if(configuredChannels == 0){
					errorID = noChannelsConfiguredToTest;
					break;
				}

				if(errorID == 0){
					// Let the first iteration roll it over to zero.
					KeyUserDebugs.currentEvent = 0xFF; // Needs to be here in case of multiple runs, init is not sufficient

					if(testMode == TEST_MODE_DODGY_MISSING_TOOTH){
						if(testEventsPerCycle <= 127){
							testEventsPerCycle *= 2;
						}else{
							errorID = tooManyEventsPerCycleMissingTth;
							break;
						}

						// Store the time per event in RPM such that it can be updated dynamically
						CoreVars->RPM = testTicksPerEvent;

						// Setup the channels to use
						outputEventPinNumbers[0] = 0; // 0 is our main signal
						outputEventPinNumbers[1] = 1; // 1 is out cam sync signal

						// Un-schedule anything that got scheduled
						outputEventInputEventNumbers[2] = 0xFF;
						outputEventInputEventNumbers[3] = 0xFF;
						outputEventInputEventNumbers[4] = 0xFF;
						outputEventInputEventNumbers[5] = 0xFF;
					}else if(testMode > TEST_MODE_DODGY_MISSING_TOOTH){
						errorID = unimplementedTestMode;
						break;
					}

					// Trigger decoder interrupt to fire thus starting the loop!
					TIE = 0x01; // The ISR does the rest!

					// Nothing went wrong, now set flag.
					coreStatusA |= BENCH_TEST_ON;
				}else{
					break;
				}


/* http://issues.freeems.org/view.php?id=155
 *
 * The following block has been left in, as I still do not know why it won't work as intended:
 *
 * - It should fire all 6 output pins with a 52ms duration pulse, exactly once.
 * - The SAME code run from anywhere else (pre main loop, in main loop, in rtc, in decoder) works fine, just not here in commsCore.c
 * - The interrupts run, but the pin doesn't change state, despite the registers being configured correctly
 *
 * I've tried quite a bit:
 *
 * - Moving this code around
 * - Checking memory definitions
 * - Completely rewriting the output ISR
 * - Adding significant debug to output ISR
 * - Checking for register contents in output ISR
 * - Checking for key things modified in this file
 * - General head scratching and confused searching
 */

//				outputEventPinNumbers[0] = 0; // 1 ign
//				outputEventPinNumbers[1] = 1; // 2 ign
//				outputEventPinNumbers[2] = 2; // 3 ign/1 fuel
//				outputEventPinNumbers[3] = 3; // 4 ign/2 fuel
//				outputEventPinNumbers[4] = 4; // 3 fuel
//				outputEventPinNumbers[5] = 5; // 4 fuel
//				outputEventDelayFinalPeriod[0] = decoderMaxCodeTime;
//				outputEventDelayFinalPeriod[1] = decoderMaxCodeTime;
//				outputEventDelayFinalPeriod[2] = decoderMaxCodeTime;
//				outputEventDelayFinalPeriod[3] = decoderMaxCodeTime;
//				outputEventDelayFinalPeriod[4] = decoderMaxCodeTime;
//				outputEventDelayFinalPeriod[5] = decoderMaxCodeTime;
//				outputEventPulseWidthsMath[0] = SHORTMAX;
//				outputEventPulseWidthsMath[1] = SHORTMAX;
//				outputEventPulseWidthsMath[2] = SHORTMAX;
//				outputEventPulseWidthsMath[3] = SHORTMAX;
//				outputEventPulseWidthsMath[4] = SHORTMAX;
//				outputEventPulseWidthsMath[5] = SHORTMAX;
//
//				unsigned short edgeTimeStamp = TCNT;
//				// call sched output with args
//				LongTime timeStamp;
//				/* Install the low word */
//				timeStamp.timeShorts[1] = edgeTimeStamp;
//				/* Find out what our timer value means and put it in the high word */
//				if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
//					timeStamp.timeShorts[0] = timerExtensionClock + 1;
//				}else{
//					timeStamp.timeShorts[0] = timerExtensionClock;
//				}
//
//				schedulePortTPin(0, timeStamp);
//				schedulePortTPin(1, timeStamp);
//				schedulePortTPin(2, timeStamp);
//				schedulePortTPin(3, timeStamp);
//				schedulePortTPin(4, timeStamp);
//				schedulePortTPin(5, timeStamp);
//
//				sleep(1000);
			}else{
				errorID = thisIsNotTheBenchTestDecoder;
			}
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
		FLAG_AND_INC_FLAGGABLE(FLAG_COMMS_ERROR_MESSAGES_NOT_SENT_OFFSET);
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
 * @param errorID is the error ID to be passed out to listening devices.
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
		FLAG_AND_INC_FLAGGABLE(FLAG_COMMS_DEBUG_MESSAGES_NOT_SENT_OFFSET);
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

