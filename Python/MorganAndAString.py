n = int(raw_input().strip())

def lexMin(l1, l2):
    #print "%s %s" % (l1, l2)
    output = []
    len1 = len(l1)
    len2 = len(l2)
    i = 0
    j = 0
    mark = None 
    while i < len1 and j < len2:
        #print l1[i:], '\n',  l2[j:] 
        if l1[i:] < l2[j:]:
            output.append(l1[i])
            i += 1
        else:
            output.append(l2[j])
            j += 1

            
        """
        else:
            mark = (i,j)
            while j < len2 and i < len1 and l2[j] == l1[i]: 
                print "len1 %s len2 %s" % (len1, len2)
                print "l1(i): %s(%s) l2: %s(%s)" % (l1, i, l2, j)
                i += 1
                j += 1

            #output.append(l1[mark[0]:i])
        """

    output.extend(l1[i:])
    output.extend(l2[j:])
    """
    for x in l1[i:]:
        #print x,
        output.append(x)
    for y in l2[j:]:
        #print y,
        output.append(y)
    """
    return output

for i in range(n):
    line1 = raw_input().strip()
    line2 = raw_input().strip()
    
    out = lexMin(line1, line2)
    print "".join(out) 

