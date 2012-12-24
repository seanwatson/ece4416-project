'''
Searches for nearby devices and prints the name and MAC address of
any devices it finds

Based on example code from MIT bluetooth programming in python
people.csail.mit.edu/albert/bluez-intro/c212.html
'''

import bluetooth

print "Searching..."
nearby_devices = bluetooth.discover_devices()

for bdaddr in nearby_devices:
    print 'Name: %s, MAC: %s' % (bluetooth.lookup_name(bdaddr), bdaddr)

print "Done."
