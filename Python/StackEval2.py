
#in + 1 2 - 7 5 + 3 1 1 1 17 - 10 9
# out -19


tmp = raw_input().strip().split(' ')

def evaluate(arr):
    operators = []
    operands = []
    while(len(arr)):
        current = arr.pop()
        result = 0
        if str(current).isdigit():
            operands.append(current)
        if current == '-':
            print "Found '-' %s %s" % (operands, len(operands))
            while(len(operands) > 1):
                op1 = operands.pop()
                op2 = operands.pop()
                result = int(op1) - int(op2)
                print "Evaluated '-' for result %s" % result
                operands.append(result)
        if current == '+':
            print "Found '+' %s %s" % (operands, len(operands))
            while(len(operands) > 1):
                op1 = operands.pop()
                op2 = operands.pop()
                result = int(op1) + int(op2)
                print "Evaluated '+' for result %s" % result
                operands.append(result)

    #print operands, current, arr
    return operands[0]

print evaluate(tmp)
