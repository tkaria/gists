def merge(left, right):
    if left is None or right is None:
        return []
    merged = []
    i,j = 0,0
    while i < len(left) and j<len(right):
        if left[i] < right[j]:
            merged.append(left[i])
            i+=1
        else: # right[j] < left[i]:
            merged.append(right[j])
            j+=1
    
    while i < len(left):
        merged.append(left[i])
        i+=1
    while j < len(right):
        merged.append(right[j])
        j+=1

    return merged
    
def mergesort(a):
    if len(a) < 2:
        return a
    print "Original array is: %s" % a
    mid = int(len(a)/2)
    print "Midpoint selected is: %d" % mid
    left_list = a[0:mid]
    print "Left array is: %s" % left_list

    right_list = a[mid:]
    print "Right array is: %s" % right_list
    left = mergesort(left_list)
    right = mergesort(right_list)
    return merge(left, right)
    
    
