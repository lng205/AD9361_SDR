import time

import adi
from math import atan, cos, sin
import numpy as np
from matplotlib import pyplot as plt
np.set_printoptions(threshold=1024) # print the entire array

# Create radio
# sdr = adi.ad9361(uri="ip:192.168.31.21")
sdr = adi.ad9361(uri="ip:analog.local") # connect to the local device

# Configure properties
sdr.rx_rf_bandwidth = 10000000 # BW = 10MHz
sdr.sample_rate = 30720000 # fs = 30.72MHz
sdr.rx_lo = 5400000000 # fc = 5.4GHz
sdr.tx_lo = 5400000000
sdr.tx_cyclic_buffer = True # keep sending the same data
sdr.tx_hardwaregain_chan0 = -10 # -10dB
sdr.gain_control_mode_chan0 = "slow_attack" # AGC

# Configuration data channels
sdr.rx_enabled_channels = [0] # Rx1
sdr.tx_enabled_channels = [0]

# # Read properties
# print("RX LO %s" % (sdr.rx_lo))
# print("gain control mode chan0 %s" % (sdr.gain_control_mode_chan0))

# Create Tx waveform
dataI = np.array([[1,1,1,-1,-1,1,-1,-1]]).transpose() * 2 ** 14 # Phase calibration
# dataI = np.array([[1,0,1,0,0,0,1,1]]).transpose() * 2 ** 14
# dataQ = dataI
i = np.array(np.matmul(dataI,np.ones([1,40])).flatten())
q = i
iq = i + 1j * q

# Send data
sdr.tx(iq)

time.sleep(0.1)
r = sdr.rx()
pPos = r > 0
I = np.average(r.real[pPos])
Q = np.average(r.imag[pPos])
phi = atan((I-Q)/(I+Q))
# print(np.average(r))
# print(sdr.rx())
print("I=%d, Q=%d, phi=%.2f" % (I,Q,phi))

rI = r.imag*sin(phi) - r.real*cos(phi)
rQ = r.imag*cos(phi) + r.real*sin(phi)
x = np.arange(1,1025)
plt.plot(x,rI,x,rQ)
plt.show()