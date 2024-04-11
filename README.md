# PID Controller for DC Motor with ROS and Arduino

## Overview

This project implements a PID controller for a direct current (DC) motor using ROS (Robot Operating System) and Arduino. It has been developed in collaboration with Manchester Robotics.

## Requirements

- ROS platform installed on your system.
- Arduino IDE to upload the code to the Arduino.
- Basic knowledge of ROS and Arduino.

## Hardware Setup

1. Connect the direct current motor to the Arduino as per the hardware specifications.
2. Upload the provided code to the Arduino using the Arduino IDE.

## Software Setup

1. Clone this repository on your workspace src directory (catkin_ws/src/).
   ```bash
   git clone <repository_url>
   
2. Navigate to the your workspace directory (catkin_ws) and execute catkin_make to compile the package.
```bash
cd catkin_ws
catkin_make
```

3. Once compiled, run source devel/setup.bash to set up your ROS workspace.
```bash
source devel/setup.bash
```

## Usage
1. To run the PID controller, execute the final.launch file using the next command
```bash
roslaunch Final_challenge_ROS final.launch
```
2. After running final.launch, the PID controller will be running
3. Change the parameters file to change the PID mode in the setPoin_file.yaml
   - op: Operation mode from 1 to 4. Where:
         1. Square signal
         2. Sinoidal signal
         3. Lineal signal
         4. Keyboard entrance, "A" is forward and "D" is backward
   - period
   - vel: Velocity
4. Change the PID constants in the control_file.yaml

## Demo

[![Demo del Proyecto](http://img.youtube.com/vi/BHTzVF8sD1Q/0.jpg)](https://www.youtube.com/watch?v=BHTzVF8sD1Q)
