

operators = []
operands = []

tmp = raw_input().strip().split(' ')

def expression(opa, opd):
    print opa
    print opd

for x in tmp:
    if x in ['+', '-']:
        operators.append(x)
    if x.isdigit():
        operands.append(int(x))

expression(operators, operands)
