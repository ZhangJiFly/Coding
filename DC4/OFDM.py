from numpy import *
from scipy import signal
import numpy as np
import pylab as pl
import matplotlib.pyplot as plt
import scipy as sp
from random import *


img = plt.imread('cheesy.png')
nIFFT = 2048
nCyclic = nIFFT/4
nTotal = (nIFFT+nCyclic)*256
pilotAmp = 2
signal = []
ymax = 100
bit = 7
i = complex(real=0, imag=1)

for y in range(0,ymax):
    row = img[y]
    print row
    spectrum = []
    k = 512
    random.seed()
    spectrum.append(pilotAmp)
    k+=1
    for x in range(0,256):
        bitSt = []
        greyVal = row(x)
        r = floor(random.random(1)*255)
        greyVal = greyVal ^ r
        while (bit >= 0):
            m = bit << 1
            testbit = m & greyvalue
            if (testbit>0):
                bitSt.append(1)
        #end while
        for cnum in range(0,4):
            spectrum.append(bitSt[cnum*2-1] + i*bitSt[cnum*2]*2-i;
            k+=1

    
#plt.imshow(gray, cmap = 'Greys')

#plt.show()
