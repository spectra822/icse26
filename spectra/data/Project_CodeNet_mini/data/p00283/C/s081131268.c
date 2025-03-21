#include <stdio.h>

#define INF 1000

int D,N;
int a[100];
int e[100];
int r[100];

int memo[101][101];

int search(int tkrk,int kkt) {
	int ret=INF;
	int i;
	if(tkrk<=0)return 0;
	if(memo[tkrk][kkt]>0)return memo[tkrk][kkt]-1;
	memo[tkrk][kkt]=INF+1;
	for(i=0;i<N;i++) {
		if(kkt>=r[i]) {
			int next_kkt=kkt+e[i];
			int candidate;
			if(next_kkt>100)next_kkt=100;
			candidate=search(tkrk-a[i],next_kkt)+1;
			if(candidate<ret)ret=candidate;
		}
	}
	memo[tkrk][kkt]=ret+1;
	return ret;
}

int main(void) {
	while(scanf("%d%d",&D,&N)==2 && (D!=0 || N!=0)) {
		int i,j;
		int ret;
		for(i=0;i<N;i++) {
			if(scanf("%d%d%d",&a[i],&e[i],&r[i])!=3)return 1;
		}
		for(i=0;i<=100;i++) {
			for(j=0;j<=100;j++)memo[i][j]=0;
		}
		ret=search(D,0);
		if(ret==INF)puts("NA"); else printf("%d\n",ret);
	}
	return 0;
}