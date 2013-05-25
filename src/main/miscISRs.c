/* FreeEMS - the open source engine management system
 *
 * Copyright 2008-2013 Fred Cooke
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
 *
 * @brief Miscellaneous Interrupt Handlers
 *
 * Various non-descript interrupt handlers that don't really fit anywhere else
 * and aren't big enough to live on their own just yet.
 */


#include "inc/freeEMS.h"
#include "inc/interrupts.h"
#include "inc/decoderInterface.h"
#include "inc/init.h"


/** @brief Unimplemented Interrupt Handler
 *
 * Unimplemented interrupt service routine for calls  we weren't expecting.
 * Currently this simply counts bad calls like any other event type.
 *
 * @todo TODO Split this into its own file, create one for each, and clear flags for all, and increment shared counter as is.
 * @todo TODO Currently not a problem, but as indirectly pointed out by johntramp, if no flag clearing is being done, then this code will run continuously, which is not a good idea...
 */
void UISR(void){
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	FLAG_AND_INC_FLAGGABLE(FLAG_CALLS_TO_UISRS_OFFSET);
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}

/** @brief Spurious Interrupt Handler
 *
 * This is fired when the correct vector for an interrupt can not be determined.
 *
 * Theoretically this should not happen, and probably indicates a code fault.
 */
void SpuriousISR(void){
	// No flag to clear
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	FLAG_AND_INC_FLAGGABLE2(FLAG_SPURIOUS_INTERRUPTS_OFFSET);
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}

/** @brief Unimplemented Opcode Handler
 *
 * Unimplemented opcode trap. This should never run and probably indicates an
 * attempt to execute data instead of code, but could be an assembler issue.
 */
void UnimplOpcodeISR(void){
	// No flag to clear
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	FLAG_AND_INC_FLAGGABLE2(FLAG_UNIMPLEMENTED_OPCODES_OFFSET);
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}

/** @brief CPU RAM Access Violation Handler
 *
 * If the CPU tries to access protected XGATE RAM, this is fired.
 */
void RAMViolationISR(void){
	// Clear the flag
	RAMWPC = AVIF;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	FLAG_AND_INC_FLAGGABLE2(FLAG_RAM_ACCESS_VIOLATIONS_OFFSET);
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}

/** @brief XGATE Software Error Handler
 *
 * If buggy code is being executed on the XGATE, this may fire alerting us to it.
 */
void XGATEErrorISR(void){
	// Clear the flag
	XGMCTL = (XGSWEIFM | XGSWEIF);
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	FLAG_AND_INC_FLAGGABLE2(FLAG_XGATE_SOFTWARE_ERRORS_OFFSET);
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}

/** @brief PLL Lock Lost/Gained
 *
 * When the Phase Locked Loop is lost or gained, this is called.
 */
void PLLLockISR(void){
	// Clear the flag
	CRGFLG = PLLLOCKIF;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	// Check the state of PLL lock
	if(CRGFLG & PLLLOCK){ // Recovered
		// Re-enable outputs with return of accurate clock
		((ignitionCutFlags *)&KeyUserDebugs.ignitionCuts)->IgnLostPLL = 0;
		((injectionCutFlags *)&KeyUserDebugs.injectionCuts)->InjLostPLL = 0;
	}else{ // Lock lost
		// Record the loss of PLL lock
		FLAG_AND_INC_FLAGGABLE(FLAG_PHASE_LOCKED_LOOP_LOCK_LOST_OFFSET);
		// Force sync loss with special code to prevent engine damage from incorrect timings
		// This is required otherwise we never see the self clock code, as it's immediately over-written by our code
		if(KeyUserDebugs.syncLostWithThisID == SELF_CLOCK_MODE_PRECAUTIONARY){
			// Don't over-write the self clock sync loss ID
			resetToNonRunningState(SELF_CLOCK_MODE_PRECAUTIONARY);
		}else{
			// This means ONLY the PLL lock was lost (at this time)
			resetToNonRunningState(PLL_LOCK_LOST_PRECAUTIONARY);
		}
		// Disable outputs as a precaution with dodgy clock
		((ignitionCutFlags *)&KeyUserDebugs.ignitionCuts)->IgnLostPLL = 1;
		((injectionCutFlags *)&KeyUserDebugs.injectionCuts)->InjLostPLL = 1;
	}
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}

/** @brief Self Clock Mode Entered/Exited
 *
 * When the main clock quality drops too low to be used, self clock is entered.
 *
 * See section 2.6.3 of the device manual for more information.
 */
void SelfClockISR(void){
	// Clear the flag
	CRGFLG = SCMIF;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	// Check the state of self clock mode flag
	if(CRGFLG & SCM){ // Self Clock Mode
		// Record the loss of main clock
		FLAG_AND_INC_FLAGGABLE(FLAG_SELF_CLOCK_MODE_ENTERED_OFFSET);
		// Force sync loss with special code to prevent engine damage from incorrect timings
		resetToNonRunningState(SELF_CLOCK_MODE_PRECAUTIONARY);
		// Disable outputs as a precaution with dodgy clock
		((ignitionCutFlags *)&KeyUserDebugs.ignitionCuts)->IgnSelfClock = 1;
		((injectionCutFlags *)&KeyUserDebugs.injectionCuts)->InjSelfClock = 1;
	}else{ // Recovered
		// Disabled when falling back to Self Clock Mode, re-enable here
		enablePLL(); // Note, busy wait with no limit, danger to the manifold!

		// Re-enable outputs with return of accurate clock
		((ignitionCutFlags *)&KeyUserDebugs.ignitionCuts)->IgnSelfClock = 0;
		((injectionCutFlags *)&KeyUserDebugs.injectionCuts)->InjSelfClock = 0;
	}
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}

/** @brief Port P pins ISR
 *
 * Interrupt handler for edge events on port P pins. Not currently used.
 */
void PortPISR(void){
	/* Clear all port P flags (we only want one at a time) */
	PIFP = ONES;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	FLAG_AND_INC_FLAGGABLE(FLAG_CALLS_TO_UISRS_OFFSET);
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}


/** @brief Port J pins ISR
 *
 * Interrupt handler for edge events on port J pins. Not currently used.
 */
void PortJISR(void){
	/* Clear all port H flags (we only want one at a time) */
	PIFJ = ONES;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	FLAG_AND_INC_FLAGGABLE(FLAG_CALLS_TO_UISRS_OFFSET);
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}


/** @brief Port H pins ISR
 *
 * Interrupt handler for edge events on port H pins. Not currently used.
 */
void PortHISR(void)
{
//	// read the interrupt flags to a variable
//	unsigned char portHFlags = PIFH;
//	portHFlags &= 0xF8; // mask out the other bits
//
//	/* Clear all port H flags (we only want one at a time) */
	PIFH = ONES;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);

	// Bump this for the time being as this should not be occurring.
	FLAG_AND_INC_FLAGGABLE(FLAG_CALLS_TO_UISRS_OFFSET);

//	// Toggle a LED so we can see if the code ran
//	PO-don't use this-RTA ^= 0x80; // Fuel pump pin (A7)
//
	// debounce
	if(portHDebounce == 0){
		portHDebounce = 2;
	}else{
		return;
	}
//
//	// find out which pin triggered it, clear the flag, perform the action.
//	switch(portHFlags)
//	{
//	case 0x80 :	// Increment cylinder count and set port count appropriately.
//		switch (configs.combustionEventsPerEngineCycle) {
//			case 1 :
//				configs.combustionEventsPerEngineCycle = 2;
//				configs.ports = 2;
//				break;
//			case 2 :
//				configs.combustionEventsPerEngineCycle = 3;
//				configs.ports = 3;
//				break;
//			case 3 :
//				configs.combustionEventsPerEngineCycle = 4;
//				configs.ports = 4;
//				break;
//			case 4 :
//				configs.combustionEventsPerEngineCycle = 5;
//				configs.ports = 5;
//				break;
//			case 5 :
//				configs.combustionEventsPerEngineCycle = 6;
//				configs.ports = 6;
//				break;
//			case 6 :
//				configs.combustionEventsPerEngineCycle = 8;
//				configs.ports = 4;
//				break;
//			case 8 :
//				configs.combustionEventsPerEngineCycle = 10;
//				configs.ports = 5;
//				break;
//			case 10 :
//				configs.combustionEventsPerEngineCycle = 12;
//				configs.ports = 6;
//				break;
//			case 12 :
//				configs.combustionEventsPerEngineCycle = 1;
//				configs.ports = 1;
//				break;
//		}
//		break;
//	case 0x40 : // Injection output enable/disable
//		break;
//	case 0x20 : // Ignition output enable/disable
//		break;
//	case 0x10 : // Staged injection enable/disable
//		break;
//	case 0x08 : // Staged injection start sched/fixed
//		break;
//	case 0x04 : // Staged injection end sched/fixed
//		break;
//	case 0x02 : // free input
//		break;
//	case 0x01 : // free input
//		break;
//	default : // Two or more pressed, nothing to do except wait for another button press
//		break;
//	}
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}


/** @brief IRQ/PE1 pin ISR
 *
 * Interrupt handler for edge events on the IRQ/PE1 pin. Not currently used.
 */
void IRQISR(void){
	/* Clear the flag */
	// ?? TODO
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	FLAG_AND_INC_FLAGGABLE(FLAG_CALLS_TO_UISRS_OFFSET);
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}


/** @brief XIRQ/PE0 pin ISR
 *
 * Interrupt handler for edge events on the XIRQ/PE0 pin. Not currently used.
 */
void XIRQISR(void){
	/* Clear the flag */
	// ?? TODO
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT7, PORTB);
	FLAG_AND_INC_FLAGGABLE(FLAG_CALLS_TO_UISRS_OFFSET);
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT7, PORTB);
}


/** @brief Low Voltage Counter
 *
 * Count how often our voltage drops lower than it should without resetting.
 */
void LowVoltageISR(void){
	/* Clear the flag */
	VREGCTRL |= 0x01;
	DEBUG_TURN_PIN_ON(DECODER_BENCHMARKS, BIT6, PORTB);
	FLAG_AND_INC_FLAGGABLE(FLAG_LOW_VOLTAGE_CONDITION_OFFSET);
	DEBUG_TURN_PIN_OFF(DECODER_BENCHMARKS, NBIT6, PORTB);
}
