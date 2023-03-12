#!/usr/bin/env python
import rospy
from std_msgs.msg import Int32
from final_challenge.msg import motor_msg
import numpy as np

receiveSetPoint_pwm = 0
receiveSetPoint_direction = ""

receiveMotorOutput_pwm = 0
receiveMotorOutput_direction = ""

def set_point_callback(msg):
    global receiveSetPoint_pwm, receiveSetPoint_direction
    receiveSetPoint_pwm = msg.pwm
    receiveSetPoint_direction = msg.direction

def motor_output_callback(msg):
    global receiveMotorOutput_pwm, receiveMotorOutput_direction
    receiveMotorOutput_pwm = msg.pwm
    receiveMotorOutput_direction = msg.direction

if __name__ == '__main__':
    # Node
    rospy.init_node("open_loop_controller")
    # Publishers
    motor_input_pub = rospy.Publisher("motor_input", motor_msg, queue_size=10)
    # Subscribers
    rospy.Subscriber("set_point", motor_msg, set_point_callback)
    rospy.Subscriber("motor_output", motor_msg, motor_output_callback)

    rate = rospy.Rate(10)

    motor_input_msg = motor_msg()

    while not rospy.is_shutdown():

        motor_input_msg.pwm = receiveSetPoint_pwm
        motor_input_msg.direction = receiveSetPoint_direction

        rospy.loginfo("MotorInput Pwm: %d", receiveSetPoint_pwm)
        rospy.loginfo("MotorInput Direction: %s", receiveSetPoint_direction)

        motor_input_pub.publish(motor_input_msg)
        rate.sleep()







