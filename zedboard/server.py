import socket, serial
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
s.bind(('192.168.13.1', 9999))
ser = serial.Serial('/dev/ttyUSB0', baudrate=230400)
while True:
     data, addr = s.recvfrom(1)
     ser.write(data)