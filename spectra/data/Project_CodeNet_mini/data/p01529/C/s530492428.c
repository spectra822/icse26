// AOJ 2415: Sashimi
// 2017.12.8 bal4u@uu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

ll w[4001];
char buf[48002], *p;
ll dp[4001][4001];
int k[4001][4001];

ll getlong()
{
	ll n = 0;
	while (*p >= '0') n = (n<<3) + (n<<1) + (*p++ & 0xf);
	p++;
	return n;
}

int main()
{
	int n, i, j, a, b;
	ll c;

	fgets(buf, 10, stdin), n = atoi(buf);
	fgets(p=buf, sizeof(buf), stdin);
	w[0] = getlong();
	for (i = 1; i < n; i++) w[i] = w[i-1] + getlong();

	memset(dp, 0x33, sizeof(dp));
	for (i = 0; i < n; i++) dp[i][i] = 0, k[i][i] = i;

	for (a = 1; a <= n; a++) for (i = 0, j = a; j < n; i++, j++) {
		for (b = k[i][j-1]; b <= k[i+1][j]; b++) {
			c = dp[i][b] + dp[b+1][j] + w[j];
			if (i > 0) c -= w[i-1];
			if (dp[i][j] > c) dp[i][j] = c, k[i][j] = b;
		}
	}
	printf("%lld\n", dp[0][n-1]);
	return 0;
}