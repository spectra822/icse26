#include<stdio.h>
#define ll long long
#define max(p,q)((p)>(q)?(p):(q))

ll a[100010];
int main(){
	int n;
	scanf("%d",&n);
	for(int i=0;i<n;i++)scanf("%lld",a+i);
	ll ans=0;
	for(int d=1;d*2<n-1;d++){
		int s=0,g=n-1;
		ll crr=0;
		while(1){
			int ns=s+d;
			int ng=g-d;
			if(ng<=d||ns==ng||ns==g)break;
			s=ns;
			g=ng;
			crr+=a[s]+a[g];
			ans=max(ans,crr);
		}
	}
	printf("%lld",ans);
}