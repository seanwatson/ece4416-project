Client
====

Files
-------

- **ece4416-project.py** - The main application for this project
- **bluetooth_connection.py** - Manages the bluetooth communication between the computer and the device
- **motion_handler.py** - Translates the received "motion codes" into mouse movements and clicks
- **motion.py** - Different motions that can be detected by the device
- **mouse_movement.py** - Different mouse actions that can be preformed when a motion is detected

Dependencies
-------------

- python-pybluez (bluetooth socket handling)
- python-pymouse (mouse movement and clicking)
