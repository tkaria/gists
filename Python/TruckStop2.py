inputs = int(raw_input().strip())
data = []

def find_start(data):
    j = 0
    sumi = 0
    for i in range(len(data)):
        sumi += int(data[i][0]) - int(data[i][1])
        print "amount: %s distance: %s i: %s  sumi: %s" % (data[i][0], data[i][1], i, sumi)
        if sumi < 0:
            sumi = 0
            j += 1
    print "SOLUTION: %s %s:  %s" % (i, j, sumi)
            
    

for i in range(inputs):
    (amount, distance) = (map(int, raw_input().strip().split(' ')))
    data.append((amount, distance))
find_start(data)
