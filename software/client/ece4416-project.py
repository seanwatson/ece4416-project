"""
The main client for my ece4416 project.

The client creates an input and output queue, sets
up a bluetooth connection to handle the wireless
communication and a motion handler to handle incoming
commands.
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
    logging.basicConfig(level=logging.DEBUG)
	
    # Bluetooth connection parameters
    dev_name = "ProjectDevBoard"
    port = 1

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
    
    btconn = bluetooth_connection.BluetoothConnection(in_q, out_q)

    print "Searching for Bluetooth device..."
    bt_addr = btconn.search(dev_name)
    if bt_addr != None:
        print "Device found: ", bt_addr
    else:
        print "Device not found. Quitting."
        sys.exit(1)

    print "Connecting to Bluetooth device..."
    if btconn.connect(bt_addr, port):
        print "Connected."
    else:
        print "Unable to connect to device. Quitting."
        sys.exit(1)
    
    print "Starting Bluetooth communication..."
    btconn.start()
    print "Communication started."

    print "Waking device..."
    cnt = 0
    while(in_q.empty() and cnt < 20):
        out_q.put("%CONNECT")
        cnt = cnt + 1
        time.sleep(0.5)
    if cnt < 20:
        in_q.get()
        in_q.task_done()
        print "Device is awake."
    else:
        print "Unable to wake device. Quitting."
        btconn.stop()
        btconn.join()
        sys.exit(1)

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
