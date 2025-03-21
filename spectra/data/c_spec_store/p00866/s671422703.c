// AOJ 1287: Stopped Watches
// 2017.10.28 bal4u@uu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int t, id; } T;
T tbl[10000]; int sz;
int min, max;
int a[12][60];
int c[6][3] = {{0,1,2},{0,2,1},{1,0,2},{1,2,0},{2,0,1},{2,1,0}};

void check(int id, int *t)
{
	int i, j, h, m, s, hh;

	for (j = 0; j < 60; j++) for (i = 0; i < 6; i++) {
		h = (t[c[i][0]] + j) % 60, hh = h/5;
		m = (t[c[i][1]] + j) % 60;
		s = (t[c[i][2]] + j) % 60;
		if (a[hh][m] == h) tbl[sz].t = ((hh*60)+m)*60+s, tbl[sz++].id = id;
	}
}

int cmp(T *a, T *b) { return a->t - b->t; }
int main()
{
	int n, i, j, k, d;
	int t[3];
	char f[11];

	for (i = 0; i < 12; i++) for (j = 0; j < 60; j++) a[i][j] = (60*i + j)/12;
	while (scanf("%d", &n) && n > 0) {
		sz = 0;
		for (i = 0; i < n; i++) {
			scanf("%d%d%d", t, t+1, t+2);
			check(i, t);
		}
		qsort(tbl, sz, sizeof(T), cmp);
		d = 0x7fffffff;
		for (i = 0; i < sz; i++) {
			memset(f, 0, sizeof(f)), k = 0;
			for (j = i; j < sz; j++) {
				if (f[tbl[j].id]) continue;
				f[tbl[j].id] = 1;
				if (++k == n) {
					if ((tbl[j].t - tbl[i].t) < d) {
						d = tbl[j].t - tbl[i].t, min = tbl[i].t, max = tbl[j].t;
					}
					break;
				}
			}
		}
		printf("%02d:%02d:%02d %02d:%02d:%02d\n",
		   min/3600, (min/60)%60, min%60, max/3600, (max/60)%60, max%60);
	}
	return 0;
}