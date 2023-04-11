import socket

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.connect(('192.168.111.163', 9999))
s.send(b'exit')
s.close()