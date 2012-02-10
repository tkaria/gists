import numpy as np

x = np.arange(1,60*60*24, 1)
windows = []
step = 4
"""
print "===============> WINDOW 1"
print x
for i in xrange(len(x)):
    cutoff = x[i] - step
    if cutoff < 0: continue
    print "cutoff: " , cutoff
    window = [j for j in x if j > cutoff and j < cutoff + step]
    print "window: ", window
    windows.append(window)

"""

print "===============> WINDOW 2"
windows2 = []
print x
step = 60*15
window2 = [x[z:z+step] for z in xrange(0, len(x), step)]
windows2.append(window2)
#print windows2
print "Num windows2: ", len(windows2[0])


print "===============> WINDOW 3"
windows3 = []
print x
step = 60*15
window3 = [x[v] for v in xrange(0, len(x), 3) if x[v] < v*step]
windows3.append(window3)
#print windows3
print "Num windows3: ", len(windows3[0])
def chunks(l, n):
    for i in xrange(0, len(l), n):
        yield l[i:i+n]

print "===============> WINDOW 4"
windows4 = []
print x
step = 60*15
import pprint
windows4.append(list(chunks(x, step)))
print "Num windows4: ", len(windows4[0])

from itertools import izip, chain, repeat
def grouper(n, iterable, padvalue=None):
    "grouper(3, 'abcdefg', 'x') --> ('a','b','c'), ('d','e','f'), ('g','x','x')"
    return izip(*[chain(iterable, repeat(padvalue, n-1))]*n)
"""
print "===============> WINDOW 5"
step = 60*15
windows4 = []
import pprint
pprint.pprint(list(grouper(step, x)))
"""

