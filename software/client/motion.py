
import mouse_movement

class Motion(object):

    def __init__(self):
        self.codes = []
        self.actions = []

    def move(self):
        for action in self.actions:
            action.execute()

class LeftMotion(Motion):

    def __init__(self):
        self.codes = [444]
        self.actions = [mouse_movement.LeftMouseMovement()]

class RightMotion(Motion):

    def __init__(self):
        self.codes = [222]
        self.actions = [mouse_movement.RightMouseMovement()]

class ForwardMotion(Motion):

    def __init__(self):
        self.codes = [111]
        self.actions = [mouse_movement.DownMouseMovement()]

class BackwardMotion(Motion):

    def __init__(self):
        self.codes = [333]
        self.actions = [mouse_movement.UpMouseMovement()]

class NodMotion(Motion):

    def __init__(self):
        self.codes = [111, 333]
        self.actions = []   #TODO: mouse click or something

class ShakeMotion(Motion):

    def __init__(self):
        self.codes = [444, 222]
        self.actions = []   #TODO: some other command

