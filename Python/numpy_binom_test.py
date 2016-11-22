import scipy
import scipy.stats as stats
import numpy
import random
import timeit


def foo(x, n=1, p=0.8):
    print "In foo x = ", x
    return stats.binom.ppf(numpy.random.rand(), n, p)


def f(c=foo):
    print "f()"
    b = numpy.random.rand()
    print foo(b)

f()

