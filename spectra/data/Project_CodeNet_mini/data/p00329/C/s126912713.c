// AOJ 0334 Amidakuji
// 2019.8.11 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//// 高速入出力
#if 1
#define gc() getchar_unlocked()
#define pc(c) putchar_unlocked(c)
#else
#define gc() getchar()
#define pc(c) putchar(c)
#endif

int in()  // 非負整数の入力
{
	int n = 0, c = gc();
	do n = 10 * n + (c & 0xf), c = gc(); while (c >= '0');
	return n;
}

void out(long long n)  // 正整数の表示（出力）
{
	int i;
	char ob[40];

	i = 0; while (n) ob[i++] = n % 10 + '0', n /= 10;
	while (i--) pc(ob[i]);
	pc('\n');
}

void outs(char *s) { while (*s) pc(*s++); pc('\n'); }

#define MAX 1005
int  hi[MAX], to[MAX][MAX];
int  seen[MAX];
int  match[MAX];
int  mark = 1;

int bpm(int u);
int bipartiteMatching(int m, int n)
{
	int u, max;

	memset(match, -1, sizeof(match));
	max = 0;
	for (u = 0; u < m; u++) if (match[u] < 0) {
		mark++;
		if (bpm(u)) max++;
	}
	return max;
}

int bpm(int u)
{
	int i, v, w;

	seen[u] = mark;
	for (i = 0; i < hi[u]; i++) {
		v = to[u][i], w = match[v];
		if (w < 0 || (seen[w] != mark && bpm(w))) {
			match[v] = u, match[u] = v;
			return 1;
		}
	}
	return 0;
}

int cmp(const void *u, const void *v) { return *(int *)u - *(int *)v; }

int main()
{
	int N, i, j, k;
	
	N = in()-1;
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			if (gc() & 1) to[j][hi[j]++] = N+i;
			gc();
		}
	}
	if (bipartiteMatching(N, N) < N) outs("no");
	else {
		outs("yes");
		for (i = 0; i < N; i++) {
			match[match[i]] = -1;
			match[i] = -1;
			mark++;
			bpm(i);
			hi[i] = 0;
			to[i][hi[i]++] = match[i];
			out(match[i]-N+1);
		}
	}
	return 0;
}
