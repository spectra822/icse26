/* https://probgate.org/viewanalysis.php?pid=978 */
#include <stdio.h>
#include <string.h>

#define N	4000
#define L	62
#define K	((N + L - 1) / L)
#define MD	998244353

void shift(long long *aa, long long *bb, int s) {
	int h, q, r;

	memset(bb, 0, K * sizeof *bb);
	q = s / L, r = s % L;
	for (h = 0; h + q < K; h++) {
		bb[h + q] |= (aa[h] & (1LL << L - r) - 1) << r;
		if (h + q + 1 < K && r > 0)
			bb[h + q + 1] |= aa[h] >> L - r;
	}
}

void xor(long long *aa, long long *bb) {
	int h;

	for (h = 0; h < K; h++)
		aa[h] ^= bb[h];
}

int main() {
	static char s[N + 1];
	static long long aa[K], bb_[K], cc[K], dd_[K], *bb = bb_, *dd = dd_;
	static int p2[N];
	int m, n, l, i, j, p, ans;

	scanf("%d%s", &m, s), n = strlen(s);
	for (i = 0; i < n; i++)
		if (s[i] == '1')
			aa[(n - 1 - i) / L] |= 1LL << (n - 1 - i) % L;
	while (m--) {
		scanf("%s", s), l = strlen(s);
		memset(bb, 0, K * sizeof *bb);
		for (i = 0; i < l; i++)
			if (s[i] == '1')
				bb[(l - 1 - i) / L] |= 1LL << (l - 1 - i) % L;
		i = j = N - 1;
		while (1) {
			long long *tt;
			int tmp;

			while (i >= 0 && (dd[i / L] & 1LL << i % L) == 0)
				i--;
			while (j >= 0 && (bb[j / L] & 1LL << j % L) == 0)
				j--;
			if (i < j)
				tt = dd, dd = bb, bb = tt, tmp = i, i = j, j = tmp;
			if (j < 0)
				break;
			shift(bb, cc, i - j);
			xor(dd, cc);
		}
	}
	l = N;
	while (l > 0 && (dd[(l - 1) / L] & 1LL << (l - 1) % L) == 0)
		l--;
	p = 1;
	for (i = 0; i < n; i++) {
		p2[i] = p;
		p = p * 2 % MD;
	}
	memset(bb, 0, K * sizeof *bb);
	ans = 0;
	for (i = n - 1; i >= 0; i--) {
		int x = aa[i / L] >> i % L & 1, y = bb[i / L] >> i % L & 1;

		if (i >= l - 1 && x == 1)
			ans = (ans + p2[i - l + 1]) % MD;
		if (x != y) {
			if (i >= l - 1) {
				shift(dd, cc, i - l + 1);
				xor(bb, cc);
			} else {
				if (x > y)
					ans = (ans + 1) % MD;
				break;
			}
		}
	}
	if (i < 0)
		ans = (ans + 1) % MD;
	printf("%d\n", ans);
	return 0;
}