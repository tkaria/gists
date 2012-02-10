import scipy
import scipy.stats as stats
import numpy
import random
import timeit

def a():
    def b():
        print "b()"

    print "a()"


a()
a.b()

#s = """
#import scipy.stats as stats
#import numpy
#stats.binom.ppf(numpy.random.rand(), n, p)
#"""
##
#t = timeit.Timer(stmt=s)
#print "$.2f usec/pass" % (1000000 * t.timeit(number=1000000)/1000000)
