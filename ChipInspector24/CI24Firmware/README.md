Chip Inspector 24 Firmware
==========================

The firmware is built and programmed with 
[Teensyduino](https://www.pjrc.com/teensy/td_download.html).

Teensyduino version 1.53
Arduino version 1.8.13

Operation
---------

To operate the Chip Inspector 24, connect the Teensy to 
computer, then run a serial terminal to communicate with
the board. The serial terminal in the Arduino environment
may be used. 

Chip Inspector 23 is controlled with the following commands
from the serial terminal.

**`logicdump <device pin count>`**

For example, `logicdump 20`. 

This command will attempt to apply every possible combination
of inputs to every non-power pin of the inserted device. Inputs 
are driven through a 10K resistor. For every combination of inputs,
the levels on the device pins are read back. Every combination 
attempted inputs and actual pin values are then output to the 
serial terminal.

Before the logic dump begins, the device is powered up and a
current test is applied. The test will be halted if excessive
current consumption is detected.
