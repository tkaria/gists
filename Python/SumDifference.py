N=input()
sumi=0;
j=0;
for i in range(N):
    a,b=raw_input().split()
    sumi+=int(a)-int(b)
    if(sumi<0):
        sumi=0
        j=i+1
print(j)

