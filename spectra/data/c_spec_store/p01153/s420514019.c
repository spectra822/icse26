// AOJ 2028: Gather on the Clock
// 2017.11.03 bal4u@uu

#include <stdio.h>
#include <string.h>

int a[102];
int dp[102][102];

int main()
{
	int t, n, i, j, k, v, ans;
	
	scanf("%d", &t); while (t--) {
		scanf("%d", &n);
		for (i = 0; i < n; i++) scanf("%d", a+i);
		memset(dp, 0, sizeof(dp));

		for (k = 1; k < n; k++) for (i = 0; i < n; i++) for (j = 0; j < k; j++) {
			int x = i+j+1;
			if (x >= n) x -= n;
			v = a[x] - a[i]; if (v < 0) v = -v;
			v += dp[x][k-j-1] + dp[i][j];
			if (v > dp[i][k]) dp[i][k] = v;
		}

		for (ans = 0, i = 0; i < n; i++) if (dp[i][n-1] > ans) ans = dp[i][n-1];
		printf("%d\n",ans);
	}
	return 0;
}