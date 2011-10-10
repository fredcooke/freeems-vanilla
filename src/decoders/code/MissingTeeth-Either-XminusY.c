/*	FreeEMS - the open source engine management system

	Copyright 2011 Fred Cooke

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


/**	@file MissingTeeth-Either-XminusY.c
 * @ingroup interruptHandlers
 * @ingroup enginePositionRPMDecoders
 *
 * @brief Missing teeth, M-N, with or without cam sync, configured externally
 *
 * This file is generic, and built as an include with multiple headers
 * containing the parameters required to make it function.
 *
 * Documentation on how this decoder was designed & written is available here:
 *
 * http://forum.diyefi.org/viewtopic.php?f=56&t=1340
 */


// Some simple checks here, more thorough checks where the arrays are generated, if not using that code, this will still complain.
#ifndef TOTAL_TEETH
#error "Total number of teeth not defined!"
#endif
#ifndef MISSING_TEETH
#error "Number of missing teeth not defined!"
#endif
#ifndef NUMBER_OF_WHEEL_EVENTS
#error "Number of wheel events not defined"
#endif


unsigned char NumberOfTwinMatchedPairs;
unsigned long lastInterEventPeriod;
match matches;


void decoderInitPreliminary(){
	TCTL4 = 0x02; /* Capture on falling edge of T0 only, capture off for 1,2,3 */
}

void perDecoderReset(){
	NumberOfTwinMatchedPairs = 0; // Var for one more opportunity to sync :-)
}


void PrimaryRPMISR(void) {
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x1;

	/* Save all relevant available data here */
	unsigned short codeStartTimeStamp = TCNT;		/* Save the current timer count */
	unsigned short edgeTimeStamp = TC0;				/* Save the edge time stamp */
	unsigned char PTITCurrentState = PTIT;			/* Save the values on port T regardless of the state of DDRT */

	/* Calculate the latency in ticks */
	ISRLatencyVars.primaryInputLatency = codeStartTimeStamp - edgeTimeStamp;

	Counters.primaryTeethSeen++;

	LongTime timeStamp;

	/* Install the low word */
	timeStamp.timeShorts[1] = edgeTimeStamp;
	/* Find out what our timer value means and put it in the high word */
	if(TFLGOF && !(edgeTimeStamp & 0x8000)){ /* see 10.3.5 paragraph 4 of 68hc11 ref manual for details */
		timeStamp.timeShorts[0] = timerExtensionClock + 1;
	}else{
		timeStamp.timeShorts[0] = timerExtensionClock;
	}
	unsigned long thisEventTimeStamp = timeStamp.timeLong;

	if(!(PTITCurrentState & 0x01)){
		// Calc this period
		unsigned long thisInterEventPeriod = thisEventTimeStamp - lastEventTimeStamp;

		unsigned long larger;
		unsigned long smaller;
		unsigned char thisLargerThanLast;
		if(thisInterEventPeriod > lastInterEventPeriod){
			larger = thisInterEventPeriod;
			smaller = lastInterEventPeriod;
			thisLargerThanLast = TRUE;
		}else{
			smaller = lastInterEventPeriod;
			larger = thisInterEventPeriod;
			thisLargerThanLast = FALSE;
		}

		// Calculate tolerance, then add and subtract it from whatever required
		unsigned long tolerance = (smaller * 1024) / 4096; // TODO un hard code this. currently 25% tolerance
		// div by 4k = fairly high minimum RPM for low teeth wheels
		// perhaps provide some options for different tolerance on different types of expected widths
		// the wide one on larger missing counts has more time to get to a higher RPM and needs a wider tolerance
		// possible options: different percent of smaller for each type, different percent and based on ideal w/b instead of smaller
		// Another option that keeps the 25% tolerance as the correct amount for any missing count is to simply take the percentage of
		// the smaller component and multiply by the number of missing teeth! This can be a flash config flag option or possibly rpm thresholded
		// it could be done on a per level basis too.
		unsigned long idealWide = smaller * (MISSING_TEETH + 1); // Do this first because it's used twice.
		// Ideal backward is dynamic because it's failing anyway...
		if(larger < (smaller + tolerance)){ // has to be first to be most efficient
			matches.pairs.thisPair = MatchedPair; // same period, roughly
		}else if((larger < (idealWide + tolerance)) && (larger > (idealWide - tolerance))){ // has to be second to be most efficient
			if(thisLargerThanLast){
				matches.pairs.thisPair = NarrowWide;
			}else{
				matches.pairs.thisPair = WideNarrow;
			}
		}else if((larger <  (((smaller * (MISSING_TEETH + 2)) / 2) + tolerance)) && (larger > (((smaller * (MISSING_TEETH + 2)) / 2) - tolerance))){ // this leads to further code running later, so should come next
			if(thisLargerThanLast){
				matches.pairs.thisPair = NarrowBackward;
			}else{
				matches.pairs.thisPair = BackwardNarrow;
			}
		}else if(larger > (idealWide + tolerance)){
			if(thisLargerThanLast){
				resetToNonRunningState(yourVRSensorHasALoosePlugFixIt);
			}else{
				resetToNonRunningState(noiseAppearedWayTooEarlyAsIfItWasAVRToothButWasnt);
			}
		}else{ // fell between the cracks, not matched, settings very tight, therefore was in two possible places on either side of (N+2)/2.
			resetToNonRunningState(yourSyncToleranceIsTighterThanAWellYouGetTheIdea);
		}


		unsigned char lastEvent = 0;
		// This all needs a little more complexity for cam only/crank only/crank + cam sync use, hard coded to crank only for now
		if(!(decoderFlags & CRANK_SYNC) && (decoderFlags & LAST_MATCH_VALID)){ // If we aren't synced and have enough data
			if(matches.pattern == MatchedPairMatchedPair){      //         | small | small | small | - All periods match, could be anywhere, unless...
				NumberOfTwinMatchedPairs++;
				// Because this method REQUIRES 4 evenly spaced teeth to work, it's only available to 5-1 or greater wheels.
				if((NUMBER_OF_WHEEL_EVENTS > 3) && (NumberOfTwinMatchedPairs == (NUMBER_OF_WHEEL_EVENTS - 3))){ // This can't find a match until it's on it's fourth execution
					// This will match repeatedly then un-sync on next cycle if tolerance is set too high
					currentEvent = NUMBER_OF_WHEEL_EVENTS - 1; // Zero indexed
					decoderFlags |= CRANK_SYNC; // Probability of this = (N + 1) / M
					// Sample RPM and ADCs here on the basis of cylinders and revolutions
					// IE, sample RPM once (total teeth (inc missing) per engine cycle / cyls) events have passed
					// And, do it from the last matching tooth, and do that on every tooth
					// So have a buffer of time stamps, which would take a LOT of RAM, hmmm, perhaps just wait.
					// Missing teeth users are clearly not fussed about fast starting anyway
					// And once sync is gained good readings can be taken without excess memory usage
				}else if((NUMBER_OF_WHEEL_EVENTS > 3) && (NumberOfTwinMatchedPairs > (NUMBER_OF_WHEEL_EVENTS - 3))){ // More matched pairs than possible with config
					resetToNonRunningState(yourSyncToleranceIsLooserThanAWellYouGetTheIdea);
				} // else fall through to wait.
			}else if(matches.pattern == MatchedPairNarrowWide){ // | small | small |      BIG      | Last tooth is first tooth after missing  - ((M-N)-3)/M = common
				currentEvent = 0;
				decoderFlags |= CRANK_SYNC;
			}else if(matches.pattern == NarrowWideWideNarrow){  // | small |      BIG      | small | Last tooth is second tooth after missing - 1/M
				currentEvent = 1;
				decoderFlags |= CRANK_SYNC;
			}else if(matches.pattern == WideNarrowMatchedPair){ // |      BIG      | small | small | Last tooth is third tooth after missing  - 1/M
				currentEvent = 2;
				decoderFlags |= CRANK_SYNC;
			}else{
				resetToNonRunningState(matches.pattern); // Where they are defined individually in the error file! Beautiful!!
			}
		}else if(decoderFlags & CRANK_SYNC){ // Make sure that we should stay in sync
			lastEvent = currentEvent;
			currentEvent++;
			if(currentEvent == numberOfRealEvents){
				currentEvent = 0;
			}

			if((currentEvent == 0) && (matches.pattern != MatchedPairNarrowWide)){ // First event after gap
				resetToNonRunningState(matches.pattern);
			}else if((currentEvent == 1) && (matches.pattern != NarrowWideWideNarrow)){ // Second event after gap
				resetToNonRunningState(matches.pattern);
			}else if((currentEvent == 2) && (matches.pattern != WideNarrowMatchedPair)){ // Third event after gap
				resetToNonRunningState(matches.pattern);
			}else if(matches.pattern != MatchedPairMatchedPair){ // All other events should be preceeded by two matched pairs
				resetToNonRunningState(matches.pattern);
			} // else carry on happily as always
		}

		if(decoderFlags & CRANK_SYNC){
			SCHEDULE_ECT_OUTPUTS();

			// sample adcs and record rpm here after scheduling
			unsigned short thisAngle = 0;
			if(currentEvent == 0){
				thisAngle = eventAngles[currentEvent] + totalEventAngleRange - eventAngles[lastEvent] ; // Optimisable... leave readable for now! :-p J/K learn from this...
			}else{
				thisAngle = eventAngles[currentEvent] - eventAngles[lastEvent];
			}

			*ticksPerDegreeRecord = (unsigned short)((ticks_per_degree_multiplier * thisInterEventPeriod) / thisAngle); // with current scale range for 60/12000rpm is largest ticks per degree = 3472, smallest = 17 with largish error
			sampleEachADC(ADCArrays);
			Counters.syncedADCreadings++;
			*mathSampleTimeStampRecord = TCNT;

			// Set flag to say calc required
			coreStatusA |= CALC_FUEL_IGN;

			// Reset the clock for reading timeout
			Clocks.timeoutADCreadingClock = 0;
		}

		if(decoderFlags & LAST_TIMESTAMP_VALID){
			if(decoderFlags & LAST_PERIOD_VALID){
				decoderFlags |= LAST_MATCH_VALID;
			}
			matches.pairs.lastPair = matches.pairs.thisPair; // Stash var for next time
			lastInterEventPeriod = thisInterEventPeriod;
//			lastTicksPerDegree = thisTicksPerDegree;
			decoderFlags |= LAST_PERIOD_VALID;
		}
		// Always
		lastEventTimeStamp = thisEventTimeStamp;
		decoderFlags |= LAST_TIMESTAMP_VALID;
	}else{
		// do checking for width variance too, perhaps optionally.
	}
}


void SecondaryRPMISR(void) { // migrate this to its own file for this decoder type such that various types of secondary sync can be handled with missing tooth main sync, thanks Abe for arguing and whinging.
	/* Clear the interrupt flag for this input compare channel */
	TFLG = 0x02;
}
