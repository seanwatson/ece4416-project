import Queue
import bluetooth_connection
import time

bd_addr = "00:06:66:45:1D:50"
port = 1

input = Queue.Queue()
output = Queue.Queue()

btconn = bluetooth_connection.BluetoothConnection(input, output)
btconn.connect(bd_addr, port)
btconn.start()

output.put("herroo\n")
time.sleep(30)

btconn.stop()
btconn.close()

btconn.join()

