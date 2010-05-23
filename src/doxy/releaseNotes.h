/** @page releaseNotes Release Notes
 *
 * This page contains a list of all notable properties of this release. To see
 * the release notes from older releases see the @subpage oldReleaseNotes page.
 *
 * @b General @b Notes
 *
 * A version of the code very similar to 0.1.0 was the first version of FreeEMS to run an engine! That
 * is the reason for moving the versioning from the 0.0.X series to the 0.1.X series. After a few minor
 * false starts, FreeEMS first ran in Baltimore on Friday October 23rd, 2009 at around 2:15am GMT. The
 * first drive was in Pompano Beach on Sunday November 1st, 2009 at around 8:45pm GMT. The first tuning
 * occurred in Naples, Florida at around 1:00am local time on Thursday November 5th, 2009 using freshly
 * written code git pulled from Aaron Barnes in Wellingon NZ in real time. The first significant drive
 * was from there up to Tampa covering ~150 miles and arriving at ~3am. Seat of pants wideband-free
 * tuning continued in Tampa over the next few days after which time the car ran exclusively (and most
 * excellently) on FreeEMS. I drove it from Tampa to Daytona Beach and then up to Atlanta Georgia with
 * Rob Ebersol fine tuning as we went. The first FreeEMS was finally uninstalled on the afternoon of
 * Monday November 9th, 2009 in Atlana after covering around 900 miles or 1500 km. During that time eight
 * people, including myself, rode in and winessed the first FreeEMS powered vehicle.
 *
 * The version that I used on my B230F powered Volvo 740GL wagon was a little less functional and more
 * hacked together. What you see here represents the same code tidied up and with some minor bug fixes
 * and documentation changes. Also note that the car used fuel-only control, not full control. When an
 * engine is run with fuel and ignition control, I will release 0.2.0 to mark the occasion.
 *
 * The version of the tuner used to talk to and tune the very first FreeEMS prototype can be found with
 * the following git commit hash 5188317b6e7418238686602d3b787250398f1ad4 or more conveniently at the
 * following link http://github.com/fredcooke/freeems-tuner/commit/5188317b6e7418238686602d3b787250398f1ad4
 *
 * To get the exact code used on the volvo, take any hash between 97f5ad1f0e6b2ef30bd987c3becc764a5d658bf5
 * and 0cc18370652f096cbcca2226e779a0370a77b113, go to line 110 or 111 of src/coreVarsGenerator.c, change
 * TRUE to FALSE and build. What you have if you do the above is exactly what I used on my Volvo sans the
 * tune itself. If you want the tune too, the S19 is included in the firmware directory. Here is a link to
 * the code : http://github.com/fredcooke/freeems-vanilla/commit/0cc18370652f096cbcca2226e779a0370a77b113
 *
 * @b New @b Features:
 * - Simple decoder
 * - 36-1 decoder
 * - Functional ETE
 * - Functional IDT
 * - Script to generate JSON lists from C
 * - Dump script serial device parameter
 * - Reference implementation of packet decoding in C
 * - Modular data structure allows easy custom builds
 *
 * @b Differences:
 * - Comms implementation and standards
 *
 * @b Known @b Issues:
 * - Transition from partial duty to 100% duty is not smooth
 * - Start and end of each packet could have superfluous bytes
 */

/** @page releaseNotes_0_0_19 FreeEMS 0.0.19 Doxygenated
 *
 * @b New @b Features:
 * - Almost all the code is doxygen commented
 * - The Makefile has been majorly reworked to allow for multiple output files
 *
 * @b Differences:
 * - Make now produces a help message by default
 *
 * @b Known @b Issues:
 * - The windows makefile is out of date and does not work
 */

/** @page releaseNotes_0_0_18 FreeEMS 0.0.18 JackTheRipper
 *
 * stuff
 */

/** @page releaseNotes_0_0_17 FreeEMS 0.0.17 SpudEchoes
 *
 * stuff
 */

/** @page releaseNotes_0_0_16 FreeEMS 0.0.16 FlashGordon
 *
 * stuff
 */

/** @page releaseNotes_0_0_15 FreeEMS 0.0.15 Avogadro
 *
 * stuff
 */

/** @page releaseNotes_0_0_14 FreeEMS 0.0.14 Entropy
 *
 * stuff
 */

/** @page releaseNotes_0_0_13 FreeEMS 0.0.13 GooGooGaGa
 *
 * stuff
 */

/** @page releaseNotes_0_0_12 FreeEMS 0.0.12 Bastard
 *
 * stuff
 */

/** @page releaseNotes_0_0_11 FreeEMS 0.0.11 Cookin'
 *
 * stuff
 */

/** @page releaseNotes_0_0_10 FreeEMS 0.0.10 Squashed
 *
 * stuff
 */

/** @page releaseNotes_0_0_9 FreeEMS 0.0.9 Exponent
 *
 * stuff
 */

/** @page releaseNotes_0_0_8 FreeEMS 0.0.8 Glen
 *
 * stuff
 */

/** @page releaseNotes_0_0_7 FreeEMS 0.0.7
 *
 * stuff
 */

/** @page releaseNotes_0_0_6 FreeEMS 0.0.6
 *
 * stuff
 */

/** @page releaseNotes_0_0_5 FreeEMS 0.0.5
 *
 * stuff
 */

/** @page releaseNotes_0_0_4 FreeEMS 0.0.4
 *
 * stuff
 */

/** @page releaseNotes_0_0_3 FreeEMS 0.0.3
 *
 * stuff
 */

/** @page releaseNotes_0_0_2 FreeEMS 0.0.2
 *
 * stuff
 */

/** @page releaseNotes_0_0_1 FreeEMS 0.0.1
 *
 * Initial version
 */

/** @page oldReleaseNotes Old Release Notes
 *
 * This page contains links to all the old release notes from every version.
 *
 * @b Old @b Notes:
 * - @subpage releaseNotes_0_0_X
 * - @subpage releaseNotes_0_1_X
 */

/** @page releaseNotes_0_0_X Release Notes - 0.0.X Versions
 *
 * - @subpage releaseNotes_0_0_1
 * - @subpage releaseNotes_0_0_2
 * - @subpage releaseNotes_0_0_3
 * - @subpage releaseNotes_0_0_4
 * - @subpage releaseNotes_0_0_5
 * - @subpage releaseNotes_0_0_6
 * - @subpage releaseNotes_0_0_7
 * - @subpage releaseNotes_0_0_8
 * - @subpage releaseNotes_0_0_9
 * - @subpage releaseNotes_0_0_10
 * - @subpage releaseNotes_0_0_11
 * - @subpage releaseNotes_0_0_12
 * - @subpage releaseNotes_0_0_13
 * - @subpage releaseNotes_0_0_14
 * - @subpage releaseNotes_0_0_15
 * - @subpage releaseNotes_0_0_16
 * - @subpage releaseNotes_0_0_17
 * - @subpage releaseNotes_0_0_18
 * - @subpage releaseNotes_0_0_19
 */

/** @page releaseNotes_0_1_X Release Notes - 0.1.X Versions
 *
 * It is wishful thinking putting this here at this stage, but never the less, here it is :-)
 *
 * Hopefully we can put it to good use fairly soon!
 */

/**	@file releaseNotes.h
 * @ingroup doxygenDocFiles
 * @brief Doxygen Release Notes page definition
 */
