/* FreeEMS - the open source engine management system
 *
 * Copyright 2009, 2010, 2011 Sean Keys, Fred Cooke
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
#define DECODER_MAX_CODE_TIME    100 // To be optimised (shortened)!
#define NUMBER_OF_REAL_EVENTS     16 // Start simple, Sean, start simple! :-)
#define NUMBER_OF_VIRTUAL_EVENTS  16 // Start simple, Sean, start simple! :-)

#include "../inc/freeEMS.h"
#include "../inc/interrupts.h"
#include "../inc/decoderInterface.h"
#include "../inc/LT1-360-8.h"


const unsigned char decoderName[] = "LT1-360-8";
const unsigned short eventAngles[] = {0,3,90,103,180,183,270,294,360,364,450,483,540,544,630,673}; /// @todo TODO fill this out...
const unsigned char eventMapping[] = {0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15};
const unsigned char eventValidForCrankSync[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}; // This is wrong, but will never be used on this decoder anyway.
//const unsigned char windowCounts = {24,66,4,86,33,57,4,86,43,46,4,87,13,77,3,87}; // @todo TODO find out which count is TDC #1


static unsigned char PAInitialized = 0;
static unsigned char skippedWindowCount = 0;

//static unsigned char* windowCountIndex = 0;
unsigned char isSynced = 0;
unsigned short angle = 0;  /* angle of our CAS */ /// @todo TODO Sean, don't count the angle, count the event number only, the angle can be got from the array that holds them above once you define what they are.
unsigned char accumulatorCount = 0; // use secondaryEventCount?
unsigned char windowState = 0;
unsigned char currentWindowIndex = 0; // FRED remove this var and use currentEvent

// FRED make this a simple array like the commented out one above
const windowCount windowCounts[] = { /* the first element is the window count, the second is the translated absolute position */
		{24,294},
		{66,360}, //TDC
		{4,364},
		{86,450}, //TDC
		{33,483},
		{57,540}, //TDC
		{4,544},
		{86,630}, //TDC
		{43,673},
		{46,0},   //TDC
		{4,3},
		{87,90},  //TDC
		{13,103},
		{77,180}, //TDC
		{3,183},
		{87,270}  //TDC
};

/** Setup PT Capturing so that we can decode the LT1 pattern
 *  @todo TODO Put this in the correct place
 *
 */
void LT1PAInit(void){
	/* set pt1 to capture on rising and falling */

	// set PACMX to 0 which is the default so there should be no need
	// set to capture on rising and falling this way if we have an odd number in the PA we know something went wrong
	// disable interrupt on PT1
	ICPAR = 0x02; // set the second bit in ICPAR (PAC1) to enable PT1's pulse accumulator
	// enable interrupt on overflow and set count to 0xFF-245 to enable an int on every ten teeth
	PACN1 = 0x00; // reset our count register
}

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
	if(!PAInitialized){
		LT1PAInit();
		PAInitialized = 1;
	}

	/* Save all relevant available data here */
	accumulatorCount = PACN1;/* save count before it changes */
	PACN1 = 0x0; /* reset the count */
	PORTB = accumulatorCount; /* echo PACount on port*/
	PORTJ |= 0x80; /* Echo input condition on J7 */
	//unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	//unsigned short edgeTimeStamp = TC0;				/* Save the edge time stamp */
    unsigned char PTITCurrentState = PTIT; /* Save the values on port T regardless of the state of DDRT */
    windowState = PTITCurrentState & 0x01;
    unsigned char i;

    if(currentWindowIndex > (numberOfRealEvents - 1)){ /* wrap our index on virtual overflow */
    	currentWindowIndex = 0; // FRED move this AFTER increment above loop var where other comment is
    }
    /* for data logging */
    Counters.testCounter0 = accumulatorCount;
    Counters.testCounter1 = windowState;

    /* TODO always make sure you have two good counts(there are a few windows that share counts), dont bother with one skip */
	if (!isSynced) {
		if(skippedWindowCount){ /* if we have skipped a window it is safe to look for our index */
			for(i = 0; i < numberOfRealEvents ;i++){
				if( windowCounts[i].count == accumulatorCount){
					skippedWindowCount = 0;
					currentWindowIndex = i;
					break;
				}
			}
		}else{
			skippedWindowCount++;
		}
	}else{/* make sure our count is good */
		// FRED update current event on separate line, current code is obfuscated by doing more than one thing on a line
		// FRED make this != instead and return; at the end of the if block after clearning sync
		if(windowCounts[/* bad/evil code here: */++currentWindowIndex].count == accumulatorCount){
		}else{
			isSynced = 0; // FRED don't clear like this, or increment var like below, just call lose sync function from interface...
			Counters.camSyncLosses++;
			// return here...
		}
		// FRED once sync is solid AND rpm is smooth, copy paste sched loop here.
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
