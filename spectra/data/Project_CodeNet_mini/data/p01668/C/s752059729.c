#include <stdio.h>
#include <string.h>

#define MOD_BY 1000000007

int add(int a,int b) {
	int r=a+b;
	if(r>=MOD_BY)r-=MOD_BY;
	return r;
}

/*
int mul(int a,int b) {
	return (int)(((long long)a*(long long)b)%MOD_BY);
}
*/

int N,M;
int existPos;
char A[10240];
char B[10240];
char C[512];

int memo[10002][502][2][2];
int numberOfNumber[10002][2][2];

int getNumberOfNumber(int pos,int ueFlag,int sitaFlag) {
	int ret=0;
	int i;
	int imin,imax;
	if(pos>=N)return 1;
	if(numberOfNumber[pos][ueFlag][sitaFlag]>0)return numberOfNumber[pos][ueFlag][sitaFlag]-1;

	imin=sitaFlag?A[pos]:0;
	imax=ueFlag?B[pos]:9;
	for(i=imin;i<=imax;i++) {
		ret=add(ret,getNumberOfNumber(pos+1,ueFlag&&(i==imax),sitaFlag&&(i==imin)));
	}

	numberOfNumber[pos][ueFlag][sitaFlag]=ret+1;
	return ret;
}

int search(int pos,int seqPos,int ueFlag,int sitaFlag) {
	int ret=0;
	int i;
	int imin,imax;

	if(seqPos>=M)return getNumberOfNumber(pos,ueFlag,sitaFlag);
	if(pos>=N)return 0;
	if(memo[pos][seqPos][ueFlag][sitaFlag]>0)return memo[pos][seqPos][ueFlag][sitaFlag]-1;

	imin=sitaFlag?A[pos]:0;
	imax=ueFlag?B[pos]:9;
	for(i=imin;i<=imax;i++) {
		if(seqPos==0) {
			ret=add(ret,search(pos+1,0,ueFlag&&(i==imax),sitaFlag&&(i==imin)));
		}
		if((!sitaFlag || i!=imin || existPos<=pos) && seqPos<M && C[seqPos]==i) {
			ret=add(ret,search(pos+1,seqPos+1,ueFlag&&(i==imax),sitaFlag&&(i==imin)));
		}
	}

	memo[pos][seqPos][ueFlag][sitaFlag]=ret+1;
	return ret;
}

int main(void) {
	int Alen,Blen;
	int i;
	if(scanf("%s%s%s",A,B,C)!=3)return 1;
	Alen=strlen(A);
	Blen=strlen(B);
	if(Alen<Blen) {
		for(i=0;i<Alen;i++)A[Blen-i-1]=A[Alen-i-1];
		for(i=0;i<Blen-Alen;i++)A[i]='0';
	}
	N=Blen;
	M=strlen(C);
	existPos=Blen-Alen;
	for(i=0;i<N;i++) {
		A[i]-='0';
		B[i]-='0';
	}
	for(i=0;i<M;i++)C[i]-='0';
	printf("%d\n",search(0,0,1,1));
	return 0;
}