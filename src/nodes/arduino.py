#!/usr/bin/env python
import rospy
import tf
import math
from math import sin, cos, pi
import sys
import datetime

from geometry_msgs.msg import Twist
from std_msgs.msg import String
from sensor_msgs.msg import JointState
from SerialDataGateway import SerialDataGateway

class Arduino(object):

	def _HandleReceivedLine(self,  line):

		js = JointState()
		count = 0
		substring = ""
		##	parsing received line into Joinstate
		if line.startswith('%'):
		 	for letter in line[1:]:
		  		if letter == ";":
		  			js.position.append(round(math.pi/180*float(substring),6))
		  			count += 1
		  			substring = ""
		  		else:
		  			substring += letter
			
			js.name = ['joint_0', 'joint_1', 'joint_2', 'joint_3']
			js.header.stamp = rospy.Time().now()
			self._jsPub.publish(js)

	def __init__(self, port="/dev/ttyUSB0", baudrate=9600):
		'''
		Initializes the receiver class.
		port: The serial port to listen to.
		baudrate: Baud rate for the serial communication
		'''
		
		self._Counter = 0

		rospy.init_node('arduino')

		port = rospy.get_param("~port", "/dev/ttyUSB0")
		baudRate = int(rospy.get_param("~baudRate", 9600))

		rospy.loginfo("Starting with serial port: " + port + ", baud rate: " + str(baudRate))

		# subscriptions
		rospy.Subscriber("cmd_vel", Twist, self._HandleVelocityCommand)

		#Publisher
		self._jsPub = rospy.Publisher('joint_states', JointState, queue_size = 128)

		self._SerialDataGateway = SerialDataGateway(port, baudRate,  self._HandleReceivedLine)


	def Start(self):
		rospy.logdebug("Starting")
		self._SerialDataGateway.Start()

	def Stop(self):
		rospy.logdebug("Stopping")
		self._SerialDataGateway.Stop()
		
	def _HandleVelocityCommand(self, twistCommand):
		""" Handle movement requests. """
		v = twistCommand.linear.x        # m/s
		omega = twistCommand.angular.z      # rad/s
		rospy.loginfo("Handling twist command: " + str(v) + "," + str(omega))

		message = 's %d %d %d %d \r' % self._GetBaseAndExponents((v, omega))
		rospy.logdebug("Sending speed command message: " + message)
		self._SerialDataGateway.Write(message)

if __name__ == '__main__':
	arduino = Arduino()
	try:
		arduino.Start()
		rospy.spin()

	except rospy.ROSInterruptException:
		arduino.Stop()
