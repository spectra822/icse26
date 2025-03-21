#include <stdio.h>
#include <string.h>
#define mod 1000000007
#define calc(x) (1LL*((x&1)?0:pw[x>>1]))
#define add_edge(u,v) to[tot]=v;pre[tot]=lst[u];lst[u]=tot++
int lst[5005],to[10005],pre[10005],tot,sz[5005],dp_sz[5005],n;
long long dp[5005][5005][2],pw[5005]={1},tmp[5005][2],ans=0;
void init_dfs(int u,int fa)
{
	sz[u]=1;
	for (int i=lst[u];~i;i=pre[i])
	{
		if (to[i]==fa) continue;
		init_dfs(to[i],u);
		sz[u]+=sz[to[i]];
	}
}
void dfs(int u,int fa)
{
	dp[u][0][0]=1;
	for (int i=lst[u];~i;i=pre[i])
	{
		int v=to[i];
		if (v==fa) continue;
		dfs(v,u);
		memset(tmp,0,sizeof(tmp));
		for (int x=dp_sz[u];x>=0;x--)
		{
			for (int y=dp_sz[v];y>=0;y--)
			{
				tmp[x+y][0]=(tmp[x+y][0]+dp[u][x][0]*dp[v][y][0])%mod;
				tmp[x+y][0]=(tmp[x+y][0]+dp[u][x][1]*dp[v][y][1])%mod;
				tmp[x+y][1]=(tmp[x+y][1]+dp[u][x][0]*dp[v][y][1])%mod;
				tmp[x+y][1]=(tmp[x+y][1]+dp[u][x][1]*dp[v][y][0])%mod;
			}
		}
		memcpy(dp[u],tmp,sizeof(tmp));
		dp_sz[u]+=dp_sz[v];
	}
	if (u)
	{
		for (int x=dp_sz[u];x>=0;x--)
		{
			dp[u][sz[u]][0]=(dp[u][sz[u]][0]+dp[u][x][1]*calc(sz[u]-x))%mod;
			dp[u][sz[u]][1]=(dp[u][sz[u]][1]+dp[u][x][0]*calc(sz[u]-x))%mod;
		}
	}
	dp_sz[u]++;
}
int main()
{
	memset(lst,-1,sizeof(lst));
	scanf("%d",&n);
	for (int i=1;i<=n;i++) pw[i]=pw[i-1]*(i*2-1)%mod;
	for (int i=1;i<n;i++)
	{
		int u,v;
		scanf("%d%d",&u,&v);
		--u,--v;
		add_edge(u,v);
		add_edge(v,u);
	}
	init_dfs(0,-1);dfs(0,-1);
	for (int i=0;i<=n;i++)
	{
		ans=(ans+dp[0][i][0]*calc(n-i))%mod;
		ans=(ans-dp[0][i][1]*calc(n-i))%mod;
	}
	printf("%lld\n",(ans+mod)%mod);
	return 0;
}