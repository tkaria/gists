
def find_start(data):
    index = 0
    total = 0
    for i in range(len(data)):
        amount, distance = data[i][0], data[i][1]
        total += (amount - distance)
        if total < 0:
                #print "Skipping %s %s" % (data[i])
                index = i + 1 
                total = 0
    print index 

inputs = int(raw_input().strip())
data = []
for i in range(inputs):
    (amount, distance) = (map(int, raw_input().strip().split(' ')))
    data.append((amount, distance))
find_start(data)

