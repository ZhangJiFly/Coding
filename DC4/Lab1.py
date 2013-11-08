from numpy import *
from scipy import signal
import numpy as np
import pylab as pl
import matplotlib.pyplot as plt
import scipy as sp

image = [[1, 1, 1, 0, 0, 1, 1, 1],
        [1, 1, 0, 0, 0, 0, 1, 1],
        [1, 0, 0, 0, 1, 0, 0, 1],
        [0, 0, 0, 0, 0, 0, 1, 1],
        [0, 0, 0, 0, 0, 1, 1, 1],
        [1, 0, 0, 0, 0, 0, 0, 1],
        [1, 1, 0, 0, 0, 0, 1, 1],
        [1, 1, 1, 0, 0, 1, 1, 1]]
fs = 8000
f= 0.1
nDummyS = 10
tsymbol = 80*5
N = len(image) * len(image[0])
ttotal = (N + 1 + nDummyS) * tsymbol
signal = []
bitSt = []
carrier = []
mixed = []
phase = np.pi
newIm = []


def dechunk(array):
    bitstream = []
    for i in range (0,len(array)):      
       for j in range (0, len(array[i])):
            bitstream.append(array[i][j])
    return bitstream

def signalbit(array, phase):
    t = 0
    global tsymbol
    for i in range (0, tsymbol):
        t += 1
        array.append(np.sin(2*np.pi*0.1*t + phase))

def chunks(l, n):
    return [l[i:i+n] for i in range(0, len(l), n)]

syncSym = [[1]]
bitSt = dechunk(image)
syncSym.append(bitSt)
dechunk(syncSym)

for i in range(0,nDummyS):
    signalbit(signal, 0) ### Creates DummySignals in signal with 0 phase shift

for j in bitSt:
    phase = j*pi
    signalbit(signal, phase) ### Creates PSK signal with phase shift


x1 = np.linspace(0, len(signal), len(signal))


##DEMODULATION##

x = 0
y = 0
t = 0

#b = np.fir1(100,0.05)
b,a = sp.signal.butter(100, 0.1, 'low')

c = 1
cDelay = 0
s = 0
sDelay = 0
bPLL = sp.signal.butter(40, 0.1, 'low')
sampleMo = (3/2) * tsymbol
nPLLSet = (nDummyS/2) * tsymbol
ignoreData = 1
VCOgain = 0.005
v = [0]
sin = []
cos = []
VCO = []
carrierInph = []
mixerInph = []
stateLowInph = []
demodThrInph = []
zfPLL = zeros(len(bPLL)-1)
lpDemodInph = zeros(ttotal)

for j in range (0, ttotal):
    sample = signal[j] ### Creates phase change free carrier wave

    w0 = 2*pi*(f+v[0]*VCOgain)
    cDelay = c
    sDelay = s
    c = cDelay * np.cos(w0) - sDelay * np.sin(w0)
    s = sDelay * np.cos(w0) - cDelay * np.sin(w0)
    sin.append(s)
    cos.append(c)
    VCO.append(v[0])

    carrierInph.append(-s)

    if (nPLLSet > 0):
        nPLLSet -= 1
        p = sample * c

        v, zfPLL = sp.signal.lfilter(bPLL, 1, p, zfPLL)
    else:
         mixerInph.append(sample*carrierInph[j])
         [lpDemodInph[j], stateLowInph] = sp.signal.lfilter(b, 1, mixerInph[j], stateLowInph)
         demodThrInph[j] = lpDemodInph[j]

         if (ignoreData):
             if (lpDemodInph[j] > 0.25):
                 ignoreData = 0
         else:
            sampleMo -= 1
            if (sampleMo == 0):
                sampleMo = tsymbol
                if (demodThrInph[j] > 0):
                    lsb = 1
                else:
                    lsb = 0
                lpDemodInph[j] = lpDemodInph[j] + 0.1

                if ((x<9 and y<9) and (ignoreData == 0)):
                    newIm.append(lsb)
                    x += 1
                    if (x>8):
                        x = 1
                        y += 1            
    t += 1
    
newIm = chunks(newIm,len(image[0]))     

plt.figure(1)
plt.subplot(321)
plt.plot(x1,signal)
plt.subplot(322)
plt.imshow(image,cmap='Greys',  interpolation='nearest')
plt.subplot(323)
plt.plot(x1,mixed)
plt.subplot(324)
plt.plot(x1,lpdemod)
plt.subplot(325)
plt.imshow(newIm,cmap='Greys',  interpolation='nearest')
plt.show()
