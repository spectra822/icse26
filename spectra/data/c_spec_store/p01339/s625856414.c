// AOJ 2222 Alien's Counting
// 2018.4.25 bal4u

#include <stdio.h>
#include <malloc.h>
#include <string.h>

#define MAX_V 1002
int  V;    // 頂点数
int  *to[MAX_V], hi[MAX_V], lim[MAX_V];
int  *r_to[MAX_V], r_hi[MAX_V], r_lim[MAX_V];
int  vs[MAX_V], vsz;
char used[MAX_V];
int  cmp[MAX_V];    // 属する強連結成分のトポロジカル順序

void check_lim(int a)
{
	if (hi[a] < lim[a]) return;
	if (lim[a] == 0) {
		lim[a] = 8, hi[a] = 0;
		to[a] = malloc(sizeof(int) *lim[a]);
	} else if (hi[a] == lim[a]) {
		int k = lim[a];
		if (k > 256) k = 256;
		lim[a] += k;
		to[a] = realloc(to[a], sizeof(int) *lim[a]);
	}
}

void check_r_lim(int a)
{
	if (r_hi[a] < r_lim[a]) return;
	if (r_lim[a] == 0) {
		r_lim[a] = 8, r_hi[a] = 0;
		r_to[a] = malloc(sizeof(int) *r_lim[a]);
	} else if (r_hi[a] == r_lim[a]) {
		int k = r_lim[a];
		if (k > 256) k = 256;
		r_lim[a] += k;
		r_to[a] = realloc(r_to[a], sizeof(int) *r_lim[a]);
	}
}

void add_edge(int _from, int _to)
{
	check_lim(_from), check_r_lim(_to);
	to[_from][hi[_from]++] = _to;
	r_to[_to][r_hi[_to]++] = _from;
}

void dfs(int v)
{
	int i;
	used[v] = 1;
	for (i = 0; i < hi[v]; i++) {
		if (!used[to[v][i]]) dfs(to[v][i]);
	}
	vs[vsz++] = v;
}

void rdfs(int v, int k)
{
	int i;
	used[v] = 1;
	cmp[v] = k;
	for (i = 0; i < r_hi[v]; i++) {
		if (!used[r_to[v][i]]) rdfs(r_to[v][i], k);
	}
}

void init(int n)
{
	V = n;
	memset(  lim, 0, V<<2), memset(  hi, 0, V<<2);
	memset(r_lim, 0, V<<2), memset(r_hi, 0, V<<2);
}

// 強連結成分への分解
int scc()
{
	int v, i, k;
	memset(used, 0, V);
	vsz = 0;
	for (v = 0; v < V; v++) if (!used[v]) dfs(v);
	memset(used, 0, V);
	k = 0;
	for (i = vsz-1; i >= 0; i--) if (!used[vs[i]]) {

		rdfs(vs[i], k++);
	}
	return k;		// 得られた強連結成分の数
}

// バッファを経ずstdinから数値を得る
//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0, c = getchar_unlocked();
	do n = 10*n + (c & 0xf), c = getchar_unlocked(); while (c >= '0');
	return n;
}

#define MOD 1000000007
int  dp[1002], nx[1002];
char mk[1002];

int main()
{
	int N, M, s, d, i, k;
	long long ans;

	V = N = in(), M = in();
//	init(N);
	while (M--) {
		s = in()-1, d = in()-1;
		add_edge(s, d);
	}

	k = scc();
	memset(nx, -1, sizeof(int)*k);
	for (i = 0; i < N; i++) if (hi[i]) nx[cmp[i]] = cmp[to[i][0]];

	ans = 1;
    for (i = 0; i < k; i++) {
        if (dp[i]) dp[i]++; else dp[i] = 2;
        if (nx[i] < 0 || nx[i] == i) ans = ans*dp[i] % MOD;
        else if (dp[nx[i]]) dp[nx[i]] = (long long)dp[nx[i]]*dp[i] % MOD;
        else                dp[nx[i]] = dp[i];
    }
	printf("%d\n", (int)ans);
	return 0;
}
