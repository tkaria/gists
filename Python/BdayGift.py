
inputs = int(raw_input().strip())
multiplier = float(1.0/(2**inputs))
EV = 0.0
ball = 0.0

for i in range(inputs):
    ball = int(raw_input().strip())
    EV += ball * 0.5
print EV
    

