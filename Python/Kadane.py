"""
Kadane-input01 output:
2617065 172083036
1274115 193037987
2202862 163398048
2454939 240462364
3239908 186256172
2486039 202399661
1092777 137409985
962621 135978139
3020911 224370860
1755033 158953999
"""

def Kadane(A):
    """ A must be a positive arrays only """
    max_ending_here = 0
    max_so_far = 0
    for x in A:
        max_ending_here = max(0, max_ending_here + x)
        max_so_far = max(max_so_far, max_ending_here)
    return max_so_far

def Kadane1(A):
    """ A may be mixed list of positive or negative numbers """
    if len(A) == 0:
        return 0
    if len(A) == 1:
        return A[0]

    max_ending_here = A[0]
    max_so_far = A[0]

    for x in A[1:]:
        max_ending_here = max(x, max_ending_here + x)
        max_so_far = max(max_so_far, max_ending_here)
    return max_so_far

def MaxNonContig(A):
    l = len(A)
    s = 0
    max_neg = -float("inf") 
    nneg = 0
    for x in A:
        #print "Current: %s" % x
        if x < 0:
            nneg += 1
            max_neg = max(max_neg, x)
            #print "max_neg: %s" % max_neg
        else:
            s += x
            #print "sum: %s" % s
    if nneg == l:
        s = max_neg
    return s



examples = int(raw_input().strip())

for x in range(examples):
    an = int(raw_input().strip())
    a = map(int, raw_input().strip().split(' '))
    print Kadane1(a), MaxNonContig(a)
