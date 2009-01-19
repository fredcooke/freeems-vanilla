/*	FreeEMS - the open source engine management system

	Copyright 2009 Fred Cooke

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
	along with any FreeEMS software.  If not, see http://www.gnu.org/licenses/

	We ask that if you make any changes to this file you email them upstream to
	us at admin(at)diyefi(dot)org or, even better, fork the code on github.com!

	Thank you for choosing FreeEMS to run your engine! */


/**	@file LT1-360-8.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief LT1 Optispark
 *
 * @todo TODO This file contains SFA but Sean Keys is going to fill it up with
 * @todo TODO wonderful goodness very soon ;-)
 *
 * @author Sean Keys
 */


#include "inc/freeEMS.h"
#include "inc/interrupts.h"

/** Setup PT Capturing so that we can decode the LT1 pattern
 *  @todo TODO Put this in the correct place
 *
 */
void LT1PTInit(void)
{
	/* set pt1 to capture on rising and falling */

}
/*	set overflow to 8 so that it will fire an interrupt on every 8th tooth, basically making it a 45tooth CAS */
/** Primary RPM ISR
 *
 * @todo TODO Docs here!
 */
void PrimaryRPMISR(void)
{
//	unsigned char risingEdge; /* in LT1s case risingEdge means signal is high */
	//			if(fixedConfigs1.coreSettingsA & PRIMARY_POLARITY){
		//			risingEdge = PTITCurrentState & 0x01;
			//	}else{
				//	risingEdge = !(PTITCurrentState & 0x01);
			//	}

		PORTJ |= 0x80; /* Echo input condition on J7 */
				if (!isSynced)  /* If the CAS is not in sync get window counts so SecondaryRPMISR can set position */
				{
					if (PTITCurrentState & 0x02)
					{
						Counters.PrimaryTeethDuringHigh++;  /* if low resolution signal is high count number of pulses */
					}
					else
					{
						Counters.PrimaryTeethDuringLow++;  /* if low resolution signal is low count number of pulses */
					}
				}
				else
				{

				}
}
/** Secondary RPM ISR
 * @brief Use the rising and falling edges...................
 * @todo TODO Docs here!
 */
void SecondaryRPMISR(void)
{
	PORTJ |= 0x40;  /* echo input condition */
	if (!isSynced){ /* If the CAS is not in sync get window counts and set position */
		if (PTITCUrrentState & 0x02){  /* if signal is high that means we can count the lows */
			switch Counters.PrimaryTeethDuringLow{
			case 8: Hook up scope to get real counts ;
			{
				Hook up scope to get real counts and set ;
				}
			Counters.PrimaryTeethDuringLow = 0;  Reset counter
			}
		}
		else    /* if the signal is low that means we can count the highs */
		{
			switch Counters.PrimaryTeethDuringHigh{
			case 8: Hook up scope to get real counts ;
			{
				Hook up scope to get real counts and set  ;
				changeAccumulatorMode();
				break;
				}
			default :
			{
				Counters.crankSyncLosses++; /* use crankSyncLosses variable to store number of invalid count cases while attempting to sync*/
			}
			Counters.PrimaryTeethDuringHigh = 0;  Reset counter
		}
		}
	}
	else    /* use adjusted count numbers to check sync */
	{

	}
}
		//	Counter.primaryTeethAfterSecondaryRise = 0;
		//	Counter.primaryTeethAfterSecondaryFall = 0;

		//	unsigned char risingEdge;
		//		if(fixedConfigs1.coreSettingsA & SECONDARY_POLARITY){
		//			risingEdge = PTITCurrentState & 0x02;
		//		}else{
		//			risingEdge = !(PTITCurrentState & 0x02);
		//		}
/** PT0 Accumulator Mode
 * @brief Change the accumulator mode of PT0
 * @todo TODO Decide if an explicit parameter is necessary if not use a status var instead for now it's explicit.
 */
void changeAccumulatorMode(mode char)
{
 if (mode == 0){ /* disable accumulator counter, so an ISR is fired on all 360 teeth */


 }
 else{  /* enable accumulator so an ISR is only fired on every "to be determined tooth" */

 }
}
