// AOJ 2456: Usoperanto
// 2018.4.17 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// マイナス値の入力に対応
//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0, c = getchar_unlocked();
	if (c == '-') { c = getchar_unlocked();
		do n = 10*n + (c & 0xf), c = getchar_unlocked(); while (c >= '0');
		return -n;
	}
	do n = 10*n + (c & 0xf), c = getchar_unlocked(); while (c >= '0');
	return n;
}

#define MAX 1000002
int  N;
int  m[MAX];
int  *base, bsz;
int  hi[MAX], *to[MAX];
int  que[MAX], top;
int  a[MAX];
long long s[MAX], b[MAX], dp[MAX];

int cmp(long long *a, long long *b)
{
	if (*a == *b) return 0;
	if (*a < *b) return 1;
	return -1;
}

void calc(int u)
{
	int i, v, sz;

	sz = 0, s[u] = m[u], dp[u] = 0;
	for (i = 0; i < hi[u]; i++) {
		v = to[u][i];
		b[sz++] = s[v], s[u] += s[v], dp[u] += dp[v];
	}
	qsort(b, sz, sizeof(long long), cmp);
	for (i = 0; i < sz; i++) dp[u] += b[i]*i;
}

int main()
{
	int i, l, t;
	long long ans;
	int *memo;

	N = in();
	memo = malloc(N<<2);
	for (i = 0; i < N; i++) {
		m[i] = in(), memo[i] = l = in();
		if (l == -1) bsz++;
		else hi[l]++;
	}
	base = malloc(bsz<<2);
	for (i = 0; i < N; i++) if (hi[i]) to[i] = malloc(hi[i]<<2);
	bsz = 0, memset(hi, 0, N<<2);

	for (i = 0; i < N; i++) {
		l = memo[i];
		if (l == -1) base[bsz++] = i;
		else to[l][hi[l]++] = i;
	}

	ans = 0;
	for (i = 0; i < bsz; i++) {
		que[1] = base[i], top = 1;
		while (top) {
			t = que[top];
			if (a[t] < hi[t]) que[++top] = to[t][a[t]++];
			else calc(t), top--;
		}
		ans += dp[base[i]];
	}
	printf("%lld\n", ans);
	return 0;
}
