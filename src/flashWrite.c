/*	flashWrite.c

	Copyright 2008 Sean Keys

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
	along with any FreeEMS software.  If not, see <http://www.gnu.org/licenses/>.

	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org

	Thank you for choosing FreeEMS to run your engine! */

#define FLASHWRITE_C
#include "inc/freeEMS.h"
#include "inc/flashWrite.h"
#include "inc/flashBurn.h"
#include "inc/commsISRs.h"




/**************************************************************************************************************/
/*	27.4.2.4 Sector Erase Command

	The sector erase operation will erase all addresses in a 1 Kbyte sector of Flash memory using an embedded
	algorithm.

	An example flow to execute the sector erase operation is shown in Figure 27-29. The sector erase
	command write sequence is as follows:

	1. Write to a Flash block address to start the command write sequence for the sector erase command.
	The Flash address written determines the sector to be erased while global address bits [9:0] and the
	data written are ignored. Multiple Flash sectors can be simultaneously erased by writing to the
	same relative address in each Flash block.

	2. Write the sector erase command, 0x40, to the FCMD register.

	3. Clear the CBEIF flag in the FSTAT register by writing a 1 to CBEIF to launch the sector erase
	command.

	If a Flash sector to be erased is in a protected area of the Flash block, the PVIOL flag in the FSTAT register
	will set and the sector erase command will not launch. Once the sector erase command has successfully
	launched, the CCIF flag in the FSTAT register will set after the sector erase operation has completed unless
	a new command write sequence has been buffered. */
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

	return 0;
}


				/* TODO for 0.0.19
				 *
				 * To be called from replace block of flash and ram to flash serial functions :
				 *
				 * create some sort of function to copy the flash sector up into
				 * the serial rx buffer in the high end and then over write with
				 * the small piece defined either from incoming data, or from its
				 * memory location. Then just call burn in the normal way.
				 *
				 * function could take :
				 * pointer to the buffer region (must be 1024 long or more)
				 * rpage, address, length of data to be persisted
				 * ppage, address of the sector to retrieve the rest of the data from
				 * pointer to the details object we want to use for the following call :
				 */


/* Pass in anything you like and it will error if it can't handle it. */
/* Note : Limited to 63k per write!! (obviously) */
/* TODO buffer, copy and do smaller regions by supplementing with data read from the block in question. TODO see above ^ */
unsigned short writeBlock(unsigned char RPage, unsigned short* RAMSourceAddress, unsigned char PPage, unsigned short* flashDestinationAddr, unsigned short size){

	if(((size % flashSectorSize) != 0) || (size == 0)){
		return sizeNotMultipleOfSectorSize;
	}

	unsigned char sectors = size / flashSectorSize;
	unsigned char i;
	for(i=0;i<sectors;i++){
		unsigned short errorID = writeSector(RPage, RAMSourceAddress, PPage, flashDestinationAddr);
		if(errorID != 0){
			return errorID;
		}
		/* Incrementing a pointer is done by blocks the size of the type, hence 512 per sector here */
		flashDestinationAddr += flashSectorSizeInWords;
		RAMSourceAddress += flashSectorSizeInWords;
	}
	return 0;
}

/*******************************************************************************
 * 	writeSector will use writeWord to write a 1k block from sourceAddress(RAM) to flashDestinationAddress.
 *  Give it the starting memory address and the destination flash address.
 *  Both addresses will be incremented by 1 word after a successful writeWord,
 *  until the whole 1024 byte sector has been written.  Before any writing occurs
 *  eraseSector is called to make sure the destination is blank. */
unsigned short writeSector(unsigned char RPage, unsigned short* RAMSourceAddress, unsigned char PPage , unsigned short* flashDestinationAddress){

	if (((unsigned short)flashDestinationAddress % flashSectorSize) != 0){
			return addressNotSectorAligned;
		}

	if(((unsigned short)flashDestinationAddress) < 0x4000){
		return addressNotFlashRegion;
	}

	//TODO Decide if we need to disable interrupts since we are manually setting Flash/RAM pages.
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
	return 0;
}
/*	27.4.2.3 Program Command

	The program operation will program a previously erased word in the Flash memory using an embedded
	algorithm.

	An example flow to execute the program operation is shown in Figure 27-28. The program command write
	sequence is as follows:

	1. Write to a Flash block address to start the command write sequence for the program command. The
	data written will be programmed to the address written. Multiple Flash blocks can be
	simultaneously programmed by writing to the same relative address in each Flash block.

	2. Write the program command, 0x20, to the FCMD register.

	3. Clear the CBEIF flag in the FSTAT register by writing a 1 to CBEIF to launch the program
	command.

	If a word to be programmed is in a protected area of the Flash block, the PVIOL flag in the FSTAT register
	will set and the program command will not launch. Once the program command has successfully launched,
	the CCIF flag in the FSTAT register will set after the program operation has completed unless a new
	command write sequence has been buffered. By executing a new program command write sequence on
	sequential words after the CBEIF flag in the FSTAT register has been set, up to 55% faster programming
	time per word can be effectively achieved than by waiting for the CCIF flag to set after each program
	operation.*/
unsigned short writeWord(unsigned short* flashDestination, unsigned short data){
	if ((unsigned short)flashDestination & 0x0001){
		return addressNotWordAligned;
	}

	FSTAT=(ACCERR | PVIOL);
	*flashDestination = data;
	FCMD = WORD_PROGRAM;        //Load Flash Command Register With Word_Program mask
    StackBurner();

    return 0;
}
