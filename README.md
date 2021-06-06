# FreeEMS - TRUE DIY Engine Management

### Introduction

FreeEMS - The open source engine management system!

### But FreeEMS Is Abandoned!

No, no it's not. Far from it:

* There's still half a dozen cars, some daily driven, running FreeEMS.
* There's still occasional active development on both experimental versions of the firmware and supporting tools
* The community around it lives on on IRC (both Freenode and Libera.chat, for now)

### But FreeEMS Is Not Open Source!

Yes, yes it is. FreeEMS firmware is licensed under the terms of the GPL and always was.

### But Where Is The Latest Code??? Liar!

Code exists in the following forms:

1. Github slightly stale version - fully public - no one uses this AFAIK but it is functional
2. Gitlab slightly updated version - available to genuine users only - I run this on one of my cars, dog fooding
3. More recent unfinished work - available to developers of that work, and their testers who understand the risks, only
4. Various branches with various innovations, improvements, and features - all close, some usable, none finished, none released

The flow of code, is, and always has been, something like this:

1. An idea forms when faced with a problem or situation that current code does not address
2. The idea is discussed with other active firmware devs
3. Some pseudo code is written to further solidify the ideas
4. Firmware is implemented in line with the pseudo code and both are iterated until it works on the bench
5. Trial on developers' vehicles/engines - if bad, more iterations, otherwise...
6. Trial on testers' vehicles/engines - typically S19 sent with precanned tune, sometimes branch sent with instructions, tester loads S19 and performs testing, starts, idles, drives, measures things, whatever, then reports back
7. Code appears to work well, a branch called "futuredev" is pushed to (ff only) and every genuine user benefits
8. When a good number of people have updated and are running it, that branch is pushed to master

If you're keen to be a part of that cycle at any level, please do get in touch. The team is still happy to work with people and help them through their journey to engine control freedom.

### Then It's NOT Open Source

You don't understand what the words mean, with all due respect, go and educate yourself.

### But Why?

I'm all for open source, I've both used it and supported it for over half of my life at this point. Great code comes from people with skill and imagination, not copy cats. Pushing unfinished ideas to places where unoriginal leeches can study and copy it does no one any good. Better for them to learn for themselves through experience over time than to just copy everything. Note, FreeEMS remains the only original free and open source ECU with its own bespoke, documented, standardised, and open protocol and associated tuning software. The other two both use, or at least used to use, the Megasquirt protocol and proprietary tuning software.

One day all of this will be pushed to Github, despite Microsoft's involvement, and it'll become very clear which system has genuine innovation and quality outcomes as a result. Until then, enjoy this README file :-)
