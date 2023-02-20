#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32
import numpy as np

if __name__ == '__main__':
    signal = rospy.Publisher("signal", Float32, queue_size=10)
    time = rospy.Publisher("time", Float32, queue_size=10)
    rospy.init_node('signal_generator')
    rate = rospy.Rate(100)
    initTime = rospy.get_time()
    currentTime = initTime
    while not rospy.is_shutdown():
        currentTime = rospy.get_time() - initTime
        signal.publish(np.sin(currentTime))
        rospy.loginfo(np.sin(currentTime))
        time.publish(currentTime)
        rate.sleep()
