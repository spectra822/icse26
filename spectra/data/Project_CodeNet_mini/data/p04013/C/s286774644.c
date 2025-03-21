#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(void){

    long long N;
    long long A;

    scanf("%lld%lld", &N, &A);

    long long x[N+1];

    long long sum = 0;

    for(long long i = 1; i <= N; i++){
        scanf("%lld", &x[i]);
        sum += x[i];
    }

    long long dp[N+1][N+1][sum+1];

    for(long long j = 0; j <= N; j++){
        for(long long k = 0; k <= N; k++){
            for(long long s = 0; s <= sum; s++){
                if(j >= 1 && s < x[j]){
                    dp[j][k][s] = dp[j-1][k][s];
                }else if(j >= 1 && k >= 1 && s >= x[j]){
                    dp[j][k][s] = dp[j-1][k][s] + dp[j-1][k-1][s-x[j]];
                }else if(j == 0 && k == 0 && s == 0){
                    dp[j][k][s] = 1;
                }else{
                    dp[j][k][s] = 0;
                }
            }
        }
    }

    long long ans = 0;

    long long max;

    if(sum/A < N){
        max = sum/A;
    }else{
        max = N;
    }

    for(long long k = 1; k <= max; k++){
        ans += dp[N][k][k*A];
    }

    printf("%lld\n", ans);

    return 0;
}