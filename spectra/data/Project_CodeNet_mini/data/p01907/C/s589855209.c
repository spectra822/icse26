// AOJ 2807 Fractal Tree
// 2018.3.21 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 高速数値入出力
#if 1
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif
int in()   // 非負整数の入力
{
	int n = 0, c = gc();
	do n = 10 * n + (c & 0xf), c = gc(); while (c >= '0');
	return n;
}

double dbl()    // 実数の入力
{
	int minus = 0;
	double x, y;
	int n = 0, c = gc();
	if (c == '-') minus = 1, c = gc();
	do n = 10 * n + (c & 0xf), c = gc(); while (c >= '0');

	if (c == '.') {
		x = 0;
		y = 1, c = gc();
		do y *= 0.1, x += y * (c & 0xf), c = gc(); while (c >= '0');
		x += n;
	}
	else x = n;
	if (minus) x = -x;
	return x;
}


// 本問題関連
#define MAX 100005
typedef struct { int to, c; } T;
int hi[MAX]; T *t[100005]; int N;
int cost[MAX], depth[MAX], depth_max;
double p[MAX], P;

typedef struct { int n, d; } Q;
Q q[MAX]; int top;
char vis[MAX];

void dfs()
{
	int i, node, d, to;

	q[0].n = 1, q[0].d = 0, top = 1;
	while (top) {
		node = q[--top].n, d = q[top].d;

		if (vis[node]) continue;
		vis[node] = 1;

		depth[node] = d;
		if (d > depth_max) depth_max = d;
		for (i = 0; i < hi[node]; i++) {
			to = t[node][i].to;
			if (!vis[to]) {
				cost[to] = t[node][i].c;
				q[top].n = to, q[top++].d = d + 1;
			}
		}
	}
}

int main()
{
	int i, k, x, y, c;
	int *memo, sz;
	double a, b;

	// 入力受付
	P = dbl(), N = in();
	memo = malloc(sizeof(int) * 3 * N);
	sz = 0; for (i = 1; i < N; i++) {
		memo[sz++] = x = in(), memo[sz++] = y = in(), memo[sz++] = in();
		hi[x]++, hi[y]++;
	}
	for (i = 1; i <= N; i++) if (hi[i]) t[i] = malloc(sizeof(T)*hi[i]);
	memset(hi+1, 0, sizeof(int)*N);
	i = 0; while (i < sz) {
		x = memo[i++], y = memo[i++], c = memo[i++];
		k = hi[x]++, t[x][k].to = y, t[x][k].c = c;
		k = hi[y]++, t[y][k].to = x, t[y][k].c = c;
	}
//	free(memo);

	dfs();
	p[0] = 1; for (i = 1; i <= depth_max; i++) p[i] = p[i - 1] * P;
	a = 0, b = 1; for (i = 1; i <= N; i++)
		a += cost[i] * p[depth[i]], b += p[depth[i]];
	printf("%.10lf\n", a*b);
	return 0;
}

