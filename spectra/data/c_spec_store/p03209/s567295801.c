typedef long long LL;
LL n,k;
LL f(LL n,LL x){if(!n)return(x<=0?0:1);
LL p=(1LL<<n)-1;
if(x<=2*p)return f(n-1,x-1);else return p+1+f(n-1,x-1-2*p);}
main(){scanf("%lld%lld",&n,&k);printf("%lld",f(n,k));}