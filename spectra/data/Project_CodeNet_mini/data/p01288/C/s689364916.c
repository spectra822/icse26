#include<stdio.h>
int P[100005],M[100005],v[100005],i,j,N,Q,t;
long long r;
char q[100005];


int main()
{
	for(;scanf("%d%d",&N,&Q),N;)
	{
		for(i=r=0;i<N;P[i]=i,M[i]=0,i++);
		M[1]=1;
		for(i=2;i<=N;P[i]=t,i++)
			scanf("%d\n",&t);
		for(i=0;i<Q;i++)
		{
			scanf("%c %d\n",&q[i],&v[i]);
			if(q[i]=='M')M[v[i]]++;
		}
		for(i=Q-1;i>=0;i--)
		{
			if(q[i]=='M')
				M[v[i]]--;
			else
			{
				for(t=v[i];!M[t];)
					t=P[t];
				r+=t;
			}
		}
		printf("%lld\n",r);
	}
	return 0;
}