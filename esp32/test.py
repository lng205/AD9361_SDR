import serial

dac = serial.Serial('/dev/ttyUSB1', baudrate=230400)
adc = serial.Serial('/dev/ttyUSB2', baudrate=230400)

while True:
    dac.write(adc.read())