#include <stdio.h>

int main()
{
	int i, N, K, P[5001], C[5001];
	scanf("%d %d", &N, &K);
	for (i = 1; i <= N; i++) scanf("%d", &(P[i]));
	for (i = 1; i <= N; i++) scanf("%d", &(C[i]));

	int j, k, dist[5001], period;
	long long ans = -(1 << 30), tmp[5001], max, loop;
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) {
			dist[j] = 0;
			tmp[j] = 0;
		}
		for (k = 1, j = i, dist[j] = k, max = -(1 << 30); k <= K && dist[P[j]] == 0; j = P[j]) {
			dist[P[j]] = ++k;
			tmp[P[j]] = tmp[j] + C[P[j]];
			if (tmp[P[j]] > max) max = tmp[P[j]];
		}
		if (k > K || tmp[j] + C[P[j]] <= tmp[P[j]]) {
			if (max > ans) ans = max;
			continue;
		}
		period = dist[j] - dist[P[j]] + 1;
		loop = tmp[j] + C[P[j]] - tmp[P[j]];
		j = P[j];
		tmp[j] += loop * ((K - dist[j] + 1) / period);
		if (tmp[j] > max) max = tmp[j];
		for (k = j; P[j] != k; j = P[j]) {
			tmp[P[j]] += loop * ((K - dist[P[j]] + 1) / period);
			if (tmp[P[j]] > max) max = tmp[P[j]];
		}
		if (max > ans) ans = max;
	}

	printf("%lld\n", ans);
	fflush(stdout);
	return 0;
}