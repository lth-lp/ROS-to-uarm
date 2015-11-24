# Testing Model View

Test the robot description:

    roslaunch uarm_description uarm_description2_gui.launch
    rosnode kill /joint_state_publisher
    roslaunch uarm_description rviz.launch

