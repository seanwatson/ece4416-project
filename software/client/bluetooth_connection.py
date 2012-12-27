"""
Maintains a connection to a bluetooth device and handles
all reads and writes to the socket.
"""
#TODO(sean): connection retries on fails

import threading
import bluetooth
import time

class BluetoothConnection(threading.Thread):
    """Connects to a bluetooth device and allows
    for asynchronous sending and receiving over SPP.

    Attributes:
        read_queue: A Queue to place received bytes in
        write_queue: A Queue of bytes to be written out
        sock: The BluetoothSocket handling the connection.
        kill: Boolean used to stop the thread
    """

    def __init__(self, read_queue, write_queue):
        """Initializes a new BluetoothConnection with the passed params."""
        threading.Thread.__init__(self)
        self.read_queue = read_queue
        self.write_queue = write_queue
        self.sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
        self.kill = False

    def run(self):
        """Handles sending and receiving over bluetooth.

        Asynchronously handles sending and receiving over the
        bluetooth connection. When characters are added to the
        write buffer they are written out over the socket.
        Similarly when bytes are received they are put in the
        read buffer for use by a client.
        """
        while not self.kill:

            # Handle any necessary writing
            while not self.write_queue.empty():
                output = self.write_queue.get()
                self.sock.send(output)
                self.write_queue.task_done()

            # Handle any necessary reading
            rec = None
            try:
                rec = self.sock.recv(256)
            except bluetooth.BluetoothError:
                pass
            while rec != None:
                self.read_queue.put(rec, True)  # Blocking call
            
            time.sleep(0.1)

    def connect(self, addr, port):
        """Connects the socket.
        
        Args:
            addr: The MAC address of the bluetooth device.
            port: The port number to connect the socket to.
        """
        self.sock.connect((addr,port))
        self.sock.setblocking(False)

    def stop(self):
        """Stops the thread from running."""
        time.sleep(1)       # Delay needed to flush send buffer
        self.kill = True

    def close(self):
        """Closes the socket."""
        self.sock.close()

    def is_running(self):
        """Returns the status of the thread

        Returns:
            True if the thread is running, false otherwise.
        """
        return self.is_alive()
