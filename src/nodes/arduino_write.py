import serial
#from trajectory_msgs.msg import JointTrajectory 

#jt = JointTrajectory()
#jt.joint_names = []
#jt.points.positions = []

ser = serial.Serial("/dev/ttyUSB0",9600)
while True:
	text = "D60.45,L100.22,R30.55,K85.37\n"
	ser.write(text)
	data = ser.readline()
	print data
ser.close()
