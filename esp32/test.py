import serial

dac = serial.Serial('/dev/ttyUSB1', baudrate=230400)
adc = serial.Serial('/dev/ttyUSB2', baudrate=230400, timeout=1)

while True:
    dac.write(adc.read(8))