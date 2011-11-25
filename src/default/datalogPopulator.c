// See README.txt in custom dir and this dir

void populateCustomDatalog(){
//	CoreVars->DRPM = Counters.; currently in use logging *ticksPerDegree as at wed nzst 3:10pm 16 march 2011 see line ~98 of derivedVarsGenerator.c and line ~277 of coreVarsGenerator.c

//	// Currently spare:
//	CoreVars->DDRPM = outputEventPulseWidthsMath[2];
//	CoreVars->DTPS = outputEventDelayFinalPeriod[2];
//	CoreVars->DMAP = outputEventInputEventNumbers[2];

	// Log scheduling data by default for the time being.
	CoreVars->DTPS = Counters.normalSchedule;
	CoreVars->DMAP = Counters.timerStretchedToSchedule;

	KeyUserDebugs.zsp3 = Counters.pinScheduledToGoHigh;
	KeyUserDebugs.zsp4 = Counters.pinScheduledAlready;
	KeyUserDebugs.zsp5 = Counters.pinScheduledToSelfSchedule;
	KeyUserDebugs.zsp6 = Counters.pinScheduledAgainToStayOn;
	KeyUserDebugs.zsp7 = Counters.pinScheduledToToggleError;
	KeyUserDebugs.zsp8 = Counters.pinScheduledToDoNothing;
	KeyUserDebugs.zsp9 = Counters.pinScheduledFromCold;
	KeyUserDebugs.zsp10 = Counters.pinScheduledWithTimerExtension;

//	// First two schedules contents:
//	KeyUserDebugs.zsp3 = outputEventPulseWidthsMath[0];
//	KeyUserDebugs.zsp4 = outputEventDelayFinalPeriod[0];
//	KeyUserDebugs.zsp5 = outputEventInputEventNumbers[0];
//	KeyUserDebugs.zsp6 = outputEventPulseWidthsMath[1];
//	KeyUserDebugs.zsp7 = outputEventDelayFinalPeriod[1];
//	KeyUserDebugs.zsp8 = outputEventInputEventNumbers[1];
//	KeyUserDebugs.zsp9 = 0;
//	KeyUserDebugs.zsp10 = 0;
}
