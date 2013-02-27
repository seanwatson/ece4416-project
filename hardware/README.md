Hardware
========

Overview
--------

The hardware consists of a microcontroller, a bluetooth module, an accelerometer, and power management circuitry:

###Microcontroller

- Atmel ATMega32U4
- Programming and debugging over USB port
- UART, ADC
- Deep sleep for power saving

###Bluetooth Module

- Roving Networks RN-42
- Communicates with MCU over UART
- Low power connect, SNIFF mode for power saving

###Accelerometer

- Analog Devices ADP3338
- 3 axis, analog outputs
- Very low power

###Power Management

- 850mA LiPo battery
- 3.3V linear regulator
- LiPo charge controller on board
- Charges over USB

Revisions
---------

The hardware for this project was developed over two revisions:

###Revision 1
- Designed as a development and debugging board for the purpose of easily diagnosing and fixing any bugs.
- Larger parts
- Debugging LEDs
- Debugging jumpers, etc. for the purpose of easily diagnosing and fixing any bugs.

###Revision 2
- Stripped down version of the circuit
- Lower power consumption
- Smaller physical size
- Smaller parts and no debugging features
- Can be concealed within a baseball cap

License
-------

These designs are licensed under a Creative Commons Attribution 3.0 license. See the
LICENSE.txt file for more details.

Acknowledgements
----------------

I'd like to thank the following companies who provided free or discount products and/or services
as part of this school project:

- Alberta Printed Circuits
- Analog Devices
- Atmel
- Microchip
- Roving Networks
