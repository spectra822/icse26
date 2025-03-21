// AOJ 1095 KND Factory
// 2018.3.7 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define QMAX 1000
typedef struct { int s; double t; } QUE;
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

void enq(int s, double t)
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

#define EPS 1e-8
#define INF 0x01010101
#define MAX 105
typedef struct { int to, rev; int cap; double cost; } E;
E *edge[MAX]; int hi[MAX], lim[MAX];
int V;				// 頂点数
double potential[MAX], min_cost[MAX];
int prevv[MAX], preve[MAX];

void check_lim(int a)
{
	if (hi[a] < lim[a]) return;
	if (lim[a] == 0) {
		lim[a] = 32, hi[a] = 0;
		edge[a] = malloc(sizeof(E) *lim[a]);
	} else if (hi[a] == lim[a]) {
		int k = lim[a];
		if (k > 128) k = 128;
		lim[a] += k;
		edge[a] = realloc(edge[a], sizeof(E) *lim[a]);
	}
}

void add_edge(int from, int to, int cap, double cost)
{
	int f, t;
	E *ep;

	check_lim(from), check_lim(to);
	f = hi[from]++, t = hi[to]++;
	ep = &edge[from][f], ep->to = to, ep->cap = cap, ep->cost = cost, ep->rev = t; 
	ep = &edge[to][t], ep->to = from, ep->cap = 0, ep->cost = -cost, ep->rev = f;
}

double minCostFlow(int S, int T, int F)
{
	int i, s, ns, k;
	double t, nt, ret;
	E *ep;

	ret = 0;
	memset(potential, 0, sizeof(potential));

	while (F > 0) {
		for (i = 0; i < V; i++) min_cost[i] = INF;
		qsize = 0;
		enq(S, 0), min_cost[S] = 0;
  
		while (qsize) {
			s = que[0].s, t = que[0].t, deq();
			if (min_cost[s] < t) continue;

			for (i = 0; i < hi[s]; i++) {
				ep = &edge[s][i], ns = ep->to;
				nt = t + ep->cost + potential[s] - potential[ns];
				if(ep->cap > 0 && min_cost[ns] > nt + EPS) {
					min_cost[ns] = nt;
					prevv[ns] = s, preve[ns] = i;
					enq(ns, nt);
				}
			}
		}
		if (min_cost[T] == INF) return -1;
		for (s = 0; s < V; s++) potential[s] += min_cost[s];

		k = F;
		for (s = T; s != S; s = prevv[s]) {
			ep = &edge[prevv[s]][preve[s]];
			if (k > ep->cap) k = ep->cap;
		}
		F -= k;

		ret += k * potential[T];
		for (s = T; s != S; s = prevv[s]) {
			ep = &edge[prevv[s]][preve[s]];
			ep->cap -= k;
			edge[s][ep->rev].cap += k;
		}
	}
	return ret;
}

// AX=C
#define N 105
int A[N][N], C[N]; double B[N][N]; double X[N];

int gauss_jordan(int n)
{
	int i, j, k, pivot;
	double t;

	for (i = 0; i < n; i++) for (j = 0; j < n; j++) B[i][j] = A[i][j];
	for (i = 0; i < n; i++) B[i][n] = C[i];

	for (i = 0; i < n; i++) {
		pivot = i;
		for (j = i; j < n; j++) {
			if (fabs(B[j][i]) > fabs(B[pivot][i])) pivot = j;
		}
		for (j = 0; j <= n; j++) {					// swap(B[i],B[pivot]);
			t = B[i][j], B[i][j] = B[pivot][j], B[pivot][j] = t;
		}
		if (fabs(B[i][i]) < EPS) return 0;			// error

		for (j = i+1; j <= n; j++) B[i][j] /= B[i][i];
		for (j = 0; j < n; j++) if (i != j) {
	        for (k = i+1; k <= n; k++) B[j][k] -= B[j][i]*B[i][k];
		}
	}
	for (i = 0; i < n; i++) X[i] = B[i][n];
	return 1;
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

int d[105];

int Vmax;
int main()
{
	int T, n, s, t, F, i, j, M;
	double ans;

	T = in();
	while (T--) {
		memset(hi, 0, sizeof(hi)), memset(lim, 0, sizeof(lim));

		n = in(), s = in(), t = in(), F = in();
		for (i = 0; i < n; i++) {
			for (j = 0; j < n; j++) A[i][j] = in();
			C[i] = in();
		}

		gauss_jordan(n);
		for (i = 0; i < n; i++) {
			M = in();
			for (j = 0; j < M; j++) d[j] = in();
			for (j = 0; j < M; j++) add_edge(i, d[j], in(), fabs(X[i]-X[d[j]]));
		}

		V = n;
		ans = minCostFlow(s, t, F);
		if (ans < 0) puts("impossible");
		else printf("%.10lf\n", ans);
	
		for (i = 0; i < V; i++) if (lim[i]) free(edge[i]);
	}
	return 0;
}
