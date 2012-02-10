#include <stdlib.h>

#include <stdio.h>
#include <time.h>
#include <math.h>


int main()
{
    //srand(time(0));
    for (int i = 0; i< 100; i++) {
        int r = rand();
        double x = (double)r/RAND_MAX;
        double inc = (floor(x*100+0.5)/100);
        fprintf(stderr, "%d=>%f=>%f \n", r, x, inc);
    }
}
