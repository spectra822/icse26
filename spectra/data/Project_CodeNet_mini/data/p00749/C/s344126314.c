// AOJ 1168: Off Balance
// 2017.12.22 bal4u@uu

#include <stdio.h>
//#include <stdlib.h>
#include <string.h>

#define MAX 602

/* UNION-FIND library */
int p[MAX], rank[MAX];

void make_set(int x) { p[x] = x, rank[x] = 0; }
void link(int x, int y) {
	if (rank[x] > rank[y]) p[y] = x;
	else { p[x] = y; if (rank[x] == rank[y]) rank[y] = rank[y] + 1;	}
}
int find_set(int x) { if (x != p[x]) p[x] = find_set(p[x]);	return p[x]; }
void union_set(int x, int y) { link(find_set(x), find_set(y)); }

char map[60][12]; int w, h;
int  rel[60][10];
int mv[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};

typedef struct { int used, m, mx, xl, xr, par, ch, sib; } T;
T tbl[100]; int sz;
int tr[MAX];

void mktree(int r, int c, int this)
{
	int k, p, s;

	if (r == h-1) {
		if (map[r][c] == '.') return;
		if (tbl[this].xl < 0) tbl[this].xl = c;
		else if (c < tbl[this].xl) tbl[this].xl = c;
		if (c > tbl[this].xr) tbl[this].xr = c;
		return;
	}
	if (map[r+1][c] == '.') return;

	k = rel[r+1][c];
	if ((p = tr[k]) == this) return;

	if (tbl[this].xl < 0) tbl[this].xl = c;
	else if (c < tbl[this].xl) tbl[this].xl = c;
	if (c > tbl[this].xr) tbl[this].xr = c;
	if (tbl[this].par) return;

	if ((s = tbl[p].ch) == 0) tbl[p].ch = this;
	else {
		while (tbl[s].sib) s = tbl[s].sib;
		tbl[s].sib = this;
	}
	tbl[this].par = p;
}

int check(int this)
{
	int par, ch, sib;
	double x;

	if (tbl[this].used) return 1;
	ch = tbl[this].ch;
	if (ch) { if (!check(ch)) return 0; }

	sib = tbl[this].sib;
	while (sib) {
		if (!check(sib)) return 0;
		sib = tbl[sib].sib;
	}

	x = 0.5+(double)tbl[this].mx / tbl[this].m;
	if (x <= tbl[this].xl || tbl[this].xr+1 <= x) return 0;

	par = tbl[this].par;
	tbl[par].m  += tbl[this].m;
	tbl[par].mx += tbl[this].mx;
	tbl[this].used = 1;
	return 1;
}

int max;

int main()
{
	int r, c, r2, c2, i, k;
	T *tp;

	while (scanf("%d%d", &w, &h) && w > 0) {

		memset(rank, 0, sizeof(rank));
		for (i = 0, r = 0; r < h; r++) {
			scanf("%s", map[r]);
			for (c = 0; c < w; c++) p[i] = i, rel[r][c] = i, i++;
		}

		for (r = 0; r < h; r++) for (c = 0; c < w; c++) {
			if (map[r][c] == '.') continue;
			for (i = 0; i < 4; i++) {
				r2 = r + mv[i][0], c2 = c + mv[i][1];
				if (r2 >= 0 && r2 < h && c2 >= 0 && c2 < w) {
					if (map[r2][c2] == map[r][c]) union_set(rel[r][c], rel[r2][c2]);
				}
			}
		}

		sz = 1,	memset(tbl, 0, sizeof(tbl));
		memset(tr, -1, sizeof(tr));
		for (r = h-1; r >= 0; r--) for (c = 0; c < w; c++) {
			if (map[r][c] == '.') continue;
			k = rel[r][c] = find_set(rel[r][c]);
			if (tr[k] < 0) i = tr[k] = sz++, tp = tbl+i, tp->xl = -1;
			else           i = tr[k],        tp = tbl+i;
			tp->m++, tp->mx += c;
			mktree(r, c, i);
		}
		tbl[1].par = 1;

		puts(check(1) ? "STABLE": "UNSTABLE");
	}
	return 0;
}