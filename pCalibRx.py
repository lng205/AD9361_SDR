# Carrier phase calibration Rx code

import adi
import numpy as np
from math import atan, cos, sin
from matplotlib import pyplot as plt

sdr = adi.ad9361(uri="ip:analog.local") # connect to the local device

# Configure properties
sdr.sample_rate = 30720000 # fs = 30.72MHz
sdr.rx_rf_bandwidth = 10000000 # BW = 10MHz
sdr.rx_lo = 5400000000 # fc = 5.4GHz
sdr.rx_enabled_channels = [0] # Rx1
sdr.gain_control_mode_chan0 = "slow_attack" # AGC

# Receive
r = sdr.rx()
pPos = r > 0
I = np.average(r.real[pPos])
Q = np.average(r.imag[pPos])
phi = atan((Q-I)/(Q+I))
print("I=%d, Q=%d, phi=%.2f" % (I,Q,phi))

# Calibration
sP = sin(phi)
cP = cos(phi)

# Test
sdr.rx_buffer_size = 2048
r = sdr.rx()
rI = r.imag*sP + r.real*cP
rQ = r.imag*cP - r.real*sP
x = np.arange(1,1025)
plt.plot(x,rI,x,rQ)
plt.show()