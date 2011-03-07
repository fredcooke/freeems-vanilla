/* This "decoder" is intended to generate an output pattern that allows various
 * testing to occur without any external stimulus. This is useful for scheduler
 * testing, injector testing, output hardware testing, coil testing, etc. It,
 * like Sean's LT1 decoder, requires that I add an init function to the decoder
 * interface. Once that is done I will work on this to test it. This will be the
 * only decoder that will be usable with just a cpu and comms interface.
 */
