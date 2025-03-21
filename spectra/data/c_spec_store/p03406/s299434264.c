#include <stdio.h>

#define N	16
#define M	16
#define N_	(1 << N)
#define MD	1000000007

int vv[N_], ff[N_], gg[N_];

void init() {
	int i;

	ff[0] = gg[0] = 1;
	for (i = 1; i < N_; i++) {
		vv[i] = i == 1 ? 1 : (long long) vv[i - MD % i] * (MD / i + 1) % MD;
		ff[i] = (long long) ff[i - 1] * i % MD;
		gg[i] = (long long) gg[i - 1] * vv[i] % MD;
	}
}

long long choose(int n, int k) {
	return k > n ? 0 : (long long) ff[n] * gg[k] % MD * gg[n - k] % MD;
}

int main() {
	static int aa[M], dp[N_];
	int n, m, h, i, b, ans;

	init();
	scanf("%d%d", &n, &m);
	for (h = 0; h < m; h++)
		scanf("%d", &aa[h]), aa[h] = (1 << n) - aa[h];
	dp[0] = 1;
	for (h = m - 1; h >= 0; h--)
		for (b = (1 << n) - 1; b >= 0; b--) {
			int x = dp[b];

			if (x == 0)
				continue;
			for (i = 0; i < n; i++)
				if ((b & 1 << i) == 0)
					dp[b | 1 << i] = (dp[b | 1 << i] + x * choose(aa[h] - b, (1 << i) - 1)) % MD;
		}
	ans = 0;
	for (b = 0; b < 1 << n; b++) {
		int x, n_, cnt;

		x = dp[b];
		if (x == 0)
			continue;
		n_ = (1 << n) - 1 - b, cnt = n;
		for (i = 0; i < n; i++)
			if ((b & 1 << i) == 0) {
				x = x * choose(n_, 1 << i) % MD;
				n_ -= 1 << i;
				cnt++;
			}
		ans = (ans + (cnt % 2 == 0 ? 1 : -1) * x) % MD;
	}
	for (i = 0; i < n; i++)
		ans = (long long) ans * ff[1 << i] * 2 % MD;
	if (ans < 0)
		ans += MD;
	printf("%d\n", ans);
	return 0;
}
