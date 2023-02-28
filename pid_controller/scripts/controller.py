#!/usr/bin/env python
import rospy
import numpy as np
from pid_controller.msg import motor_output, motor_input, set_point
from std_msgs.msg import Float32

# Defining our Controller class
class Controller:
    def __init__(self, dt):
        # Declaration of PID constants from parameters
        self.dt = dt
        self.kp = rospy.get_param("/control_Kp", 0)
        self.ki = rospy.get_param("/control_Ki", 0)
        self.kd = rospy.get_param("/control_Kd", 0)
        # Initialization of PID variables
        self.error = 0
        self.prev_e = 0
        self.sum_e = 0
        self.diff_e = 0
        self.u = 0
        self.set_point_time = 0
        self.set_point = 0
        self.motor_output = 0
        self.motor_time = 0
        self.motor_status = ""
        # Declaration of Output message, which will be the input for the motor
        self.Output = motor_input()
        # Declaration of publishers for /motor_input and /error channels
        self.control_out = rospy.Publisher("/motor_input", motor_input, queue_size=1)
        self.error_out = rospy.Publisher("/error", Float32, queue_size=1)
        # Subscribing to /motor_output and /set_point channels
        rospy.Subscriber("/motor_output", motor_output, self.motor_output_callback)
        rospy.Subscriber("/set_point", set_point, self.set_point_callback)

    # motor_output callback function
    def motor_output_callback(self, msg):
        # Update of values related to the motor output
        self.motor_output = msg.output
        self.motor_time = msg.time
        self.motor_status = msg.status

    # set_point callback function
    def set_point_callback(self, msg):
        # Update of values related to the set point
        self.set_point = msg.set_point
        self.set_point_time = msg.time

    # Main control function
    def control(self):
        # Error calculation from set point and actual value
        self.error = self.set_point - self.motor_output
        # Error integration
        self.sum_e += self.error * self.dt
        # Error differentiation
        self.diff_e = (self.error - self.prev_e) / self.dt
        # Control variable calculation
        self.u = self.kp * self.error + self.ki * self.sum_e + self.kd * self.diff_e
        # Output message update
        self.Output.input = self.u
        self.Output.time = rospy.get_time()
        # Output message publication
        self.control_out.publish(self.Output)
        # Error message publication
        self.error_out.publish(self.error)
        # Previous error update
        self.prev_e = self.error

    # Shutdown function
    def stop(self):
        print("Control Out")


if __name__ == '__main__':
    # Node initializing
    rospy.init_node("controller")
    # New controller instance
    controller = Controller(rospy.get_param("/control_dt", 1.0/100.0))
    rate = rospy.Rate(100)
    # Shutdown function declaration
    rospy.on_shutdown(controller.stop)
    # Node loop
    while not rospy.is_shutdown():
        # Update controller
        controller.control()
        # Node sleep
        rate.sleep()

