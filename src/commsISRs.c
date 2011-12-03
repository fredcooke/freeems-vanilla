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
 * @ingroup interruptHandlers
 * @ingroup communicationsFiles
 *
 * @brief Send and receive bytes serially
 *
 * This file contains the code for both send and receive of serial bytes
 * through the UART SCI0 device. It is purely interrupt driven and controlled
 * by a set of register and non-register flags that are toggled both inside
 * and outside this file. Some additional helper functions are also kept here.
 *
 * @todo TODO SCI0ISR() needs to be split into some hash defines and an include file that formats it to be the ISR for a specific channel.
 *
 * @author Fred Cooke
 */


#define COMMSISRS_C
#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/utils.h"
#include "inc/commsCore.h"
#include "inc/commsISRs.h"


/* The C89 standard is used in the 3.3.6 GCC compiler, please	*
 * see the following URL for more info on inline functions :	*
 * http://gcc.gnu.org/onlinedocs/gcc-3.3.6/Inline.html#Inline	*/


/** @brief Send And Increment
 *
 * Increment the pointer, decrement the length, and send it!
 *
 * @author Fred Cooke
 *
 * @note This is an extern inline function and as such is always inlined.
 *
 * @param rawValue is the raw byte to be sent down the serial line.
 */
extern inline void sendAndIncrement(unsigned char rawValue){
	SCI0DRL = rawValue;
	TXPacketLengthToSendSCI0--;
	TXBufferCurrentPositionSCI0++;
}


/** @brief Receive And Increment
 *
 * Store the value and add it to the checksum, then increment the pointer and length.
 *
 * @author Fred Cooke
 *
 * @note This is an extern inline function and as such is always inlined.
 *
 * @param value is the byte of data to store in the buffer and add to the checksum.
 */
extern inline void receiveAndIncrement(const unsigned char value){
	*RXBufferCurrentPosition = value;
	RXCalculatedChecksum += value; // Remove, do afterwards in non ISR time!
	RXBufferCurrentPosition++;
	RXPacketLengthReceived++; // Remove, do afterwards by subtracting the start point of the buffer!
}


/** @brief Reset Receive State
 *
 * Reset communications reception to the state provided.
 *
 * @author Fred Cooke
 *
 * @todo TODO this is in the wrong file!! Either move the header declaration or move the function!
 *
 * @param sourceIDState is the state to apply to the RX buffer state variable.
 */
void resetReceiveState(unsigned char sourceIDState){
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
		/// @todo TODO CAN0CTL1 &= CANCTL1_RX_DISABLE;
		/// @todo TODO CAN0CTL1 &= CANCTL1_RX_ISR_DISABLE;
		/* SPI ? I2C ? SCI1 ? */
	}else if(sourceIDState & COM_SET_CAN0_INTERFACE_ID){
		/* Turn off all others here */
		/* Only SCI for now */
		SCI0CR2 &= SCICR2_RX_ISR_DISABLE;
		/* SPI ? I2C ? SCI1 ? */
	}else{ /* If clearing all flags then enable RX on all interfaces */
		/* Only SCI for now */
		unsigned char devnull; // Is there a better way to do this?
		devnull = SCI0SR1; // Reading the flags combined with...
		devnull = SCI0DRL; // ...reading the data clears the flags
		SCI0CR2 |= SCICR2_RX_ISR_ENABLE;
		/// @todo TODO CAN0CTL1 |= CANCTL1_RX_ENABLE;
		/// @todo TODO CAN0CTL1 |= CANCTL1_RX_ISR_ENABLE;
		/* SPI ? I2C ? SCI1 ? */
	}
}


/** @brief Serial Communication Interface 0 ISR
 *
 * SCI0 ISR handles all interrupts for SCI0 by reading flags and acting
 * appropriately. Its functions are to send raw bytes out over the wire from a
 * buffer and to receive bytes from the wire un-escape them, checksum them and
 * store them in a buffer.
 *
 * @author Fred Cooke
 *
 * @todo TODO Move this code into an include file much like the fuel interrupts such that it can be used for multiple UART SCI devices without duplication.
 * @todo TODO Fix the init code such that this doesn't run at boot without a serail device attached. Clear buffer maybe? or flag clearing/isr enabling ordering?
 * @todo TODO Fix the dual start/stop issue by finding out why bytes get dropped at the ends. IE, read docs thoroughly.
 */
void SCI0ISR(){
	/* Read the flags register */
	unsigned char flags = SCI0SR1;
	/* Note: Combined with reading or writing the data register this also clears the flags. */

	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT4, PORTB);

	/* If the RX interrupt is enabled check RX related flags */
	if(SCI0CR2 & SCICR2_RX_ISR_ENABLE){
		/* Grab the received byte from the register */
		unsigned char rawByte = SCI0DRL;

		/* If there is noise on the receive line record it */
		if(flags & SCISR1_RX_NOISE){
			FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_NOISE_ERRORS_OFFSET);
			KeyUserDebugs.serialHardwareErrors++;
			resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
			return;
		}

		/* If an overrun occurs record it */
		if(flags & SCISR1_RX_OVERRUN){
			FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_OVERRUN_ERRORS_OFFSET);
			KeyUserDebugs.serialOverrunErrors++;
			resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
			return;
		}

		/* If a framing error occurs record it */
		if(flags & SCISR1_RX_FRAMING){
			FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_FRAMING_ERRORS_OFFSET);
			KeyUserDebugs.serialHardwareErrors++;
			resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
			return;
		}

		/* If a parity error occurs record it */
		if(flags & SCISR1_RX_PARITY){
			FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_PARITY_ERRORS_OFFSET);
			KeyUserDebugs.serialHardwareErrors++;
			resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
			return;
		}

		/* If there is data waiting to be received */
		if(flags & SCISR1_RX_REGISTER_FULL){
			/* Look for a start bresetReceiveStateyte to indicate a new packet */
			if(rawByte == START_BYTE){
				/* If another interface is using it (Note, clear flag, not normal) */
				if(RXBufferContentSourceID & COM_CLEAR_SCI0_INTERFACE_ID){
					/* Turn off our reception */
					SCI0CR2 &= SCICR2_RX_ISR_DISABLE;
				}else{
					/* If we are using it */
					if(RXBufferContentSourceID & COM_SET_SCI0_INTERFACE_ID){
						/* Increment the counter */
						FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_STARTS_INSIDE_A_PACKET_OFFSET);
						KeyUserDebugs.serialAndCommsCodeErrors++;
					}
					/* Reset to us using it unless someone else was */
					resetReceiveState(COM_SET_SCI0_INTERFACE_ID);
				}
			}else if(RXPacketLengthReceived >= RX_BUFFER_SIZE){
				/* Buffer was full, record and reset */
				FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_PACKETS_OVER_LENGTH_OFFSET);
				KeyUserDebugs.serialAndCommsCodeErrors++;
				resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
			}else if(RXBufferContentSourceID & COM_SET_SCI0_INTERFACE_ID){
				if(RXStateFlags & RX_SCI_ESCAPED_NEXT){
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
						FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_ESCAPE_PAIR_MISMATCHES_OFFSET);
						KeyUserDebugs.serialAndCommsCodeErrors++;
					}
				}else if(rawByte == ESCAPE_BYTE){
					/* Set flag to indicate that the next byte should be un-escaped. */
					RXStateFlags |= RX_SCI_ESCAPED_NEXT;
				}else if(rawByte == STOP_BYTE){
					/* Turn off reception */
					SCI0CR2 &= SCICR2_RX_ISR_DISABLE;

					/* Bring the checksum back to where it should be */
					unsigned char RXReceivedChecksum = (unsigned char)*(RXBufferCurrentPosition - 1);
					RXCalculatedChecksum -= RXReceivedChecksum;

					/* Check that the checksum matches and that the packet is big enough for header,ID,checksum */
					if(RXPacketLengthReceived < 4){
						resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
						FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_PACKETS_UNDER_LENGTH_OFFSET);
						KeyUserDebugs.serialAndCommsCodeErrors++;
					}else if(RXCalculatedChecksum == RXReceivedChecksum){
						/* If it's OK set process flag */
						RXStateFlags |= RX_READY_TO_PROCESS;
					}else{
						/* Otherwise reset the state and record it */
						resetReceiveState(CLEAR_ALL_SOURCE_ID_FLAGS);
						FLAG_AND_INC_FLAGGABLE(FLAG_SERIAL_CHECKSUM_MISMATCHES_OFFSET);
						KeyUserDebugs.serialAndCommsCodeErrors++;
					}
				}else{
					/* If it isn't special process it! */
					receiveAndIncrement(rawByte);
				}
			} /* ELSE: Do nothing : drop the byte */
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
			if(coreStatusA & BIT7){
				/* Turn off transmission interrupt */
				SCI0CR2 &= (SCICR2_TX_ISR_DISABLE & SCICR2_TX_DISABLE);
				/* Clear the TX in progress flag */
				TXBufferInUseFlags &= COM_CLEAR_SCI0_INTERFACE_ID;
				coreStatusA &= NBIT7;
			}else{
				coreStatusA |= BIT7;
				/* Send the stop byte */
				SCI0DRL = STOP_BYTE;
			}
		}
	}

	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT4, PORTB);
}
