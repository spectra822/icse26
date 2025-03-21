#include <stdio.h>
#define ll long long
#define rep(i,l,r)for(ll i=l;i<r;i++)

ll d4[]={0,1,0,-1,0};

int main(){
	ll n;
	while(scanf("%lld",&n),n){
		ll a[25][25]={};
		rep(i,0,n){
			ll x,y;
			scanf("%lld%lld",&x,&y);
			a[x][y]=1;
		}
		ll m;
		scanf("%lld",&m);
		ll px=10,py=10;
		if(a[px][py]){
			a[px][py]=0;
			n--;
		}
		rep(i,0,m){
			char c;
			ll d,q;
			scanf(" %c %lld",&c,&q);
			if(c=='N')d=0;
			else if(c=='E')d=1;
			else if(c=='S')d=2;
			else d=3;
			while(q--){
				px+=d4[d];
				py+=d4[d+1];
				if(a[px][py]){
					a[px][py]=0;
					n--;
				}
			}
		}
		puts(n?"No":"Yes");
	}
}
