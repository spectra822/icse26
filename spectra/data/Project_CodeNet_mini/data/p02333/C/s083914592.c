#include <stdio.h>
#define ll long long
#define rep(i,l,r)for(ll i=(l);i<(r);i++)
ll pom(ll a,ll n,int m){ll x=1;for(a%=m;n;n/=2)n&1?x=x*a%m:0,a=a*a%m;return x;}
#define MOD 1000000007
#define invp(a,p)pom(a,p-2,p)

//階乗,二項係数
//*
ll fact[100010];
ll invfact[100010];
void makefact(int n,ll m){
	fact[0]=1;
	rep(i,0,n)fact[i+1]=fact[i]*(i+1)%m;
	invfact[n]=invp(fact[n],m);
	for(int i=n;i>0;i--)invfact[i-1]=invfact[i]*i%m;
}
ll choose(int n,int r,int m){return n<0||r<0||n-r<0?0:fact[n]*invfact[r]%m*invfact[n-r]%m;}
//*/

int main(){
	makefact(2000,MOD);
	int n,m;
	scanf("%d%d",&n,&m);
	ll s=0;
	rep(i,0,m+1)s=(s+choose(m,i,MOD)*pom(i,n,MOD)*((m-i)%2==0?1:-1))%MOD;
	printf("%lld\n",(s+MOD)%MOD);
}
