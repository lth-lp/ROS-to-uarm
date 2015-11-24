# ROS-to-uarm
<<<<<<< HEAD

Project to read data from uarm to rviz

to test the function:
1. roscore
2. rosrun uarm_arduino arduino.py
3. roslaunch uarm_description uarm_description2_gui.launch
4. rosnode kill /joint_state_publisher
5. roslaunch uarm_description rviz.launch
