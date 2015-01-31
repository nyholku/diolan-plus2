## diolan-plus2 -- Diolan bootloader with standard instruction set

Dialoan bootloader is an excellent bootloader that allows updating the firmware of Microchip PIC18 based device via USB.


Diolan-plus2 is the  Diolan bootloader for PIC18 family of devices with all the features intact modified to use the standard (non extended aka legacy) instructions set and still fit in the 2 kB bootblock.

The code was originally ported to PIC18F450 and modified to use the standard instruction set in order to be compatible with the [SDCC](http://sdcc.sourceforge.net) compiler and to support my [EasyCNC Project](http://www.sparetimelabs.com/eazycnc/welcome/welcome.php).

It was originally created by the Israely company Diolan that gracefully licensed it under GPL 3.0 .

You can read all about it here:

[http://usb-pic.org/usb-pic-bootloader](http://usb-pic.org/usb-pic-bootloader)

and get the original code from here:

[https://diolan.com/pic-bootloader](https://diolan.com/pic-bootloader)

There are lots of bootloaders available for PIC USB devices; what sets Dialan apart is that it is coded in assembly language to fit in the 2kB bootblock of many PIC devices and that it supports encrypted firmware updates which is mandatory for many commercial projects.

However it has one overriding problem -- it is written to take advantage of the Extended Instruction Set (EIS) available with PIC18 family of devices. This creates a problem because the device always boots up in either 'legacy' or EIS mode and that cannot be changed on the fly. If the bootloader starts in EIS then the 'application' code also needs to be written to work with it. And that is a problem, since *no supported C-compilers for EIS are available* and the EIS seems to be abandoned by Microchip.

Dangerous Prototypes has released a modified bootloader they call 'Diolan Plus'. 

You can find the code here:

[Dangerous Prototypes 'diolan plus' source code](http://code.google.com/p/dangerous-prototypes-open-hardware/source/browse/#svn%2Ftrunk%2FBootloaders%2FUSB-HID-Diolan)

and the documentation here:

[Dangerous Prototypes 'diolan plus readme.pdf'](https://github.com/nyholku/diolan-plus2/blob/master/references/diolan%20plus%20readme.pdf?raw=true)


That (diolan plus) is an excellent port of this project that works with most PIC USB devices but it leaves out the encryption making it unsuitable for many commercial projects or projects that need to have some secret key embedded in the firmware. 

This project, diolan-plus2, seeks to provide the best of both i.e. it provides all the original features and runs in standard (non extended) instruction set mode allowing the application code to be written with the nice Free SDCC compiler or with Microchip's own commercial XC8 compiler.

Out-of-the box this project is usable with PIC18F4550 using 4 MHz crystal with Mac OS X and Microchip's MPLAB X and PICKit 2.

See building and porting for suggestions on how to build the bootloader with other compilers, under other operating systems or for other devices.

The Dangerous Prototypes' project also cleaned the original project's build system to make it easier to use the bootloader with other processors. Those changes are not incorporated (yet) to this project.



