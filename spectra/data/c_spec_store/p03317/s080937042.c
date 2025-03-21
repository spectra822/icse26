#include<stdio.h>
int main()
{
    long long int n,k,i,x,t;
    scanf("%lld%lld",&n,&k);
    long long int a[n];
    for(i=0;i<n;i++){
        scanf("%lld",&a[i]);
    }
    t=((n-k)/(k-1))+1;
   if(k+((t-1)*(k-1))<n)t++;
   printf("%lld\n",t);
}
