#!/usr/bin/env python
 
import socket
BUFFER_SIZE = 20  # Normally 1024, but we want fast response

# server socket for receing from ad
s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('192.168.1.200', 2000))
s.listen(5)

# client socket
s1 = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s1.connect(('192.168.111.163', 9999))

conn, addr = s.accept()
print('Connection address:', addr)
while 1:
     data = conn.recv(BUFFER_SIZE)
     if not data: break
     print("received data:", data)
     s1.send(data)
conn.close()
