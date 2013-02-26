"""
The main client for my ece4416 project.

The client creates an input and output queue, sets
up a bluetooth connection to handle the wireless
communication and a motion handler to handle incoming
commands.

Copyright (c) 2013 Sean Watson
Licensed under the MIT license
 
"""

import Queue
import sys
import time
import logging
import motion_handler
import motion
import bluetooth_connection


def main():

    # Set up logging
    logging.basicConfig(level=logging.INFO)
	
    # Bluetooth connection parameters
    dev_name = "ProjectDevBoard"

    in_q = Queue.Queue()
    out_q = Queue.Queue()

    print "Creating motion handler..."
    handler = motion_handler.MotionHandler(in_q)
    handler.add_motion(motion.LeftMotion())
    handler.add_motion(motion.RightMotion())
    handler.add_motion(motion.ForwardMotion())
    handler.add_motion(motion.BackwardMotion())
    handler.add_motion(motion.FastLeftMotion())
    handler.add_motion(motion.FastRightMotion())
    handler.add_motion(motion.FastForwardMotion())
    handler.add_motion(motion.FastBackwardMotion())
    handler.add_motion(motion.NodMotion())
    handler.add_motion(motion.ShakeMotion())
    print "Created. Detecting left, right, forward, backward, nod, shake."
    
    btconn = bluetooth_connection.BluetoothConnection(dev_name, in_q, out_q)

    print "Starting Bluetooth communication..."
    btconn.start()
    print "Communication started."

    print "Starting motion handler..."
    handler.start()
    print "Started."

    raw_input("Press enter to finish...")

    print "Stopping Bluetooth communication..."
    btconn.stop()
    print "Stopped."

    btconn.join()
    print "Bluetooth successfully finished."

    print "Stopping motion handler..."
    handler.stop()
    print "Stopped."

    handler.join()
    print "Motion handler successfully finished."

if __name__ == '__main__':
    main()
