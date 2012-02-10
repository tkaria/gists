import scipy
import scipy.stats as stats
import numpy
import random
import timeit

def foo(x, n=1,p=0.8):
    print "In foo x = ", x
    return stats.binom.ppf(numpy.random.rand(), n, p)

def f(c=foo):
    print "f()"
    b = numpy.random.rand()
    print foo(b)

f()

#s = """
#import scipy.stats as stats
#import numpy
#stats.binom.ppf(numpy.random.rand(), n, p)
#"""
##
#t = timeit.Timer(stmt=s)
#print "$.2f usec/pass" % (1000000 * t.timeit(number=1000000)/1000000)
