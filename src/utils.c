/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009, 2010 Fred Cooke, Philip L Johnson
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
 * @brief Utility functions only
 *
 * General purpose utility functions that are used in various places throughout
 * the code base. Functions should only be placed here if they are not strongly
 * related to any other set of functionality.
 *
 * @author Fred Cooke
 */


#define UTILS_C
#include "inc/freeEMS.h"
#include "inc/commsISRs.h"
#include "inc/utils.h"
#include <string.h>


/** @brief Add two unsigned shorts safely
 *
 * This will either return short max or the sum of the two arguments.
 *
 * @author Fred Cooke
 *
 * @param addend1
 * @param addend2
 */
unsigned short safeAdd(unsigned short addend1, unsigned short addend2){
	if((SHORTMAX - addend1) > addend2){
		return addend1 + addend2;
	}else{
		return SHORTMAX;
	}
}


/** @brief Add signed short to an unsigned short safely
 *
 * This will either return short max, zero, or the sum of the two arguments.
 *
 * @author Fred Cooke
 *
 * @param addend1
 * @param addend2
 */
unsigned short safeTrim(unsigned short addend1, signed short addend2){

	if(addend2 < 0){
		if(addend1 > -addend2){
			return addend1 + addend2;
		}else{
			return 0;
		}
	}else if(addend2 > 0){
		if(addend2 < (SHORTMAX - addend1)){
			return addend1 + addend2;
		}else{
			return SHORTMAX;
		}
	}else{
		return addend1;
	}
}


/** @brief Scale without overflow
 *
 * Takes a base value and a scaler where 0x8000/32768 means 100%, 0 means 0%
 * and 0xFFFF/65535 means 200%, and returns the baseValue multiplied, in effect, by the
 * resulting percentage figure.
 *
 * @author Fred Cooke
 *
 * @param baseValue
 * @param scaler
 */
unsigned short safeScale(unsigned short baseValue, unsigned short dividend, unsigned short divisor){
	/* Perform the scaling */
	unsigned short scaled = ((unsigned long)baseValue * dividend) / divisor;

	/* If the trim is greater than 100% then the trimmedPW MUST be larger */
	/* If it's less than 100% it can't have overflowed. If it's not larger, it overflowed */
	if((dividend > divisor) && (baseValue > scaled)){
		return SHORTMAX;
	}else{
		return scaled;
	}
}


/** @brief Setup tune switching
 *
 * Place the correct set of tables in RAM based on a boolean parameter
 *
 * @todo TODO change parameter style to be a pointer to a register and a mask?
 *
 * @author Fred Cooke
 *
 * @param bool which set of data to enable.
 */
void setupPagedRAM(unsigned char bool){
	if(bool){
		currentFuelRPage = RPAGE_FUEL_ONE;
		currentTimeRPage = RPAGE_TIME_ONE;
		currentTuneRPage = RPAGE_TUNE_ONE;
	}else{
		currentFuelRPage = RPAGE_FUEL_TWO;
		currentTimeRPage = RPAGE_TIME_TWO;
		currentTuneRPage = RPAGE_TUNE_TWO;
	}

	RPAGE = currentTuneRPage;
}


/** @brief Demonstrate PWM
 *
 * Demonstrate basic PWM module usage by setting duty to scaled ADC inputs.
 *
 * @author Fred Cooke
 */
void adjustPWM(){
	PWMDTY0 = ATD0DR0 >> 2; // scale raw adc to a duty
	PWMDTY1 = ATD0DR1 >> 2; // scale raw adc to a duty
	PWMDTY2 = ATD0DR2 >> 2; // scale raw adc to a duty
	PWMDTY3 = ATD0DR3 >> 2; // scale raw adc to a duty
	PWMDTY4 = ATD0DR4 >> 2; // scale raw adc to a duty
	PWMDTY5 = ATD0DR5 >> 2; // scale raw adc to a duty
	PWMDTY6 = ATD0DR6 >> 2; // scale raw adc to a duty
	PWMDTY7 = ATD0DR7 >> 2; // scale raw adc to a duty (user led instead at the moment, see init)
}


/** @brief Read ADCs one at a time
 *
 * Read ADCs into the correct bank one at a time by name.
 *
 * @author Fred Cooke
 *
 * @param Arrays a pointer to an ADCBuffer struct to store ADC values in.
 */
void sampleEachADC(ADCBuffer *Arrays){
	/* ATD0 */
	Arrays->IAT = ATD0DR0;
	Arrays->CHT = ATD0DR1;
	Arrays->TPS = ATD0DR2;
	Arrays->EGO = ATD0DR3;
	Arrays->MAP = ATD0DR4;
	Arrays->AAP = ATD0DR5;
	Arrays->BRV = ATD0DR6;
	Arrays->MAT = ATD0DR7;

	/* ATD1 */
	Arrays->EGO2 = ATD1DR0;
	Arrays->IAP = ATD1DR1;
	Arrays->MAF = ATD1DR2;
	Arrays->SpareADC3 = ATD1DR3;
	Arrays->SpareADC4 = ATD1DR4;
	Arrays->SpareADC5 = ATD1DR5;
	Arrays->SpareADC6 = ATD1DR6;
	Arrays->SpareADC7 = ATD1DR7;
}


/** @brief Read ADCs in a loop
 *
 * Read ADCs into the correct bank in a loop using pointers.
 *
 * @author Fred Cooke
 *
 * @param Arrays a pointer to an ADCBuffer struct to store ADC values in.
 */
void sampleLoopADC(ADCBuffer *Arrays){
	// get the address of the ADC array
	unsigned short addr = (unsigned short)Arrays;

	//sendUS(addr);
	unsigned char loop;
	/* (value of((address of ADCBuffers struct) + (offset to start of bank(0 or half struct length)) + (offset to particular ADC (loopcounter * 4)) + (offset to correct element(0 or 2)))) =
	 * (value of((address of ARRAY block) + (loop counter * 2))) */

	for(loop=0;loop<16;loop += 2){
		/* Do the first block */
		DVUSP(addr + loop) = DVUSP(ATD0_BASE + loop);

		/* Do the second block */
		DVUSP(addr + 16 + loop) = DVUSP(ATD1_BASE + loop);
		/// @todo TODO this needs to be split into two loops one for the small block and one for the big one for the future chips.
	}
}


/* @brief Read ADCs with memcpy()
 *
 * Read ADCs into the correct bank using two fixed calls to memcpy()
 *
 * @author Fred Cooke
 *
 * @param Arrays a pointer to an ADCBuffer struct to store ADC values in.
 *
 * @warning this will corrupt your comms if you use it... don't use it
 * @bug this will corrupt your comms if you use it... don't use it
 *
void sampleBlockADC(ADCBuffer *Arrays){
	memcpy(Arrays, (void*)ATD0_BASE, 16);
	memcpy(Arrays+16, (void*)ATD1_BASE, 16);
}*/


/** @brief Sleep for X milli seconds
 *
 * Run in a nested loop repeatedly for X milli seconds.
 *
 * @author Fred Cooke
 *
 * @param ms the number of milli seconds to kill
 */
void sleep(unsigned short ms){
	unsigned short j, k;
	for(j=0;j<ms;j++){
		for(k=0;k<5714;k++){
		}
	}
}


/** @brief Sleep for X micro seconds
 *
 * Run in a nested loop repeatedly for X micro seconds.
 *
 * @note Very approximate...
 *
 * @author Fred Cooke
 *
 * @param us the number of micro seconds to kill
 */
void sleepMicro(unsigned short us){
	unsigned short j, k;
	for(j=0;j<us;j++){
		for(k=0;k<6;k++){
		}
	}
}


/** @brief Simple checksum
 *
 * Generate a simple additive checksum for a block of data.
 *
 * @author Fred Cooke
 *
 * @param block a pointer to a memory region to checksum.
 * @param length how large the memory region to checksum is.
 *
 * @return a simple additive checksum.
 */
unsigned char checksum(unsigned char *block, unsigned short length){
	unsigned char sum = 0;
	while (length-- > 0){
		sum += *block++;
	}
	return sum;
}


/** @brief Homebrew strcpy()
 *
 * strcpy() wouldn't compile for me for some reason so I wrote my own.
 *
 * @author Fred Cooke
 *
 * @param dest where to copy the null terminated string to.
 * @param source where to copy the null terminated string from.
 *
 * @return the length of the string copied, including the zero byte terminator.
 */
unsigned short stringCopy(unsigned char* dest, unsigned char* source){
	unsigned short length = 0;
	do {
		*dest++ = *source++;
		length++;
	} while(*(source-1) != 0);
	return length;
}

/**
 * @returns a one based index of the failure point
 *
 * @note this will return a positive result with bad data in the last position of a maximum sized block
 */
unsigned short compare(unsigned char* original, unsigned char* toCheck, unsigned short length){
	unsigned short i;
	for(i=0;i<length;i++){
		if(original[i] != toCheck[i]){
			return i + 1; // zero = success
		}
	}
	return 0;
}
