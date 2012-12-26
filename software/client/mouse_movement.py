"""
Interface for a mouse movement command

A client can invoke the execute command
to move the mouse according to the type of
MouseMovement
"""

import pymouse


class MouseMovement(object):
    """Interface for creating mouse movements.
    
    Attributes:
        mouse: The mouse object
        screen_size: A tuple of the x and y dimensions of the screen
    """

    def __init__(self):
        """Creates a new mouse object."""
        self.mouse = pymouse.PyMouse()
        self.screen_size = self.mouse.screen_size()

    def execute(self):
        """Abstract method to move the mouse.

        This method must be overridden by the subclass.
        When called it will move the mouse according to
        the type of subclass.
        """
        #TODO(sean): raise an exception if not implemented
        pass

class LeftMouseMovement(MouseMovement):

    def execute(self):
        pos = self.mouse.position()
        if pos[0] > 0:
            self.mouse.move(pos[0] - 1, pos[1])

class RightMouseMovement(MouseMovement):

    def execute(self):
        pos = self.mouse.position()
        if pos[0] < self.screen_size[0]:
            self.mouse.move(pos[0] + 1, pos[1])

class UpMouseMovement(MouseMovement):

    def execute(self):
        pos = self.mouse.position()
        if pos[1] > 0:
            self.mouse.move(pos[0], pos[1] - 1)

class DownMouseMovement(MouseMovement):

    def execute(self):
        pos = self.mouse.position()
        if pos[1] < self.screen_size[1]:
            self.mouse.move(pos[0], pos[1] + 1)

class MouseLeftClick(MouseMovement):

    def execute(self):
        pos = self.mouse.position()
        self.mouse.click(pos[0], pos[1])

class MouseRightClick(MouseMovement):

    def execute(self):
        pos = self.mouse.position()
        self.mouse.click(pos[0], pos[1], 2)