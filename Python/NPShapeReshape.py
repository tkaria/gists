import numpy

a = map(int, raw_input().strip().split(' '))

na = numpy.array(a)

print numpy.reshape(na, (3,3))

