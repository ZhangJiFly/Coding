import mathsFunctions as mf
import matplotlib.pyplot as plt
from math import *
import random as random

def readFile(fileName):
    f = open(fileName)
    array = f.readlines()
    array = [int(numStr) for numStr in array]
    return array

def values(name, i):
    number = str(i)
    if (i < 10):
        number = "0" + str(i)

    Rect = []
    for i in range (0,240):
        Rect.append(1)
        
    DataIn = readFile("./silence_speech/" + name + "_" + number + ".dat")

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
    
    E = mf.logBase(mf.mean(Energy), exp(1))
    M = mf.logBase(mf.mean(Magn), exp(1))
    Z = mf.mean(ZCR)
    return E, M, Z

def setEMZ(array):
    E = []
    M = []
    Z = []
    for i in range (0,len(array)):
        E.append(array[i][0])
        M.append(array[i][1])
        Z.append(array[i][2])
    return E, M, Z

def postSil(sample):
    global ESil, MSil, ZSil
    return 0.5 * mf.probDens(ESil,sample[0]) * mf.probDens(MSil, sample[1]) * mf.probDens(ZSil, sample[2])

def postSpe(sample):
    global ESpe, MSpe, ZSpe
    return  0.5 * mf.probDens(ESpe,sample[0]) * mf.probDens(MSpe, sample[1]) * mf.probDens(ZSpe, sample[2])

def genKSet(Sil, Spe):
    KSets = []
    random.shuffle(Sil)
    random.shuffle(Spe)
    for i in range (0,10):
        KSets.append([Sil[i*5:(i+1)*5], Spe[i*5:(i+1)*5]])
    return KSets

def reform(Kset):
    Sil = []
    Spe = []
    for i in range (0, len(Kset)):
        Sil.append(KSet[i][0])
        Spe.append(KSet[i][1])
    Sil = dechunk(Sil)
    Spe = dechunk(Spe)
    return Sil, Spe

def dechunk(array):
    dechunked = []
    for i in range (0,len(array)):      
       for j in range (0, len(array[i])):
            dechunked.append(array[i][j])
    return dechunked

Sil = []
Spe = []

for i in range (1,51):
    Sil.append(values("silence", i))
for i in range (1,51):
    Spe.append(values("speech", i))


KSet = genKSet(Sil, Spe)
correctCount = 0
errorCount = 0
for i in range(0,10):
    trainingSet = []
    for j in range (0,10):
        if (j != i):
            trainingSet.append(KSet[j])
    testSet = [KSet[i]]
    trainSil, trainSpe = reform(trainingSet)
    print "trainingSet: " + str(len(trainingSet))
    print "trainSil: " + str(len(trainSil))
    ESil, MSil, ZSil = setEMZ(trainSil)
    ESpe, MSpe, ZSpe = setEMZ(trainSpe)
    testSil, testSpe = reform(testSet)
    for i in range (0, len(testSil)):
        if (postSil(testSil[i]) > postSpe(testSil[i])):
            correctCount += 1
        else:
            errorCount += 1
    for i in range (0, len(testSpe)):
        if (postSpe(testSpe[i]) > postSil(testSpe[i])):
            correctCount += 1
        else:
            errorCount += 1

print mf.variance([1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17])

ESil, MSil, ZSil = setEMZ(Sil)
ESpe, MSpe, ZSpe = setEMZ(Spe)

print correctCount
print errorCount

plt.figure(1)
plt.subplot(311)
plt.scatter(ESil, MSil, color = 'red')
plt.scatter(ESpe, MSpe, color = 'blue')
plt.subplot(312)
plt.scatter(ESil, ZSil, color = 'red')
plt.scatter(ESpe, ZSpe, color = 'blue')
plt.subplot(313)
plt.scatter(MSil, ZSil, color = 'red')
plt.scatter(MSpe, ZSpe, color = 'blue')

plt.show()
    
