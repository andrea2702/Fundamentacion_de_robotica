#!/usr/bin/env python
import rospy
from pid_controller.msg import set_point
import numpy as np

if __name__ == '__main__':
    # Set Point Publisher
    sP = rospy.Publisher("set_point", set_point, queue_size=10)
    # Initializing node
    rospy.init_node('setPoint')
    # Getting and setting noderate from parameters
    r = rospy.get_param("/setPoint_noderate", 100)
    rate = rospy.Rate(r)
    # Getting signal amplitude from parameters
    a = rospy.get_param("/setPoint_amplitude", 10)
    # Node loop
    while not rospy.is_shutdown():
        # Creating new set point message
        msg = set_point()
        # Setting msg time to current time
        msg.time = rospy.get_time()
        # Creating sinusoidal signal with param amplitude from current time
        msg.set_point = a*np.sin(rospy.get_time())
        # Publishing message
        sP.publish(msg)
        # Loop sleep
        rate.sleep()