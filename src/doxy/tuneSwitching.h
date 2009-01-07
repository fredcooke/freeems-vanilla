/** @page tuneSwitching Tune Switching
 *
 * This feature is similar to one known as "table switching" that you may
 * have used before on other systems except that instead of just switching
 * the tables, the entire tune is switched. The only exceptions to this are
 * physical constants that there is only one available copy of.
 *
 * @todo TODO insert discussion about various uses of tune switching here.
 *
 * The primary copy of all switchable items is enabled by default and is
 * normally what you want to adjust while tuning the engine. It is also what is
 * in use when the tune switching mechanism is enabled and not engaged. The
 * secondary copy of a given switchable item is enabled when the tune switching
 * mechanism is enabled and engaged. If tune switching is not enabled then the
 * secondary copy is never used.
 *
 * @b Warning:
 *
 * Although this boils down to paranoia, some precautions are best taken when
 * tuning your vehicle with FreeEMS. Because there are always two copies of all
 * settings and the code has the ability to switch between them you you should
 * always configure the secondary copy explicitly.
 *
 * If you are not using the tune switching feature it is wise to configure all
 * values in the secondary set to be exactly the same as what is in the primary
 * set. This way if you have tune switching	turned on by accident and the input
 * pin is floating you will not get erratic engine behaviour.
 *
 * @b Developers:
 *
 * When adding things to the set of switchable data please ensure you insert
 * appropriate default values in both the primary and secondary copies.
 */

/**	@file tuneSwitching.h
 * @ingroup doxygenDocFiles
 * @brief Doxygen Tune Switching page definition
 */
