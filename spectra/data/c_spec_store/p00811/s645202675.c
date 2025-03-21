#include <stdio.h>

char isprime[100000];
int pr[100000];
int primenum;

void mpl(void) {
	int i,j;
	for(i=0;i<100000;i++)isprime[i]=1;
	isprime[0]=isprime[1]=0;
	primenum=0;
	for(i=2;i<100000;i++) {
		if(isprime[i]) {
			pr[primenum++]=i;
			for(j=i+i;j<100000;j+=i)isprime[j]=0;
		}
	}
}

int main(void) {
	int m,a,b;
	mpl();
	while(scanf("%d%d%d",&m,&a,&b)==3 && (m|a|b)!=0) {
		int i;
		int p=0,q=0;
		for(i=0;i<primenum;i++) {
			int l=i,r=primenum-1;
			while(l<=r) {
				int j=(l+r)/2;
				if((long long)pr[i]*pr[j]<=m &&
				(long long)a*pr[j]<=(long long)pr[i]*b) {
					l=j+1;
				} else {
					r=j-1;
				}
			}
			if(l>i && (long long)pr[i]*pr[l-1]<=m &&
			(long long)a*pr[l-1]<=(long long)pr[i]*b && pr[i]*pr[l-1]>p*q) {
				p=pr[i];
				q=pr[l-1];
			}
		}
		printf("%d %d\n",p,q);
	}
	return 0;
}