import Queue
import motion_handler
import motion
import bluetooth_connection

bd_addr = "00:06:66:45:1D:50"
port = 1

input = Queue.Queue()
output = Queue.Queue()

print "Creating motion handler..."
handler = motion_handler.MotionHandler(input)
handler.add_motion(motion.LeftMotion())
handler.add_motion(motion.RightMotion())
handler.add_motion(motion.ForwardMotion())
handler.add_motion(motion.BackwardMotion())
handler.add_motion(motion.NodMotion())
print "Created. Detecting left, right, forward, backward, nod, shake."

print "Starting motion handler..."
handler.start()
print "Started."

btconn = bluetooth_connection.BluetoothConnection(input, output)
print "Connecting to Bluetooth device..."
btconn.connect(bd_addr, port)
print "Connected."

print "Starting Bluetooth communication..."
btconn.start()
print "Communication started."

raw_input("Press enter to finish...")

print "Stopping Bluetooth communication..."
btconn.stop()
print "Stopped."

print "Closing Bluetooth connection..."
btconn.close()
print "Closed."

btconn.join()
print "Bluetooth successfully finished."

print "Stopping motion handler..."
handler.stop()
print "Stopped."

handler.join()
print "Motion handler successfully finished."

