/* FreeEMS - the open source engine management system
 *
 * Copyright 2008, 2009 Sean Keys
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


/*See  http://www.cs.nmsu.edu/~pfeiffer/classes/273/notes/stacks-procedures.html for additional information*/


include "inc/9S12XDP512asm.s"


.global StackBurner


StackBurner:

  ldab PPAGE                   ;Store current PPAGE, so we can restore it later.

  pshb                         ;Stacks the content of accumulator B. The stack pointer is decremented by one.
  							   ;The content of B is then stored at the address the SP points to. (program page index register)

  ldx   #SpSubEnd-2            ;point at last word to move to stack
                               ;Loads the most significant byte of index register X with the content of memory location M, and loads
                               ;the least significant byte of X with the content of the next byte of memory at M + 1.


SpmoveLoop:
  ldd   2,x-                   ;read from flash
                               ;Loads the contents of memory locations M and M+1 into double accumulator D. The condition codes
                               ;are set according to the data. The information from M is loaded into accumulator A, and the
                               ;information from M+1 is loaded into accumulator B.

  pshd                         ;move onto stack
                               ;Stacks the content of double accumulator D. The stack pointer is decremented by two, then the contents
                               ;of accumulators A and B are stored at the location to which the SP points.
                               ;After PSHD executes, the SP points to the stacked value of accumulator A. This stacking order is the
                               ;opposite of the order in which A and B are stacked when an interrupt is recognized. The interrupt
                               ;stacking order is backward-compatible with the M6800, which had no 16-bit accumulator.
                               ;Push instructions are commonly used to save the contents of one or more CPU registers at the start of
                               ;a subroutine. Complementary pull instructions can be used to restore the saved CPU registers just
                               ;before returning from the subroutine.

  cpx   #SpSub-2               ;past end?
                               ;Compares the content of index register X with a 16-bit value at the address specified and sets the
                               ;condition codes accordingly. The compare is accomplished internally by a 16-bit subtract of
                               ;(M : M + 1) from index register X without modifying either index register X or (M : M + 1).

  bne   SpmoveLoop             ;loop to load subroutine on stack then break
                               ;Tests the Z status bit and branches if Z = 0.

  tfr   sp,x                   ;point to subroutine on stack
                               ;Transfers the content of a source register to a destination register specified in the instruction. The order
                               ;in which transfers between 8-bit and 16-bit registers are specified affects the high byte of the 16-bit
                               ;registers differently. Cases involving TMP2 and TMP3 are reserved for Freescale use, so some
                               ;assemblers may not permit their use. It is possible to generate these cases by using DC.B or DC.W
                               ;assembler directives.

  ldaa  #CBEIF                 ;preload mask to register command
                               ;Loads the content of memory location M into accumulator A. The condition codes are set according
                               ;to the data.

  jsr  0,x                     ;execute the subroutine on stack
                               ;Sets up conditions to return to normal program flow, then transfers control to a subroutine in expanded
                               ;memory. Uses the address of the instruction following the CALL as a return address. For code
                               ;compatibility, CALL also executes correctly in devices that do not have expanded memory capability.
                               ;Decrements the SP by two, then stores the return address on the stack. The SP points to the high-order
                               ;byte of the return address.
                               ;Decrements the SP by one, then stacks the current memory page value from the PPAGE register on the
                               ;stack.
                               ;Writes a new page value supplied by the instruction to PPAGE and transfers control to the subroutine.
                               ;In indexed-indirect modes, the subroutine address and the PPAGE value are fetched from memory in
                               ;the order M high byte, M low byte, and new PPAGE value.
                               ;Expanded-memory subroutines must be terminated by an RTC instruction, which restores the return
                               ;address and PPAGE value from the stack.

  leas SpSubEnd-SpSub,sp       ;deallocate space used by subroutine
                               ;Loads the stack pointer with an effective address specified by the program. The effective address can
                               ;be any indexed addressing mode operand address except an indirect address. Indexed addressing mode
                               ;operand addresses are formed by adding an optional constant supplied by the program or an
                               ;accumulator value to the current value in X, Y, SP, or PC. See Section 3.10, “Indexed Addressing
                               ;Modes”” for more details.
                               ;LEAS does not alter condition code bits. This allows stack modification without disturbing CCR bits
                               ;changed by recent arithmetic operations.
                               ;Operation is a bit more complex when LEAS is used with auto-increment or auto-decrement operand
                               ;specifications and the SP is the referenced index register. The index register is loaded with what would
                               ;have gone out to the address bus in the case of a load index instruction. In the case of a pre-increment
                               ;or pre-decrement, the modification is made before the index register is loaded. In the case of a
                               ;post-increment or post-decrement, modification would have taken effect after the address went out on
                               ;the address bus, so post-modification does not affect the content of the index register.
                               ;In the unusual case where LEAS involves two different index registers and post-increment or
                               ;post-decrement, both index registers are modified as demonstrated by the following example. Consider
                               ;the instruction LEAS 4,Y+. First S is loaded with the value of Y, then Y is incremented by 4.

  pulb                         ;restore register B
                               ;Accumulator B is loaded from the address indicated by the stack pointer. The SP is then incremented
                               ;by one.
                               ;Pull instructions are commonly used at the end of a subroutine, to restore the contents of CPU registers
                               ;that were pushed onto the stack before subroutine execution.

  rts                          ;to flash where StackIt was called
                               ;Terminates subroutines in expanded memory invoked by the CALL instruction. Returns execution flow
                               ;from the subroutine to the calling program. The program overlay page (PPAGE) register and the return
                               ;address are restored from the stack; program execution continues at the restored address. For code
                               ;compatibility purposes, CALL and RTC also execute correctly in devices that do not have expanded
                               ;memory capability.


.align 2   					 ;make code start word aligned


SpSub:
  ldab SpSubEnd-SpSub+2,sp     ;get PPAGE back
                              ;Loads the content of memory location M into accumulator B. The condition codes are set according to
                               ;the data.

  stab PPAGE                   ;store the PPAGE address
                               ; In other words write the PPAGE register to change the page
                               ;Stores the content of accumulator B in memory location M. The content of B is unchanged.


  tfr ccr,b                    ;get copy of ccr

  orcc #0x10                   ;disable interrupts, disable stop inst., disable XIRQ
                               ;Performs bitwise logical inclusive OR between the content of memory location M and the content of
                               ;the CCR and places the result in the CCR. Each bit of the CCR after the operation is the logical OR of
                               ;the corresponding bits of M and of CCR before the operation. To set one or more bits, set the
                               ;corresponding bit of the mask equal to 1. Bits corresponding to 0s in the mask are not changed by the
                               ;ORCC operation.

  staa FSTAT                   ;[PwO] register command
                               ;Stores the content of accumulator A in memory location M. The content of A is unchanged.

                               ; two extra nop's had to be added before writeBlock would behave
  nop                          ;[O] wait min 4~ from w cycle to r
  nop                          ;[O]
  nop                          ;[O]

                               ;This single-byte instruction increments the PC and does nothing else. No other CPU12 registers are
                               ;affected. NOP is typically used to produce a time delay, although some software disciplines discourage
                               ;CPU12 frequency-based time delays. During debug, NOP instructions are sometimes used to
                               ;temporarily replace other machine code instructions, thus disabling the replaced instruction(s).

  brclr FSTAT,CCIF,.           ;[rfPPP] wait for queued commands to finish
                               ;Performs a bitwise logical AND of memory location M and the mask supplied with the instruction,
                               ;then branches if and only if all bits with a value of 1 in the mask byte correspond to bits with a value
                               ;of 0 in the tested byte. Mask operands can be located at PC + 1, PC + 2, or PC + 4, depending on
                               ;addressing mode. The branch offset is referenced to the next address after the relative offset (rr) which
                               ;is the last byte of the instruction object code.

  tfr b,ccr                    ;restore ccr and interrupt condition



  rts                          ;back into StackIt in flash
                               ;Restores context at the end of a subroutine. Loads the program counter with a 16-bit value pulled from
                               ;the stack and increments the stack pointer by two. Program execution continues at the address restored
                               ;from the stack.
SpSubEnd:
