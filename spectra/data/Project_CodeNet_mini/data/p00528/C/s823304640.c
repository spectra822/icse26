// AOJ 	0605: Modern Mansion
// 2018.1.10 bal4u@uu

#include <stdio.h>
#include <stdlib.h>

#define QMAX 80000
typedef struct { int s; long long t; } QUE;
QUE que[QMAX]; int qsize;

#define PARENT(i) ((i)>>1)
#define LEFT(i)   ((i)<<1)
#define RIGHT(i)  (((i)<<1)+1)

void min_heapify(int i)
{
	int l, r, min;
	QUE qt;

	l = LEFT(i), r = RIGHT(i);
	if (l < qsize && que[l].t < que[i].t) min = l; else min = i;
	if (r < qsize && que[r].t < que[min].t) min = r;
	if (min != i) {
		qt = que[i], que[i] = que[min], que[min] = qt;
		min_heapify(min);
	}
}

void deq()
{
	que[0] = que[--qsize];
	min_heapify(0);
}

void enq(int s, long long t)
{
	int i, min;
	QUE qt;

	i = qsize++;
	que[i].s = s, que[i].t = t;
	while (i > 0 && que[min = PARENT(i)].t > que[i].t) {
		qt = que[i], que[i] = que[min], que[min] = qt;
		i = min;
	}
}

#define ABS(a)  ((a)>=0?(a):-(a))
#define INF 0x7ffffff
typedef struct { int x, y, id; } T;
T sw[200005];
int sz;
int to[400005][5], dt[400005][5], hi[400005];
char used[400005];

int xcmp(T *a, T *b) { if (a->x - b->x) return a->x - b->x; return a->y - b->y; }
int ycmp(T *a, T *b) { if (a->y - b->y) return a->y - b->y; return a->x - b->x; }

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

long long dijkstra(int start, int flag, int goal)
{
	int i, s, e;
	long long d;

	qsize = 0;
	enq(start, 0);
	if (flag < 0) {
		for (i = 0; i < hi[start]; i++) if (to[start][i] == start+1) {
			dt[start][i] = INF, hi[start+1] = 0;
		}
	}

	while (qsize) {
		s = que[0].s, d = que[0].t, deq();
		if (s == goal || s == goal+1) return d;
		if (used[s]) continue;
		used[s] = 1;
		for (i = 0; i < hi[s]; i++) {
			e = to[s][i];
			if (used[e]) continue;
			enq(e, d+dt[s][i]);
		}
	}
	return -1;
}

int main()
{
	int m, n, k, i, j;
	int s, ss, g, a, b, d;

	m = in(), n = in(), k = in();
	sz = 0, s = g = -1;
	for (i = 0; i < k; i++) {
		int x, y;
		sw[i].x = x = in(), sw[i].y = y = in(), sw[i].id = sz;
		if (x == 1 && y == 1) s = sz;
		else if (x == m && y == n) g = sz;
		sz += 2;
	}
	ss = s;
	if (s < 0) sw[k].x = 1, sw[k].y = 1, sw[k].id = sz, s = sz, k++, sz+=2;
	if (g < 0) sw[k].x = m, sw[k].y = n, sw[k].id = sz, g = sz, k++, sz+=2;

	qsort(sw, k, sizeof(T), xcmp);
	a = sw[0].id, b = a+1;
	to[a][0] = b, dt[a][0] = 1, hi[a] = 1;
	to[b][0] = a, dt[b][0] = 1, hi[b] = 1;

	for (i = 1; i < k; i++) {
		a = sw[i].id, b = a+1;
		j = hi[a]++, to[a][j] = b, dt[a][j] = 1;
		j = hi[b]++, to[b][j] = a, dt[b][j] = 1;
		if (sw[i-1].x == sw[i].x) {
			a = sw[i-1].id, b = sw[i].id, d =  ABS(sw[i-1].y - sw[i].y);
			j = hi[a]++, to[a][j] = b, dt[a][j] = d;
			j = hi[b]++, to[b][j] = a, dt[b][j] = d;
		}
	}

	qsort(sw, k, sizeof(T), ycmp);
	for (i = 1; i < k; i++) {
		if (sw[i-1].y == sw[i].y) {
			a = sw[i-1].id+1, b = sw[i].id+1, d =  ABS(sw[i-1].x - sw[i].x);
			j = hi[a]++, to[a][j] = b, dt[a][j] = d;
			j = hi[b]++, to[b][j] = a, dt[b][j] = d;
		}
	}

	printf("%lld\n", dijkstra(s, ss, g));
	return 0;
}
