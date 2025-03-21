// AOJ 1318 Long Distance Taxi
// 2018.3.2 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Hash table for string
#define HASHSIZ   29989
typedef struct { char *s; short id; } HASH;
HASH hash[HASHSIZ+2], *hashend = hash+HASHSIZ;

int insert(char *s, int id)
{
	unsigned long long i;
	char *p;
	HASH *tp;

	i = 0, p = s; while (*p) i = (i<<6) + *p++;
	tp = hash + (int)(i % HASHSIZ);
	while (tp->s != NULL) {
		if (!strcmp(tp->s, s)) return tp->id;
		if (++tp == hashend) tp = hash;
	}
	tp->s = s, tp->id = id;
	return -1;
}

#define QMAX 1200000
typedef struct { int t; short s, c; } QUE;
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

void enq(short s, int t, short c)
{
	int i, min;
	QUE qt;

	i = qsize++;
	que[i].s = s, que[i].t = t, que[i].c = c;
	while (i > 0 && que[min = PARENT(i)].t > que[i].t) {
		qt = que[i], que[i] = que[min], que[min] = qt;
		i = min;
	}
}

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

void ins(char *buf)
{
	while ((*buf = getchar_unlocked()) > ' ') buf++;
	*buf = 0;
}

#define MAX 6002
short memo[3002*3];
short hi[MAX], *to[MAX], *dd[MAX];
char city[MAX][17]; int sz;
char LPG[MAX];
int dist[MAX][2002];

int dijkstra(int n, int cap, int start, int goal)
{
	int i, s, e, c, nc, d, nd;

	memset(dist, 0x10, sizeof(dist));
	qsize = 0;
	enq(start, 0, cap); dist[start][cap] = 0;
	while (qsize) {
		s = que[0].s, d = que[0].t, c = que[0].c, deq();
		if (s == goal) return d;

		if (dist[s][c] < d) continue;

		if (LPG[s]) c = cap;
		for (i = 0; i < hi[s]; i++) {
			e = to[s][i], nd = d + dd[s][i], nc = c - dd[s][i];
			if (nc < 0) continue;
			if (dist[e][nc] > nd) dist[e][nc] = nd, enq(e, nd, nc);
		}
	}
	return -1;
}

int main()
{
	int N, M, cap, i, j, a, b, c;
	char buf[20];

	while (N = in()) {
		M = in(), cap = 10*in();
		memset(hash, 0, sizeof(hash));

		ins(city[0]), ins(city[1]);
		insert(city[0], 0), insert(city[1], 1);

		memset(hi, 0, sizeof(hi));
		sz = 2;
		j = 0, i = N; while (i--) {
			ins(city[sz]), a = insert(city[sz], sz);
			if (a < 0) a = sz++;
			memo[j++] = a, hi[a]++;
			ins(city[sz]), b = insert(city[sz], sz);
			if (b < 0) b = sz++;
			memo[j++] = b, hi[b]++;
			memo[j++] = in();
		}
		for (a = 0; a < sz; a++) if (hi[a]) {
			to[a] = malloc(hi[a] << 1);
			dd[a] = malloc(hi[a] << 1);
		}
		memset(hi, 0, sizeof(hi));
		j = 0; while (N--) {
			a = memo[j++], b = memo[j++], c = memo[j++];
			i = hi[a]++, to[a][i] = b, dd[a][i] = c;
			i = hi[b]++, to[b][i] = a, dd[b][i] = c;
		}
		memset(LPG, 0, sz);
		for (i = 0; i < M; i++) {
			ins(buf), a = insert(buf, -1);
			if (a >= 0) LPG[a] = 1;
		}

		printf("%d\n", dijkstra(sz, cap, 0, 1));

		for (a = 0; a < sz; a++) {
			if (hi[a]) free(to[a]), free(dd[a]);
		}
	}
	return 0;
}
