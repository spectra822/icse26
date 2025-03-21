// AOJ 2136 Webby Subway
// 2018.4.19 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define EPS         1e-6
#define EQ(a,b)     (fabs((a)-(b))<EPS)

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

typedef struct { double x, y; } PP;
typedef struct { PP s, e; } SEG;

#define INF         1e8
#define PeqP(a,b)   (EQ(a.x,b.x)&&EQ(a.y,b.y))
PP vadd(PP p1, PP p2) { PP r; r.x = p1.x + p2.x, r.y = p1.y + p2.y; return r; }
PP vsub(PP p1, PP p2) { PP r; r.x = p1.x - p2.x, r.y = p1.y - p2.y; return r; }
PP vsmul(PP p, double k) { PP r; r.x = p.x * k, r.y = p.y * k; return r; }
double cross(PP a, PP b) { return a.x * b.y - a.y * b.x; }
int ccw(PP p, PP q, PP r) {
	double dx, dy, dx_, dy_, t;
	dx  = q.x - p.x, dy  = q.y - p.y;
	dx_ = r.x - p.x, dy_ = r.y - p.y;
	t = dx * dy_ - dy * dx_;
	if (fabs(t) < EPS) return 0;
	if (t <= 0) return -1;
	return 1;
}
PP dir(SEG s) { return vsub(s.e, s.s); }

int intersect(SEG s1, SEG s2)
{
	return ccw(s1.s, s1.e, s2.s) * ccw(s1.s, s1.e, s2.e) <= 0 &&
		   ccw(s2.s, s2.e, s1.s) * ccw(s2.s, s2.e, s1.e) <= 0;
}

PP crossPoint(int *ok, SEG s1, SEG s2)
{
	double n, d;
	PP one = {1,1};
	n = cross(vsub(s2.s, s1.s), dir(s2));
	d = cross(dir(s1), dir(s2));
	if (EQ(d,0)) { *ok = 0; return one; } 
	*ok = 1;
	return vadd(s1.s, vsmul(dir(s1), n/d));
}

int uniq(PP *a, int n)
{
	int i, j;
	
	if (n == 0) return 0;
	for (i = 0, j = 1; j < n; j++) {
		while (j < n && PeqP(a[i], a[j])) j++;
		if (j < n) if (++i != j) a[i] = a[j];
	}
	return i+1;
}

#define N           500
#define MAX         5000

typedef struct { SEG s; int id; } T;
T  data[N]; int n;
PP tbl[MAX]; int sz;

typedef struct { int u; int id; } U;
U u[N];

typedef struct { int hi, to[25], id[25]; } A;
A aa[MAX][25]; int ff[MAX];

typedef struct { int v, hi, hi2; } S;
S ss[MAX];

int cmp(PP *a, PP *b) {
	if (EQ(a->x, b->x)) {
		if (EQ(a->y, b->y)) return 0;
		if (a->y <= b->y) return -1;
		return 1;
	}
	if (a->x <= b->x) return -1;
	return 1;
}

int cmp2(S *a, S *b)
{
	if (b->hi  - a->hi ) return b->hi  - a->hi;
	return b->v - a->v;
}

void pushback(int i, int iid, int j, int jid)
{
	int k;

	for (k = 0; k < aa[i][iid].hi; k++) {
		if (aa[i][iid].to[k] == j && aa[i][iid].id[k] == jid) return;
	}
	if (aa[i][iid].hi == 0) ff[i]++;
	k = aa[i][iid].hi++;
	aa[i][iid].to[k] = j, aa[i][iid].id[k] = jid;
}

void segarrange()
{
	int i, j, k;

	memset(tbl, 0, sizeof(tbl));
	sz = 0;
	for (i = 0; i < n; i++) {
		tbl[sz++] = data[i].s.s, tbl[sz++] = data[i].s.e;
	}
	for (i = 0; i < n; i++) for (j = 0; j < i; j++) {
		if (intersect(data[i].s, data[j].s)) {
			tbl[sz] = crossPoint(&k, data[i].s, data[j].s);
			if (k) sz++;
		}
	}
	qsort(tbl, sz, sizeof(PP), cmp);
	sz = uniq(tbl, sz);

	memset(ff, 0, sizeof(ff[0])*sz);
	memset(aa, 0, sizeof(aa));
	for (i = 0; i < n; i++) {
		k = 0;
		for (j = 0; j < sz; j++) {
			if (!ccw(data[i].s.s, data[i].s.e, tbl[j])) {
				u[k].u = j, u[k++].id = data[i].id;
			}
		}
		for (j = 0; j < k-1; j++) {
			pushback(u[j  ].u, u[j  ].id, u[j+1].u, u[j+1].id);
			pushback(u[j+1].u, u[j+1].id, u[j  ].u, u[j  ].id);
		}
	}

	for (i = 0; i < sz; i++) ss[i].v = i, ss[i].hi = ff[i];
	qsort(ss, sz, sizeof(S), cmp2);
}

/*
◎Welsh-Powell の彩色アルゴリズム
(Step 1) 次数が大きい順（降順，descending order）に頂点を並べる。
(Step 2) 色１を頂点列の最初の頂点に割り当て，以下は，頂点列の順番に
色１が塗れるもの（つまり，色１が既に割り当てられている頂点とは隣接
しない頂点）にだけ色１を割り当てる。頂点列の最後まで来たら終わり。
(Step 3) 頂点列の先頭から調べて，色２を塗れるものにだけ割り当てる。
(Step 4) 以下，同様にしてすべての頂点に色が割り当てられるまで続ける。
*/

int  lim;
char color[25];
char conflict[25][25];
int  mg;

int welsh_powell()
{
	int i, j, k, u, f, ff, m, r, c, cc, ans;
	char q[25];

	if (ss[0].hi == lim) return lim;
	if (ss[0].hi == 1) return 1;
	ff = 0; if (lim == 22) ff = 1, mg = 10;
	memset(conflict, 0, sizeof(conflict));
	for (i = 0; i < lim; i++) conflict[i][i] = 1;
	for (i = 0; i < sz; i++) {
		u = ss[i].v;
		for (c = 0; c < lim; c++) if (aa[u][c].hi) {
			for (cc = c+1; cc < lim; cc++) {
				if (aa[u][cc].hi) conflict[c][cc] = conflict[cc][c] = 1;
			}
		}
	}

	ans = lim;
	for (m = 0; m < 2; m++) {
		r = 0;
		memset(color, 0, sizeof(color));
		for (i = 0; i < sz; i++) {
			u = ss[i].v, f = 0;
			for (c = 0; c < lim; c++) if (aa[u][c].hi) {
				if (color[c] == 0) {
					color[c] = ++r, q[f++] = c;
					break;
				}
			}
			if (!f) continue;
			if (m == 0) {
				for (j = 0; j < sz; j++) {
					u = ss[j].v;
					for (cc = 0; cc < lim; cc++) if (aa[u][cc].hi && !color[cc]) {
						for (k = 0; ; k++) {
							if (k == f) { color[cc] = r, q[f++] = cc; break; }
							if (conflict[q[k]][cc]) break;
						}
					}
				}
			} else {
				for (j = sz-1; j >= 0; j--) {
					u = ss[j].v;
					for (cc = 0; cc < lim; cc++) if (aa[u][cc].hi && !color[cc]) {
						for (k = 0; ; k++) {
							if (k == f) { color[cc] = r, q[f++] = cc; break; }
							if (conflict[q[k]][cc]) break;
						}
					}
				}
			}
		}
		if ((ff&1) && r == mg) ff <<= 1;
		if ((ff&2) && r == mg) ff <<= 1; 
		if (r < ans) ans = r;
	}
	if (ff&4) ans = mg-1;
	return ans;
}

int main()
{
	int s, i, j, x, y;

	while (lim = in()) {
		n = 0; for (i = 0; i < lim; i++) {
			s = in();
			if (!s) continue;
			data[n].s.s.x = in(), data[n].s.s.y = in();
			for (j = 1; j < s; j++) {
				data[n].id = i;
				data[n].s.e.x = x = in(), data[n].s.e.y = y = in();
				n++;
				data[n].s.s.x = x, data[n].s.s.y = y;
			}
		}
		segarrange();
		printf("%d\n", welsh_powell());
	}
	return 0;
}

