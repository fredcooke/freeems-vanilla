// See README.txt in custom dir and this dir

void populateCustomDatalog(){
//	CoreVars->DRPM = Counters.; currently in use as at wed nzst 3:10pm 16 march 2011
//	CoreVars->DDRPM = Counters.testUS1;
//	CoreVars->DTPS = Counters.testUS2;
//	CoreVars->DMAP = Counters.testUS3;
	CoreVars->DDRPM = injectorMainPulseWidthsMath[1];
	CoreVars->DTPS = postReferenceEventDelays[1];
	CoreVars->DMAP = outputEventInputEventNumbers[1];

	// Use these any way you like:
	DerivedVars->zsp1 = Clocks.realTimeClockMain;
	DerivedVars->zsp2 = Clocks.realTimeClockMillis;
	DerivedVars->zsp3++;
	DerivedVars->zsp4 = (decoderFlags << 8) + coreStatusA;
	DerivedVars->zsp5 = Counters.calculationsPerformed;
//	DerivedVars->zsp6 = Counters.testUS0;
	DerivedVars->zsp6 = injectorMainPulseWidthsMath[0];
	DerivedVars->zsp7 = postReferenceEventDelays[0];
	DerivedVars->zsp8 = outputEventInputEventNumbers[0];
	DerivedVars->zsp9 = currentEvent;
	DerivedVars->zsp10 = syncLostOnThisEvent;
	DerivedVars->zsp11 = syncCaughtOnThisEvent;
	DerivedVars->zsp12 = Counters.primaryTeethSeen;
	DerivedVars->zsp13 = Counters.secondaryTeethSeen;
	DerivedVars->zsp14 = *ticksPerDegree;
//	DerivedVars->zsp15 = Counters.testUS4;
//	DerivedVars->zsp16 = Counters.testUS5;
//	DerivedVars->zsp17 = Counters.testUS6;
	DerivedVars->zsp15 = Counters.camSyncLosses;
	DerivedVars->zsp16 = Counters.crankSyncLosses;
	DerivedVars->zsp17 = Counters.combustionSyncLosses;
	DerivedVars->zsp18 = Counters.camSyncCorrections;
	DerivedVars->zsp19 = syncLostWithThisID;
//	DerivedVars->zsp18 = Counters.DwellStretchedToSchedule;
//	DerivedVars->zsp19 = Counters.TooFarToSchedule;

	/* UART/serial specific counters */
//	DerivedVars->zsp? = Counters.serialEscapePairMismatches + Counters.serialStartsInsideAPacket + Counters.serialPacketsOverLength + Counters.serialNoiseErrors + Counters.serialOverrunErrors + Counters.serialFramingErrors + Counters.serialParityErrors;
	/* Generic com counters */
//	DerivedVars->zsp? = Counters.commsChecksumMismatches + Counters.commsPacketsUnderMinLength + Counters.commsDebugMessagesNotSent + Counters.commsErrorMessagesNotSent;

}
