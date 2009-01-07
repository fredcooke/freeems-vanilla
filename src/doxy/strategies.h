/** @page generalStrategies General Strategies
 *
 * This page exists to document general coding strategies used in this
 * firmware. Each item should contain a title, description, situations
 * it is useful in and somewhere you can see an example of it in use.
 *
 * Reading/Writing from/to a specific page :
 *
 * Save the current page value to a variable, change the page value to the desired one, read or write the paged memory, change the page back and return the value
 *
 * This is applicable to all three available memory types: Flash, RAM and EEPROM.
 *
 * Examples of its use can be found in flashWrite.c
 *
 * @todo TODO TBC (other strategies)
 */

/**	@file strategies.h
 * @ingroup doxygenDocFiles
 * @brief Doxygen General Strategies page definition
 */
