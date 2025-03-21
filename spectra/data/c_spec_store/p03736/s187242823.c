#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N	200000
#define INF	0x3f3f3f3f3f3f3f3fLL

long long min(long long a, long long b) { return a < b ? a : b; }

void update(long long *ft, int i, int n, long long x) {
	while (i < n) {
		ft[i] = min(ft[i], x);
		i |= i + 1;
	}
}

long long query(long long *ft, int i) {
	long long x = INF;

	while (i >= 0) {
		x = min(x, ft[i]);
		i &= i + 1, i--;
	}
	return x;
}

int main() {
	static long long dp[N], ft1[N], ft2[N];
	int n, q, i, j;
	long long d, ans;

	scanf("%d%d%d%d", &n, &q, &i, &j), i--, j--;
	memset(ft1, 0x3f, n * sizeof *ft1);
	memset(ft2, 0x3f, n * sizeof *ft2);
	update(ft1, j, n, -j);
	update(ft2, n - 1 - j, n, j);
	d = 0;
	while (q--) {
		int i_;
		long long x;

		scanf("%d", &i_), i_--;
		d += abs(i - i_);
		x = min(query(ft1, i_) + i_, query(ft2, n - 1 - i_) - i_) - abs(i - i_);
		dp[i] = min(dp[i], x);
		update(ft1, i, n, x - i);
		update(ft2, n - 1 - i, n, x + i);
		i = i_;
	}
	ans = INF;
	for (i = 0; i < n; i++)
		ans = min(ans, dp[i]);
	ans += d;
	printf("%lld\n", ans);
	return 0;
}
