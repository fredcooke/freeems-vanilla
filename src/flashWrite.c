/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009 Sean Keys, Fred Cooke
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
 * @brief Flash manipulation functions
 *
 * This file contains all functions that operate directly or indirectly and
 * only on flash memory. They are used for erasing data from and reprogramming
 * data to the embedded flash non-volatile storage area.
 *
 * @author Sean Keys, Fred Cooke
 */


#define FLASHWRITE_C
#include "inc/freeEMS.h"
#include "inc/utils.h"
#include "inc/flashWrite.h"
#include "inc/flashBurn.h"
#include "inc/commsISRs.h"
#include "inc/commsCore.h"
#include <string.h>


/** @brief Erases a sector of flash memory
 *
 * This will erase a 1k sector in flash.  Write 0xFFFF to the starting sector
 * to be erased, 0xFFFF will be written regardless. Register the flash sector
 * erase command(0x40) and call StackBurner();. If you try to erase a protected
 * sector you will get PVIOL in the FSTAT register.
 *
 * @author Sean Keys
 *
 * @warning This will erase an entire 1k block starting at flashAddr
 *
 * @param PPage the flash page the sector is in
 * @param flashAddr the start address of the sector
 *
 * @return An error code. Zero means success, anything else is a failure.
 */
unsigned short eraseSector(unsigned char PPage, unsigned short *flashAddr){

	if (((unsigned short)flashAddr % flashSectorSize) != 0){
		return addressNotSectorAligned;
	}
	unsigned char currentPage = PPAGE;
	PPAGE = PPage;
	FSTAT = (PVIOL|ACCERR); /* clear any errors */
	(*flashAddr) = 0xFFFF;     /* Dummy data to first word of page to be erased it will write FFFF regardless with the erase command*/
	PPAGE = currentPage;
	FCMD = SECTOR_ERASE;            /* set the flash command register mode to ERASE */
	StackBurner();   //PPAGE loaded into Register B, PPAGE is set with Reg B in StackBurn asm file
	//TODO add return for accerr and pviol error bits

	// @todo TODO verify the erase, is this necessary or is it taken care of by the hardware??
	return 0;
}


/** @brief Writes a block of memory to flash
 *
 * The block size must either be under 1024, or an exact multiple of 1024.
 * Additionally, if under 1024 the destination should be within a single flash
 * sector, and if a multiple of 1024, the destination should be sector aligned.
 *
 * Because the RAM version will be in an arbitrary place we need to base
 * our positioning from the flash location. Firstly we need to ensure that
 * it doesn't cross any sector boundaries. Then we need to find the address
 * of the sector to be burned to. We also need to determine if there are
 * 2 or 3 chunks of memory to be copied to the buffer, three cases exist
 * for that :
 *
 * | From Flash |  From RAM  | From flash |
 * |    From Flash    |     From RAM      |
 * |     From RAM     |    From Flash     |
 *
 * @warning Limited to 63k per write! (obviously)
 *
 * @author Fred Cooke
 *
 * @param details contains the RAM address and page to be read from, the flash address and page to be burned to and the size to be read.
 * @param buffer is a pointer to a block of RAM at least 1024 bytes long used to allow small chunks to be burned independently.
 *
 * @return An error code. Zero means success, anything else is a failure.
 */
unsigned short writeBlock(blockDetails* details, void* buffer){
	unsigned char sectors;
	unsigned char RAMPage;
	/* FlashPage is always the one provided and is just used as is. */
	unsigned short* RAMAddress;
	unsigned short* FlashAddress;

	/* Check that the size isn't zero... */
	if(details->size == 0){
		return sizeOfBlockToBurnIsZero;
	}else if(details->size < 1024){
		unsigned short chunkFlashAddress = (unsigned short)details->FlashAddress;
		/* Get the offset from the start of the sector */
		unsigned short offset = chunkFlashAddress % flashSectorSize;

		/* Check for flash sector boundary crossing */
		if((offset + details->size) > 1024){
			return smallBlockCrossesSectorBoundary;
		}

		/* Configure the final burn variables */
		sectors = 1; /* By definition if we are in this code there is only one */
		RAMPage = RPAGE; /* The buffer is always in linear RAM region */
		RAMAddress = buffer; /* Save the buffer start address */
		FlashAddress = (unsigned short*)(chunkFlashAddress - offset); /* Get the start of the flash sector */

		/* Possibly three parts to copy to the buffer, copy only what is required */

		/* Save the PPAGE value and set the flash page */
		unsigned char oldFlashPage = PPAGE;
		PPAGE = details->FlashPage;

		/* If the chunk doesn't start at the beginning of the sector, copy the first area from flash */
		if(offset != 0){
			memcpy(buffer, FlashAddress, offset);
			buffer += offset;
		}

		/* Copy the middle section up regardless */
		unsigned char oldRAMPage = RPAGE;
		RPAGE = details->RAMPage;
		memcpy(buffer, details->RAMAddress, details->size);
		buffer += details->size;
		RPAGE = oldRAMPage;

		/* If the chunk doesn't end at the end of the sector, copy the last are from flash */
		if((offset + details->size) < 1024){
			void* chunkFlashEndAddress = details->FlashAddress + details->size;
			memcpy(buffer, chunkFlashEndAddress, (1024 - (offset + details->size)));
		}

		/* Restore the PPAGE value back */
		PPAGE = oldFlashPage;
	} else {
		/* If not smaller than 1024, check size is product of sector size */
		if((details->size % flashSectorSize) != 0){
			return sizeNotMultipleOfSectorSize;
		}

		/* Set the variables to what they would have been before */
		sectors = details->size / flashSectorSize;
		RAMPage = details->RAMPage;
		RAMAddress = (unsigned short*)details->RAMAddress;
		FlashAddress = (unsigned short*)details->FlashAddress;
	}

	unsigned char i;
	for(i=0;i<sectors;i++){
		unsigned short errorID = writeSector(RAMPage, RAMAddress, details->FlashPage, FlashAddress);
		if(errorID != 0){
			return errorID;
		}
		/* Incrementing a pointer is done by blocks the size of the type, hence 512 per sector here */
		RAMAddress += flashSectorSizeInWords;
		FlashAddress += flashSectorSizeInWords;
	}
	// @todo TODO verify the write? necessary??
	return 0;
}


/** @brief Writes a sector from memory to a sector in flash
 *
 * Uses writeWord to write a 1k block from sourceAddress(RAM) to
 * flashDestinationAddress, one word at a time. Give it the starting memory
 * address and the destination flash address. Both addresses will be
 * incremented by 1 word after a successful writeWord, until the whole 1024
 * byte sector has been written.  Before any writing occurs eraseSector is
 * called to make sure the destination is blank.
 *
 * @author Sean Keys
 *
 * @param RPage the page of RAM the RAMSourceAddress is located
 * @param RAMSourceAddress the address of the source data
 * @param PPage the page of flash where your flashDestinationAddress is located
 * @param flashDestinationAddress where your data will be written to in flash
 *
 * @return an error code. Zero means success, anything else is a failure.
 */
unsigned short writeSector(unsigned char RPage, unsigned short* RAMSourceAddress, unsigned char PPage , unsigned short* flashDestinationAddress){

	if(((unsigned short)flashDestinationAddress % flashSectorSize) != 0){
			return addressNotSectorAligned;
	}

	if(((unsigned short)flashDestinationAddress) < 0x4000){
		return addressNotFlashRegion;
	}

	/// @todo TODO Decide if we need to disable interrupts since we are manually setting Flash/RAM pages.
	eraseSector((unsigned char)PPage, (unsigned short*)flashDestinationAddress);  /* First Erase our destination block */

	unsigned short wordCount = flashSectorSizeInWords;

	/* Save pages */
	unsigned char currentRPage = RPAGE;
	unsigned char currentPPage = PPAGE;

	/* Switch pages */
	RPAGE = RPage;
	PPAGE = PPage;

	while (wordCount > 0)
	{
    	unsigned short sourceData = *RAMSourceAddress; /*Convert the RAMAddr to data(dereference) */
    	unsigned short errorID = writeWord(flashDestinationAddress, sourceData);
        if(errorID != 0){
			return errorID;
		}
		RAMSourceAddress++;
		flashDestinationAddress++;
	 	wordCount--; /* Decrement our word counter */
	}

	/* Restore pages */
	RPAGE = currentRPage;
	PPAGE = currentPPage;
	// @todo TODO verify the write? necessary??
	return 0;
}


/**	@brief Program Command
 *
 * This will write 1 word to an empty(0xFFFF) flash address. If you try to
 * write to an address containing data(not 0xFFFF),an error will register at
 * FSTAT. The embedded algorithm works like this, just write to the desired
 * flash address as you would any other writable address. Then register the
 * program command(0x20) at FCDM, the rest is handled by StackBurner();
 *
 * @author Sean Keys
 *
 * @warning Be sure your destination address is not protected or you will flag an error in FSTAT
 *
 * @param flashDestination where you want to write your data
 * @param data the data you are going to write
 *
 * @return an error code. Zero means success, anything else is a failure.
 */
unsigned short writeWord(unsigned short* flashDestination, unsigned short data){
	if((unsigned short)flashDestination & 0x0001){
		return addressNotWordAligned;
	}

	FSTAT=(ACCERR | PVIOL);
	*flashDestination = data;
	FCMD = WORD_PROGRAM;        //Load Flash Command Register With Word_Program mask
    StackBurner();

	// @todo TODO verify the write? necessary??
    return 0;
}
