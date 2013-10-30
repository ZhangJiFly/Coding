from numpy import *
from scipy import signal
import numpy as np
import pylab as pl
import matplotlib.pyplot as plt
import scipy as sp

signal = []
bitSt = []
carrier = []
mixed = []
phase = np.pi
newIm = []
image = [
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0],
[0,1,1,1,1,1,1,0,1,1,0,0,1,1,0,1,1,0,0,1,1,0,1,1,1,1,1,1,0],
[0,1,1,1,1,1,1,0,1,1,0,0,1,1,0,1,1,1,0,1,1,0,1,1,1,1,1,1,0],
[0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0],
[0,1,1,0,0,0,0,0,1,1,0,0,1,1,0,1,1,1,1,1,1,0,0,0,1,1,0,0,0],
[0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,1,1,1,0,0,0,1,1,0,0,0],
[0,1,1,1,1,1,1,0,1,1,1,1,1,1,0,1,1,0,0,1,1,0,0,0,1,1,0,0,0],
[0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]]

N = len(image) * len(image[0])

def dechunk(array):
    bitstream = []
    for i in range (0,len(array)):      
       for j in range (0, len(array[i])):
            bitstream.append(array[i][j])
    return bitstream

bitSt = dechunk(image)
def signalbit(array, phase):
    t = 0
    for i in range (0,80):
        t += 1
        array.append(np.sin(2*np.pi*0.1*t + phase))

def chunks(l, n):
    return [l[i:i+n] for i in range(0, len(l), n)]

for j in bitSt:
    phase = j*pi
    signalbit(signal, phase)

for j in range (0, len(bitSt)):
    signalbit(carrier, 0)


mixed = np.multiply(signal, carrier)
#b = np.fir1(100,0.05)
b, a = sp.signal.butter(10, 0.05, 'low')
lpdemod = sp.signal.lfilter(b, 1, mixed)

x1 = np.linspace(0, len(signal), len(signal))

for i in range (0, len(lpdemod)/80):
    count = 0
    bit = np.mean(lpdemod[(i*80):(i+1)*80])<0
    newIm.append(bit)
    
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
