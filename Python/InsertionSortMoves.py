
def insertion_sort_distance(arr):
    swap_count = 0
    for i in range(1, len(arr)):
        j = i
        #print "Inspecting (%d), i (%d), j(%d)" % (arr[i], i, j)
        while j > 0 and arr[j] < arr[j-1]:
            swap(arr, j, j-1)
            swap_count += 1
            #print "After swap: %s" % arr
            j = j-1
    print arr
    return (swap_count, arr)   

def insertion_sort(arr):
    for i in range(1, len(arr)):
        j = i
        #print "Inspecting (%d), i (%d), j(%d)" % (arr[i], i, j)
        while j > 0 and arr[j] < arr[j-1]:
            swap(arr, j, j-1)
            #print "After swap: %s" % arr
            j = j-1
    print arr
    return arr    

def swap(arr, i,j):
    tmp = arr[i]
    arr[i] = arr[j]
    arr[j] = tmp



