// See README.txt in custom dir and this dir

void populateCustomDatalog(){
//	CoreVars->DRPM = Counters.; currently in use logging *ticksPerDegree as at wed nzst 3:10pm 16 march 2011 see line ~98 of derivedVarsGenerator.c and line ~277 of coreVarsGenerator.c

	// Comms issues:
	CoreVars->DDRPM = Counters.commsChecksumMismatches + Counters.serialEscapePairMismatches + Counters.serialStartsInsideAPacket + Counters.commsPacketsUnderMinLength + Counters.serialPacketsOverLength; // Something was wrong with the contents or size of a packet
	CoreVars->DTPS = Counters.serialOverrunErrors; // Interrupt load is too high, incoming packets end up with a byte or two missing
	CoreVars->DMAP = Counters.serialNoiseErrors + Counters.serialFramingErrors + Counters.serialParityErrors; // Users hardware is junk

	// Accurate clocks:
	DerivedVars->zsp1 = Clocks.realTimeClockMain;
	DerivedVars->zsp2 = Clocks.realTimeClockMillis;
	// First two schedules contents:
	DerivedVars->zsp3 = injectorMainPulseWidthsMath[0];
	DerivedVars->zsp4 = postReferenceEventDelays[0];
	DerivedVars->zsp5 = outputEventInputEventNumbers[0];
	DerivedVars->zsp6 = injectorMainPulseWidthsMath[1];
	DerivedVars->zsp7 = postReferenceEventDelays[1];
	DerivedVars->zsp8 = outputEventInputEventNumbers[1];
	// Decoder stuff:
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

}
