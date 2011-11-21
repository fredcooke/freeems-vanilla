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
 * @ingroup measurementsAndCalculations
 *
 * @brief Generate and average the core variables.
 *
 * This file contains the function that transfers the raw ADC values to actual
 * physical measurements and averages them.
 *
 * @author Fred Cooke
 */


#define COREVARSGENERATOR_C
#include "inc/freeEMS.h"
#include "inc/commsCore.h"
#include "inc/coreVarsGenerator.h"
#include "inc/decoderInterface.h"


/** @brief Generate the core variables and average them.
 *
 * Each raw ADC value is converted to a usable measurement via a variety of
 * methods chosen at runtime by configured settings. Once in their native units
 * and therefore closer to maximal use of the available data range they are
 * all averaged.
 *
 * @todo TODO incorporate averaging code, right now its a straight copy.
 * @todo TODO change the way configuration is done and make sure the most common options are after the first if().
 * @todo TODO add actual configuration options to the fixed config blocks for these items.
 *
 * @author Fred Cooke
 */
void generateCoreVars(){
	/*&&&&&&&& Calculate and obtain the basic variables with which we will perform the calculations &&&&&&&&*/


	/* Pre calculate things used in multiple places */

	/* Bound the TPS ADC reading and shift it to start at zero */
	unsigned short unboundedTPSADC = ADCBuffers->TPS;
	if(unboundedTPSADC > fixedConfigs2.sensorRanges.TPSMaximumADC){
		boundedTPSADC = TPSADCRange;
	}else if(unboundedTPSADC > fixedConfigs2.sensorRanges.TPSMinimumADC){ // force secondary config to be used... TODO remove this
		boundedTPSADC = unboundedTPSADC - fixedConfigs2.sensorRanges.TPSMinimumADC;
	}else{
		boundedTPSADC = 0;
	}


	/* Get BRV from ADC using transfer variables (all installations need this) */
	unsigned short localBRV;
	if(TRUE){ /* If BRV connected  */
/// @todo TODO WARNING: HACK!!! Remove ASAP!!! IE, As Soon As Preston (get's a new cpu on the TA card!)
#ifdef HOTEL
		localBRV = (((unsigned long)ADCBuffers->MAT * fixedConfigs2.sensorRanges.BRVRange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.BRVMinimum;
#else
		localBRV = (((unsigned long)ADCBuffers->BRV * fixedConfigs2.sensorRanges.BRVRange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.BRVMinimum;
#endif
	}else if(FALSE){ /* Configured to be fixed value */
		/* Get the preferred BRV figure from configuration settings */
		localBRV = fixedConfigs2.sensorPresets.presetBRV;
	}else{ /* Fail safe if config is broken */
		/* Default to normal alternator charging voltage 14.4V */
		localBRV = runningVoltage;
		/* If anyone is listening, let them know something is wrong */
		sendErrorIfClear(BRV_NOT_CONFIGURED_CODE);
	}


	unsigned short localCHT;
	/* Get CHT from ADC using the transfer table (all installations need this) */
	if(TRUE){ /* If CHT connected  */
		localCHT = CHTTransferTable[ADCBuffers->CHT];
	}else if(FALSE){ /* Configured to be read From ADC as dashpot */
		/* Transfer the ADC reading to an engine temperature in a reasonable way */
		localCHT = (ADCBuffers->CHT * 10) + freezingPoint; /* 0 ADC = 0C = 273.15K = 27315, 1023 ADC = 102.3C = 375.45K = 37545 */
	}else if(FALSE){ /* Configured to be fixed value */
		/* Get the preferred CHT figure from configuration settings */
		localCHT = fixedConfigs2.sensorPresets.presetCHT;
	}else{ /* Fail safe if config is broken */
		/* Default to normal running temperature of 85C/358K */
		localCHT = runningTemperature;
		/* If anyone is listening, let them know something is wrong */
		sendErrorIfClear(CHT_NOT_CONFIGURED_CODE);
	}


	unsigned short localIAT;
	/* Get IAT from ADC using the transfer table (all installations need this) */
	if(TRUE){ /* If IAT connected  */ /* using false here causes iat to default to room temp, useful with heatsoaked OEM sensors like the Volvo's... */
		localIAT = IATTransferTable[ADCBuffers->IAT];
	}else if(FALSE){ /* Configured to be read From ADC as dashpot */
		/* Transfer the ADC reading to an air temperature in a reasonable way */
		localIAT = (ADCBuffers->IAT * 10) + 27315; /* 0 ADC = 0C = 273.15K = 27315, 1023 ADC = 102.3C = 375.45K = 37545 */
	}else if(FALSE){ /* Configured to be fixed value */
		/* Get the preferred IAT figure from configuration settings */
		localIAT = fixedConfigs2.sensorPresets.presetIAT;
	}else{ /* Fail safe if config is broken */
		/* Default to normal air temperature of 20C/293K */
		localIAT = roomTemperature;
		/* If anyone is listening, let them know something is wrong */
		sendErrorIfClear(IAT_NOT_CONFIGURED_CODE);
	}


	unsigned short localMAT;
	/* Determine the MAT reading for future calculations */
	if(TRUE){ /* If MAT sensor is connected */
		/* Get MAT from ADC using same transfer table as IAT (too much space to waste on having two) */
		localMAT = IATTransferTable[ADCBuffers->MAT];
	}else if(FALSE){ /* Configured to be fixed value */
		/* Get the preferred MAT figure from configuration settings */
		localMAT = fixedConfigs2.sensorPresets.presetMAT;
	}else{ /* Fail safe if config is broken */
		/* If not, default to same value as IAT */
		localMAT = localIAT;
		/* If anyone is listening, let them know something is wrong */
		sendErrorIfClear(MAT_NOT_CONFIGURED_CODE);
	}


	unsigned short localMAP;
	unsigned short localIAP;
	/* Determine the MAP pressure to use for future calculations */
	if(TRUE){ /* If MAP sensor is connected */
		/* get MAP from ADC using transfer variables */
		localMAP = (((unsigned long)ADCBuffers->MAP * fixedConfigs2.sensorRanges.MAPRange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.MAPMinimum;
		if(TRUE){ /* If Intercooler boost sensor connected */
			/* Get IAP from ADC using the same transfer variables as they both need to read the same range */
			localIAP = (((unsigned long)ADCBuffers->IAP * fixedConfigs2.sensorRanges.MAPRange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.MAPMinimum;
		}
	}else if(FALSE){ /* Configured for MAP to imitate TPS signal */
		/* Get MAP from TPS via conversion */
		localMAP = (((unsigned long)boundedTPSADC * TPSMAPRange) / TPSADCRange) + fixedConfigs2.sensorRanges.TPSClosedMAP;
	}else if(FALSE){ /* Configured for dash potentiometer on ADC */
		/* Get MAP from ADC via conversion to internal kPa figure where 1023ADC = 655kPa */
		localMAP = ADCBuffers->MAP << 6;
		if(TRUE){ /* If Intercooler boost sensor enabled */
			/* Get IAP from ADC via conversion to internal kPa figure where 1023ADC = 655kPa */
			localIAP = ADCBuffers->IAP << 6;
		}
	}else if(FALSE){ /* Configured for fixed MAP from config */
		/* Get the preferred MAP figure from configuration settings */
		localMAP = fixedConfigs2.sensorPresets.presetMAP;
	}else{ /* Fail safe if config is broken */
		/* Default to zero to nulify all other calcs and effectively cut fuel */
		localMAP = 0;
		/* If anyone is listening, let them know something is wrong */
		sendErrorIfClear(MAP_NOT_CONFIGURED_CODE); // or maybe queue it?
	}


	/* Determine MAF variable if required */
	unsigned short localMAF = 0; // Default to zero as it is not required for anything except main PW calcs optionally
	if(TRUE){
		localMAF = MAFTransferTable[ADCBuffers->MAF];
	}

	unsigned short localAAP;
	/* Determine the Atmospheric pressure to use for future calculations */
	if(TRUE){ /* Configured for second sensor to read AAP */
		/* get AAP from ADC using separate vars to allow 115kPa sensor etc to be used */
		localAAP = (((unsigned long)ADCBuffers->AAP * fixedConfigs2.sensorRanges.AAPRange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.AAPMinimum;
	}else if(FALSE){ /* Configured for dash potentiometer on ADC */
		/* Get AAP from ADC via conversion to internal kPa figure where 1023ADC = 102.3kPa */
		localAAP = ADCBuffers->AAP * 10;
	}else if(FALSE){ /* Configured for fixed AAP from config */
		/* Get the preferred AAP figure from configuration settings */
		localAAP = fixedConfigs2.sensorPresets.presetAAP;
	}else{ /* Fail safe if config is broken */
		/* Default to sea level */
		localAAP = seaLevelKPa; /* 100kPa */
		/* If anyone is listening, let them know something is wrong */
		sendErrorIfClear(AAP_NOT_CONFIGURED_CODE); // or maybe queue it?
	}


	unsigned short localEGO;
	/* Get main Lambda reading */
	if(TRUE){ /* If WBO2-1 is connected */
		/* Get EGO from ADCs using transfer variables */
		localEGO = (((unsigned long)ADCBuffers->EGO * fixedConfigs2.sensorRanges.EGORange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.EGOMinimum;
	}else if(FALSE){ /* Configured for fixed EGO from config */
		/* Get the preferred EGO figure from configuration settings */
		localEGO = fixedConfigs2.sensorPresets.presetEGO;
	}else{ /* Default value if not connected incase other things are misconfigured */
		/* Default to stoichiometric */
		localEGO = stoichiometricLambda; /* EGO / 32768 = Lambda */
		/* If anyone is listening, let them know something is wrong */
		sendErrorIfClear(EGO_NOT_CONFIGURED_CODE); // or maybe queue it?
	}


	unsigned short localEGO2;
	/* Get second Lambda reading */
	if(TRUE){ /* If WBO2-2 is connected */
		/* Get EGO2 from ADCs using same transfer variables as EGO */
		localEGO2 = (((unsigned long)ADCBuffers->EGO2 * fixedConfigs2.sensorRanges.EGORange) / ADC_DIVISIONS) + fixedConfigs2.sensorRanges.EGOMinimum;
	}else if(FALSE){ /* Configured for fixed EGO2 from config */
		/* Get the preferred EGO2 figure from configuration settings */
		localEGO2 = fixedConfigs2.sensorPresets.presetEGO2;
	}else{ /* Default value if not connected incase other things are misconfigured */
		/* Default to stoichiometric */
		localEGO2 = stoichiometricLambda;
		/* If anyone is listening, let them know something is wrong */
		sendErrorIfClear(EGO2_NOT_CONFIGURED_CODE); // or maybe queue it?
	}


	unsigned short localTPS;
	/* Get TPS percentage */
	if(TRUE){ /* If TPS is connected */
		/* Get TPS from ADC no need to add TPS min as we know it is zero by definition */
		localTPS = ((unsigned long)boundedTPSADC * TPS_RANGE_MAX) / TPSADCRange;
	}else if(FALSE){ /* Configured for TPS to imitate MAP signal */
		/* Get TPS from MAP via conversion */
		/* Box MAP signal down */
		if(localTPS > fixedConfigs2.sensorRanges.TPSOpenMAP){ /* Greater than ~95kPa */
			localTPS = TPS_RANGE_MAX; /* 64000/640 = 100% */
		}else if(localTPS < fixedConfigs2.sensorRanges.TPSClosedMAP){ /* Less than ~30kPa */
			localTPS = 0;
		}else{ /* Scale MAP range to TPS range */
			localTPS = localMAP - fixedConfigs2.sensorRanges.TPSClosedMAP;
		}
		// get TPS from MAP no need to add TPS min as we know it is zero by definition
		localTPS = ((unsigned long)localTPS * TPS_RANGE_MAX) / (fixedConfigs2.sensorRanges.TPSOpenMAP - fixedConfigs2.sensorRanges.TPSClosedMAP);
	}else if(FALSE){ /* Configured for dash potentiometer on ADC */
		/* Get TPS from ADC as shown : 1023 ADC = 100%, 0 ADC = 0% */
		localTPS = ((unsigned long)ADCBuffers->TPS * TPS_RANGE_MAX) / ADC_DIVISIONS;
	}else if(FALSE){ /* Configured for fixed TPS from config */
		/* Get the preferred TPS figure from configuration settings */
		localTPS = fixedConfigs2.sensorPresets.presetTPS;
	}else{ /* Fail safe if config is broken */
		/* Default to 50% to not trigger any WOT or CT conditions */
		localTPS = halfThrottle;
		/* If anyone is listening, let them know something is wrong */
		sendErrorIfClear(TPS_NOT_CONFIGURED_CODE); // or maybe queue it?
	}


	/* Get RPM by locking out ISRs for a second and grabbing the Tooth logging data */
	//atomic start
	// copy rpm data
	//atomic end

	// Calculate RPM and delta RPM and delta delta RPM from data recorded
	if(*ticksPerDegree != 0){
		CoreVars->RPM = (unsigned short)(degreeTicksPerMinute / *ticksPerDegree);
	}else{
		CoreVars->RPM = 0;
	}

	CoreVars->DRPM = *ticksPerDegree;
//	unsigned short localDRPM = 0;
//	unsigned short localDDRPM = 0;


	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/




	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&& Average the variables as per the configuration &&&&&&&&&&&&&&&&&&&&&&&&&&*/
	/* Strictly speaking only the primary variables need to be averaged. After that, the derived ones are	*/
	/* already averaged in a way. However, there may be some advantage to some short term averaging on the	*/
	/* derived ones also, so it is something to look into later.											*/

	/// @todo TODO average the generated values here

//			newVal var word        ' the value from the ADC
//			smoothed var word    ' a nicely smoothed result
//
//			if newval > smoothed then
//			        smoothed = smoothed + (newval - smoothed)/alpha
//			else
//			        smoothed = smoothed - (smoothed - newval)/alpha
//			endif

	// from : http://www.tigoe.net/pcomp/code/category/code/arduinowiring/41

	// for now just copy them in.
	CoreVars->IAT = localIAT;
	CoreVars->CHT = localCHT;
	CoreVars->TPS = localTPS;
	CoreVars->EGO = localEGO;
	CoreVars->BRV = localBRV;
	CoreVars->MAP = localMAP;
	CoreVars->AAP = localAAP;
	CoreVars->MAT = localMAT;

	CoreVars->EGO2 = localEGO2;
	CoreVars->IAP = localIAP;
	CoreVars->MAF = localMAF;
//	CoreVars->DRPM = localDRPM;
//	CoreVars->DDRPM = localDDRPM;
//	CoreVars->DTPS = localDTPS;

	// later...
	unsigned short i;
	for(i=0;i<sizeof(CoreVar);i++){ // TODO
		/* Perform averaging on all primary variables as per the configuration array */
		// get old value(s)
		// process new and old to produce result based on config array value */
		// assign result to old value holder
	} // TODO

	/*&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&*/
}
