/*	commsISRs.c

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

#define COMMSISRS_C
#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/utils.h"
#include "inc/commsCore.h"
#include "inc/commsISRs.h"


/* The C89 standard is used in the 3.3.6 GCC compiler, please	*
 * see the following URL for more info on inline functions :	*
 * http://gcc.gnu.org/onlinedocs/gcc-3.3.6/Inline.html#Inline	*/


/* Increment the pointer, decrement the length, and send it! */
extern inline void sendAndIncrement(unsigned char rawValue){
	SCI0DRL = rawValue;
	TXPacketLengthToSendSCI0--;
	TXBufferCurrentPositionSCI0++;
}


/* Store and checksum the value, then increment the pointer and length */
extern inline void receiveAndIncrement(const unsigned char value){
	*RXBufferCurrentPosition = value;
	RXCalculatedChecksum += value;
	RXBufferCurrentPosition++;
	RXPacketLengthReceived++;
}


/* Reset serial reception to one of two states */
void resetReceiveState(unsigned char sourceIDState){ // WRONG
	/* Set the receive buffer pointer to the beginning */
	RXBufferCurrentPosition = (unsigned char*)&RXBuffer;

	/* Zero the flags, buffer length and checksum */
	RXPacketLengthReceived = 0;
	RXCalculatedChecksum = 0;
	RXStateFlags = 0;

	/* Set the source ID state (clear all or all but one flag(s)) */
	RXBufferContentSourceID = sourceIDState;

	/* Which ever interface we are setting is the one we came from. By definition	*/
	/* it must be on and we want it to stay on, so just turn off all the others.	*/
	if(sourceIDState & COM_SET_SCI0_INTERFACE_ID){
		/* Turn off all others here */
		// TODO CAN0CTL1 &= CANCTL1_RX_DISABLE;
		// TODO CAN0CTL1 &= CANCTL1_RX_ISR_DISABLE;
		/* SPI ? I2C ? SCI1 ? */
	}else if(sourceIDState & COM_SET_CAN0_INTERFACE_ID){
		/* Turn off all others here */
		/* Only SCI for now */
		SCI0CR2 &= SCICR2_RX_DISABLE;
		SCI0CR2 &= SCICR2_RX_ISR_DISABLE;
		/* SPI ? I2C ? SCI1 ? */
	}else{ /* If clearing all flags then enable RX on all interfaces */
		/* Only SCI for now */
		SCI0CR2 |= SCICR2_RX_ENABLE;
		SCI0CR2 |= SCICR2_RX_ISR_ENABLE;
		// TODO CAN0CTL1 |= CANCTL1_RX_ENABLE;
		// TODO CAN0CTL1 |= CANCTL1_RX_ISR_ENABLE;
		/* SPI ? I2C ? SCI1 ? */
	}
}


/* SCI0 ISR handles all interrupts for SCI0 by reading the flag registers and acting appropriately. */
void SCI0ISR(void){
	/* Read the flags register */
	unsigned char flags = SCI0SR1;
	/* Note: Combined with reading or writing the data register this also clears the flags. */

	/* Start counting */
	unsigned short start = TCNT;

	/* If the RX interrupt is enabled check RX related flags */
	if(SCI0CR2 & SCICR2_RX_ISR_ENABLE){
		/* Grab the received byte from the register */
		unsigned char rawByte = SCI0DRL;

		PORTB |= BIT0;

		/* Record error conditions always */
		unsigned char resetOnError = 0;
		/* If there is noise on the receive line record it */
		if(flags & SCISR1_RX_NOISE){
			Counters.serialNoiseErrors++;
			resetOnError++;
		}/* If an overrun occurs record it */
		if(flags & SCISR1_RX_OVERRUN){
			Counters.serialOverrunErrors++;
			resetOnError++;
		}/* If a framing error occurs record it */
		if(flags & SCISR1_RX_FRAMING){
			Counters.serialFramingErrors++;
			resetOnError++;
		}/* If a parity error occurs record it */
		if(flags & SCISR1_RX_PARITY){
			Counters.serialParityErrors++;
			resetOnError++;
		}

		/* Drop out because of error flags	*/
		if(resetOnError){
			resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
			PORTB |= BIT1;
			return;
		}

		/* If there is data waiting to be received */
		if(flags & SCISR1_RX_REGISTER_FULL){
			PORTB |= BIT2;
			/* Look for a start bresetReceiveStateyte to indicate a new packet */
			if(rawByte == START_BYTE){
				PORTB |= BIT3;
				/* If another interface is using it (Note, clear flag, not normal) */
				if(RXBufferContentSourceID & COM_CLEAR_SCI0_INTERFACE_ID){
					/* Turn off our reception */
					SCI0CR2 &= SCICR2_RX_DISABLE;
					SCI0CR2 &= SCICR2_RX_ISR_DISABLE;
					PORTB |= BIT4;
				}else{
					PORTB |= BIT5;
					/* If we are using it */
					if(RXBufferContentSourceID & COM_SET_SCI0_INTERFACE_ID){
						/* Increment the counter */
						Counters.serialStartsInsideAPacket++;
					}
					/* Reset to us using it unless someone else was */
					resetReceiveState(COM_SET_SCI0_INTERFACE_ID);
				}
			}else if(RXPacketLengthReceived >= RX_BUFFER_SIZE){
				/* Buffer was full, record and reset */
				Counters.serialPacketsOverLength++;
				resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
				PORTB |= BIT6;
			}else if(RXBufferContentSourceID & COM_SET_SCI0_INTERFACE_ID){
				if(RXStateFlags & RX_SCI_ESCAPED_NEXT){
					PORTB |= BIT7;
					/* Clear escaped byte next flag, thanks Karsten! ((~ != !) == (! ~= ~)) == LOL */
					RXStateFlags &= RX_SCI_NOT_ESCAPED_NEXT;

					if(rawByte == ESCAPED_ESCAPE_BYTE){
						/* Store and checksum escape byte */
						receiveAndIncrement(ESCAPE_BYTE);
					}else if(rawByte == ESCAPED_START_BYTE){
						/* Store and checksum start byte */
						receiveAndIncrement(START_BYTE);
					}else if(rawByte == ESCAPED_STOP_BYTE){
						/* Store and checksum stop byte */
						receiveAndIncrement(STOP_BYTE);
					}else{
						/* Otherwise reset and record as data is bad */
						resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
						Counters.serialEscapePairMismatches++;
					}
				}else if(rawByte == ESCAPE_BYTE){
					PORTA |= BIT0;
					/* Set flag to indicate that the next byte should be un-escaped. */
					RXStateFlags |= RX_SCI_ESCAPED_NEXT;
				}else if(rawByte == STOP_BYTE){
					PORTA |= BIT1;
					/* Turn off reception */
					SCI0CR2 &= SCICR2_RX_DISABLE;
					SCI0CR2 &= SCICR2_RX_ISR_DISABLE;

					/* Bring the checksum back to where it should be */
					unsigned char RXReceivedChecksum = (unsigned char)*(RXBufferCurrentPosition - 1);
					RXCalculatedChecksum -= RXReceivedChecksum;

					/* Check that the checksum matches */
					if(RXCalculatedChecksum == RXReceivedChecksum){
						/* If it's OK set process flag */
						RXStateFlags |= RX_READY_TO_PROCESS;
						PORTA |= BIT2;
					}else{
						PORTA |= BIT3;
						/* Otherwise reset the state and record it */
						resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
						Counters.commsChecksumMismatches++;
					}
				}else{
					PORTA |= BIT4;
					/* If it isn't special process it! */
					receiveAndIncrement(rawByte);
				}
			}else{
				/* Do nothing : drop the byte */
				PORTA |= BIT5;
			}
		}
	}

	/* If the TX interrupt is enabled check the register empty flag. */
	if((SCI0CR2 & SCICR2_TX_ISR_ENABLE) && (flags & SCISR1_TX_REGISTER_EMPTY)){
		/* Get the byte to be sent from the buffer */
		unsigned char rawValue = *TXBufferCurrentPositionSCI0;

		if(TXPacketLengthToSendSCI0 > 0){
			if(TXByteEscaped == 0){
				/* If the raw value needs to be escaped */
				if(rawValue == ESCAPE_BYTE){
					SCI0DRL = ESCAPE_BYTE;
					TXByteEscaped = ESCAPED_ESCAPE_BYTE;
				}else if(rawValue == START_BYTE){
					SCI0DRL = ESCAPE_BYTE;
					TXByteEscaped = ESCAPED_START_BYTE;
				}else if(rawValue == STOP_BYTE){
					SCI0DRL = ESCAPE_BYTE;
					TXByteEscaped = ESCAPED_STOP_BYTE;
				}else{ /* Otherwise just send it */
					sendAndIncrement(rawValue);
				}
			}else{
				sendAndIncrement(TXByteEscaped);
				TXByteEscaped = 0;
			}
		}else{ /* Length is zero */
			/* Turn off transmission interrupt */
			SCI0CR2 &= SCICR2_TX_ISR_DISABLE;
			/* Send the stop byte */
			SCI0DRL = STOP_BYTE;
			/* Clear the TX in progress flag */
			TXBufferInUseFlags &= COM_CLEAR_SCI0_INTERFACE_ID;
		}
	}

	/* Record how long the operation took */
	RuntimeVars.serialISRRuntime = TCNT - start;
}
