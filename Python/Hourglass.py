
def hourglass_sum(arr):
    rows = len(arr)
    hourglass = []
    hsum, total = -float("inf"),0
    #hourglass.append([], [], [])
    for i in range(4):
        for j in range(4):
            top = arr[i][j:j+3]
            mid = arr[i+1][j+1]
            bot = arr[i+2][j:j+3]
            #print top
            #print mid 
            #print bot
            #print '----------------------'
            total = mid
            for e in (top +  bot):
                total += int(e)
            if total > hsum:
                hsum = total
            #print arr[i][i:i+3]
    print hsum

arr = []
#arr = [[0, 1, 2, 3, 4, 5],
 #[6, 7, 8, 9, 10, 11],
 #[12, 13, 14, 15, 16, 17],
 #[18, 19, 20, 21, 22, 23],
 #[24, 25, 26, 27, 28, 29],
 #[30, 31, 32, 33, 34, 35]]

#arr = [[1,1,1,0,0,0],
    #[0,1,0,0,0,0],
    #[1,1,1,0,0,0],
    #[0,0,2,4,4,0],
    #[0,0,0,2,0,0],
    #[0,0,1,2,4,0]]

if len(arr) == 0:
    for i in xrange(6):
        arr_temp = map(int, raw_input().strip().split(' '))
        arr.append(arr_temp)
        print arr_temp


hourglass_sum(arr)


