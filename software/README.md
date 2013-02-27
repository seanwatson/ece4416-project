Software
=======

Overview
-------------

I have divided the software for this project into client and embedded software:

###Client

- Runs on the user's computer
- Searches for the device
- Automatically connects to the device when it was found
- Translates received commands into mouse movements and clicks on the screen

###Embedded

- Software running on the remote device
- Puts the device into a sleep state until a connection is found
- Once connected it continutally takes accelerometer readings
- Processes the accelerometer readings to determine motions
- Transmits the detected motions to the computer over bluetooth

Please refer to the individual "client" and "embedded" directories for more information.

License
-------------

The software for this work is licensed under an MIT license. Please refer to LICENSE.md for more details.
