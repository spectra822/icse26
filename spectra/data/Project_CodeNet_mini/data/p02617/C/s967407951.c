#include <stdio.h>

int main()
{
	int i, N, u, w;
	long long ans = 0, tmp;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) ans += (long long)(N - i + 2) * (N - i + 1) / 2;
	for (i = 1; i <= N - 1; i++) {
		scanf("%d %d", &u, &w);
		if (u > w) {
			u ^= w;
			w ^= u;
			u ^= w;
		}
		ans -= (long long)u * (N - w + 1);
	}
	printf("%lld\n", ans);
	fflush(stdout);
	return 0;
}