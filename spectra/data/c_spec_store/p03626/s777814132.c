#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

int main(void){

    int N;

    scanf("%d", &N);

    char S1[N+1], S2[N+1];

    scanf("%s%s", S1, S2);

    long long ans = 1;

    int t;

    if(S1[0] == S2[0]){
        ans = 3;
        t = 1;
    }else{
        ans = 6;
        t = 0;
    }

    long long m = 1000000007;

    for(int i = 1; i < N; i++){
        if(S1[i] == S2[i]){
            if(t == 1){
                ans = (ans * 2) % m;
            }
            t = 1;
        }
        if(S1[i] == S1[i+1]){
            if(t == 1){
                ans = (ans * 2) % m;
            }else{
                ans = (ans * 3) % m;
            }
            t = 0;
        }
    }

    printf("%lld\n", ans);

    return 0;
}