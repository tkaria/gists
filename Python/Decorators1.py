import numpy


def bar(f):
    def s(a): 
        for i in range(len(a)):
            #print "Examining: ", num
            num = a[i]
            if len(num) == 10:
                num = "+91" + num
                formatted = num[0:3] + ' ' + num[3:8] + ' ' + num[8:]
            elif num[0] == '+':
                formatted = num[0:3] + ' ' + num[3:8] + ' ' + num[8:]
            elif num[0:2] == '91':
                num = '+' + num
                formatted = num[0:3] + ' ' + num[3:8] + ' ' + num[8:]
            elif num[0] == '0':
                num = num[1:]
                num  = '+91' + num
                formatted = num[0:3] + ' ' + num[3:8] + ' ' + num[8:]
            #print formatted    
            a[i] = formatted
        return f(a)
    return s

        
@bar
def foo(a):
    a.sort()
    return a

n = int(raw_input().strip())
a = []
for i in range (n):
    a.append(raw_input().strip())

g = foo(a)
for n in g:
    print n
