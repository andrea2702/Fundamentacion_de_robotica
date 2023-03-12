#!/usr/bin/env python
import rospy
from std_msgs.msg import Int32
from final_challenge.msg import motor_msg
import numpy as np

# Shutdown function to stop the motor
def shutdown():
    shutdown_msg = motor_msg()
    shutdown_msg.pwm = 0
    shutdown_msg.direction = "forward"
    pub.publish(shutdown_msg)

if __name__ == '__main__':
    # Node
    rospy.init_node("set_point")
    # Topics
    pub = rospy.Publisher("set_point", motor_msg, queue_size=10)
    rate = rospy.Rate(10)

    #operationMode = rospy.get_param("/op")
    operationMode = 1

    msg = motor_msg()

    rospy.on_shutdown(shutdown)
    while not rospy.is_shutdown():
        duty_cicle = 0
        direction = ""

        # sinusoidal signal
        if(operationMode == 1):
            rawPWM = 255 * np.sin(rospy.get_time())
            duty_cicle = np.abs(rawPWM)
            direction = "forward" if rawPWM >= 0 else "backward"
        
        # square signal
        elif(operationMode == 2):
            period = rospy.get_param("/period")
            aP = rospy.get_param("/aP")
            duty_cicle = 255 if np.abs(np.sin(np.pi/period * rospy.get_time())) < np.sin(np.pi/2 * aP) else 0
            direction = "forward"


        msg.pwm = duty_cicle
        msg.direction = direction

        # Publish topic
        pub.publish(msg)
        rospy.loginfo("Pwm: %d", duty_cicle)
        rospy.loginfo("Direction: %s", direction)

        rate.sleep()
