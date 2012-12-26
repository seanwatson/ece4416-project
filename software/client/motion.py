
import mouse_movement

class Motion(object):

    def __init__(self):
        self.motions = []
        self.code = 0
        self.position = 0
        self.actions = []

    def move(self):
        for action in self.actions:
            action.execute()

class LeftMotion(Motion):

    def __init__(self):
        super(LeftMotion, self).__init__()
        self.motions = [self]
        self.code = 4
        self.actions = [mouse_movement.LeftMouseMovement()]

class RightMotion(Motion):

    def __init__(self):
        super(RightMotion, self).__init__()
        self.motions = [self]
        self.code = 2
        self.actions = [mouse_movement.RightMouseMovement()]

class ForwardMotion(Motion):

    def __init__(self):
        super(ForwardMotion, self).__init__()
        self.motions = [self]
        self.code = 1
        self.actions = [mouse_movement.DownMouseMovement()]

class BackwardMotion(Motion):

    def __init__(self):
        super(BackwardMotion, self).__init__()
        self.motions = [self]
        self.code = 3
        self.actions = [mouse_movement.UpMouseMovement()]

class NodMotion(Motion):

    def __init__(self):
        super(NodMotion, self).__init__()
        self.motions = [ForwardMotion(), BackwardMotion()]
        self.actions = [mouse_movement.MouseLeftClick()]

class ShakeMotion(Motion):

    def __init__(self):
        super(ShakeMotion, self).__init__()
        self.motions = [LeftMotion(), RightMotion()]
        self.actions = [mouse_movement.MouseRightClick()]

