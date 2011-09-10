// See README.txt in custom dir and this dir

void populateCustomDatalog(){
//	CoreVars->DRPM = Counters.; currently in use logging *ticksPerDegree as at wed nzst 3:10pm 16 march 2011 see line ~98 of derivedVarsGenerator.c and line ~277 of coreVarsGenerator.c

	// Currently unused, use as you wish:
	CoreVars->DDRPM = injectorMainPulseWidthsMath[2];
	CoreVars->DTPS = postReferenceEventDelays[2];
	CoreVars->DMAP = outputEventInputEventNumbers[2];

	// Use these any way you like:
	DerivedVars->zsp1 = Clocks.realTimeClockMain;
	DerivedVars->zsp2 = Clocks.realTimeClockMillis;
	DerivedVars->zsp3 = injectorMainPulseWidthsMath[0];
	DerivedVars->zsp4 = postReferenceEventDelays[0];
	DerivedVars->zsp5 = outputEventInputEventNumbers[0];
	DerivedVars->zsp6 = injectorMainPulseWidthsMath[1];
	DerivedVars->zsp7 = postReferenceEventDelays[1];
	DerivedVars->zsp8 = outputEventInputEventNumbers[1];
	DerivedVars->zsp9 = currentEvent;
	DerivedVars->zsp10 = syncLostWithThisID;
	DerivedVars->zsp11 = syncLostOnThisEvent;
	DerivedVars->zsp12 = syncCaughtOnThisEvent;
	DerivedVars->zsp13 = Counters.primaryTeethSeen;
	DerivedVars->zsp14 = Counters.secondaryTeethSeen;
	DerivedVars->zsp15 = Counters.decoderSyncLosses;
	DerivedVars->zsp16 = Counters.decoderSyncCorrections;
	DerivedVars->zsp17 = Counters.calculationsPerformed;
//	DerivedVars->zsp? = Counters.tooFarToSchedule; currently unused in sched code
//	DerivedVars->zsp? = Counters.dwellStretchedToSchedule; currently unused in sched code

	/* UART/serial specific counters */
//	DerivedVars->zsp? = Counters.serialEscapePairMismatches + Counters.serialStartsInsideAPacket + Counters.serialPacketsOverLength + Counters.serialNoiseErrors + Counters.serialOverrunErrors + Counters.serialFramingErrors + Counters.serialParityErrors;
	/* Generic com counters */
//	DerivedVars->zsp? = Counters.commsChecksumMismatches + Counters.commsPacketsUnderMinLength + Counters.commsDebugMessagesNotSent + Counters.commsErrorMessagesNotSent;

}
