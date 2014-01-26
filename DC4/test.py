from random import *
from numpy import *



bitstream = zeros(8)
greyvalue = 32
r = randint(0,255);

greyvalue = int(greyvalue)^int(r);
ifft = fft.ifft([10,40,30,10,9,12])
print ifft
print fft.fft(ifft)
