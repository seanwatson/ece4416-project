"""
Defines classes for different types of motions.

Each motion is a subclass of a general motion class.
There are 4 primary motions: left, right, forward,
and backward. Each primary motion has a "code" associated
with it. This is the code that the wireless device transmits
to signal that that type of motion has occoured.
Composite motions or "gestures" can be made up by a sequence
of these primary motions.

Motion codes:
    0: Reserved. No motion can use this code
    1: Forward
    2: Right
    3: Backward
    4: Left
"""

import mouse_movement

class Motion(object):
    """A general motion.

    Attributes:
        motions: A list of the necessary motions required to
                 complete the whole motion.
        code: The wireless code associated with the motion.
        position: The next motion that needs to be found in
                  order for this motion to be completed.
        actions: A list of actions to be preformed when the
                 motion is successfully completed.
    """

    def __init__(self):
        """Initializes all member attributes."""
        self.motions = []
        self.code = 0
        self.position = 0
        self.actions = []

    def move(self):
        """Preforms all of the actions associated with the motion.

        All of the actions in the actions list are iterated through
        and the execute method is called on each one to preform that
        action.
        """
        for action in self.actions:
            action.execute()

class LeftMotion(Motion):
    """A primary motion for tilting the head to the left."""

    def __init__(self):
        """Initializes a new LeftMotion.

        The only required motion is one tilt to the left.
        Code for a left motion is 4.
        The action is to move the mouse to the left.
        """
        super(LeftMotion, self).__init__()
        self.motions = [self]
        self.code = 4
        self.actions = [mouse_movement.LeftMouseMovement()]

class RightMotion(Motion):
    """A primary motion for tilting the head to the right."""

    def __init__(self):
        """Initializes a new RightMotion.

        The only required motion is one tilt to the right.
        Code for a right motion is 2.
        The action is to move the mouse to the right.
        """
        super(RightMotion, self).__init__()
        self.motions = [self]
        self.code = 2
        self.actions = [mouse_movement.RightMouseMovement()]

class ForwardMotion(Motion):
    """A primary motion for tilting the head forwards."""

    def __init__(self):
        """Initializes a new ForwardMotion.

        The only required motion is one tilt forwards.
        Code for a forward motion is 1.
        The action is to move the mouse downwards.
        """
        super(ForwardMotion, self).__init__()
        self.motions = [self]
        self.code = 1
        self.actions = [mouse_movement.DownMouseMovement()]

class BackwardMotion(Motion):
    """A primary motion for tilting the head backwards."""

    def __init__(self):
        """Initializes a new BackwardMotion.

        The only required motion is one tilt backwards.
        Code for a backward motion is 3.
        The action is to move the mouse upwards.
        """
        super(BackwardMotion, self).__init__()
        self.motions = [self]
        self.code = 3
        self.actions = [mouse_movement.UpMouseMovement()]

class NodMotion(Motion):
    """A composite motion for nodding the head."""

    def __init__(self):
        """Initializes a new NodMotion.

        The required motions are a tilt forward then backward.
        As a composite motion it has no code.
        The action is to left click the mouse.
        """
        super(NodMotion, self).__init__()
        self.motions = [ForwardMotion(), BackwardMotion()]
        self.actions = [mouse_movement.MouseLeftClick()]

class ShakeMotion(Motion):
    """A composite motion for shaking the head."""

    def __init__(self):
        """Initializes a new ShakeMotion.

        The required motions are a tilt to the left then the right.
        As a composite motion it has no code.
        The action is to right click the mouse.
        """
        super(ShakeMotion, self).__init__()
        self.motions = [LeftMotion(), RightMotion()]
        self.actions = [mouse_movement.MouseRightClick()]

