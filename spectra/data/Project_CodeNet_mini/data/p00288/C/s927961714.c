// AOJ 0293 Algorithm Exam
// 2018.3.10 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QMAX 3005
typedef struct { int t, s; } QUE;
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

void enq(int s, int t)
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

#define INF 0x10101010
#define MAX 110
typedef struct { int to, rev; int cap, cost; } EDGE;
EDGE edge[MAX][MAX]; int hi[MAX];
int V;				// 頂点数
int potential[MAX], dist[MAX], prevv[MAX], preve[MAX];

void add_edge(int from, int to, int cap, int cost)
{
	int f, t;
	EDGE *ep;

	f = hi[from]++, t = hi[to]++;
	ep = &edge[from][f], ep->to = to, ep->cap = cap, ep->cost = cost, ep->rev = t; 
	ep = &edge[to][t], ep->to = from, ep->cap = 0, ep->cost = -cost, ep->rev = f;
}

int minCostFlow(int S, int T, int F)
{
	int i, v, nv, t, nt, ret;
	EDGE *ep;

	ret = 0;
	memset(potential, 0, V << 2);
  
	while (F > 0) {
		memset(dist, INF, V << 2);
		qsize = 0;
		enq(S, 0), dist[S] = 0;
		while (qsize) {
			v = que[0].s, t = que[0].t, deq();
			if (dist[v] < t) continue;
			for (i = 0; i < hi[v]; i++) {
				ep = &edge[v][i];
				if (ep->cap <= 0) continue;
				nv = ep->to;
				nt = t + ep->cost - potential[nv] + potential[v];
				if(dist[nv] > nt) {
					dist[nv] = nt;
					prevv[nv] = v, preve[nv] = i;
					enq(nv, nt);
				}
			}
		}
		if (dist[T] == INF) return -1;
		for (v = 0; v < V; v++) potential[v] += dist[v];

		t = F;
		for (v = T; v != S; v = prevv[v]) {
			ep = &edge[prevv[v]][preve[v]];
			if (t > ep->cap) t = ep->cap;
		}
		F -= t;

		ret += t * potential[T];
		for (v = T; v != S; v = prevv[v]) {
			ep = &edge[prevv[v]][preve[v]];
			ep->cap -= t;
			edge[v][ep->rev].cap += t;
		}
	}
	return ret;
}

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	if (c == '-') {
		c = getchar_unlocked();
		do n = 10*n + (c & 0xf), c = getchar_unlocked();
		while (c >= '0');
		return -n;
	}
	do n = 10*n + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

#define ABS(a)   ((a)>=0?(a):-(a))
int N, M, source, sink;
int ax[101], ay[101];
int bx[6], by[6], c[6], f[6];

void make_edge(int s, int mi)
{
	int i, j, x;

	memset(hi, 0, V << 2);
	for (i = 0; i < N; i++) add_edge(source, i, 1, 0);
	for (i = 0; i < M; i++) if ((1<<i) & s) {
		for (j = 0; j < N; j++) {
			x = ABS(ax[j]-bx[i]) + ABS(ay[j]-by[i]) - mi;
			if (x < 0) x = 0;
			add_edge(j, N+i, 1, x);
		}
		add_edge(N+i, sink, c[i], 0);
	}
}

int main()
{
	int B, i, s, lim, res, cnt, ans;
	int lb, mi, ub;

	while (N = in()) {
		M = in(), B = in();
		for (i = 0; i < N; i++) ax[i] = in(), ay[i] = in();
		for (i = 0; i < M; i++) bx[i] = in(), by[i] = in(), c[i] = in(), f[i] = in();

		source = N + M, sink = source + 1, V = sink + 1;

		ans = INF, lim = 1 << M;
	    for (s = 0; s < lim; s++) {
			res = 0, cnt = 0;
			for (i = 0; i < M; i++) if ((s>>i) & 1) res += f[i], cnt++;
			lb = 0, ub = 4002;
			while (lb + 1 < ub) {
				int a1, a2;
				mi = (lb + ub) >> 1;
				make_edge(s, mi);
				a1 = minCostFlow(source, sink, N) + mi*B*cnt;
				make_edge(s, mi-1);
				a2 = minCostFlow(source, sink, N) + (mi-1)*B*cnt;
				if (a1 < 0 || a2 < 0) goto next;
				if (a1 < a2) lb = mi; else ub = mi;
			}
			make_edge(s, lb);
			res += minCostFlow(source, sink, N) + lb*B*cnt;
			if (ans > res) ans = res;
next:		;
		}
		printf("%d\n", ans);
	}
	return 0;
}

