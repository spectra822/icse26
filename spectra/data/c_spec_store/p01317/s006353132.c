#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MN 205
#define INF 100000000
#define init(a) memset(a,0x0f,sizeof(a))
#define min(a,b) (a<b?a:b)
int N,M,R,de[1005],S[MN][MN],L[MN][MN],i,j,k,x,y,s;
int dp[1005][205];

int main()
{
	for(;scanf("%d%d",&N,&M),N;)
	{
		init(S);init(L);init(dp);
		for(i=0;i<N;i++)L[i][i]=S[i][i]=0;
		for(i=0;i<M;i++)
		{
			char t;
			scanf("%d%d%d %c",&x,&y,&s,&t);
			x--;y--;
			if(t=='L')L[x][y]=L[y][x]=s;
			else S[x][y]=S[y][x]=s;
		}
		for(scanf("%d",&R),i=0;i<R;de[i++]--)scanf("%d",&de[i]);
		for(k=0;k<N;k++)
			for(i=0;i<N;i++)
				for(j=0;j<N;j++)
				{
					S[i][j]=min(S[i][j],S[i][k]+S[k][j]);
					L[i][j]=min(L[i][j],L[i][k]+L[k][j]);
				}
		dp[0][de[0]]=0;
		for(k=0;k<R-1;k++)
			for(i=0;i<N;i++)
				for(j=0;j<N;j++)
				{
					dp[k+1][i] = min(dp[k+1][i],dp[k][j]+L[de[k]][j]+S[j][i]+L[i][de[k+1]]);
					if(i == j) dp[k+1][i] = min(dp[k+1][i], dp[k][j] + L[de[k]][de[k+1]]);
				}
		for(i=0,s=INF;i<N;i++)s=min(s,dp[R-1][i]);
		printf("%d\n",s);
	}
	return 0;
}