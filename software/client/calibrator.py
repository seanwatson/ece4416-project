"""
Calibraton utility for ECE 4416 project.

Prompts the user to move their head into the desired
positions that will trigger each type of movement and
signals the device to store the current orientation into
non-volatile storage.

Copyright (c) 2013 Sean Watson
Licensed under the MIT license

"""

import Queue
import motion
import bluetooth_connection
import sys
import logging
import string
import threading
import time

class BluetoothPrinter(threading.Thread):
    
    def __init__(self, in_queue):
        threading.Thread.__init__(self)
        self.in_queue = in_queue
        self.kill = False
        self.timeout = 1

    def run(self):
        rec = ""
        while not self.kill:
            rec += str(self.in_queue.get(True))
            if len(rec) > 10:
                sys.stdout.write("Angles: %s   \r" % (string.replace(rec, '\n', '')))
                sys.stdout.flush()
                rec = ""

    def stop(self):
        self.kill = True
        self.in_queue.put(0)

def main():
    
    logging.basicConfig(level=logging.INFO)

    # Bluetooth connection parameters
    dev_name = "ProjectDevBoard"
    port = 1

    in_q = Queue.Queue()
    out_q = Queue.Queue()

    printer = BluetoothPrinter(in_q)
    btconn = bluetooth_connection.BluetoothConnection(dev_name, in_q, out_q, False)

    """
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
    """
    printer.start()
    btconn.start()

    while(btconn.connected == False):
        time.sleep(1)

    out_q.put('+')
    print "\n"
    raw_input("Move your head slightly forward and hit Enter when ready...\n")
    out_q.put(motion.ForwardMotion().code)
    print "Forward motion calibrated."
    
    out_q.put('+')
    raw_input("Move your head more forward and hit Enter when ready...\n")
    out_q.put(motion.FastForwardMotion().code)
    print "Fast forward motion calibrated."
    
    out_q.put('+')
    raw_input("Move your head slightly right and hit Enter when ready...\n")
    out_q.put(motion.RightMotion().code)
    print "Right motion calibrated."
    
    out_q.put('+')
    raw_input("Move your head more right and hit Enter when ready...\n")
    out_q.put(motion.FastRightMotion().code)
    print "Fast right motion calibrated."
    
    out_q.put('+')
    raw_input("Move your head slightly backward and hit Enter when ready...\n")
    out_q.put(motion.BackwardMotion().code)
    print "Backward motion calibrated."
    
    out_q.put('+')
    raw_input("Move your head more backward and hit Enter when ready...\n")
    out_q.put(motion.FastBackwardMotion().code)
    print "Fast backward motion calibrated."
    
    out_q.put('+')
    raw_input("Move your head slightly left and hit Enter when ready...\n")
    out_q.put(motion.LeftMotion().code)
    print "Left motion calibrated."
    
    out_q.put('+')
    raw_input("Move your head more left and hit Enter when ready...\n")
    out_q.put(motion.FastLeftMotion().code)
    print "Fast left motion calibrated."

    print "Stopping Bluetooth communication..."
    btconn.stop()
    printer.stop()
    print "Stopped."

    printer.join()
    btconn.join()
    print "Bluetooth successfully finished."
    
    print "Done."

if __name__ == '__main__':
    main()
