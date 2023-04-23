import socket, serial
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
ser = serial.Serial('/dev/ttyUSB0', baudrate=230400)
while True:
     d = ser.read()
     s.sendto(d, ('192.168.13.1', 9999))