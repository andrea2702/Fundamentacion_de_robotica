#!/usr/bin/env python
import rospy
import random
from std_msgs.msg import Int32
from motor_control.msg import motor_msg
import numpy as np

def shutdown():
    shutdown_msg = motor_msg()
    shutdown_msg.pwm = 0
    shutdown_msg.direction = "forward"
    pub.publish(shutdown_msg)

if __name__ == '__main__':
    rospy.init_node("Input")
    pub = rospy.Publisher("cmd_pwm", motor_msg, queue_size=10)
    rate = rospy.Rate(10)

    operationMode = rospy.get_param("/op")
    msg = motor_msg()

    rospy.on_shutdown(shutdown)

    while not rospy.is_shutdown():
        duty_cicle = 0
        direction = ""

        if(operationMode == 1):
            rawPWM = 255 * np.sin(rospy.get_time())
            duty_cicle = np.abs(rawPWM)
            direction = "forward" if rawPWM >= 0 else "backward"
            
        elif(operationMode == 2):
            period = rospy.get_param("/period")
            aP = rospy.get_param("/aP")
            duty_cicle = 255 if np.abs(np.sin(np.pi/period * rospy.get_time())) < np.sin(np.pi/2 * aP) else 0
            direction = "forward"

        msg.pwm = duty_cicle
        msg.direction = direction

        pub.publish(msg)
        rospy.loginfo("Pwm: %d", duty_cicle)
        rospy.loginfo("Direction: %s", direction)

        rate.sleep()
