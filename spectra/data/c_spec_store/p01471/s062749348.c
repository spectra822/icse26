// AOJ 2354 Fractional Knapsack
// 2018.3.17 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// library
//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0, c = getchar_unlocked();
	if (c == '-') {	c = getchar_unlocked();
		do n = 10*n + (c & 0xf), c = getchar_unlocked(); while (c >= '0');
		return -n;
	}
	do n = 10*n + (c & 0xf), c = getchar_unlocked(); while (c >= '0');
	return n;
}
// library

#define ZERO(a)  (fabs(a)<1e-7)

typedef struct { int w, v; double r; } T;
T tbl[100002]; int sz;

int cmp(T *a, T *b) { if (fabs(b->r - a->r)<1e-8) return 0; if (a->r <= b->r) return 1; return -1; }

int main()
{
	int N, i, w, v;
	double W, x, ans;

	N = in(), W = in();
	sz = 0, ans = 0;
	while (N--) {
		w = in(), v = in();
		if (w >= 0 && v <= 0) continue;
		if (w < 0 && v > 0) ans += v, W -= w;
		else {
			if ( w < 0) w = -w, v = -v, ans -= v, W += w; 
			tbl[sz].w = w, tbl[sz].v = v, tbl[sz++].r = (double)v/w;
		} 
	}
	qsort(tbl, sz, sizeof(T), cmp);

	for (i = 0; i < sz && !ZERO(W); i++) {
		x = W/tbl[i].w;	if (x > 1) x = 1;
		W -= x*tbl[i].w, ans += x*tbl[i].v;
	}
	printf("%lf\n", ans);
	return 0;
}
