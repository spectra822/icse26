#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(void){

    int n, m;

    scanf("%d%d", &n, &m);

    long long x[n+1], y[m+1];

    for(int i = 1; i <= n; i++){
        scanf("%lld", &x[i]);
    }
    for(int i = 1; i <= m; i++){
        scanf("%lld", &y[i]);
    }

    long long t = 0;

    for(int i = 1; i <= n; i++){
        t = (t + (i-1)*x[i] - (n-i)*x[i]) % 1000000007;
    }

    long long k = 0;

    for(int i = 1; i <= m; i++){
        k = (k + (i-1)*y[i] - (m-i)*y[i]) % 1000000007;
    }

    printf("%lld\n", (t*k)%1000000007);

    return 0;
}