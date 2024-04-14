WD76UTIL
========

This is a DOS utility for controlling and inspecting the [WD7600 family of chipsets](https://theretroweb.com/chipsets/590), included on a handful of Intel 286, 386, and 486 motherboards by Compaq, Dell, IBM, and Packard Bell (among others).

I created this utility because on the IBM/Sega Tera Drive, and likely other systems, there is no BIOS configuration menu to speak of, and the chipset supports many more configuration options than are actually utilized by the BIOS POST process. For example, on the Tera Drive, the RA9 and RA10 pins of the SIMM sockets are left floating, but the chipset is capable of utilizing these if they're connected properly and the RAM being used is wired correctly. Note that the A9/A10 pins of the SIMM socket have a "sense" purpose on the PC platform, and a _different_ sense purpose on some IBM hardware, but other systems (Apple, Amiga) that support DRAMs >1Mbit in 30 pin SIMMs use these pins as this chipset expects, so not all memory is supported. This is probably the reason these pins are left floating on this board. As this utility is developed, I will be able to document the exact procedure required to get more memory added to this system, and hopefully it will apply to other systems.

Another thing to note is that the WD76C10 treats two SIMM slots as one 16-bit bank of memory, meaning that you must install memory in pairs of identical size and configuration.

TODO
----

* [ ] Support getting all memory-related configuration (including timings)
* [ ] Support getting all CPU-related configuration
* [ ] Support getting all EMS-related configuration
* [ ] Create a DOS .SYS driver that will reconfigure the bank size and location to allow for more RAM than is supported by the BIOS
