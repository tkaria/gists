#!/bin/python
def insertionSort(ar):    
    for i in range(1,len(ar)):
        j = i
        key = ar[j]
        while j > 0 and key < ar[j-1]:
            ar[j] = ar[j-1]
            j -= 1
            print " ".join(map(str, ar))
        ar[j] = key
    print " ".join(map(str, ar))
    return ""

m = input()
ar = [int(i) for i in raw_input().strip().split()]
insertionSort(ar)

