#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <limits.h>
#include <stdbool.h>

/* 
 * INPUT:
 * 5
 * 1000000001 1000000002 1000000003 1000000004 1000000005
 *
 * OUTPUT:
 * 5000000015
 */

long int sum(int n, long int* arr) {
    long int sum = 0;
    for (int i = 0; i<n; i++) {
        //printf("%d\n", arr[i]);
        sum += arr[i];
    }
    return sum;
}

int main(){
    int n; 
    scanf("%d",&n);
    long int arr[n];
    for(int arr_i = 0; arr_i < n; arr_i++){
       scanf("%ld",&arr[arr_i]);
    }
    
    printf("%ld", sum(n, arr));
    return 0;
}
