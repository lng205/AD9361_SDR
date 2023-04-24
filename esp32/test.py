import serial

dac = serial.Serial('/dev/ttyUSB1', baudrate=115200)
adc = serial.Serial('/dev/ttyUSB2', baudrate=115200, timeout=1)

while True:
    # print(ord(adc.read()))
    s = adc.readline()
    print(s)
    dac.write(s)