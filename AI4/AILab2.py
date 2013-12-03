import mathsFunctions as mf
import matplotlib.pyplot as plt
import math as math
import random as random

def readFile(fileName):
    f = open(fileName,'r')
    array = f.readlines()
    array = [int(numStr) for numStr in array]
    f.close()
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
    Datapos = mf.absolute(DataIn)
    Datasign = mf.absolute(Datasign)

    Energy = mf.convolve(Datafft, Rect)
    Magn = mf.convolve(Datapos, Rect)
    ZCR = mf.convolve(Datasign, Rect)
    ZCR = mf.divide(ZCR, 480)    

    E = mf.logBase(mf.mean(Energy), math.exp(1))
    M = mf.logBase(mf.mean(Magn), math.exp(1))
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
    global trainESil, trainMSil, trainZSil
    return 0.5 * mf.probDens(trainESil,sample[0]) * mf.probDens(trainMSil, sample[1]) * mf.probDens(trainZSil, sample[2])

def postSpe(sample):
    global trainESpe, trainMSpe, trainZSpe
    return  0.5 * mf.probDens(trainESpe,sample[0]) * mf.probDens(trainMSpe, sample[1]) * mf.probDens(trainZSpe, sample[2])

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
        Sil.append(Kset[i][0])
        Spe.append(Kset[i][1])
    Sil = dechunk(Sil)
    Spe = dechunk(Spe)
    return Sil, Spe

def dechunk(array):
    dechunked = []
    for i in range (0,len(array)):      
       for j in range (0, len(array[i])):
            dechunked.append(array[i][j])
    return dechunked

def testSample(sample):
    result = postSil(sample) < postSpe(sample)
    return result


def writeFile(fileName, array1, array2):
    array = []
    array3 = array1.ca
    f = open(fileName, 'w')
    f.write(array1)
    
    f.close()
    return array

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
    
    trainESil, trainMSil, trainZSil = setEMZ(trainSil)
    trainESpe, trainMSpe, trainZSpe = setEMZ(trainSpe)
    
    testSil, testSpe = reform(testSet)
 
    for k in range (0, len(testSil)):
        if not (testSample(testSil[k])):
            correctCount += 1
        else:
            errorCount += 1
    for k in range (0, len(testSpe)):
        if (testSample(testSpe[k])):
            correctCount += 1
        else:
            errorCount += 1


ESil, MSil, ZSil = setEMZ(Sil)
ESpe, MSpe, ZSpe = setEMZ(Spe)

print correctCount
print errorCount


fig1 = plt.figure(1)
EM1 = plt.scatter(ESil, MSil, color = 'red')
EM2 = plt.scatter(ESpe, MSpe, color = 'blue')
fig1.suptitle("Engery vs Magnitude", fontsize=20)
plt.xlabel('Log Average Energy', fontsize=18)
plt.ylabel('Log Average Magnitude', fontsize=16)
plt.legend(( EM1, EM2), ("Silence", "Speech"),loc='lower right', ncol=3, fontsize=8)

fig2 = plt.figure(2)
EZ1 = plt.scatter(ESil, ZSil, color = 'red')
EZ2 = plt.scatter(ESpe, ZSpe, color = 'blue')
fig2.suptitle("Engery vs Non-Zero Crossing Rate", fontsize=20)
plt.xlabel('Log Average Energy', fontsize=18)
plt.ylabel('Average Non-Zero Crossing', fontsize=16)
plt.legend((EZ1, EZ2), ("Silence", "Speech"),loc='lower right', ncol=3, fontsize=8)

fig3 = plt.figure(3)
MZ1 = plt.scatter(MSil, ZSil, color = 'red')
MZ2 = plt.scatter(MSpe, ZSpe, color = 'blue')
fig3.suptitle("Magnitude vs Non-Zero Crossing Rate", fontsize=20)
plt.xlabel('Log Average Magnitude', fontsize=18)
plt.ylabel('Average Non-Zero Crossin', fontsize=16)
plt.legend((MZ1, MZ2),( "Silence", "Speech"), loc='lower right', ncol=3, fontsize=8)
plt.show()
    
