def reader():
    list1 =  []
    var = raw_input("Do you like cheese? ")
    var1 = raw_input("What about peanut butter? ")
    list1.append(var)
    list1.append(var1)
    return list1

var = ""

def response(list1):
    macncheese = "let's make mac n cheese then!"
    silly = "you're silly"
    print list1
    if (list1[0] == "yes" and list1[1] == "no"):
        print macncheese[0:14] + silly[6:12]
    if (list1[0] == "no" or list1[1] == "no"):
        print "you're silly"
    if (list1[1] =="yes" and list1[0] == "yes"):
        print "let's make peanut butter cheesecake!"


while (not var=="yes"):
    list2 = reader()
    response(list2)
