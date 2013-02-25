"""
Calibraton utility for ECE 4416 project.

Prompts the user to move their head into the desired
positions that will trigger each type of movement and
signals the device to store the current orientation into
non-volatile storage.

"""

import Queue
import motion
import bluetooth_connection

def main():

    # Bluetooth connection parameters
    dev_name = "ProjectDevBoard"
    port = 1

    in_q = Queue.Queue()
    out_q = Queue.Queue()

    btconn = bluetooth_connection.BluetoothConnection(dev_name, in_q, out_q)

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

    btconn.start()

    raw_input("Move your head slightly forward and hit Enter when ready...")
    out_q.put('+')
    out_q.put(motion.ForwardMotion().code)
    print "Forward motion calibrated."
    
    raw_input("Move your head more forward and hit Enter when ready...")
    out_q.put('+')
    out_q.put(motion.FastForwardMotion().code)
    print "Fast forward motion calibrated."
    
    raw_input("Move your head slightly right and hit Enter when ready...")
    out_q.put('+')
    out_q.put(motion.RightMotion().code)
    print "Right motion calibrated."
    
    raw_input("Move your head more right and hit Enter when ready...")
    out_q.put('+')
    out_q.put(motion.FastRightMotion().code)
    print "Fast right motion calibrated."
    
    raw_input("Move your head slightly backward and hit Enter when ready...")
    out_q.put('+')
    out_q.put(motion.BackwardMotion().code)
    print "Backward motion calibrated."
    
    raw_input("Move your head more backward and hit Enter when ready...")
    out_q.put('+')
    out_q.put(motion.FastBackwardMotion().code)
    print "Fast backward motion calibrated."
    
    raw_input("Move your head slightly left and hit Enter when ready...")
    out_q.put('+')
    out_q.put(motion.LeftMotion().code)
    print "Left motion calibrated."
    
    raw_input("Move your head more left and hit Enter when ready...")
    out_q.put('+')
    out_q.put(motion.FastLeftMotion().code)
    print "Fast left motion calibrated."

    print "Stopping Bluetooth communication..."
    btconn.stop()
    print "Stopped."

    btconn.join()
    print "Bluetooth successfully finished."
    
    print "Done. Restart the device for the new readings to take effect."

if __name__ == '__main__':
    main()
