#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int N,i,j,k,c,a,A[10000000],R[3]={9999999999,9999999999,9999999999};

int cmp(int *a,int *b){return *a>*b;}

int main()
{
	scanf("%d",&N);
	for(i=0;i<N;i++)scanf("%d",&A[i]);

	for(i=0;i<N;i++)
		for(j=0;j<N;j++)
		{
			if(i!=j)
			{
				for(k=10;A[j]%k!=A[j];k*=10);
				a=A[i]*k+A[j];
				for(k=0;k<3;k++)
					if(R[k]>a)a^=R[k]^=a^=R[k];
			}
		}
	printf("%d\n",R[2]);
	return 0;
}