tmp = map(int, raw_input().strip().split(' '))

memo = {} 

def ffib(n0, n1, cnt):
    if cnt == 0:
        return n0
    n2 = n0 + n1**2;
    return ffib(n1, n2, cnt-1)

n0 = tmp[0]
n1 = tmp[1]
term = tmp[2]
if term < 2:
    print  tmp[term-1]
    #print "Already specified first two terms." 
    exit(-1)

print ffib(n0, n1, term-1)


