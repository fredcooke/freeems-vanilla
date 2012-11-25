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

include "assemblyxgate/xgate.inc"
; *****************************************************************************
;
; Thanks to Edward Karpicz for help with getting all the xgate registers sorted.
;
; *****************************************************************************

; *****************************************************************************
;
;	EQUIVILANTS/DEFs (Just like c hash define)
;
; *****************************************************************************

.equ    SOMEVALUE, 0x01
.equ    AVALUE, 0x05

;	.sect .data
    .sect .ppageE1
startXGATECode:

; *****************************************************************************
;
;	REGISTERS
;
; *****************************************************************************

;PORTF   	=     	0x1005	; Port F register

; *****************************************************************************
;
;	CODE
;
; *****************************************************************************
; -----------------------------------------------------------------------------
;	Interrupts
; -----------------------------------------------------------------------------

;; Default interrupt handler.
def:
;        rts
.global startXGATECode
.global endXGATECode
.global xgateSchedule
.global xgateScheduleEnd
.global xgatePITTurnOn
.global xgatePITTurnOnEnd
.global xgatePITTurnOff
.global xgatePITTurnOffEnd
.global xgateDelayCounter
.global parameterGuard

; -----------------------------------------------------------------------------
;	Main subroutine
;	the value of R1 is passed by the vector table
; -----------------------------------------------------------------------------
xgateSchedule: ; SoftWare Trigger 0, call this from the main core when you want to add/update an xgate scheduled event
    ;clear interrupt flag
	LDD R3, SW_ISR_FLAG_REG
	LDD R2, SW_ISR_ZERO_CFLAG_MASK
	STW R2, R3, ZERO_OFFSET

	;update pervious parameter guard(previousParameterGuard = parameterGuard) FRED says we dont need to worry about this
	LDD R2, parameterGuard
	LDD R3, previousParameterGuard
	LDW R4, R2, ZERO_OFFSET
	STW R4, R3, ZERO_OFFSET

	;for Debugging write our previousParameterGuard to the port
	;LDD R4, previousParameterGuard ; load variable address
	;LDD R2, PORTB ; load register address
	;LDW R5, R4, ZERO_OFFSET
	;STB R5, R2, ZERO_OFFSET ; move data from one address to another

	;for debugging flip the led's states on portp
	LDD R5, xgatePORTPFlip
	JAL R5; jump to xgatePORTPFlip

	; pseudo code:
	;update the proper que array member's data, lets say R4=cyl#, R5=eventTime, R6=bang on or off
	;check to see if this event is scheduled to happen before the pit fires next(nextEventTime) if so update PIT count down

	;check to make sure we completed our thread before the s12 tried to overwrite our current set of parameters
	;	another way to do this would be to set a ro guard on the s12 side much like we have done here. Since it's the one doing the writing it actually make more sence
	; Fred please comment.

	;
	RTS
xgateScheduleEnd:

xgateDelayCounter: ; PIT 2 ISR, called by PIT2 interrupt. Decrement out delayCounter.
    ;CIF
	LDD R3, PITTF
	LDD R2, PIT2_CFLAG_MASK
	STB R2, R3, ZERO_OFFSET

	;decrement our Delay Extension
	LDD R4, parameterDelayExtension ; load variable address
	LDW R5, R4, ZERO_OFFSET
	SUBL R5, #0x01
	STW R5, R4, ZERO_OFFSET

	;LDD R5, xgatePORTPFlip
	;JAL R5; jump to xgatePORTPFlip

	RTS
xgateDelayCounterEnd:

xgatePITTurnOn: ; PIT 0 ISR, called by PIT0 interrupt. Loop though our que and see if we need to bang any registers
    ;CIF
	LDD R3, PITTF
	LDD R2, PIT0_CFLAG_MASK
	STB R2, R3, ZERO_OFFSET

	;Echo deal to port B
	LDD R4, parameterDelayExtension ; load variable address
	LDD R1, PORTB
	LDW R5, R4, ZERO_OFFSET
	STB R5, R1, ZERO_OFFSET ; move data from one address to another
	;SUBL R5, #0x01
	;STW R5, R4, ZERO_OFFSET

	;if parameterDelayExtension is zero turn off the interrupt
	;LDD R2, #0xFFFF
	;SUB R1, R2, R5
	;BHS noPIT0Shutdown

	/* test code */
	;LDD R2, PORTBA ; load port-p address
	;LDD R1, 0xFFFF; load data(1 byte) at port-p address to R1
	;STW R1, R2, ZERO_OFFSET ; write the byte to port-p address
	/* end test code */

	; shutdown code PITINTE &= IGNITION_DISABLE
	;LDD R3, PITTF
	;LDD R2, PIT0_CFLAG_MASK
	;STB R2, R3, ZERO_OFFSET
	;PITINTE &= IGNITION_DISABLE
	;LDD R3, PITTF
	;LDD R2, PIT0_CFLAG_MASK
	;STB R2, R3, ZERO_OFFSET

	;disable channels
	;PITCE &= IGNITION_DISABLE
	noPIT0Shutdown:
	; Turn on all the bits at PORTB
	;LDD R2, PORTB ; load port-p address
	;LDD R1, 0xFFFF; load data(1 byte) at port-p address to R1
	;STB R1, R2, ZERO_OFFSET ; write the byte to port-p address

	;Loop though the que to see if there are any events that need to be fired if so band the proper bits
	;Update PIT count down with the nearest nextEventTime
	RTS
xgatePITTurnOnEnd:

xgatePITTurnOff: ; PIT 1 ISR, called by PIT1 interrupt. Loop though our que and see if we need to bang any registers
	;CIF
	LDD R3, PITTF
	LDD R2, PIT1_CFLAG_MASK
	STB R2, R3, ZERO_OFFSET

	; Turn off all the bits at PORTB
	LDD R2, PORTB ; load port-p address
	LDD R1, 0x0000; load data(1 byte) at port-p address to R1
	;STB R1, R2, ZERO_OFFSET ; write the byte to port-p address

	;Loop though the que to see if there are any events that need to be fired if so band the proper bits
	;Update PIT count down with the nearest nextEventTime
	RTS
xgatePITTurnOffEnd:

xgateErrorThread:
	;R1 will have the xgate channel number that was executed
	;TODO build some defualt code to increment an error counter, Fred can you give me the addres of a a status var that will show in the log output !
xgatePORTPFlip:
	; Flip the bits at PORTP
	LDD R2, PORTP ; load port-p address
	LDB R1, R2, ZERO_OFFSET; load data(1 byte) at port-p address to R1
	COM R1, R1 ; flip the bits
	STB R1, R2, #0x00 ; write the byte to port-p address

	;test if we can write to a var, led will fail to flash(xgate error state) if an error occours
	LDD R2, eventStruct
	LDD R4, 0x4321
	STW R4, R2, ZERO_OFFSET
	JAL R5 ; return

; *****************************************************************************
;
;	VARIABLES
;
;	Remember we are dealing with a 16-bit RISC CPU, alignment care should be
;	taken when defining 8-bit vars/constants
;
; *****************************************************************************

;.ascii "FreeEMS > MS"
;.word 0x1010
;.skip 40 ; block of 40 bytes uninitialized
;variables:
;.word 0; nextEventTime holds the next(soonest) event time

;example to sch cyl 1 with a delay of 145ms with an injection period of 10ms you would pass the following parameters
parameterPinMask: ;mask 0x0001
	.word parameterPinMask
parameterDelayExtension: ;this var should read  (delay / 52ms)
	.word 0x00FF
parameterDelay: ;this var should read  (delay % 52ms)
	.word parameterDelay
;parameterRuntimeMultiplier: ;this var should read  (runtime / 52ms) SHOULD NEVER BE NEEDED
;	.word parameterRuntimeMultiplier
parameterOnRuntime: ;this var should read  (runtime % 52ms)
	.word parameterOnRuntime

parameterGuard: ;
	.word parameterGuard
previousParameterGuard: ;
	.word previousParameterGuard
portBAProtectionMask: ;protecting against chaning port pins which should not be touched
	.word PORTBA_PROTECTION_MASK

nextEvent: ;nextEventTime holds the next(soonest) event time
	.word 0x0000
nextEventExtension:
	.word 0x000

; our event structure[12]
eventStruct: ; The last four pins in portsBA are used for other functions and
;              must not be modified by this code or the mask below (0x0FFF).
	.word 0x00FF  ;"cylinderMask" the mask to apply to our bit bang port
	.word 0x0000  ;"scheduledTime" the time when you want an event to happen
	.word 0x0000  ;"scheduledTimeExtension"
	.word 0x0000; "isReady"  a var to test if the event is enabled
eventStructEnd:

endXGATECode:
end
