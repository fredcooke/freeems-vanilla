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


; ****************************************************************************
;
; Thanks to Edward Karpicz for help with getting all the xgate registers sorted.
;
; ***************************************************************************


; ****************************************************************************
;
;	EQUIVILANTS/DEFs
;
; ***************************************************************************

.equ    SOMEVALUE, 0x01
.equ    AVALUE, 0x05


; ****************************************************************************
;
;	VARIABLES
; -Remember we are dealing with a 16-bit RISC CPU alignment care should be taken
; when defining 8-bit vars/constants
; ****************************************************************************

	.sect .data

;.ascii "FreeEMS > MS"
;.word 0x1010
;.skip 40 ; block of 40 bytes uninitialized

; ****************************************************************************
;
;	REGISTERS
;
; ****************************************************************************

;PORTF   	=     	0x1005	; Port F register

; ****************************************************************************
;
;	CODE
;
; ****************************************************************************

        .sect .text

; ----------------------------------------------------------------------------
;	Interrupts
; ----------------------------------------------------------------------------

;; Default interrupt handler.
def:
;        rts


; ----------------------------------------------------------------------------
;	Main subroutine
; ----------------------------------------------------------------------------
.global xgateThread0
.global xgateThread0End


xgateThread0: ; SoftWare Trigger 0
	LDL R3, #0x98
	LDH R3, #0x03
	LDL R4, #0x00
	LDH R4, #0x01
	STW R4, R3, #0x00 ; clear interrupt flag
	NOP
	NOP
	LDB R2, R1, #0x00 ; get data at port-p, the value of R1 is passed by the vector table
	COM R2, R2  ; flip the bits
	STB R2, R1, #0x00  ; write the bits to port-p
	RTS
xgateThread0End:


xgateErrorThread:
	; R1 will have the xgate channel number that was executed
	; TODO build some defualt code to flag an LED or error in software


end
