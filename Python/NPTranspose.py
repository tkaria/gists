import numpy 

dim = raw_input().strip().split(' ')
n = int(dim[0])
m = int(dim[1])
a = []

for i in range(int(n)):
        a.append(map(int, raw_input().strip().split(' ')))

np = numpy.array(a)
np = numpy.reshape(np, (n,m))
print numpy.transpose(np)
print np.flatten()



