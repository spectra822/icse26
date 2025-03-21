#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N	1000
#define M	200000

int max(int a, int b) { return a > b ? a : b; }

int oo[1 + M * 3], oh[1 + M * 3];

int link(int o, int h) {
	static int _ = 1;

	oo[_] = o, oh[_] = h;
	return _++;
}

int ii[M], jj[M];
int ae[N], af[N], ae_[N], cc[N], qu[N], cnt;

void dfs1(int i) {
	int o;

	if (cc[i])
		return;
	cc[i] = -1;
	for (o = ae[i]; o; o = oo[o]) {
		int h = oh[o], j = jj[h];

		dfs1(j);
	}
	qu[--cnt] = i;
}

void dfs2(int j, int c) {
	int o;

	if (cc[j] != -1)
		return;
	cc[j] = c;
	for (o = af[j]; o; o = oo[o]) {
		int h = oh[o], i = ii[h];

		dfs2(i, c);
	}
}

char visited[N]; int c;
int hh[N * 2], cnt_;

void dfs3(int i) {
	int o;

	visited[i] = 1;
	for (o = ae[i]; o; o = oo[o]) {
		int h = oh[o], j = jj[h];

		if (!visited[j] && cc[j] == c)
			hh[cnt_++] = h, dfs3(j);
	}
}

void dfs4(int j) {
	int o;

	visited[j] = 2;
	for (o = af[j]; o; o = oo[o]) {
		int h = oh[o], i = ii[h];

		if (visited[i] == 1 && cc[i] == c)
			hh[cnt_++] = h, dfs4(i);
	}
}

int h_;

int dfs5(int i, int t) {
	int o;

	if (i == t)
		return 1;
	if (visited[i])
		return 0;
	visited[i] = 1;
	for (o = ae[i]; o; o = oo[o]) {
		int h = oh[o], j = jj[h];

		if (h != h_ && cc[j] == c && dfs5(j, t))
			return 1;
	}
	return 0;
}

int main() {
	static int dd[N];
	static char diff[M];
	int n, n_, m, g, g_, h, i, j, s;

	scanf("%d%d", &n, &m);
	for (h = 0; h < m; h++) {
		scanf("%d%d", &i, &j), i--, j--;
		ii[h] = i, jj[h] = j;
		ae[i] = link(ae[i], h);
		af[j] = link(af[j], h);
	}
	cnt = n;
	for (i = 0; i < n; i++)
		if (!cc[i])
			dfs1(i);
	n_ = 0;
	for (g = 0; g < n; g++) {
		i = qu[g];
		if (cc[i] == -1)
			dfs2(i, n_++);
	}
	for (h = 0; h < m; h++) {
		i = cc[ii[h]], j = cc[jj[h]];
		if (i != j)
			ae_[i] = link(ae_[i], h);
	}
	for (s = 0; s < n_; s++) {
		int o;

		memset(dd, 0, n_ * sizeof *dd);
		for (o = ae_[s]; o; o = oo[o]) {
			h = oh[o], j = cc[jj[h]];
			dd[j]++;
		}
		for (o = ae_[s]; o; o = oo[o]) {
			h = oh[o], j = cc[jj[h]];
			if (dd[j] > 1)
				diff[h] = 1;
		}
		memset(dd, -1, n_ * sizeof *dd), dd[s] = 0;
		for (i = s; i < n_; i++)
			if (dd[i] != -1)
				for (o = ae_[i]; o; o = oo[o]) {
					h = oh[o], j = cc[jj[h]];
					dd[j] = max(dd[j], dd[i] + 1);
				}
		for (o = ae_[s]; o; o = oo[o]) {
			h = oh[o], j = cc[jj[h]];
			if (dd[j] > 1)
				diff[h] = 1;
		}
	}
	for (c = 0; c < n_; c++) {
		cnt = 0;
		for (i = 0; i < n; i++)
			if (cc[i] == c)
				qu[cnt++] = i;
		cnt_ = 0;
		dfs3(qu[0]);
		dfs4(qu[0]);
		for (g_ = 0; g_ < cnt_; g_++) {
			h = hh[g_];
			for (g = 0; g < cnt; g++)
				visited[qu[g]] = 0;
			h_ = h;
			diff[h] = !dfs5(ii[h], jj[h]);
		}
	}
	for (h = 0; h < m; h++)
		printf(diff[h] ? "diff\n" : "same\n");
	return 0;
}
