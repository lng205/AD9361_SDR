# Carrier phase calibration
import time
import adi
import numpy as np

sdr = adi.ad9361(uri="ip:analog.local") # connect to the local device

# Configure properties
sdr.sample_rate = 10000000
sdr.tx_lo = 5400000000 # fc/Hz
sdr.tx_cyclic_buffer = True # keep sending the same data
sdr.tx_hardwaregain_chan0 = 0 # dB
sdr.tx_enabled_channels = [0] # Tx1

# Create Tx waveform
dataI = np.array([[1,1,1,-1,-1,1,-1,-1]]).transpose() * 2 ** 14
i = np.array(np.matmul(dataI,np.ones([1,40])).flatten())
iq = i + 1j * i

# Send data
sdr.tx(iq)

#Rx
from math import atan, cos, sin
from matplotlib import pyplot as plt

# Configure properties
# sdr.sample_rate = 30720000 # fs = 30.72MHz
sdr.rx_rf_bandwidth = 10000000
sdr.rx_lo = 5400000000
sdr.rx_enabled_channels = [0] # Rx1
sdr.gain_control_mode_chan0 = "slow_attack" # AGC

# Receive
r = sdr.rx()
pPos = r > 0
I = np.average(r.real[pPos])
Q = np.average(r.imag[pPos])
phi = atan((Q-I)/(Q+I))
print("I=%d, Q=%d, phi=%.2f" % (I,Q,phi))
with open("../../media/phi.txt",'w') as f:
    f.write(str(phi))

# Calibration
sP = sin(phi)
cP = cos(phi)

# Test
r = sdr.rx()
rI = r.imag*sP + r.real*cP
rQ = r.imag*cP - r.real*sP
x = np.arange(1,1025)
plt.plot(x,rI,x,rQ)
plt.show()