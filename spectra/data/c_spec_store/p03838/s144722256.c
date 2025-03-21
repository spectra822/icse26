#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
typedef long long ll;
#define rep(i,n) for(ll i=0; i<(ll)(n); i++)
#define max(l,r) ((l)>(r)?l:r)
#define min(l,r) ((l)<(r)?l:r)

int main(){
    //input
    int x, y;
    scanf("%d%d", &x, &y);

    //solve
    ll ans = 0;
    if(x >= 0){
        if(y >= x) ans = - x + y;
        else if(y > 0) ans = x - y + 2;
        else if(y >= -x) ans = x + y + 1;
        else ans = - y - x + 1;
    }else{
        if(y >= -x) ans = x + y + 1;
        else if(y > 0) ans = - x - y + 1;
        else if(y >= x) ans = - x + y;
        else ans = x - y + 2;
    }

    //output
    printf("%lld", ans);
}