n = int(raw_input().strip())
stack = []
m = -float("inf")

import timeit


for x in range(n):
    instructions = raw_input().strip().split(' ')
    #print "Instructions: %s" % instructions
    if int(instructions[0]) == 1:
        print "Appending: %s" % instructions[1]
        n = long(instructions[1])
        if n > m:
            m = n
        stack.append(long(instructions[1])) 

    if int(instructions[0]) == 2:
        x = stack.pop()
        print "Removing: %s and m is %s" % (x, m)
    
        if (long(x) == long(m)):
            print "Old max %s New max %s" % (x,m)
            if len(stack):
                m = max(stack)
            else:
                m = -float("inf")

    if int(instructions[0]) == 3:
        print m 
