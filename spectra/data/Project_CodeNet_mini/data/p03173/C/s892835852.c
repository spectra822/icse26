#include <stdio.h>

int N, a[401];
long long dp[401][401] = {}, sum[401];
const long long sup = (long long)1 << 60;

long long recursion(int l, int r)
{
	if (dp[l][r] != 0 || l == r) return dp[l][r];
	else dp[l][r] = sup;
	
	int k;
	long long tmp;
	for (k = l + 1; k <= r; k++) {
		tmp = recursion(l, k - 1) + recursion(k, r);
		if (tmp < dp[l][r]) dp[l][r] = tmp;
	}
	dp[l][r] += sum[r] - sum[l-1];
	return dp[l][r];
}

int main()
{
	int i;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%d", &(a[i]));
	for (i = 1, sum[0] = 0; i <= N; i++) sum[i] = sum[i-1] + a[i];
	printf("%lld\n", recursion(1, N));
	fflush(stdout);
	return 0;
}