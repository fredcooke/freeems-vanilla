// See README.txt in custom dir and this dir

void populateCustomDatalog(){
//	CoreVars->DRPM = Counters.; currently in use logging *ticksPerDegree as at wed nzst 3:10pm 16 march 2011 see line ~98 of derivedVarsGenerator.c and line ~277 of coreVarsGenerator.c

	// Currently spare:
	CoreVars->DDRPM = injectorMainPulseWidthsMath[2];
	CoreVars->DTPS = postReferenceEventDelays[2];
	CoreVars->DMAP = outputEventInputEventNumbers[2];

	// First two schedules contents:
	KeyUserDebugs.zsp3 = injectorMainPulseWidthsMath[0];
	KeyUserDebugs.zsp4 = postReferenceEventDelays[0];
	KeyUserDebugs.zsp5 = outputEventInputEventNumbers[0];
	KeyUserDebugs.zsp6 = injectorMainPulseWidthsMath[1];
	KeyUserDebugs.zsp7 = postReferenceEventDelays[1];
	KeyUserDebugs.zsp8 = outputEventInputEventNumbers[1];
//	KeyUserDebugs.zsp9 = ;
//	KeyUserDebugs.zsp10 = ;
}
