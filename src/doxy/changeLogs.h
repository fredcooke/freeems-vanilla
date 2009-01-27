/** @page changeLogs Change Logs
 *
 * This page contains a log of all changes made to the FreeEMS firmware since
 * the beginning of the project, ever such a long time ago. The changes that
 * occurred between the last version and this version are listed below. For
 * old change logs see the @ref oldChangeLogs page.
 *
 * Please place your entries at the bottom of the list in the same format as the rest.
 *
 * @version 0.0.19 Doxygenated
 *
 * @date 26/1/09 00:02 GMT
 *
 * @b Changes:
 * - Fred 25/12/08 15:30 GMT:
 *     - Modified writeBlock to burn small blocks via buffer
 *     - Added validation to flash burn direct function
 *     - Added upper range to small table validation check
 *     - Added test packets for small chunk write/burn
 *     - Wrapped braces around protocol case blocks
 * - Fred 26/12/08 12:26 GMT:
 *     - Added addresses for all the small table stuff
 *     - Fixed buffer address creation code by casting
 *     - Finished validation call blocks off
 *     - Added return to block lookup for when ID not found
 *     - Added more test packets for small chunk write/burn
 * - Fred 26/12/08 21:41 GMT:
 *     - Removed stale comments from flashWrite.c
 *     - Filled out file names in comments and header defs for decode
 *     - Updated some TODOs entries etc in preparation for the weekends work
 * - Fred 31/12/08 09:45 GMT:
 *     - Doxygenated the source code
 *     - Modularised the initial contents of the tunable config structs for reuse
 *     - Separated the content from the two copies of the tunable config structs in a shared header
 *     - Added extra header checks for EXTERN pre definition
 *     - Moved zassembly to assembly
 *     - Removed the silly z prefix from the build dir names in the Makefiles
 *     - Added .gitignore for generated .s, .o, .pp.c and output files and doxygen output files
 *     - Moved this change logs to this doxygen html format for easier releases
 *     - Added coding style document
 *     - Added doc page for files not parsed by doxy
 * - Fred 1/1/09 00:36 GMT:
 *     - Named the next release :-)
 *     - Started converting TODOs into doxy format
 *     - Added mainPage doxy page for an intro page when entering the doxy docs
 * - Fred 1/1/09 13:24 GMT:
 *     - Rearranged headers and comments for FixedConfigs.h and TunableConfigs.h
 *     - Fixed up random comments in various headers
 *     - Changed the way the headers are used for core global stuff
 * - Fred 1/1/09 15:35 GMT:
 *     - Removed dangerous and unrequired EXTERN stuff from flash header
 *     - Added note on include order to code style doc
 *     - Fixed all links to gnu.org/licenses to not be wrapped in < >
 *     - Changed some TODOs to appear in todo list
 *     - Tidied line spacing of headers
 *     - Added checks for extern predef to headers
 *     - Removed non functional header checks from asm header
 *     - Updated various copyright statements to include 2009
 *     - Removed all empty headers - not needed now, shouldn't be in there!
 * - Fred 1/1/09 18:34 GMT:
 *     - Added the three linker scripts to be processed by doxygen
 *     - Formatted global constants files a bit as a reason to push a commit
 * - Fred 4/1/09 14:18 GMT:
 *     - Added more coding style information to the docs
 *     - Merged in Seans branch via git cherry-pick
 *     - Doxygenated the template files
 *     - Added tune switching documentation in its own file
 *     - Added grouping file to make doc navigation easier
 *     - Tweaked Doxyfile a bit to format things more nicely
 *     - Removed the gfdl.txt file as we won't be using that license
 *     - Split the GPL and Doxygen comments in the templates
 *     - Added ref to github and sanitised my diyefi admin email in the GPL comments
 *     - Finalised the Doxygen docs for now
 * - Fred 5/1/09 18:08 GMT:
 *     - Added contributors page to docs - incomplete
 *     - Added headers group to modules/groups and populated it
 *     - Added rest of doxy page files to doxy group
 *     - Added EXTERN predef check to more headers
 *     - Formatted some old headers a bit with blank lines
 *     - Removed another empty header file
 *     - Documented many special header files
 * - Fred 6/1/09 18:58 GMT:
 *     - Added brief descriptions to .c files
 *     - Added ISR doc group
 *     - Added comms doc group
 *     - Added and reformatted file documentation for doxygen in about half of all .c files
 * - Fred 9/1/09 21:40 GMT:
 *     - Heavily refactored the Makefile to cleanly build many variants with different wheel decoders
 *     - Added documenation to the Makefile to describe how it works
 * - Fred 10/1/09 22:39 GMT:
 *     - Added .PHONY declarations to the Makefile
 * - Fred 11/1/09 21:42 GMT:
 *     - Added 4 new decoders in skeleton form for others to work from.
 *     - Added a new group for decoders in doxygen groups
 *     - Added preprocessing, compiling, assembling, linking and copying to s19s to the make file
 *     - Added file name conventions to the code style doc
 * - Fred 15/1/09 22:26 GMT:
 *     - Added size reporting to linux makefile
 *     - Refactored init functions for paged ram copies and addresses
 *     - Split up fixed conf 1 into 5 addressable chunks
 *     - Added core vars test generator file
 *     - Added note about s19 files
 *     - More doxygen docs and titles in gpl headers
 * - Fred 25/1/09 23:55 GMT:
 *     - More doxygen docs
 *     - Sean started work on the LT1 decoder
 *     - Split up fixed conf 2 into a bunch of parts
 *     - Added all memory to the block lookup dictionary
 *     - Updated doxyfile to 1.5.8 spec
 *     - Removed redundant flash files and code and documented it better
 *     - Implemented most features of the new makefile
 *     - Added hack to work around windows mkdir commands differences
 *
 * @anchor oldChangeLogs
 * @b Old @b Changes:
 * - @subpage changeLogs_0_0_X
 * - @subpage changeLogs_0_1_X
 */

/* cache
 * @b Changes:
 * - Fred 25/12/08 15:30 GMT:
 *     - Modified writeBlock to burn small blocks via buffer
 *     - Added validation to flash burn direct function
 *     - Added upper range to small table validation check
 *     - Added test packets for small chunk write/burn
 *     - Wrapped braces around protocol case blocks
 * - Fred 26/12/08 12:26 GMT:
 *     - Added addresses for all the small table stuff
 *     - Fixed buffer address creation code by casting
 *     - Finished validation call blocks off
 *     - Added return to block lookup for when ID not found
 *     - Added more test packets for small chunk write/burn
 * - Fred 26/12/08 21:41 GMT:
 *     - Removed stale comments from flashWrite.c
 *     - Filled out file names in comments and header defs for decode
 *     - Updated some TODOs entries etc in preparation for the weekends work
 * - Fred 31/12/08 09:45 GMT:
 *     - Doxygenated the source code
 *     - more even more lots more etc
 */

/** @page changeLogs_0_0_X Change Logs - 0.0.X Versions
 *
 * - @subpage changeLog_0_0_1
 * - @subpage changeLog_0_0_2
 * - @subpage changeLog_0_0_3
 * - @subpage changeLog_0_0_4
 * - @subpage changeLog_0_0_5
 * - @subpage changeLog_0_0_6
 * - @subpage changeLog_0_0_7
 * - @subpage changeLog_0_0_8
 * - @subpage changeLog_0_0_9
 * - @subpage changeLog_0_0_10
 * - @subpage changeLog_0_0_11
 * - @subpage changeLog_0_0_12
 * - @subpage changeLog_0_0_13
 * - @subpage changeLog_0_0_14
 * - @subpage changeLog_0_0_15
 * - @subpage changeLog_0_0_16
 * - @subpage changeLog_0_0_17
 * - @subpage changeLog_0_0_18
 *
 */

/** @page changeLogs_0_1_X Change Logs - 0.1.X Versions
 *
 * It is wishful thinking putting this here at this stage, but never the less, here it is :-)
 *
 * Hopefully we can put it to good use fairly soon!
 */

/** @page changeLog_0_0_1 FreeEMS 0.0.1
 *
 * @version 0.0.1
 *
 * @date 18/2/08 15:55 GMT
 *
 * @b Changes:
 * - Initial version
 * - Sleep function
 * - User LED toggled once per main loop iteration
 * - 6 primary fuel outputs strobed through in a sequential fashion
 */

/** @page changeLog_0_0_2 FreeEMS 0.0.2
 *
 * @version 0.0.2
 *
 * @date 19/2/08 02:21 GMT
 *
 * @b Changes:
 * - Added ADC input for controlling sleep period
 */

/** @page changeLog_0_0_3 FreeEMS 0.0.3
 *
 * @version 0.0.3
 *
 * @date 23/2/08 14:43 GMT
 *
 * @b Changes:
 * - Added strobing port P channels as well as Port T channels (0.0.2plus)
 * - Added strobing of pairs of port A and B channels (0.0.2++)
 * - Added broken logic to strobe more LED's in 5 different ways based on some variables
 */

/** @page changeLog_0_0_4 FreeEMS 0.0.4
 *
 * @version 0.0.4
 *
 * @date 24/2/08 18:02 GMT
 *
 * @b Changes:
 * - Added dual ADC input to speed controller
 * - Added variables for configuration of cylinder count etc etc
 * - Added one pulse per event tacho style pulse
 * - Added PWM code that cycles its period and duty semi randomly
 */

/** @page changeLog_0_0_5 FreeEMS 0.0.5
 *
 * @version 0.0.5
 *
 * @date 26/2/08 12:58 GMT
 *
 * @b Changes:
 * - Added RTI code to cycle the "user led" at 1Hz (Many thanks to Karsten for pointing out my mistake)
 * - Added port H input interrupt code with basic debounce and variables to control what is switched and when
 * - Fixed a small bug in the logic for cylinder count etc
 * - Rearranged significant portions of the code
 * - Added these release notes
 */

/** @page changeLog_0_0_6 FreeEMS 0.0.6
 *
 * @version 0.0.6
 *
 * @date 3/3/08 00:42 GMT
 *
 * @b Changes:
 * - Setup Timer interrupts and mimicked the JimStim input signal on port J 6,7
 * - Fixed init bug (hadn't done it at all yet) that only sampled ADC 0 - 3
 * - Added reset of port B so it can be used for numerical display of debug info
 * - Added wheel analysis document
 * - Made MakeFile dump pre-processed C
 * - Fixed up all header structure
 * - Split interrupt vector table out of main
 * - Added timer overflow handler and extension variable
 * - Moved all injector code to Timer ISR's
 * - Attempted some basic math in the main RPM input ISR and failed
 */

/** @page changeLog_0_0_7 FreeEMS 0.0.7
 *
 * @version 0.0.7
 *
 * @date 5/3/08 16:35 GMT
 *
 * @b Changes:
 * - Moved pins for ignition around
 * - Changed obsolete code in main.c with idea inspired by Alex
 * - Tidied and removed some TODOs
 * - Added port A and B access together for ignition output (registers are conveniently next to each other for word access)
 * - Moved PWM experimentation to a function and init.c
 * - Shifted all macros for main injectors to freeems.h for use in (at least) two source files
 * - Rearranged and changed all global variables
 * - Added new status and settings bitwise variables
 * - Implemented very basic NipponDenso decoder that I would not trust to do much at all.
 */

/** @page changeLog_0_0_8 FreeEMS 0.0.8 Glen
 *
 * @version 0.0.8 Glen
 *
 * @date 9/3/08 02:25 GMT
 *
 * @b Changes:
 * - Added code and constants to watch pulsewidth vs. min and max and act appropriately
 * - Split constants out to separate files
 * - Managed to make overlapping injection work with "Plan B"
 * - Recording time between odd second triggers in 32 bits using timer overflow technique
 */

/** @page changeLog_0_0_9 FreeEMS 0.0.9 Exponent
 *
 * @version 0.0.9 Exponent
 *
 * @date 21/3/08 23:48 GMT
 *
 * @b Changes:
 * - Refined injector control further
 * - Implemented RTC in RTI for 1/8 milli, milli, tenths of, seconds, minutes each with 65535 max
 * - Removed 6x duplication in injection_isrs.c by splitting to injector_isr.c and using defines and imports.
 * - Added support for individual fuel pulse widths
 * - Added latency adjustments and recording to minimum pulse width
 * - Added code run time recording for each channel
 * - Updated docs for injection algorithm
 * - Added LVI interrupt logging to record low voltage conditions.
 * - Added ADC sampling and flagging code
 * - Heavily revised all fuel code to use arrays instead of defines.
 * - Removed 6x duplication in the scheduler code
 * - Tidied up MANY comments and code blocks a LOT
 */

/** @page changeLog_0_0_10 FreeEMS 0.0.10 Squashed
 *
 * @version 0.0.10 Squashed
 *
 * @date 23/3/08 19:51 GMT
 *
 * @b Changes:
 * - Fixed bug 1 : array index out of bounds corruption in scheduler.
 * - Added code to limit retard/advance of fueling, untested, may not be working correctly.
 * - Added modulus down counter interrupt to flash "user led" to indicate board is functioning.
 * - Fixed banked in and out calcs system
 */

/** @page changeLog_0_0_11 FreeEMS 0.0.11 Cookin'
 *
 * @version 0.0.11 Cookin'
 *
 * @date 27/3/08 17:58 GMT
 *
 * @b Changes:
 * - Added freemind mind map of FreeEMS code layout/structure
 * - Removed legacy code snippets.c
 * - Found and fixed bug where the period time was being used before it was valid
 * - Found and fixed a bug where injector timing was not functioning correctly
 * - Found and fixed a bug whereby overlapping injection working correctly relied on an accurate period of a future cycle
 * - Added more realistic sync loss in several places
 * - Changed some variable names etc
 */

/** @page changeLog_0_0_12 FreeEMS 0.0.12 Bastard
 *
 * @version 0.0.12 Bastard
 *
 * @date 4/5/08 08:04 GMT+1
 *
 * @b Changes:
 * - Fixed bug 5 : forgot to add code run time to test for injector hard on behaviour!
 * - Added tooth counters for displaying tooth timing patterns in conjunction with last tooth time stamps at low RPM
 * - Added configurable tooth polarity to rpm/engine position inputs
 * - Fixed a mistake in the code that allowed a ~0x10 to occur (wasn't causing a problem in this instance)
 * - Added PIT based queued ignition functionality which kinda sorta works
 */

/** @page changeLog_0_0_13 FreeEMS 0.0.13 GooGooGaGa
 *
 * @version 0.0.13 GooGooGaGa
 *
 * @date 12/6/08 09:32 GMT+1
 *
 * @b Changes:
 * - Added more comments
 * - Added basic logging of interesting vars using serial
 * - Added serial send unsigned char,short,long
 * - Added itoa() functions for char,short,long
 * - Added serial send string
 * - Added header section for SCI0
 * - Started adding serial setup stuff
 * - Fixed baud config const
 * - Added comments about structure to scheduler
 * - Fixed issue with loops in ign sched
 * - Remove unused bit bang demo function
 * - Add trial send call to main loop
 * - Added duplicate SCI0 section to header with base to use later
 * - Added interface, version, and user strings and definitions
 */

/** @page changeLog_0_0_14 FreeEMS 0.0.14 Entropy
 *
 * @version 0.0.14 Entropy
 *
 * @date 23/6/08 15:32 GMT+1
 *
 * @b Changes:
 * - Added FreeTherm generated transfer table for IAT
 * - Added FreeTherm generated transfer table for CHT
 * - Added code to obtain MAP from a min range pair
 * - Added code to obtain EGO from a min range pair
 * - Added code to obtain TPS from an ADC min/max/range and max set of data
 * - Changed logging code to be more readable and compact
 * - Changed SCI block to use a base address
 * - Added configuration and header for the second block of ADC inputs
 * - Added code to sample the second block
 * - Changed ADC blocks to use base address
 * - Added AAP variable and calculation
 * - Added BRV variable and calculation
 * - Changed 3 ints to 3 unsigned chars in utils.c
 * - Factored out ADC sampling to two methods in different ways
 * - Fixed poor header structure (again) (might have it right this time)
 * - Removed unrequired void from init() definition.
 * - Added ADC reading counters
 * - Renamed ADC reading timeout counter
 * - CamelCased all files except linker scripts
 * - Factored out hr serial logging
 * - Moved pwm demo to utils.c
 * - Measured time of ADC reading functions at less than 1us each, and removed non loop implementation
 * - Used hash define to ensure extern keyword applied appropriately
 * - Fixed makefile dependencies to only recompile sources that are changed
 * - Fix makefile paths for execution from explicit to user based
 * - Changed makefile to chain execution such that each stage is done only once
 * - Added output dir to keep clutter down
 * - Added backup of .s19 to makefile
 * - Added extern hash define structure to all headers
 * - Split oversized freeems.h down to managable chunks
 * - Moved s19 storage to own directory
 * - Introduced dependency on all headers for all source files (previously rebuilding ALL files EVERY time)
 */

/** @page changeLog_0_0_15 FreeEMS 0.0.15 Avogadro
 *
 * @version 0.0.15 Avogadro
 *
 * @date 10/7/08 17:51 GMT+1
 *
 * @b Changes:
 * - Moved injector.c inc file into inc
 * - Added main running variables struct
 * - Added input handling code for all main vars
 * - Renamed all clock counters clock instead of counter
 * - Added counter for calcs routine
 * - Added struct for counters
 * - Added struct for clocks
 * - Added struct for runtimes
 * - Added flash .c and .h files
 * - Added derived vars struct
 * - Added lookup .c and .h files
 * - Added VE tables and Advance tables
 * - Reformated structs to use typedef statement
 * - Added error codes define file
 * - Added config defaults file
 * - Split remaining settings out into structs.h file
 * - Moved documentation about structs to structs file
 * - Removed contents of initConfiguration()
 * - Moved tuning tables and lookup tables and configuration to the other primary flash block.
 * - Added table lookup routine for X by Y unsigned short main tables
 * - Changed main table structure to be more suitable for variable sizing
 * - Added config checker that outputs a count of misconfigurations
 * - Added send function for string without length relying on null byte to terminate
 * - Added send function for block of data from memory with address and length
 * - Fixed the ignition out pins in the pin out doc
 * - Added the hardware flow control pin to PE7 in the pin out doc
 * - Added full length equation with divisors and scaling
 * - Sorted out the memory management up to 48k
 * - Setup the paged macros for data and functions
 * - Moved some vars to globals calculated at boot time to save loop time
 * - Moved user string to config block
 * - Added 16x2xunsigned short table struct
 * - Added MAF input to the pin out doc
 * - Added MAF transfer lookup table
 * - Added correct and physics based mathematics code and calcs
 * - Relocated rodata into text for loading convenience
 * - Added text2 region temporarily (page window)
 * - Added dependency on makefile and linker stuff to make file
 * - Added relocation of flash block lma addresses to make file
 * - Added realistic data to the MAF lookup table
 * - Added a couple of basic hard coded scripts for memory analysis
 * - Added dumps of each object file
 * - Refactored IO banking system and documented it
 * - Changed timer extension use code to use union for performance
 * - Split core vars generation out into own function
 * - Split derived vars generation out into own function
 * - Added some structure for corrections to PW
 * - Swapped order of CRLF pair to be correct in HR log function
 * - Rearranged main.c code for better effect
 * - Slowed logging down to 10x per second
 * - Increased verbosity of log
 * - Added reset rpm to zero if non synchronously sampling ADCs
 * - Split Lambda table out from VETables.c so it can be arranged in memory more conveniently
 * - Split config into tunable and fixed
 * - Moved many literals to hash defines
 * - Fixed "out by 100" error on load indices in tables
 * - Moved rough RPM calc to per event rather than per rev and inited cycleTime to longmax
 * - Reincluded the broken ignition code
 * - General tidy up of all files
 */

/** @page changeLog_0_0_16 FreeEMS 0.0.16 FlashGordon
 *
 * @version 0.0.16 FlashGordon
 *
 * @date 05/10/08 22:20 GMT+1
 *
 * @b Changes:
 * - Fred: Removed reference to TX0 pin S1 from portHISR()
 * - Fred: Used fuel pump pin for portHISR() indicator
 * - Fred: Removed flow control pin function from pin out definition
 * - Fred: Added tachometer function to pin out definition
 * - Fred: Moved User LED flash to RTC to free MDC ISR for Tacho use
 * - Fred: Fixed Makefile dumps section
 * - Fred: Added configurable tacho output
 * - Fred: Fixed RPM calc to use correct variable scale
 * - Fred: Fixed scheduler to always sample ADCs
 * - Fred: Made baud configurable (default 115200)
 * - Fred: Added more runtimes to struct and code to populate them
 * - Fred: Added latencies struct and code to populate them
 * - Fred: Changed broken sync code to be more simple
 * - Fred: Refactored sleep function to allow more range
 * - Fred: Added micro second sleep function
 * - Fred: Moved reset variables to a function
 * - Fred: Added flash globals temporary file
 * - Fred: Added dwell spread sheet
 * - Fred: Added injector dead time spread sheet
 * - Fred: Added tables for IDT and dwell vs voltage
 * - Fred: Added table lookup for unsigned short 2d 16 long
 * - Fred: Added overflow check for reference PW
 * - Fred: Changed table functions to return values directly
 * - Fred: Removed duplicate MAT storage call
 * - Fred: Moved flag clear for RTI to front
 * - Fred: Reduced Ram to 6k to allow 2k of minor data and 4k window of big tables
 * - Fred: Reduced Ram to 5k to allow 1k of flash burn buffer 2k of minor data and 4k window of big tables
 * - Fred: Added more MAP sensor and other definitions to the globalDefines file
 * - Fred: Modified Makefile to compile hand written assembly with C cleanly
 * - Fred: Renamed stoichOct to stoichAFROct
 * - Fred: Updated IAT and CHT tables to use correct bias resistor value of 2.7k
 * - Fred: Reformatted pinout doc and added two columns for bootload and reset states
 * - Fred: Moved ADC pins to final locations on bank 0
 * - Fred: Merged in Seans Flash changes :
 * - Sean: Added flash related header and source files
 * - Sean: Added assembly to load code to stack for burning own flash
 * - Sean: Added flash erase sector function
 * - Sean: Added flash word write function
 * - Sean: Added flash write aligned block function
 * - Sean: Documented flash functionality in the code
 * - Fred: Added output to makefile to see each operation type
 * - Fred: Removed hash define from all constants C files
 * - Fred: Added main table unions
 * - Fred: Added ram regions for the purpose of aligning large blocks of data
 * - Fred: Added include and memcpy references to bring data up into ram
 * - Fred: Added RPAGE to header to allow paging of tables in and out of visible space
 * - Fred: Added paged tuning blocks such that table switching almost changes a full tune
 * - Fred: Migrated small tables into struct for paging
 * - Fred: Split flash into 5 blocks to ensure no overflow occurs in smalltables
 * - Fred: Created mechanism to ensure paged data is retrieved correctly by implementing basis of table switching
 * - Fred: Moved all references to tables to ram copies
 * - Fred: Split flash again for fixed config block.
 * - Fred: General formatting and file name and content changes
 * - Fred: Shifted tunable configs to structs for paging
 * - Fred: Moved copy from flash to ram to start of init
 * - Fred: Future comms pseudo code added
 * - Fred: Various spelling fixes
 */

/** @page changeLog_0_0_17 FreeEMS 0.0.17 SpudEchoes
 *
 * @version 0.0.17 SpudEchoes
 *
 * @date 11/11/08 12:17 GMT
 *
 * @b Changes:
 * - Fred 8/10/08 07:40 GMT
 *     - Moved flash routine from old text1 to text
 *     - Added descriptive comment to the main table definition
 *     - Added sizeof defines to the structs file
 *     - Shrunk and renamed text1 to lookup with 3 2k tables in it
 * - Fred 15/10/08 10:50 GMT:
 *     - Removed all old busy wait ascii serial code
 *     - Added packetising escaping checksumming receive ISR code
 *     - Added packetising escaping checksumming send ISR code
 *     - Added code to send back whatever it receives for testing purposes
 *     - Temporarily changed make file to avoid a couple of options an old version of gcc didn't have
 *     - Added document describing serial implementation
 * - Fred 20/10/08 10:56 GMT:
 *     - Added serial specification docs to the project docs dir and renamed them
 *     - Added test packet directory
 *     - Made some fixes to the ISR handling code for serial
 *     - Added some more serial counters and masks
 * - Fred 20/10/08 20:11 GMT:
 *     - Added core comms source and header files
 *     - Removed commented out legacy code in places
 *     - Updated tasks, bugs, tests, mindmap
 * - Fred 21/10/08 08:00 GMT:
 *     - Refactored escape code in rx section
 *     - Added test packet for escape code generation EMS side
 * - Fred 21/10/08 21:50 GMT:
 *     - Updated serial impl document
 *     - Reordered receive statements for better speed and accuracy
 *     - Generated individual bytes for sending
 * - Fred 22/10/08 18:55 GMT:
 *     - Made the serial packet handler compile
 *     - Commented out the copy-only sections in makefile
 *     - Moved things out of commsISRs.h and added more things to commsCore.h
 * - Fred 22/10/08 21:30 GMT:
 *     - Updated release procedure to include internal version changes to prevent incorrect ones recurring
 *     - Removed burnbuf as unrequired now
 *     - Bumped the versions in the constants file.
 * - Fred 23/10/08 01:54 GMT:
 *     - Completed and tested serial checksum and escape functionality.
 * - Fred 23/10/08 23:54 GMT:
 *     - Added substantial packet handling logic.
 * - Fred 25/10/08 15:00 GMT:
 *     - Fixed array length mismatch
 *     - Added header decoding logic
 *     - Refactored serial headers to be more sensible and share vars
 *     - Removed instances of using "&= ~0x" from the code
 *     - Renamed various serial variables
 * - Fred 25/10/08 21:49 GMT:
 *     - Added line count of s19 to makefile
 * - Fred 26/10/08 00:19 GMT:
 *     - Added interface version request/response code
 * - Fred 26/10/08 18:47 GMT:
 *     - Added firmware version request/response code
 *     - Added max packet size request/response code
 *     - Added echo wrapper packet request/response code
 *     - Added hard reset request and action code (using real vector location)
 *     - Added async error code packets
 *     - Added async debug packets
 *     - Added stringCopy utility to avoid using another library
 *     - Added call to writeAlignedBlock function
 * - Sean 29/10/08 23:30 GMT:
 *     - Fixed flashWrite.c mistakes
 * - Fred 31/10/08 18:00 GMT:
 *     - Fixed issue number 4 by changing linker script with AT() clause
 *     - Moved output dirs to lowercase and shorter names
 *     - Moved some functions to fixedconf flash blocks temporarily
 *     - Reclaimed 16 bytes of space with a mem.x fix
 * - Fred 03/11/08 00:48 GMT:
 *     - Made a number of fixes to the serial comms code to be detailed in later change log
 * - Fred 04/11/08 19:25 GMT:
 *     - Migrated memory management to paged style upto 128k of space in one flash block.
 * - Fred 07/11/08 13:23 GMT:
 *     - Added flash block return by ID function
 * - Fred 08/11/08 13:38 GMT:
 *     - Added soft reset function
 * - Fred 09/11/08 02:37 GMT:
 *     - Added ram block return by ID function
 *     - Added ram to flash burn by ID function
 *     - Added comm to ram write by ID function
 *     - Added comm to flash write by ID function (and update ram)
 * - Fred 09/11/08 12:30 GMT:
 *     - Added memory location lookup and struct
 * - Fred 09/11/08 17:29 GMT:
 *     - Removed bigtables linear page stuff
 * - Fred 10/11/08 08:16 GMT:
 *     - Added validation function for main tables
 *     - Added limits to table return functions
 *     - Fixed bug when address not ours dropping packet
 * - Fred 10/11/08 23:26 GMT:
 *     - Added debug and error packets back in
 *     - Merged Seans fixes for flash in
 *
 */

/** @page changeLog_0_0_18 FreeEMS 0.0.18 JackTheRipper
 *
 * @version 0.0.18 JackTheRipper
 *
 * @date 22/12/08 23:58 GMT
 *
 * @b Changes:
 * - Fred 12/11/08 07:04 GMT:
 *     - Added flash and ram receive functions
 *     - Added wrappers for debug and error
 *     - Modified flash error handling to be compatible with overall scheme
 *     - Renamed all counters more sensibly
 *     - Major tidy up of init.c - more to do in the future
 * - Fred 12/11/08 19:51 GMT:
 *     - Created generic flash burning wrapper
 *     - Moved flash error handling into wrapper
 *     - Moved page ram init to functions per block of data
 *     - Moved tables to 3 pages from 2 and put functions in place to init them
 *     - Created multi sector flash burn function
 *     - Previously added table size guide
 *     - Previously added testing matrix for comms
 *     - Previously added hardware interface doc
 * - Fred 13/11/08 08:52 GMT:
 *     - Fixed bug where config was coming from flash, not ram.
 *     - Completed paging memory exercise for now
 *     - Removed all linker warnings by shuffling code and data
 * - Fred 14/11/08 07:45 GMT:
 *     - Split regions into regions.x out of the main linker script
 *     - Split page for small tables into chunks to cause link issues if oversize and still work if undersize
 * - Fred 16/11/08 17:05 GMT:
 *     - Fixed hard reset functionality
 *     - Refactored the table lookup to be faster and use less space
 *     - Updated serial core docs
 *     - Added doc describing the datalog format
 *     - More comms test packets
 *     - Pin out doc update!
 * - Fred 18/11/08 18:04 GMT:
 *     - Fixed missing text1 copy options
 *     - Changed makefile to be faster and more versatile
 *     - Migrated rodata back to its own section(s)
 *     - Moved ADC tables and core var gen to a paged flash region together
 * - Fred 19/11/08 08:30 GMT:
 *     - Migrated data init to static from dynamic
 *     - Fixed comms dictionary lookup addresses with lookup addr init function
 * - Fred 19/11/08 17:55 GMT:
 *     - Moved all ISR code to text1 so we know how big it is and how big the rest is
 * - Fred 20/11/08 07:55 GMT:
 *     - Added check for packet from own address
 *     - Changed error codes to be more meaningful
 * - Fred 20/11/08 18:37 GMT:
 *     - Added interface data map
 * - Fred 21/11/08 20:27 GMT:
 *     - Added windows Makefile
 *     - Added size utility call
 *     - Added example datalog json
 *     - Merged lambda and ve into fuel files
 * - Fred 22/11/08 14:27 GMT:
 *     - Split fixed config in two different pieces
 *     - Rearranged makefile
 *     - Split fixed configs into two different files
 *     - Added extra user text field and filled out to section boundary
 *     - Moved some functions back into the text areas
 *     - Added interface packet descriptions
 *     - Fixed init values
 *     - Split headers out a bit
 *     - Fixed and added some comments etc
 *     - Added win make file generator
 *     - Tweaked makefile to work with windows
 * - Fred 25/11/08 23:37 GMT:
 *     - Added test packets to dump registers with SM
 *     - Added memory management documentation
 *     - Added example settings file
 *     - Added tuner interface overview doc
 *     - Further updated pin out doc
 * - Fred 26/11/08 23:12 GMT:
 *     - Added Sean's flash fixes in and looped flash erase/burn to test it
 *     - More changes to the json stuff
 *     - Fixed bug with makefile that caused it to regen files without need
 * - Fred 27/11/08 18:31 GMT:
 *     - Added custom packet definition file for tuner
 *     - Added windows makefile generation to the makefile
 *     - Optimised flash writing by moving page swapping up one level
 *     - Removed cruft from comms core
 *     - Relocated dictionary to paged flash
 * - Fred 29/11/08 19:20 GMT:
 *     - Added axis and cell value adjustment routines for the main tables
 *     - Added axis adjustment error checking function
 *     - Rearranged error codes a bit
 *     - Added test data block for testing serial comms
 * - Fred 30/11/08 10:19 GMT:
 *     - Removed redundant code from serial comms
 *     - Added basic datalog function and serial option
 *     - Updated readme file
 *     - Rearranged and renamed some doc files and interface descriptors
 * - Fred 30/11/08 20:04 GMT:
 *     - Added async datalog sender
 *     - Added configurator for async logging
 *     - Added all minor parts of the dynamic config to the dictionary
 *     - Divided page f9 into data and functions
 *     - Added two d us table adjuster functions and serial routines
 * - Fred  1/12/08 22:22 GMT:
 *     - Fixed serial bug with small hack (needs better fix)
 *     - Moved many functions to paged flash
 *     - Fixed copy paste error in address init code
 *     - Fixed - instead of + in cell setting function
 * - Fred  7/12/08 22:41 GMT:
 *     - Added data map overview doc
 * - Fred 11/12/08 12:31 GMT:
 *     - Added JSONSchema for one JSON file
 * - Fred 18/12/08 18:29 GMT:
 *     - Refactored array based banking to pointer based - Awesome change
 *     - Fixed pointer to a pointer bug in datalog introduced above
 *     - Removed extra copies of core and derived vars from header
 *     - Documented new pointer scheme in header
 * - Fred 21/12/08 02:37 GMT:
 *     - Fixed bug, flash and ram pages/addresses were swapped in a flash burn function call
 *     - Added check for dest address in ram region
 * - Fred 21/12/08 22:46 GMT:
 *     - Hacked in datalog delay of 1 second
 *     - Hacked orange button to turn basic datalog off and on
 *     - Added comments for future changes to serial stuff
 *     - Added ifdef wrappers around unrequired init stuff
 * - Fred 22/12/08 20:46 GMT:
 *     - Split address lookup function out of comms file
 *     - Added more comments etc
 *     - Moved old bugs to mantis and removed bugs.txt
 *     - Cleaned out HEAPS of old cruft, tidied up and commented stuff
 */

/**	@file changeLogs.h
 * @ingroup doxygenDocFiles
 * @brief Doxygen Change Logs page definition
 */
