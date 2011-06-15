# FreeEMS - TRUE DIY Engine Management

### Introduction

FreeEMS - The open source engine management system!

Please see [FreeEMS.org](http://freeems.org) for the most up to date inforamation and links!

Before using FreeEMS read the [disclaimer](http://www.diyefi.org/disclaimer.htm)!

### Building the firmware

Ensure that you have the latest release or latest code from the [github repository](http://github.com/fredcooke/freeems-vanilla).

To build this firmware you need the latest build environment from the [tools site](http://tools.diyefi.org).

### Loading the firmware

**Please note**: hcs12mem is no longer capable of loading the firmare unassisted.

You need either FreeEMS Loader or mtxloader. The former is a standalone app,
and the latter is packaged with MTX.

If you are working on the dev board, you need to flip the load/run switch
to "load" and depress the reset button, or send a reset packet, prior to
flashing.  Return the switch to the "run" position when complete.

### Tuning your FreeEMS

Tuning is currently done with a combination of techniques. For the full story
check out [this thread](http://forum.diyefi.org/viewtopic.php?f=54&t=1166)
and the threads that it links to.

### Footnote

Please post any and all feedback on code, documentation, the system, anything
at all, even subtle and minor stuff to [the forum](http://forum.diyefi.org).

Thanks for playing with FreeEMS :-)

Good luck and regards,

Fred.

