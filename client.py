import socket, serial
s = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
ser = serial.Serial('/dev/ttyUSB2', baudrate=230400, rtscts=True)
# while True:
for i in range(10000):
     d = ser.read()
     print(ord(d))
     s.sendto(d, ('192.168.10.122', 9999))
# ser.close()