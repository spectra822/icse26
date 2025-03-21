#include <stdio.h>

const long long sup = (long long)1 << 60;

typedef struct {
	int t, h, cost;
} edge;

int main()
{
	int i, u, w, c, N, M;
	edge e[2001];
	scanf("%d %d", &N, &M);
	for (i = 0; i < M; i++) {
		scanf("%d %d %d", &u, &w, &c);
		e[i].t = u;
		e[i].h = w;
		e[i].cost = -c;
	}

	int k;
	long long min[1001], ans;
	for (i = 2, min[1] = 0; i <= N; i++) min[i] = sup;
	for (k = 1; k < N; k++) {
		for (i = 0; i < M; i++) {
			u = e[i].t;
			w = e[i].h;
			c = e[i].cost;
			if (min[u] < sup && min[w] > min[u] + c) min[w] = min[u] + c;
		}
	}
	ans = min[N];
	for (k = 1; k <= N; k++) {
		for (i = 0; i < M; i++) {
			u = e[i].t;
			w = e[i].h;
			c = e[i].cost;
			if (min[u] < sup && min[w] > min[u] + c) min[w] = min[u] + c;
		}
	}
	
	if (min[N] == ans) printf("%lld\n", -ans);
	else printf("inf\n");
	fflush(stdout);
	return 0;
}