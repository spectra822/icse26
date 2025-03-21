// AOJ 1064: Yanagi's Comic
// 2018.1.18 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int id, x1, y1, x2, y2; char used; } T;
T tbl[10];
int ans[10];
int order;

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

int cmp(T *a, T *b) { if (a->x1 - b->x1) return a->x1 - b->x1; return a->y1 - b->y1; }

void calc(T *t, int n)
{
	int i, j, x, y, xx, yy;
	T tmp[10];

	qsort(t, n, sizeof(T), cmp);
	ans[t[0].id] = ++order, t[0].used = 1;

	y = t[0].y2, x = 501;
	for (i = 0; i < n; i++) {
		if (t[i].used) continue;
		if (t[i].y1 < y && y < t[i].y2) { x = t[i].x1; break; }
	}

	xx = yy = 501, j = 0;
	for (i = 0; i < n; i++) {
		if (t[i].used) continue;
		if (t[i].y2 <= y && t[i].x2 <= x) tmp[j++] = t[i], t[i].used = 1;
	}
	if (j > 0) calc(tmp, j);

	for (i = 0; i < n; i++) if (t[i].used == 0) calc(t+i, n-i);
}

int main()
{
	int n, x1, y1, x2, y2;
	int cno, i;

	cno = 0; while (n = in()) {
		for (i = 0; i < n; i++) {
			x1 = in(), y1 = in(), x2 = in(), y2 = in();
			tbl[i].id = i, tbl[i].used = 0;
			if (x1 <= x2) tbl[i].x1 = x1, tbl[i].x2 = x2;
			else          tbl[i].x1 = x2, tbl[i].x2 = x1;
			if (y1 <= y2) tbl[i].y1 = y1, tbl[i].y2 = y2;
			else          tbl[i].y1 = y2, tbl[i].y2 = y1;
		}

		order = 0;
		calc(tbl, n);

		if (!cno) cno = 1;
		else putchar('\n');
		for (i = 0; i < n; i++) printf("%d\n", ans[i]);
	}
	return 0;
}
