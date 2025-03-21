#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MOD 1000000007
#define ll long long

int main(){
    ll k;
    ll n;
    scanf("%lld",&k);
    if(k>=50){
        n=50;
        ll a[n];
        ll rem=k/50;
        ll x=49+rem;
        ll t=k%50;
        ll i,j;
        for(i=0;i<50;i++) a[i]=x;
        for(i=0;i<t;i++){
            a[i]+=50;
            for(j=0;j<50;j++) if(j!=i) a[j]--;
        }
        printf("50\n");
        for(i=0;i<50;i++) printf("%lld ",a[i]);
    } else if(k>=2){
        n=k;
        printf("%lld\n",n);
        for(int i=0;i<n;i++) printf("%lld ",n);
    } else if(k==0) printf("4\n3 3 3 3\n");
    else printf("3\n1 0 3\n");
    return 0;
}
