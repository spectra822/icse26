// AOJ 0275 Railroad
// 2018.2.21 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define QMAX 200000
typedef struct { int t, s; } QUE;
QUE que[QMAX+2]; int qsize;

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
int S; 
int hi[100002], *to[100002]; short *w[100002];
int dist[100002];
char mk[100002];
int c[40002], d[40002];

int q[100002], top, tail;
int hi2[100002], *to2[100002];
int deg[100002];
int ord[100002], cnt;

unsigned long long dp[100002];

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

void dijkstra(int start)
{
	int i, s, e, d;

	memset(dist, INF, S << 2);
	qsize = 0;
	enq(start, 0), dist[start] = 0;
	while (qsize) {
		s = que[0].s, deq();
		for (i = 0; i < hi[s]; i++) {
			e = to[s][i];
			d = dist[s] + w[s][i];
			if (dist[e] > d) dist[e] = d, enq(e, d);
		}
	}
}

void tsort(int start, int goal)
{
    int i, s, e;

	memset(mk, 0, S);
	q[0] = goal, top = 0, tail = 1;
	while (top < tail) {
		s = q[top++];
		if (mk[s]) continue;
		for (i = 0; i < hi[s]; i++) {
			e = to[s][i];
			if (dist[s] == dist[e] + w[s][i]) {
				q[tail++] = e;
				to2[e][hi2[e]++] = s;
			}
		}
		mk[s] = 1;
	}

	cnt = 0;
	for (s = 0; s < S; s++) for (i = 0; i < hi2[s]; i++) deg[to2[s][i]]++;
	q[0] = start, top = 0, tail = 1;
	while (top < tail) {
		s = q[top++];
		ord[cnt++] = s;
		for (i = 0; i < hi2[s]; i++) {
			e = to2[s][i];
			if (--deg[e] == 0) q[tail++] = e;
		}
	}
}

int main()
{
	int R, Q, u, v, _w, a, b, i, j, k, ii;
	int *memo;
	
	S = in(), R = in();
	memo = malloc(R*3*sizeof(int));
	j = 0, i = R; while (i--) {
		memo[j++] = u = in()-1, hi[u]++;
		memo[j++] = v = in()-1, hi[v]++;
		memo[j++] = in();
	}
	for (i = 0; i < S; i++) if (hi[i]) {
		to [i] = malloc(hi[i] << 2), w[i] = malloc(hi[i] << 1);
		to2[i] = malloc(hi[i] << 2);
	}
	
	memset(hi, 0, S << 2);
	j = 0; while (R--) {
		u = memo[j++], v = memo[j++], _w = memo[j++];
		k = hi[u]++, to[u][k] = v, w[u][k] = _w;
		k = hi[v]++, to[v][k] = u, w[v][k] = _w;
	}
	free(memo);
	
	a = in()-1, b = in()-1, Q = in();
	for (i = 0; i < Q; i++) c[i] = in()-1, d[i] = in()-1;

	dijkstra(a);
	tsort(a, b);

	
    ii = (Q+63)>>6; for (i = 0; i < ii; i++) {
        memset(dp, 0, sizeof(dp));
		for (j = 0; j < 64; j++) if ((i<<6)+j < Q) dp[c[(i<<6)+j]] |= 1LL << j;
		for (j = 0; j < cnt; j++) {
			u = ord[j];
			for (k = 0; k < hi2[u]; k++) dp[to2[u][k]] |= dp[u];
		}
        for (j = 0; j < 64; j++) if ((i<<6)+j < Q) {
            puts(dp[d[(i<<6)+j]] & (1LL<<j)? "Yes": "No");
		}
    }
	return 0;
}

