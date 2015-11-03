cmake_minimum_required(VERSION 2.8.3)
project(uarm)


find_package(catkin REQUIRED COMPONENTS
  roscpp
  rospy
  tf
  math
  sys
  datetime
  threading
  serial
  time
  StringIO
  std_msgs
  sensor_msgs
  geometry_msgs
)

catkin_package(
#  INCLUDE_DIRS include
#  LIBRARIES uarm
#  CATKIN_DEPENDS roscpp rospy
#  DEPENDS system_lib
)

include_directories(
  ${catkin_INCLUDE_DIRS}
)

