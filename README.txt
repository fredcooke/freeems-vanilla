#################### FreeEMS - TRUE DIY Engine Management #####################

For the most up to date inforamation, please see the forums at :

http://www.diyefi.org/forum/

Before using this system, please see the disclaimer here :

www.diyefi.org/disclaimer.htm

Before going any further, please ensure you have the latest release or latest code by visiting :

http://github.com/fredcooke/freeems-vanilla

If you want to modify and build this firmware there an out-of-date guide available :

http://www.diyefi.org/forum/viewtopic.php?f=8&t=508

For all your documenation needs please see the docs page :

http://docs.freeems.org

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

