#################### FreeEMS - TRUE DIY Engine Management #####################

For the most up to date inforamation, please see the forums at :

http://www.diyefi.org/forum/

Before using this system, please see the disclaimer here :

www.diyefi.org/disclaimer.htm

Before going any further, please ensure you have the latest release :

http://sourceforge.net/project/showfiles.php?group_id=214452&package_id=258422

If you want to modify and build this firmware there is a guide available :

http://www.diyefi.org/forum/viewtopic.php?f=8&t=508

The docs directory contains a fairly comprehensive set of documentation
describing most aspects of the system. Additionally there is a generated
doxygen page describing the source on the sourceforge site here :

http://freeems.sourceforge.net/doxygen/

Setting up the tuning application is described in the following thread :

http://www.diyefi.org/forum/viewtopic.php?f=43&t=519

Loading the firmware S19 file to the device :

Firstly you will need hcs12mem setup correctly. Install it as normal, then copy
the file mc9s12xdp512.dat from the bin directory to /usr/local/share/hcs12mem/

If you are working on the dev board, you need to flip the load/run switch
to "load" and depress the reset button, prior to flashing.  Return the switch
to the "run" position when complete.

Also in the bin directory is a bash script, use it with the first argument
being your serial device, and the second being your s19 file.

Please post any and all feedback on code, documentation, the system, anything
at all, even subtle and minor stuff to the forums :

http://www.diyefi.org/forum/

Thanks for playing with FreeEMS :-)

Good luck and regards,

Fred.

