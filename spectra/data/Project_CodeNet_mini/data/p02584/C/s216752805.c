#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
int main(int argv,char* argc[]){
    long long x,d,k;
    scanf("%lld%lld%lld",&x,&k,&d);
    //double c=(double)d*(double)k;
    x=llabs(x);
    long long now=x;
    if(x/d<=k){
        now-=d*(x/d);
        k-=x/d;
        if(k%2){
            now-=d;
        }
    }else{
        now-=d*k;
    }
    printf("%lld",llabs(now));
    return 0;
}
