"""
Handles incoming motion commands and translates them to actions.
"""

import threading
import time

class MotionHandler(threading.Thread):
    """Translates motion commands to actions.

    When a new motion command is received over the wireless
    connection it is consumed by the MotionHandler. The 
    MotionHandler then scans through the motions it has been
    set up to detect trying to match the command to the motions.
    If a match is found and that motion is completed the corresponding
    action is executed.

    Attributes:
        motion_queue: A Queue for incoming motion commands.
        motions: The motions that should be detected
        kill: A boolean flag for stopping the thread
        timeout: The amount of time in seconds a composite motion is
                 allowed to take
    """

    def __init__(self, motion_queue):
        """Initializes a new MotionHandler.

        Args:
            motion_queue: A queue where the incoming commands will be placed
        """
        threading.Thread.__init__(self)
        self.motion_queue = motion_queue
        self.motions = []
        self.kill = False
        self.timeout = 1

    def run(self):
        """The main thread process.

        Waits for commands to be received, processes them and calls the
        appropriate actions when necessary.
        """
        start = time.time()
        while not self.kill:
            code = int(self.motion_queue.get(True))  # Blocking get call

            # Reset all motions if stationary for too long
            if(time.time() - start > self.timeout):
                for mot in self.motions:
                    mot.position = 0

            # Check the code against the handled motions
            for mot in self.motions:
                # Check if it matches the next code in the motion
                if code == mot.motions[mot.position].code:
                    # If the motion is done, preform the movement
                    if mot.position == len(mot.motions) - 1:
                        mot.position = 0
                        mot.move()
                    # Otherwise start looking for the next motion
                    else:
                        mot.position += 1
                # Reset the position for a wrong motion
                else:
                    mot.position = 0

            self.motion_queue.task_done()
            start = time.time()
    
    def stop(self):
        """Stops the thread."""
        self.kill = True
        self.motion_queue.put(0)    # Needed to get out of blocking call

    def add_motion(self, mot):
        """Adds a motion to detect.

        Once added the handler will try to detect this motion.
        Duplicate motions are allowed, but it will cause the action
        to get executed multiple times for each detection.

        Args:
            The new motion to be detected.
        """
        self.motions.append(mot)
