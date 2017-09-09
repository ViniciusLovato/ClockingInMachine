import serial
from subprocess import check_output

ser = serial.Serial('/dev/ttyACM0', 9600)

while True:
	person = ser.readline().strip()
	print 'Clocking in for ' + person
	out = check_output(['./bater.sh', person])
	ser.write(out)
		
	
