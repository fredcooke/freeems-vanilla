/* FreeEMS - the open source engine management system
 *
 * Copyright 2011 Fred Cooke
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
 * @ingroup allHeaders
 * @ingroup enginePositionRPMDecoders
 *
 * Predefined sync loss IDs to make it easy to lookup and diagnose issues.
 *
 * - Change all 4 hash defines to the filename uppercased and underscored
 *
 */

/* Header file multiple inclusion protection courtesy eclipse Header Template	*/
/* and http://gcc.gnu.org/onlinedocs/gcc-3.1.1/cpp/ C pre processor manual		*/
#ifndef FILE_SYNC_LOSS_IDS_H_SEEN
#define FILE_SYNC_LOSS_IDS_H_SEEN


// Special case for timeout
#define EVENT_ARRIVAL_TIMEOUT                  0

// Common to all decoders
#define PRIMARY_EVENT_ARRIVED_TOO_LATE         1
#define PRIMARY_EVENT_ARRIVED_TOO_EARLY        2
#define SECONDARY_EVENT_ARRIVED_TOO_LATE       3
#define SECONDARY_EVENT_ARRIVED_TOO_EARLY      4

// Count based decoders
#define COUNT_OF_EVENTS_IMPOSSIBLY_LOW_NOISE   5
#define COUNT_OF_EVENTS_IMPOSSIBLY_HIGH_NOISE  6

// Logic based CAS as found on most Mitsi and Mazda engines
#define STATE_MISMATCH_IN_PRIMARY_RPM_ISR      7
#define STATE_MISMATCH_IN_SECONDARY_RPM_ISR    8

// MissingTeeth uses from 0x40 - 0x8D, below and above are free for all other decoders to use.

// Pair designations, possibly move this elsewhere to support defining the others as errors elsewhere too
#define FellThrough     64 // 0x40 The cracks, ie, no match
#define MatchedPair      4 // ~1:1
#define NarrowWide       6 // ~1:(N+1)
#define WideNarrow       7 // ~(N+1):1
#define NarrowBackward   8 // ~1:(N+2)/2
#define BackwardNarrow   5 // ~(N+2)/2:1
#define NarrowTooWide   65 // 0x41 1:>(N+1)
#define TooWideNarrow   66 // 0x42 >(N+1):1

// This is for transposing errors to a unique number to indicate loss of sync different to clear during search
#define MaskBySumPattern       0x05 // 0xN4 >> 0xN9, 0xN8 >> 0xND, no collisions, free space for more too

// Possible conditions of success and failure.
//
// Literals here for readability, checked below with formula and names
//
// Note, whether it is possible to strike these depends on the tolerance used

// In sync:
#define MatchedPairMatchedPair  68 // 0x44 small small small - All periods match
#define MatchedPairNarrowWide   70 // 0x46 small small BIG - First tooth after missing
#define NarrowWideWideNarrow   103 // 0x67 small BIG small - Second tooth after missing, the strongest and most certain sync
#define WideNarrowMatchedPair  116 // 0x74 BIG small small - Third tooth after missing

// Except when we should get something else:
#define MatchedPairMatchedPairPlusMask  73 // 0x49 small small small - All periods match (Indicates wrong decoder with too few teeth, same missing)
#define MatchedPairNarrowWidePlusMask   75 // 0x4B small small BIG - First tooth after missing (Indicates wrong decoder with too many teeth, same missing)
#define NarrowWideWideNarrowPlusMask   108 // 0x6C small BIG small - Second tooth after missing, the strongest and most certain sync
#define WideNarrowMatchedPairPlusMask  121 // 0x79 BIG small small - Third tooth after missing

// Wild noise and bad settings:
#define yourVRSensorHasALoosePlugFixIt                    NarrowTooWide
#define noiseAppearedWayTooEarlyAsIfItWasAVRToothButWasnt TooWideNarrow
#define yourSyncToleranceIsTighterThanAWellYouGetTheIdea  FellThrough
#define yourSyncToleranceIsLooserThanAWellYouGetTheIdea   MatchedPairMatchedPair // Too many matched pairs in a row

// Fails:
#define NearlySyncedNarrowWideBackwardNarrow           101 // 0x65
#define NearlySyncedNarrowBackwardWideNarrow           135 // 0x87
#define NearlySyncedNarrowBackwardBackwardNarrow       133 // 0x85
#define NearlySyncedMatchedPairNarrowBackward           72 // 0x48
#define NearlySyncedBackwardNarrowMatchedPair           84 // 0x54
#define ExtraToothWideNarrowNarrowWide                 118 // 0x76
#define ExtraToothWideNarrowNarrowBackward             120 // 0x78
#define ExtraToothBackwardNarrowNarrowWide              86 // 0x56
#define ExtraToothBackwardNarrowNarrowBackward          88 // 0x58
#define VRWiringBackwardMatchedPairBackwardNarrow       69 // 0x45 Engineered to be 69 for humour value!
#define VRWiringBackwardMatchedPairWideNarrow           71 // 0x47
#define VRWiringBackwardNarrowWideMatchedPair          100 // 0x64
#define VRWiringBackwardNarrowBackwardMatchedPair      132 // 0x84
#define ExcessDecelerationNarrowBackwardNarrowBackward 136 // 0x88
#define ExcessDecelerationNarrowBackwardNarrowWide     134 // 0x86
#define ExcessDecelerationNarrowWideNarrowBackward     104 // 0x68
#define ExcessDecelerationNarrowWideNarrowWide         102 // 0x66
#define ExcessAccelerationBackwardNarrowBackwardNarrow  85 // 0x55
#define ExcessAccelerationBackwardNarrowWideNarrow      87 // 0x57
#define ExcessAccelerationWideNarrowBackwardNarrow     117 // 0x75
#define ExcessAccelerationWideNarrowWideNarrow         119 // 0x77

// Fails while synced:
#define NearlySyncedNarrowWideBackwardNarrowPlusMask           106 // 0x6A
#define NearlySyncedNarrowBackwardWideNarrowPlusMask           140 // 0x8C
#define NearlySyncedNarrowBackwardBackwardNarrowPlusMask       138 // 0x8A
#define NearlySyncedMatchedPairNarrowBackwardPlusMask           77 // 0x4D
#define NearlySyncedBackwardNarrowMatchedPairPlusMask           89 // 0x59
#define ExtraToothWideNarrowNarrowWidePlusMask                 123 // 0x7B
#define ExtraToothWideNarrowNarrowBackwardPlusMask             125 // 0x7D
#define ExtraToothBackwardNarrowNarrowWidePlusMask              91 // 0x5B
#define ExtraToothBackwardNarrowNarrowBackwardPlusMask          93 // 0x5D
#define VRWiringBackwardMatchedPairBackwardNarrowPlusMask       74 // 0x4A
#define VRWiringBackwardMatchedPairWideNarrowPlusMask           76 // 0x4C
#define VRWiringBackwardNarrowWideMatchedPairPlusMask          105 // 0x69
#define VRWiringBackwardNarrowBackwardMatchedPairPlusMask      137 // 0x89
#define ExcessDecelerationNarrowBackwardNarrowBackwardPlusMask 141 // 0x8D
#define ExcessDecelerationNarrowBackwardNarrowWidePlusMask     139 // 0x8B
#define ExcessDecelerationNarrowWideNarrowBackwardPlusMask     109 // 0x6D
#define ExcessDecelerationNarrowWideNarrowWidePlusMask         107 // 0x6B
#define ExcessAccelerationBackwardNarrowBackwardNarrowPlusMask  90 // 0x5A
#define ExcessAccelerationBackwardNarrowWideNarrowPlusMask      92 // 0x5C
#define ExcessAccelerationWideNarrowBackwardNarrowPlusMask     122 // 0x7A
#define ExcessAccelerationWideNarrowWideNarrowPlusMask         124 // 0x7C

// Self-checks on the above
#if (MatchedPairMatchedPair != ((MatchedPair << 4) + MatchedPair))
#error "Header is broken, fix it!"
#endif
#if (MatchedPairNarrowWide != ((MatchedPair << 4) + NarrowWide))
#error "Header is broken, fix it!"
#endif
#if (NarrowWideWideNarrow != ((NarrowWide << 4) + WideNarrow))
#error "Header is broken, fix it!"
#endif
#if (WideNarrowMatchedPair != ((WideNarrow << 4) + MatchedPair))
#error "Header is broken, fix it!"
#endif
#if (NearlySyncedNarrowWideBackwardNarrow != ((NarrowWide << 4) + BackwardNarrow))
#error "Header is broken, fix it!"
#endif
#if (NearlySyncedNarrowBackwardWideNarrow != ((NarrowBackward << 4) + WideNarrow))
#error "Header is broken, fix it!"
#endif
#if (NearlySyncedNarrowBackwardBackwardNarrow != ((NarrowBackward << 4) + BackwardNarrow))
#error "Header is broken, fix it!"
#endif
#if (NearlySyncedMatchedPairNarrowBackward != ((MatchedPair << 4) + NarrowBackward))
#error "Header is broken, fix it!"
#endif
#if (NearlySyncedBackwardNarrowMatchedPair != ((BackwardNarrow << 4) + MatchedPair))
#error "Header is broken, fix it!"
#endif
#if (ExtraToothWideNarrowNarrowWide != ((WideNarrow << 4) + NarrowWide))
#error "Header is broken, fix it!"
#endif
#if (ExtraToothWideNarrowNarrowBackward != ((WideNarrow << 4) + NarrowBackward))
#error "Header is broken, fix it!"
#endif
#if (ExtraToothBackwardNarrowNarrowWide != ((BackwardNarrow << 4) + NarrowWide))
#error "Header is broken, fix it!"
#endif
#if (ExtraToothBackwardNarrowNarrowBackward != ((BackwardNarrow << 4) + NarrowBackward))
#error "Header is broken, fix it!"
#endif
#if (VRWiringBackwardMatchedPairBackwardNarrow != ((MatchedPair << 4) + BackwardNarrow))
#error "Header is broken, fix it!"
#endif
#if (VRWiringBackwardMatchedPairWideNarrow != ((MatchedPair << 4) + WideNarrow))
#error "Header is broken, fix it!"
#endif
#if (VRWiringBackwardNarrowWideMatchedPair != ((NarrowWide << 4) + MatchedPair))
#error "Header is broken, fix it!"
#endif
#if (VRWiringBackwardNarrowBackwardMatchedPair != ((NarrowBackward << 4) + MatchedPair))
#error "Header is broken, fix it!"
#endif
#if (ExcessDecelerationNarrowBackwardNarrowBackward != ((NarrowBackward << 4) + NarrowBackward))
#error "Header is broken, fix it!"
#endif
#if (ExcessDecelerationNarrowBackwardNarrowWide != ((NarrowBackward << 4) + NarrowWide))
#error "Header is broken, fix it!"
#endif
#if (ExcessDecelerationNarrowWideNarrowBackward != ((NarrowWide << 4) + NarrowBackward))
#error "Header is broken, fix it!"
#endif
#if (ExcessDecelerationNarrowWideNarrowWide != ((NarrowWide << 4) + NarrowWide))
#error "Header is broken, fix it!"
#endif
#if (ExcessAccelerationBackwardNarrowBackwardNarrow != ((BackwardNarrow << 4) + BackwardNarrow))
#error "Header is broken, fix it!"
#endif
#if (ExcessAccelerationBackwardNarrowWideNarrow != ((BackwardNarrow << 4) + WideNarrow))
#error "Header is broken, fix it!"
#endif
#if (ExcessAccelerationWideNarrowBackwardNarrow != ((WideNarrow << 4) + BackwardNarrow))
#error "Header is broken, fix it!"
#endif
#if (ExcessAccelerationWideNarrowWideNarrow != ((WideNarrow << 4) + WideNarrow))
#error "Header is broken, fix it!"
#endif

// And for the masked ones:
#if (MatchedPairMatchedPairPlusMask != ((MatchedPair << 4) + MatchedPair) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (MatchedPairNarrowWidePlusMask != ((MatchedPair << 4) + NarrowWide) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (NarrowWideWideNarrowPlusMask != ((NarrowWide << 4) + WideNarrow) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (WideNarrowMatchedPairPlusMask != ((WideNarrow << 4) + MatchedPair) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (NearlySyncedNarrowWideBackwardNarrowPlusMask != ((NarrowWide << 4) + BackwardNarrow) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (NearlySyncedNarrowBackwardWideNarrowPlusMask != ((NarrowBackward << 4) + WideNarrow) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (NearlySyncedNarrowBackwardBackwardNarrowPlusMask != ((NarrowBackward << 4) + BackwardNarrow) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (NearlySyncedMatchedPairNarrowBackwardPlusMask != ((MatchedPair << 4) + NarrowBackward) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (NearlySyncedBackwardNarrowMatchedPairPlusMask != ((BackwardNarrow << 4) + MatchedPair) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExtraToothWideNarrowNarrowWidePlusMask != ((WideNarrow << 4) + NarrowWide) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExtraToothWideNarrowNarrowBackwardPlusMask != ((WideNarrow << 4) + NarrowBackward) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExtraToothBackwardNarrowNarrowWidePlusMask != ((BackwardNarrow << 4) + NarrowWide) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExtraToothBackwardNarrowNarrowBackwardPlusMask != ((BackwardNarrow << 4) + NarrowBackward) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (VRWiringBackwardMatchedPairBackwardNarrowPlusMask != ((MatchedPair << 4) + BackwardNarrow) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (VRWiringBackwardMatchedPairWideNarrowPlusMask != ((MatchedPair << 4) + WideNarrow) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (VRWiringBackwardNarrowWideMatchedPairPlusMask != ((NarrowWide << 4) + MatchedPair) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (VRWiringBackwardNarrowBackwardMatchedPairPlusMask != ((NarrowBackward << 4) + MatchedPair) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExcessDecelerationNarrowBackwardNarrowBackwardPlusMask != ((NarrowBackward << 4) + NarrowBackward) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExcessDecelerationNarrowBackwardNarrowWidePlusMask != ((NarrowBackward << 4) + NarrowWide) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExcessDecelerationNarrowWideNarrowBackwardPlusMask != ((NarrowWide << 4) + NarrowBackward) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExcessDecelerationNarrowWideNarrowWidePlusMask != ((NarrowWide << 4) + NarrowWide) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExcessAccelerationBackwardNarrowBackwardNarrowPlusMask != ((BackwardNarrow << 4) + BackwardNarrow) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExcessAccelerationBackwardNarrowWideNarrowPlusMask != ((BackwardNarrow << 4) + WideNarrow) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExcessAccelerationWideNarrowBackwardNarrowPlusMask != ((WideNarrow << 4) + BackwardNarrow) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif
#if (ExcessAccelerationWideNarrowWideNarrowPlusMask != ((WideNarrow << 4) + WideNarrow) + MaskBySumPattern)
#error "Header is broken, fix it!"
#endif


#else
	/* let us know if we are being untidy with headers */
	#warning "Header file SYNC_LOSS_IDS_H seen before, sort it out!"
/* end of the wrapper ifdef from the very top */
#endif
