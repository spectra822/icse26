// AOJ 2251 Merry Christmas
// 2018.3.6 bal4u

#include <stdio.h>
#include <string.h>

#define MAX 2002
short hi[MAX], to[MAX][MAX];
char  seen[MAX];
short match[MAX];

int bpm(int u)
{
	int i, v;

	for (i = 0; i < hi[u]; i++) {
		v = to[u][i];
		if (seen[v]) continue;
		seen[v] = 1;
		if (match[v] < 0 || bpm(match[v])) {
			match[u] = v, match[v] = u;
			return 1;
		}
	}
	return 0;
}

#define INF 0x1010
int dist[102][102];
int p[1002], t[1002];

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

int main()
{
	int N, M, L, u, v, d, k;

	while (N = in()) {
		M = in(), L = in();
		memset(dist, INF, sizeof(dist));
		for (k = 0; k < N; k++) dist[k][k] = 0;
		for (k = 0; k < M; k++) {
			u = in(), v = in(), d = in();
			dist[u][v] = dist[v][u] = d;
		}
		for (k = 0; k < N; k++) {
			for (u = 0; u < N; u++) if (dist[u][k] != INF) {
				for (v = 0; v < N; v++) if (dist[k][v] != INF) {
					d = dist[u][k] + dist[k][v];
					if (dist[u][v] > d) dist[u][v] = d;
				}
			}
		}

		memset(hi, 0, sizeof(hi));
		for (k = 0; k < L; k++) p[k] = in(), t[k] = in();
		for (u = 0; u < L; u++) for (v = 0; v < L; v++) if (u != v) {
			if (dist[p[u]][p[v]] <= t[v]-t[u]) to[u][hi[u]++] = v+L;
		}

	    memset(match, -1, L << 2);
		k = L;
		for (u = 0; u < L; u++) {
			memset(seen, 0, L << 1);
			if (bpm(u)) k--;
		}
		printf("%d\n", k);
	}
	return 0;
}
