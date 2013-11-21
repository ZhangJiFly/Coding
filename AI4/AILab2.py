from numpy import *
from mathsFunctions import *
import mathsFunctions as mf
#import numpy as np
import matplotlib.pyplot as plt

Rect = []
ELogAv = []
MLogAv = []
ZAv = []

for i in range (0,240):
    Rect.append(1)

def values(name, i):
    global ELogAv, MLogAv, ZAv, Rect
    number = str(i)
    if (i < 10):
        number = "0" + str(i)
    DataIn = loadtxt("/Users/Crippled.Josh/Coding/AI4/silence_speech/" + name + "_" + number + ".dat")

    sampleRate = len(DataIn)/0.3
    Datafft = []
    DataPos = []
    Datasign = []

    for j in range (1,len(DataIn)): 
        Datasign.append(mf.sign(DataIn[j]) - mf.sign(DataIn[j-1]))

    Datafft = mf.square(DataIn)
    Datafft = mf.divide(Datafft, pow(10,6))
    Datapos = mf.absolute(DataIn)
    Datapos = mf.divide(Datapos, pow(10,2))
    Datasign = mf.absolute(Datasign)
    Datasign = mf.multiply(Datasign, pow(12,2))

    Energy = mf.convolve(Datafft, Rect) #convolve takes an upsetting amount of time compared to the numpy implementation, might try optimising at some 
    Magn = mf.convolve(Datapos, Rect)
    ZCR = mf.convolve(Datasign, Rect)
    
    ELogAv.append(mf.logBase(mf.mean(Energy), exp(1)))
    MLogAv.append(mf.logBase(mf.mean(Magn), exp(1)))
    ZAv.append(mf.mean(ZCR))
    

for i in range (1,51):
    values("silence", i)
for i in range (1,51):
    values("speech", i)
    
plt.figure(1)
plt.subplot(311)
plt.scatter(ELogAv, MLogAv)
plt.subplot(312)
plt.scatter(ELogAv, ZAv)
plt.subplot(313)
plt.scatter(MLogAv, ZAv)
plt.legend(['x = ELogAv y = MLogAv', 'x = ELogAv y = ZAv', 'x = MLogAv y = ZAv'], loc='upper left')

plt.show()
    
