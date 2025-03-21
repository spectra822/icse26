#include <stdio.h>

#define N	8
#define MD	1000000007

long long min(long long a, long long b) { return a < b ? a : b; }
long long max(long long a, long long b) { return a > b ? a : b; }

int cnt[N + 1];

void init() {
	int i;

	cnt[1] = 9;
	for (i = 2; i <= N; i++)
		cnt[i] = cnt[i - 1] * 10;
}

long long power(int a, int k) {
	long long p = 1, b = a;

	while (k) {
		if (k & 1)
			p = p * b % MD;
		b = b * b % MD;
		k >>= 1;
	}
	return p;
}

int main() {
	int s, l1, l2, r1, a, ans;

	init();
	scanf("%d", &s);
	ans = (s - 1) / N;
	for (l1 = 1; l1 <= N; l1++) {
		int s_;

		if (s % l1 == 0 && cnt[l1] >= s / l1)
			ans = (ans + cnt[l1] - s / l1 + 1) % MD;
		s_ = s;
		for (l2 = l1 + 1; l2 <= N; l2++) {
			long long lower, upper;

			lower = (max(s_ - (long long) cnt[l2] * l2, 1) + l1 - 1) / l1;
			upper = min((s_ - l2) / l1, cnt[l1]);
			if (lower <= upper)
				for (r1 = 1; r1 <= l2; r1++)
					if ((s_ - r1 * l1) % l2 == 0)
						ans = (ans + (upper + l2 - r1) / l2 - (lower - 1 + l2 - r1) / l2) % MD;
			if (s_ / l2 < cnt[l2])
				break;
			s_ -= cnt[l2] * l2;
		}
	}
	for (a = 1; a <= s / a; a++)
		if (s % a == 0) {
			if (a > N)
				ans = (ans + power(10, a - 1) * 9 - s / a) % MD;
			if (a != s / a && s / a > N)
				ans = (ans + power(10, s / a - 1) * 9 - a) % MD;
		}
	if (ans < 0)
		ans += MD;
	printf("%d\n", ans);
	return 0;
}
