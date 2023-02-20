#!/usr/bin/env python2
import rospy
from std_msgs.msg import Float32
import numpy as np

time = 0
signal = 0
prev = 0

def timeCallBack(msg):
    global time
    time = msg.data

def signalCallBack(msg):
    global signal
    global prev
    signal = msg.data
    signalTransform = (np.cos(2*np.pi/3)*signal + np.sign(signal-prev)*np.sqrt(1-signal*signal)*np.sin(2*np.pi/3)) / 2 + 1
    proc_signal.publish(signalTransform)
    rospy.loginfo(signalTransform)
    prev = signal

if __name__ == '__main__':
    proc_signal = rospy.Publisher("proc_signal", Float32, queue_size=10)
    rospy.init_node('process')
    rospy.Subscriber("time", Float32, timeCallBack)
    rospy.Subscriber("signal", Float32, signalCallBack)
    rospy.spin()
