
import threading
import time

class MotionHandler(threading.Thread):

    def __init__(self, motion_queue):
        threading.Thread.__init__(self)
        self.motion_queue = motion_queue
        self.motions = []
        self.kill = False
        self.timeout = 1

    def run(self):
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
        self.kill = True
        self.motion_queue.put(0)    # Needed to get out of blocking call

    def add_motion(self, mot):
        self.motions.append(mot)
