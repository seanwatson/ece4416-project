"""
Maintains a connection to a bluetooth device and handles
all reads and writes to the socket.
"""

import threading
import bluetooth
import time
import logging

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
        logging.debug("BluetoothConnection created. Read %s, Write %s, Sock %s",
            self.read_queue, self.write_queue, self.sock)

    def run(self):
        """Handles sending and receiving over bluetooth.

        Asynchronously handles sending and receiving over the
        bluetooth connection. When characters are added to the
        write buffer they are written out over the socket.
        Similarly when bytes are received they are put in the
        read buffer for use by a client.
        """
        logging.info("BlueoothConnection thread started")
        while not self.kill:

            # Handle any necessary writing
            while not self.write_queue.empty():
                output = str(self.write_queue.get())
                self.sock.send(output)
                self.write_queue.task_done()
                logging.debug("Wrote to bluetooth: %s", output)

            # Handle any necessary reading
            try:
                rec = self.sock.recv(256)
                if len(rec) > 0:                    # Prevents empty chars
                    self.read_queue.put(rec, True)  # Blocking call
                logging.debug("Received from bluetooth: %s", rec)
            except bluetooth.BluetoothError:
                pass
            
            time.sleep(0.001)
        
	    # Close the socket before finishing
        self.sock.close()
        logging.info("BluetoothConnection thread stopped")

    def connect(self, addr, port):
        """Connects the socket.

        Will make up to "max_attempts" tries to open a
        socket to the given address. If it is still unable
        to open a connection after "max_attempts" it will
        give up.
        
        Args:
            addr: The MAC address of the bluetooth device.
            port: The port number to connect the socket to.
		
       Returns:
            True if a successful connection was made. False
            otherwise.
        """
        max_attempts = 3
        
        while max_attempts > 0:
            try:
                self.sock.connect((addr,port))
                break
            except bluetooth.BluetoothError:
                max_attempts = max_attempts - 1
                self.sock = bluetooth.BluetoothSocket(bluetooth.RFCOMM)
                logging.warning("Failed to connect. Attempts remaining: %s",
                    max_attempts)

        if max_attempts > 0:
            self.sock.setblocking(False)
            logging.info("Connected to Bluetooth: %s", addr)
            return True
        else:
            logging.error("Failed to connect to device")
            return False

    def search(self, name):
        """Searches nearby devices for a given name.

        Args:
            name: The name of the device to search for.

        Returns:
            The MAC address of the device with the given
            name if it was found. Otherwise returns None
        """
        nearby_devices = bluetooth.discover_devices()

        max_attempts = 3
        
        while max_attempts > 0:
            
            for addr in nearby_devices:
                logging.info("Found device: %s", addr)
                if bluetooth.lookup_name(addr) == name:
                    logging.info("Device %s is %s", addr, name)
                    return addr
            logging.warning("Device not found. Attempts remaining: %s",
                    max_attempts)
            
            max_attempts = max_attempts - 1

        return None

    def stop(self):
        """Stops the thread from running."""
        time.sleep(0.01)       # Delay needed to flush send buffer
        self.kill = True
        logging.info("Killing Bluetooth connection")
