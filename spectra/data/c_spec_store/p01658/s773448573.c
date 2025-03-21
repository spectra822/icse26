#include<stdio.h>
int N,M,A[106],i,j,l,r,a=0;

int main()
{
	scanf("%d%d",&M,&N);
	for(i=0;i<M;i++)
	{
		for(j=0;j<N;j++)
		{
			scanf("%d",&A[j]);
			if(i!=0)A[j]^=1;
		}
		for(l=0,r=N-1;l<=r;)
		{
			if(A[l]==1)
			{
				a++;
				A[++l]^=1;
			}
			else if(A[r]==1)
			{
				a++;
				A[--r]^=1;
			}
			else
			{
				A[++l]^=1;
			}
		}
	}
	printf("%d\n",a);
	return 0;
}