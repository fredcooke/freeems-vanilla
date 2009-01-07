/*	Copyright 2008 Fred Cooke

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


/**	@file derivedVarsGenerator.c
 * @ingroup measurementsAndCalculations
 *
 * @brief Generate the derived variables.
 *
 * Second level variables are derived from the core variables and generated here.
 *
 * @author Fred Cooke
 */


#define DERIVEDVARSGENERATOR_C
#include "inc/freeEMS.h"
#include "inc/commsCore.h"
#include "inc/tableLookup.h"
#include "inc/derivedVarsGenerator.h"


/** @brief Generate the derived variables.
 *
 * This function uses the core variables to lookup and calculate further second
 * order variables such as load, VE, Lamdda, Transient fuel correction, engine
 * temperature enrichment, Injector dead time, etc.
 *
 * @author Fred Cooke
 */
void generateDerivedVars(){
	/*&&&&&&&&&&&&&&&&&&&& Use basic variables to lookup and calculate derived variables &&&&&&&&&&&&&&&&&&&*/


	/* Determine load based on options */
	if(TRUE){ /* Use MAP as load */
		DerivedVars->LoadMain = CoreVars->MAP;
	}else if(FALSE){ /* Use TPS as load */
		DerivedVars->LoadMain = CoreVars->TPS;
	}else if(FALSE){ /* Use AAP corrected MAP as load */
		DerivedVars->LoadMain = ((unsigned long)CoreVars->MAP * CoreVars->AAP) / seaLevelKPa;
	}else{ /* Default to MAP, but throw error */
		DerivedVars->LoadMain = CoreVars->MAP;
		/* If anyone is listening, let them know something is wrong */
		sendErrorIfClear(LOAD_NOT_CONFIGURED_CODE); // or maybe queue it?
	}


	/* Look up VE with RPM and Load */
	DerivedVars->VEMain = lookupPagedMainTableCellValue((mainTable*)&TablesA.VETableMain, CoreVars->RPM, DerivedVars->LoadMain, currentFuelRPage);


	/* Look up target Lambda with RPM and Load */
	DerivedVars->Lambda = lookupPagedMainTableCellValue((mainTable*)&TablesD.LambdaTable, CoreVars->RPM, DerivedVars->LoadMain, currentFuelRPage);


	/* Look up injector dead time with battery voltage */
	DerivedVars->IDT = lookupTwoDTableUS((twoDTableUS*)&TablesA.SmallTablesA.injectorDeadTimeTable, CoreVars->BRV);


	/* Calculate the engine temperature enrichment */
//	unsigned short localETEPercentage = lookupTwoDTableUS(&engineTempEnrichmentTable, CoreVars.CHT);
//	DerivedVars->ETE = ((unsigned long)finalMasterTotalEndPW * localETEPercentage) / oneHundredPercentETE;
	/* TODO The above needs some careful thought put into it around different loads and correction effects. */


	/* Calculate the Transient Fuel Correction */
	if(TRUE /*WWTFC*/){ /* Do ONLY WW correction if enabled */
		// Do ww stuff, maybe pre done via RTC/RTI for consistent period?
		DerivedVars->TFCTotal = 0; /* TODO replace with real code */
	}else if(FALSE /*STDTFC*/){ /* Do any combination of standard approximate methods */
		/* Initialse the variable as a base */
		DerivedVars->TFCTotal = 0;
		/* Based on the rate of change of MAP and some history/taper time */
		if(FALSE /*MAPTFC*/){
			// Do MAP based
			DerivedVars->TFCTotal += 0;
		}

		/* Based on the rate of change of TPS and some history/taper time */
		if(FALSE /*TPSTFC*/){
			// Do TPS based
			DerivedVars->TFCTotal += 0;
		}

		/* Based on the rate of change of RPM and some history/taper time */
		if(FALSE /*RPMTFC*/){
			// Do RPM based
			DerivedVars->TFCTotal += 0;
		}
	}else{ /* Default to no correction */
		DerivedVars->TFCTotal = 0;
		/* Don't throw error as correction may not be required */
	}


	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
}
