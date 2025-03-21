#include <stdio.h>
#define ll long long
#define rep(i,l,r)for(ll i=(l);i<(r);i++)
ll pom(ll a,ll n,int m){ll x=1;for(a%=m;n;n/=2)n&1?x=x*a%m:0,a=a*a%m;return x;}
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
	int n,m;
	scanf("%d%d",&n,&m);
	makefact(2010,m);
	ll ans=0;
	rep(i,1,n){
		ll temp=0;
		rep(j,0,n-i){
			//赤がi個で、黒n-i個のうちj個が赤と繋がっていない
			ll aaa=pom(pom(2,(n-i-j),m)-1,i,m)*choose(n-i,j,m)%m;
			temp+=j%2?-aaa:aaa;
		}
		ans+=temp%m*pom(2,i*(i-1)/2,m)%m*pom(2,(n-i)*(n-i-1)/2,m)%m*choose(n,i,m)%m;
	}
	printf("%lld\n",(ans%m+m)%m);
}
