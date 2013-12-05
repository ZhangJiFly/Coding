from numpy import *
from mathsFunctions import *
import mathsFunctions as mf
import numpy as np
import matplotlib.pyplot as plt

DataIn = loadtxt("./laboratory.dat");

Rect = []
Datasign = []

for i in range (0,240):
    Rect.append(1)

for i in range (1,len(DataIn)): 
    Datasign.append(np.sign(DataIn[i]) - np.sign(DataIn[i-1]))

Datafft = mf.square(DataIn)

Datapos = mf.absolute(DataIn)

Datasign = mf.absolute(Datasign)

Energy = mf.convolve(Datafft, Rect)
Magn = mf.convolve(Datapos, Rect)
ZCR = mf.convolve(Datasign, Rect)

DataIn = mf.divide(DataIn, max(DataIn))
Energy = mf.divide(Energy, max(Energy))
Magn = mf.divide(Magn, max(Magn))
ZCR = mf.divide(ZCR, max(ZCR))

x1 = np.linspace(0, len(DataIn), len(DataIn))
x2 = np.linspace(0, len(Energy), len(Energy))
x3 = np.linspace(0, len(Magn), len(Magn))
x4 = np.linspace(0, len(ZCR), len(ZCR))


plt.figure(1)

plt.plot(x1,DataIn)

plt.plot(x2, Energy)
plt.plot(x3, Magn)
plt.plot(x4, ZCR)
plt.legend(['y = Signal', 'y = Energy', 'y = Magnitude', 'y=ZCR'], loc='upper left')

plt.show()
