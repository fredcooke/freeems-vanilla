/** @page codingStyle Coding Style
 *
 * @b Sections:
 * - Licensing
 * - Copyright
 * - Documentation
 *     - Doxygen
 * - Naming
 *     - Abbreviations
 *     - Multiple names - which to use
 * - Formatting
 * - Reserved words
 * - Language use
 * - References
 * - Structure
 *     - New variables
 *     - New features/functions
 *
 * @b Details:
 * - All new files should be based on the gpl.template.* files and have documentation about their intended use
 * - All files should have the GPL header inside them
 * - When you work on a file that exists, add your name to the copyright (unless the edit is extremely minor)
 * - If the the copyright year is not the current year, add the copyright
 * - eg Copyright 2008, 2009 Fred Cooke, Sean Keys
 * - Dates in the code should be DD/MM/YY for easy reading
 * - Dates in file names should be YYYY-MM-DD for easy sorting
 * - Use Doxygen style comments
 * - Document all parameters
 * - Document return object details
 * - use @ instead of \
 * - to start a function comment block use ** instead of *!
 * - when declaring a pointer make it (type* name) not (type *name)
 * - Never use int, always char, short or long
 * - Always use full types, eg unsigned char not char and signed short instead of short
 * - use // style comments for temporary work/documentation and block comments for permanent stuff.
 * - order for doc tags : author, param(s), return
 * - tabs should be used for indentation
 * - spaces should be used to space out from variable width text before more tabs
 * - generally, two blank lines between functions, one blank line between logical blocks
 * - default tab size is 4 spaces, currently best viewed with that, but working on making it clean for any.
 * - Include order should have the most general thing first and most specific last :
 * @code
 * #include <string.h>
 * #include "inc/freeEMS.h"
 * #include "inc/utils.h"
 * #include "inc/thisFilesHeader.h"
 * @endcode
 *
 * - braces should be positioned as follows with the opening brace on the same line as the function name and no leading space:
 * @code
 * void function(){
 *     // code
 * }
 * @endcode
 *
 * - case statements should always use braces :
 * @code
 * switch(var){
 * case 666:
 * {
 *     // code
 * }
 * }
 * @endcode
 *
 * - parameter lists should look like this with a space after each comma and no leading or trailing spaces
 * @code
 * void function(unsigned char one, signed short another){
 *     // code
 * }
 *
 * function(255, -32768);
 * @endcode
 *
 * @b Discussion:
 *
 * We need to figure out a consistent way of naming variables and functions and
 * files etc. The main thing that needs deciding is which scheme from the following:
 * - UPPER_CASE
 * - lower_case
 * - lowerCamelCase
 * - UpperCamelCase
 * - Other ways?
 *
 * The categories of names required to be discussed are as follows:
 * - hash defines
 *     - register aliases
 *     - register masks
 *     - custom masks
 *     - error codes
 *     - payload IDs
 *     - constant values (would be literals)
 *     - what else?
 * - structs (and unions)
 *     - struct typedefs
 *     - struct members
 *     - struct instances
 * - local variables
 * - global variables
 * - files
 *     - header see source :
 *     - source - RPM ISRs and data initialisers UpperCamelCase - the rest lowerCamelCase
 *     - doxygen
 *     - standalone documentation
 *     - JSON files and schemas
 *     - linker scripts
 *     - makefiles
 *     - readme/readme.txt/README/README.txt
 *
 * Please see the following Mantis issue for the original mandate to produce this document:
 * - http://freeems.aaronb.info/tracker/view.php?id=10
 */

/** @file codingStyle.h
 * @ingroup doxygenDocFiles
 * @brief Doxygen Coding Style page definition
 */
