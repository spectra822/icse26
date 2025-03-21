#include <stdio.h>

#define Mod 1000000007

int main()
{	
	int N, M;
	scanf("%d %d", &N, &M);
	
	int i, j, k;
	long long dp[302][302] = {}, tmp;
	for (k = 1, dp[1][1] = 1; k <= M; k++) {
		for (i = k; i >= 1; i--) {
			for (j = i; j >= 1; j--) {
				tmp = dp[i][j] % Mod;
				dp[i][j] = 0;
				dp[i+1][j] += tmp * (N - i);
				dp[i][i] += tmp * j;
				dp[i][j] += tmp * (i - j);
			}
		}
	}
	
	printf("%lld\n", dp[N][N] % Mod);
	fflush(stdout);
	return 0;
}