# RPM/Position Decoders

The firmware is built N times, where N is the number of decoders in this
directory. Each build has only one decoder inside, this is a sound design choice
for many reasons. An interface is provided through which all decoders must
interract. Adding a new decoder is as simple as copying another one into a new
file, adjusting the logic to read your patterns, and adding it to the makefile.

### Documentation

When coding these, consider the doxygen comments essential. They should explain
the way it works, the vehicles it is suited to, limitations, interface and
setting concerns, etc. Web documentation via doxygen will be the golden source
for the decoders. Further decoder coding guidelines will be added at a later
date with respect to what you can, can not and must do, and suitable
justifications for certain things, etc.

### Decoder Naming

The name of these files should be consistent, right now it's not, but that will change soon.

The format should be something like "UniqueName-Location-Pattern.c" with a
matching header.

 - UniqueName = Manufacturer, vehicle model, engine model, vehicle trim level, year of manufacture, style of sensor, etc.
 - Location = Cam/Crank/Both
 - Pattern = A combination of digits and letters that describes the pattern adequately, usually edge counts, but can be angles.

The following conventions are used for pattern descriptor strings

 - m = minus, used for "Base minus Missing", possibly repeated, eg 36m1 or 60m2 etc. Base counts are assumed to be evenly spaced.
 - a = and, used as "Crank and Cam" or "Outer and Inner", eg 4a1
 - t = then, used for more complex patterns, eg 36m2m2t13m2 (RX8) reads as 36 minus 2 [then 1] minus 2 then 13 minus 2 [then 16] with implicit teeth in square brackets. At least one implicit tooth must seperate any missing groups. More than one should be specified explicity. Left overs are also implicit.
 - Note, the ordering of such complex patterns is important as there are pairs of similar patterns that need to be differentiated such as RX8 (above) and EZ30: 36m2m2t19m2 which reads as 36 minus 2 [then 1] minus 2 then 19 minus 2 [then 10].
 - Just use "Unique" for patterns that are too difficult to describe and suitably unique

### Getting A Decoder Included

This section needs some additional work, which is coming soon.

There are three categories of decoders that are allowed to exist in the source tree!

1. Release Quality. To make it into the makefile permanently it must be functional to a fairly high standard. An appropriate level of sync must be gained and lost at appropriate times via logic where possible, and timing where no logic is possible. RPM must be accurately calculated and scheduling data must be provided for the main loop code to interface with. ADC sampling must be performed at the highest frequency possible whilst still occurring in an evenly spaced way in terms of cylinder count. Inter event timing must be checked for excess variance in any way that makes sense for the particular pattern. Documentation on logic, patterns, source of data, angles, etc must be included in the @file documentation doxygen section.
2. Experimental. To make it into the code base it must compile and link cleanly, it doesn't have to work. The level of functionality must be documented accurately in the code, however so as not to mislead people.
3. Ideas and Documentation. If you have data, LA logs, images, descriptions, logic discussion, application lists, etc, put them in a C multiline comment in an appropriately named file in the future directory.

