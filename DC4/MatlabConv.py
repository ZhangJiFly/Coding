from numpy import *
from scipy import signal
import numpy as np
import pylab as pl
import matplotlib.pyplot as plt
import scipy as sp

# cosine output
c = 1
# delayed cosine by one timestep
cdelay = 0
# sine output
s = 0
# delayed sine by one timestep
sdelay = 0

# vectors storing the results by adding the samples one by one
sine = []
cosine = []
vco = []
psk = []

# PLL loop filter
b = sp.signal.butter(100, 0.1, 'low')
# filter state because we just feed one value at a time in it and
# then come back to it every timestep so we need to save the state
zf = np.zeros(len(b) - 1)

v = 0

# main loop: reading data one by one
for i in range(1,1000):

    # test signal, will be replaced by the input PSK signal
    # the PLL needs to lock on it, let's assume our
    # frequency is 1% off. Should be f=0.1 but is f=0.099
    # and we have some random phase angle.
    y = sin(2 * pi * 0.099 * i + pi / 2.345543)

    #"voltage" controlled oscillator with f=0.1 +/- v input
    w0 = 2 * pi * (0.1 + v * 0.0025)
    cdelay = c
    sdelay = s
    c = cdelay * cos(w0) - sdelay * sin(w0)
    s = sdelay * cos(w0) + cdelay * sin(w0)

    # phase detector
    p = y * c

    # filtering out the 2f term
    v, zf = sp.signal.lfilter(b, 1, p, zf)

    # let's save everything in handy vectors for plotting
    sine = [sine, s]
    cosine = [cosine, c]
    psk = [psk, y]
    vco = [vco, v]
end

plt.plot(vco)
plt.show()
