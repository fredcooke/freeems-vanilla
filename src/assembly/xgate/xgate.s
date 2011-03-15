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

include "assembly/xgate/xgate.inc"
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

; -----------------------------------------------------------------------------
;	Main subroutine TODO move to RAM at RPAGE_TIME_TWO
; -----------------------------------------------------------------------------
xgateSchedule: ; SoftWare Trigger 0, call this from the main core when you want to add/update an xgate scheduled event
    ;CIF
	LDD R3, SWISRFLAGREG
	LDD R4, SWISRZEROCLEARMASK
	STW R4, R3, ZEROOFFSET ; clear interrupt flag

	;LDD R5, eventStruct ; unused at this time, currently still flashes User LED on TA

	LDB R2, R1, #0x00 ; get data at port-p, the value of R1 is passed by the vector table
	COM R2, R2 ; flip the bits
	STB R2, R1, #0x00 ; write the bits to port-p

	LDD R2, eventStruct
	LDD R4, 0x4321
	STW R4, R2, ZEROOFFSET
	; pseudo code:
	;update the proper que array member's data, lets say R4=cyl#, R5=eventTime, R6=bang on or off
	;check to see if this event is scheduled to happen before the pit fires next(nextEventTime) if so update PIT count down
	RTS
xgateScheduleEnd:

xgatePITTurnOn: ; PIT 0 ISR, called by PIT0 interrupt. Loop though our que and see if we need to bang any registers
	;CIF
	;Loop though the que to see if there are any events that need to be fired if so band the proper bits
	;Update PIT count down with the nearest nextEventTime
	RTS
xgatePITTurnOnEnd:

xgatePITTurnOff: ; PIT 1 ISR, called by PIT0 interrupt. Loop though our que and see if we need to bang any registers
	;CIF
	;Loop though the que to see if there are any events that need to be fired if so band the proper bits
	;Update PIT count down with the nearest nextEventTime
	RTS
xgatePITTurnOffEnd:

xgateErrorThread:
	;R1 will have the xgate channel number that was executed
	;TODO build some defualt code to increment an error counter

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
; our event structure[8]
eventStruct: ; The last four pins in portsBA are used for other functions and
;              must not be modified by this code or the mask below (0xAAAA).
.word 0xAAAA; "cylinderMask" the mask to apply to our bit bang port
.word 0; "scheduledTime" the time when you want an event to happen
.word 0; "stateToSet" 0 to turn somting off, 1 to turn something on
.word 0xDDDD; "isReady"  a var to test if the event is enabled

endXGATECode:
end
