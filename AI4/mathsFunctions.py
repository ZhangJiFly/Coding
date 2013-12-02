from math import *
import numpy as np

def convolve(array1, window):
    array2 = []

    for i in range (0, len(array1)):
        low = max(i-len(window)/2, 0)
        high = min(i+len(window)/2, len(array1))
        total = sum(array1[low:high])
        array2.append(total)
    return array2

def divide(array1, x):
    array2 = [(num/x) for num in array1]
    return array2

def multiply(array1, x):
    array2 = [(num*x) for num in array1]
    return array2

def absolute(array1):
    array2 = []
    for i in range(0, len(array1)):
        if (array1[i] >= 0):
            array2.append(array1[i])
        else:
            array2.append(array1[i] * -1)
    return array2

def square(array1):
    array2 = [sqr**2 for sqr in array1]
    return array2

def mean(array):
    total = 0.0
    for i in range (0, len(array)):
        total += array[i]
    mean = total/len(array)
    return mean

def logBase(x, base):
    return log(x,base)


def sign(value):
    if (value < 0):
        x = -1
    if (value == 0):
        x = 0
    if (value > 0):
        x = 1
    return x
    
def variance(array):
    array2 = []
    m = mean(array)
    array2 = [(num-m)**2 for num in array]    
    return mean(array2)

def probDens(array, quality):
    m = mean(array)
    var = variance(array)
    first = (sqrt(2*pi*var))
    second = exp(-(quality-m)**2/(2*var))
    return second/first
