#include<stdio.h>
#include<string.h>

long long dp[2010][2010];
#define mod 1000000007
int main(){
	int n, m;
	int s[2010], t[2010];
	scanf("%d%d", &n,&m);	
	for(int i = 0; i < n; i++) scanf("%d", s+i);
	for(int i = 0; i < m; i++) scanf("%d", t+i);

	for(int i = 0; i <= n; i++){
		for(int j = 0; j <= m; j++){
			if(i == 0 || j == 0){
				dp[i][j] = 1;
				continue;
			}
			dp[i][j] = (dp[i-1][j] + dp[i][j-1]) % mod;
			if(s[i-1] != t[j-1]){
				// dp[i-1][j-1] を mod の世界で引く
				dp[i][j] -= dp[i-1][j-1];
				dp[i][j] = dp[i][j] % mod;
				if(dp[i][j] < 0) {
					dp[i][j] += mod;
				}
			} 	
		}
	}
	printf("%lld\n", dp[n][m]);
	//cout << dp[n][m] << endl;
}
