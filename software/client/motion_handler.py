
import threading

class MotionHandler(threading.Thread):

    def __init__(self, motion_queue):
        threading.Thread.__init__(self)
        self.motion_queue = motion_queue
        self.motions = []
        self.kill = False

    def run(self):
        while not self.kill:
            code = self.motion_queue.get(True)  # Blocking get call
            for mot in self.motions:
                if code == mot.codes[0]: #TODO: handle composites
                    mot.move()
            self.motion_queue.task_done()
    
    def stop(self):
        self.kill = True
        self.motion_queue.put(0)    # Needed to get out of blocking call

    def add_motion(self, mot):
        self.motions.append(mot)
