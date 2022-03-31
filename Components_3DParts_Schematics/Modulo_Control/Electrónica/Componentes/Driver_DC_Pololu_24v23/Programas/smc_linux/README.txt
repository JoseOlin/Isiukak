Pololu Simple Motor Controller Software

Release Date: 2010-11-19
http://www.pololu.com/


== Summary ==

This binary release contains the Pololu Simple Motor Control Center
(SmcCenter) and the Simple Motor Controller command-line utility
(SmcCmd).  These programs allow you to configure and control the
Simple Motor Controller over USB.


== Prerequisites ==

You will need to download and install these packages:

  libusb-1.0-0-dev mono-runtime libmono-winforms2.0-cil

In Ubuntu, you can do this with the command:

  sudo apt-get install libusb-1.0-0-dev mono-runtime libmono-winforms2.0-cil


== USB Configuration ==

You will need to copy the file 99-pololu.rules to /etc/udev/rules.d/
in order to grant permission for all users to use Pololu USB devices.
If you already plugged in a Pololu USB device, you should unplug it at
this point so the new permissions will get applied later when you plug
it back in.


== Running the programs ==

You can run the programs by typing one of the following commands:

   ./SmcCenter
   ./SmcCmd

O alternativamente: 
   $ mono ./SmcCenter

If you get an error message that says "cannot execute binary file",
then try running the program with the mono runtime, for example:

   mono ./SmcCmd

(si no encuentra la tarjeta correr con sudo)

== Source Code ==

The C# source code for SmcCmd will be available in the Pololu USB
Software Development Kit, available at:

  http://www.pololu.com/docs/0J41


== Contact Us ==

If you have any questions, please contact us by visiting:
  http://www.pololu.com/contact
