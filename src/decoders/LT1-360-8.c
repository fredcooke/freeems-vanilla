/* FreeEMS - the open source engine management system
 *
 * Copyright 2009, 2010 Sean Keys, Fred Cooke
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


/**	@file LT1-360-8.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief LT1 Optispark
 *
 * Uses PT1 to interrupt on rising and falling events of the 8x cam sensor track.
 * A certain number of 360x teeth will pass while PT1 is in a high or low state.
 * Using that uniquek count we can set the positing of your Virtual CAS clock.
 * After VCAS's position is set set PT7 to only interrupt on every 5th tooth, lowering
 * the amount of interrupts generated, to a reasonable level.
 *
 * @note Pseudo code that does not compile with zero warnings and errors MUST be commented out.
 *
 * @todo TODO This file contains SFA but Sean Keys is going to fill it up with
 * @todo TODO wonderful goodness very soon ;-)
 *
 * @author Sean Keys
 */


#define DECODER_IMPLEMENTATION_C
#define LT1_360_8_C

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"
#include "../inc/LT1-360-8.h"


const unsigned short eventAngles[] = {0, 1}; /// @todo TODO fill this out...
const unsigned char decoderName[] = "LT1-360-8.c";
static unsigned char synced = 0;
static unsigned char skippedWindowCount = 0;

unsigned short angle = 0;  /* angle of our CAS */
unsigned short accumulatorCount = 0;
unsigned char currentCyl;

//enum CYLENDAR{ONE, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT}

//windowAngle windowAngles[2] = {
//	{ONE, LOW, 23, 0, 2},
//	{EIGHT, HIGH, 43, 7}
//};

/** Setup PT Capturing so that we can decode the LT1 pattern
 *  @todo TODO Put this in the correct place
 *
 */
//void LT1PTInit(void){
	/* set pt1 to capture on rising and falling */

//}

/**
 * @brief Interrupt on rising and falling edges to count the number of teeth that have passed
 * in that window. 4 of the windows on the 8 tooth channel have a unique width. The pulse
 * accumulator will hold that count so there is no need to interrupt on the 360 tooth channel.
 *
 * @notes Primary LT1 Optispark Interrupt wired to the 8x channel.
 * @todo TODO Docs here!
 * @todo TODO config pulse accumulator to fire its own RPM interrupt to give the wheel more
 * resoloution. Such as fire on every 10x.
 */
void PrimaryRPMISR(void) {
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x01;
	accumulatorCount = 5;/* save count ASAP! TODO find the correct register to read from */
	unsigned char windowCount = 0;
	PORTJ |= 0x80; /* Echo input condition on J7 */

	/* Save all relevant available data here */
		//unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
		//unsigned short edgeTimeStamp = TC0;				/* Save the edge time stamp */
	     unsigned char PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */


	//if (!isSynced) {
	//	if (skippedWindowCount == SKIPWINDOWS) {
	if (PTITCurrentState & 0x01) { /* pin is high so we look for a low window count */
		switch (accumulatorCount) {
		case 23: /* wheel is at 0 deg TDC #1, set our virtual CAS to tooth 0 of 720 */
		{
			windowCount = accumulatorCount;
			//configPulseAccumulator((unsigned char) 1);
			break;
		}
		case 38: /* wheel is at 90 deg TDC #4, set our virtual CAS to tooth 180 of 720 */
		{
			windowCount = accumulatorCount;
			//configPulseAccumulator((unsigned char) 1);
			break;
		}
		case 33: /* wheel is at 180 deg TDC #6 set our virtual CAS to tooth 360 of 720 */
		{
			windowCount = accumulatorCount;
			//configPulseAccumulator((unsigned char) 1);
			break;
		}
		case 28: /* wheel is at 270 deg TDC #7 set our virtual CAS to tooth 540 of 720 */
		{
			windowCount = accumulatorCount;
			//configPulseAccumulator((unsigned char) 1);
			break;
		}
		case 43: /* wheel is at +45 */
		{
			windowCount = accumulatorCount;
			break;
		}
		default: {
			Counters.crankSyncLosses++; /* use crankSyncLosses variable to store number of invalid count cases while attempting to sync*/
			isSynced = 0;
			return;
			break;
		}
			PrimaryTeethDuringLow = 0; /* In any case reset counter */
		}
	} else {/* pin is low, so we look for a high count */

		switch (PrimaryTeethDuringHigh) { /* will need to additional code to off-set the initialization of PACNT since they are not
		 evenly divisible by 5 */
		case 12: /* wheel is at 147 deg, 12 deg ATDC #3 set our virtual CAS to tooth 294 of 720 */
		{
			windowCount = accumulatorCount;
			break;
		}
		case 17: /* wheel is at 242 deg, 17 deg ATDC #5 set our virtual CAS to tooth 484 of 720 */
		{
			windowCount = accumulatorCount;
			break;
		}
		case 22: /* wheel is at 337 deg, 22 deg ATDC #2 set our virtual CAS to tooth 674 of 720 */
		{
			windowCount = accumulatorCount;
			break;
		}
		case 7: /* wheel is at +45 */
				{
					windowCount = accumulatorCount;
					break;
				}
		default: {
			Counters.crankSyncLosses++; /* use crankSyncLosses variable to store number of invalid/default count cases while attempting to sync*/
			isSynced = 0;
			return;
			break;
		}

		}

	}

	//} else {
	//		skippedWindowCount++;
	//	}
	//}

	//	unsigned char risingEdge; /* in LT1s case risingEdge means signal is high */
	//	if(fixedConfigs1.coreSettingsA & PRIMARY_POLARITY){
	//		risingEdge = PTITCurrentState & 0x01;
	//	}else{
	//		risingEdge = !(PTITCurrentState & 0x01);
	//	}

	if (!isSynced) { /* If the CAS is not in sync get window counts so SecondaryRPMISR can set position */
		if (skippedWindowCount == SKIPWINDOWS) {
			skippedWindowCount = 0;
			//TODO lookup and set VCAS to correct cyl

		} else {
			skippedWindowCount++;
		}
	} else { /* The CAS is synced and we need to update our position */
		angle += 90;
	}
}


/** Secondary RPM ISR
 * @brief Update the scheduler every time 5 teeth are counted by the pulse accumulator
 * @todo TODO Docs here!
 * @todo TODO
 * @todo TODO
 */
void SecondaryRPMISR(void){
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;

	/* Save all relevant available data here */
//	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
//	unsigned short edgeTimeStamp = TC1;				/* Save the timestamp */
//	unsigned char PTITCurrentState = PTIT;			/* Save the values on port T regardless of the state of DDRT */

	/** PT0 Accumulator Mode
 * @brief Change the accumulator mode to overflow every 5 inputs on PT0 making our 360
 *  tooth wheel interrupt like a 72 tooth wheel
 *
 @todo TODO Decide if an explicit parameter is necessary if not use a existing status var instead for now it's explicit.
 */
}


/** custom init routine
 * @todo TODO Docs here!
 */
void configPulseAccumulator(){
	if (synced != 1) { /* disable accumulator counter, so an ISR is fired on all 360 teeth */
		PACTL = 0x00; /* disable PAEN and PBOIV */
		/*	(PACTL) 7   6    5     4     3    2    1    0
			 		  PAEN PAMOD PEDGE CLK1 CLK0 PAOVI PAI */
	}else{  /* enable accumulator so an ISR is only fired on every "5th tooth of the 360x track" */
		TIOS = TIOS & 0x80;  /* PT7 input */
		TCTL1 = TCTL1 & 0xC0; /* Disconnect IC/OC logic from PT7 */
		/// @todo TODO the register below does not exist and I couldn't figure out what you meant to do...
		PACN0 = 0xFB ; /* Calculation, $00 – $05 = $FB. This will overflow in 5 more edges. */
		PACTL = 0x52; /* Enable PA in count mode, rising edge and interrupt on overflow  01010010 */
	}
}
