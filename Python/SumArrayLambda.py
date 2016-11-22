import sys

n = (raw_input().strip())
arr = map(int, raw_input().strip().split())

print reduce(lambda x,y: x+y, arr)

