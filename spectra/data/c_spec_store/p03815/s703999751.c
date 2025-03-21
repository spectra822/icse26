#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(void){

    long long x;

    scanf("%lld", &x);

    if(x % 11 == 0){
        printf("%lld\n", 2 * (x / 11));
    }else if(x % 11 > 6){
        printf("%lld\n", 2 * (x / 11) + 2);
    }else{
        printf("%lld\n", 2 * (x / 11) + 1);
    }

    return 0;
}