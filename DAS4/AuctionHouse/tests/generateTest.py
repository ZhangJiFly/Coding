from time import *
from random import *


itemC = 1
totalString = "register\n"

def add(minVal):
    global itemC
    #print millis
    string = ""
    string += "add\nItem"
    string = string + str(itemC) + " " + str(minVal) + " " + str(3) + "\n"
    itemC += 1
    return string

def bid(value):
    global itemC
    string = ""
    string += "bid\n"
    string += str(randint(1,itemC)) + " " + str(value) + "\n"
    return string

totalString += add(randint(1,10000))

for j in range(0,1000):
    for i in range(0, 30):
        if (randint(0,1)):
            totalString += add(randint(1,10000))
        else:
            totalString += bid(randint(1,100000))
    f = open('test' + str(j), 'w')
    f.write(totalString + "end")
    totalString = "register\n" + add(randint(1,10000))

