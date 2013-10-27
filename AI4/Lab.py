from numpy import *
import numpy as np
import pylab as pl
import matplotlib.pyplot as plt

DataIn = loadtxt("/Users/Crippled.Josh/Desktop/laboratory.dat");

accousticImp = 413.3
Rect = []
sampleRate = len(DataIn)/0.3
Datafft = []
DataPos = []
Datasign = []

for i in range (0,240):
    Rect.append(1)

for i in range (1,len(DataIn)): 
    Datasign.append(np.sign(DataIn[i]) - np.sign(DataIn[i-1]))

Datafft = np.square(DataIn)
Datafft = np.divide(Datafft, pow(10,6))
Datapos = np.absolute(DataIn)
Datapos = np.divide(Datapos, pow(10,2))
Datasign = np.absolute(Datasign)
Datasign = np.multiply(Datasign, pow(12,2))

Energy = np.convolve(Datafft, Rect, mode = 'same')
Magn = np.convolve(Datapos, Rect, mode = 'same')
ZCR = np.convolve(Datasign, Rect, mode = 'same')

x1 = np.linspace(0, len(DataIn), len(DataIn))
x2 = np.linspace(0, len(Energy), len(Energy))
x3 = np.linspace(0, len(Magn), len(Magn))
x4 = np.linspace(0, len(ZCR), len(ZCR))

plt.figure(1)
#plt.subplot(211)
plt.plot(x1,DataIn)
#plt.subplot(211)
plt.plot(x2, Energy)
#plt.subplot(211)
plt.plot(x3, Magn)
#plt.subplot(212)
plt.plot(x4, ZCR)
plt.legend(['y = Signal', 'y = Energy', 'y = Magnitude', 'y=ZCR'], loc='upper left')

plt.show()
