/** @page codingStyle Coding Style
 *
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
 *
 */
