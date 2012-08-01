/* FreeEMS - the open source engine management system
 *
 * Copyright 2012 Fred Cooke
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
 * @brief Simple GPIO functionality
 *
 * Code for handling low frequency bit-bang switching of general pins based on
 * the value of internal variables lives in this file.
 */


#define SIMPLE_GPIO_C
#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/simpleGPIO.h"


/**
 * Perform GP outputs based on values of assigned variables. Compare upper and
 * lower thresholds with the value of the selected variable and switch on or off
 * as appropriate. Atomic blocks ensure no concurrency issues with current ECT.
 */
void performSimpleGPIO(){
	unsigned char i;
	for(i = 0;i < fixedConfigs1.simpleGPIOSettings.numberConfigured && i < NUMBER_OF_OUTPUT_CONFIGS;i++){
		unsigned short value = *(fixedConfigs1.simpleGPIOSettings.outputConfigs[i].variable);
		if(value >= fixedConfigs1.simpleGPIOSettings.outputConfigs[i].upperValue){
			if(!(fixedConfigs1.simpleGPIOSettings.outputConfigs[i].flags)){
				ATOMIC_START(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
				*(fixedConfigs1.simpleGPIOSettings.outputConfigs[i].port) |= fixedConfigs1.simpleGPIOSettings.outputConfigs[i].mask;
				ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
			}else{
				ATOMIC_START(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
				*(fixedConfigs1.simpleGPIOSettings.outputConfigs[i].port) &= (unsigned char)~(fixedConfigs1.simpleGPIOSettings.outputConfigs[i].mask);
				ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
			}
		}else if(value <= fixedConfigs1.simpleGPIOSettings.outputConfigs[i].lowerValue){
			if(fixedConfigs1.simpleGPIOSettings.outputConfigs[i].flags){
				ATOMIC_START(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
				*(fixedConfigs1.simpleGPIOSettings.outputConfigs[i].port) |= fixedConfigs1.simpleGPIOSettings.outputConfigs[i].mask;
				ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
			}else{
				ATOMIC_START(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
				*(fixedConfigs1.simpleGPIOSettings.outputConfigs[i].port) &= (unsigned char)~(fixedConfigs1.simpleGPIOSettings.outputConfigs[i].mask);
				ATOMIC_END(); /*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
			}
		} // Do nothing if in hysteresis region
	}
}
