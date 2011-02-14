RPM/Position Decoders

The firmware is built N times, where N is the number of decoders in this directory. Each build has only one decoder inside, this is a sound design choice for many reasons. An interface is provided through which all decoders must interract. Adding a new decoder is as simple as copying another one into  a new file, adjusting the contents to read your patterns, and adding it to the makefile.

The name of these files should be consistent, right now it's not, but that will change soon.

The format should be something like:

UniqueName-Location-Pattern.c with a matching header

UniqueName = Manufacturer, vehicle model, engine model, vehicle trim level, year of manufacture, style of sensor, etc
Location = Cam/Crank/Both
Pattern: 
M-N such as 36-2-2-2 (thirty six minus two minus two minus two) where teeth are missing from a consistant pattern
MandN such as 4and1 (four and one) where there are two paterns involved (typically inner and outer on a CAS)
Unique for patterns that are too difficult to describe and suitably unique

When coding these, consider the doxygen comments essential. They should explain the way it works, the vehicles it is suited to, limitations, interface and setting concerns, etc. Web documentation via doxygen will be the golden source for the decoders.

Further decoder coding guidelines will be added at a later date with respect to what you can, can not and must do, and suitable justifications for certain things, etc.

