from numpy import *
from matplotlib.pyplot import *
from random import *
import numpy as np


def heaviside(x):
    if x == 0:
        return 0.5

    return 0 if x < 0 else 1

def dechunk(array):
    dechunked = []
    for i in range (0,len(array)):      
       for j in range (0, len(array[i])):
            dechunked.append(array[i][j])
    return dechunked

f = open('thefile.txt', 'w')

b = imread('figure_1.png');

a = []
c = []

for i in range(0,len(b)):
    for j in range(0,len(b[i])):
        if(b[i][j][0]*b[i][j][1]*b[i][j][2]*b[i][j][3] != 1):
            c.append(0)
        else:
            c.append(1)

    a.append(c)
            
nIFFT = 2048;
nCyclic = nIFFT/4;
nTotal = (nIFFT+nCyclic)*320;
pilot_amplitude = 2;

offset = nIFFT*3;

signal = zeros(offset);
ymax = len(a)
xmax = len(a[0])
print ymax
print xmax

for y in range(1,ymax):

    row = a[y:-1];
    spectrum = zeros(nIFFT);
    k = 1024+512;
    seed(1);
    spectrum[k] = pilot_amplitude;
    k = k + 1;

    for x in range(1,xmax):


        bitstream = zeros(8);
        greyvalue = row[x];
        #print greyvalue
        r = randint(0,255);
        greyvalue = int(greyvalue)^int(r);

        for bit in range(8,0,-1):
            m = 1<<bit;
            testbit = m & greyvalue;
            if ( testbit > 0 ):
                bitstream[8-bit] = 1;
            #end %if
        #end %for

        for cnum in range(1,4):
            spectrum[k] = bitstream[cnum*2-1]*2-1 + i*bitstream[cnum*2]*2-i;
            k = k + 1;
            if (k >= nIFFT):
                k = 1;
            #end
        #end

    #end % for x
    print spectrum
    complex_symbol = np.fft.ifft[spectrum];
    tx_symbol = zeros(len(complex_symbol)*2);
    s = 1;
    txindex = 1;
    for symbidx in range(1,len(complex_symbol)):
        tx_symbol[txindex] = s * real(complex_symbol[symbidx]);
        txindex = txindex + 1;
        tx_symbol[txindex] = s * imag(complex_symbol[symbidx]);
        txindex = txindex + 1;
        s = s * -1;
    #end

    cyclicPrefix = tx_symbol[nIFFT*2-nCyclic*2+1:nIFFT*2];
    signal = cat(1,signal,cyclicPrefix);
    signal = cat(1,signal,tx_symbol);

#end % for y


#wavwrite(signal,'ofdm8000_tx2.wav');

rx_image = zeros((ymax,xmax));

nSymbol = nIFFT+nCyclic;

s = 1;
rxindex = 1+offset;
for a in range(0,(len(signal)/2-offset/2)):
    realpart = s * signal[rxindex];
    rxindex = rxindex + 1;
    imagpart = s * signal[rxindex];
    rxindex = rxindex + 1;
    rx_complex_signal[a] = realpart + i * imagpart;
    s = s * -1;
#end

for y in range(0,ymax):

    rx_symbol = rx_complex_signal[(y-1)*nSymbol+nCyclic+1:(y-1)*nSymbol+nCyclic+nIFFT];
    isymbol = fft[rx_symbol];

    seed(1);
    k = 1024+512;
    k = k + 1;
    for x in range(1,xmax):
        bitstream = zeros(8);
        for cnum in range(1,4):
            bitstream[cnum*2-1] = heaviside(real(isymbol(k)));
            bitstream[cnum*2] = heaviside(imag(isymbol(k)));
            k = k + 1;
            if (k >= nIFFT):
                k = 1;
            #end
        #end
        greyvalue = 0;

        for bit in range(8,0,-1):
            mask = bitshift(1,bit);
            if (bitstream(8-bit) == 1):
                greyvalue = mask | greyvalue;
            #end %if
        #end %for

        r = randint(0,255);
        greyvalue = greyvalue ^ r;
        rx_image[y,x] = greyvalue;
    #end % for x

#end % for y

imagesc(rx_image);
colormap(gray);
