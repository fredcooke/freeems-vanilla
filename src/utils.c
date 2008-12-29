/*	utils.c

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
	along with any FreeEMS software.  If not, see <http://www.gnu.org/licenses/>.

	We ask that if you make any changes to this file you send them upstream to us at admin@diyefi.org

	Thank you for choosing FreeEMS to run your engine! */

#define UTILS_C
#include "inc/freeEMS.h"
#include "inc/commsISRs.h"
#include "inc/utils.h"
#include <string.h>


/* Do table switching based on boolean parameter */
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


/* Reset all state to non running */
void resetToNonRunningState(){
	/* Reset RPM to zero */
	RPM0 = 0;
	RPM1 = 0;

	/* Ensure tacho reads lowest possible value */
	engineCyclePeriod = ticksPerCycleAtOneRPM;

	/* Clear all sync flags to lost state */
	//coreStatusA &= CLEAR_RPM_VALID;
	coreStatusA &= CLEAR_PRIMARY_SYNC;
	//coreStatusA &= CLEAR_SECONDARY_SYNC;

	// TODO more stuff needs resetting here, but only critical things.
}


/* Demonstrate basic PWM usage */
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


/* Read ADCs into the correct bank one at a time linearly */
void sampleEachADC(ADCArray *Arrays){
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


/* Read ADCs into the correct bank in a loop using pointers */
void sampleBlockADC(ADCArray *Arrays){
	memcpy(Arrays, (void*)ATD0_BASE, 16);
	memcpy(Arrays+16, (void*)ATD1_BASE, 16);
}


/* Loop repeatedly for X milli seconds. */
void sleep(unsigned short ms){
	unsigned short j, k;
	for(j=0;j<ms;j++)
		for(k=0;k<5714;k++);
}


/* Loop repeatedly for X micro seconds. */
void sleepMicro(unsigned short us){ /* Very approximate... */
	unsigned short j, k;
	for(j=0;j<us;j++)
		for(k=0;k<6;k++);
}


/* Generate a checksum for a block of data */
unsigned char checksum(unsigned char *block, unsigned short length){
	unsigned char sum = 0;
	unsigned short i;
	for(i=0;i<length;i++){
		sum += *block;
		block++;
	}
	return sum;
}

unsigned short stringCopy(unsigned char* dest, unsigned char* source){
	unsigned short length = 0;
	while(*source != 0){
		*dest = *source;
		dest++;
		source++;
		length++;
	}
	*dest = 0;
	return length;
}
