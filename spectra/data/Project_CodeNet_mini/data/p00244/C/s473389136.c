// Aizu 0244: Hot Spring Trip
// 2017.9.10 bal4u@uu

#include <stdio.h>
#include <string.h>

#define INF 0x7fffffff
#define MAX 5000
#define min(a,b) ((a)<=(b)?(a):(b))
typedef struct { int t, k, c; } QUE;
QUE que[MAX]; int qsize;

#define PARENT(i) ((i)>>1)
#define LEFT(i)   ((i)<<1)
#define RIGHT(i)  (((i)<<1)+1)

void min_heapify(int i)
{
  int l, r;
  int smallest;

  l = LEFT(i), r = RIGHT(i);
  if (l < qsize && que[l].t < que[i].t) smallest = l; else smallest = i;
  if (r < qsize && que[r].t < que[smallest].t) smallest = r;
  if (smallest != i) {
    QUE t = que[i]; que[i] = que[smallest]; que[smallest] = t;
    min_heapify(smallest);
  }
}

int deq(int *k, int *c)
{
  if (qsize == 0) return 0;
  *k = que[0].k, *c = que[0].c;
  que[0] = que[--qsize];
  min_heapify(0);
  return 1;
}

void enq(int k, int t, int c)
{
  int i, ii;

  i = qsize++;
  que[i].t = t, que[i].k = k, que[i].c = c;
  while (i > 0 && que[ii = PARENT(i)].t > que[i].t) {
    QUE tt = que[i]; que[i] = que[ii]; que[ii] = tt;
    i = ii;
  }
}

typedef struct { int len, to[102], c[102]; } TBL;
TBL tbl[102];
int node[102][3]; int size;
int start, goal;

int search()
{
	int s, i, c, s2, f2, c2, k;
	TBL *p;

	qsize = 0;
	memset(node, -1, sizeof(node));
	node[start][2] = 0;
	enq(start, 0, 2);
	while(deq(&s, &c)) {
		if (s == goal) {
			if (c != 1) break;
		}
		for (p = tbl+s, i = 0; i < p->len; i++) {
			s2 = p->to[i], f2 = p->c[i];
			k = node[s][c] + f2;
			if (c != 1) {
				if (node[s2][c] < 0 || k < node[s2][c]) node[s2][c] = k, enq(s2, k, c);
			}
			if (c > 0) {
				c2 = c-1;
				k = node[s][c];
				if (node[s2][c2] < 0 || k < node[s2][c2]) node[s2][c2] = k, enq(s2, k, c2);
			}
		}
	}
	if (node[goal][0] >= 0 && node[goal][2] >= 0) return min(node[goal][0], node[goal][2]);
	if (node[goal][0] >= 0) return node[goal][0];
	return node[goal][2];
}

int main()
{
	int m, a, b, c;
	TBL *p;

	while (scanf("%d%d", &size, &m) && size) {
		memset(tbl, 0, sizeof(TBL)*size);
		start = 0, goal = size-1;
		while (m-- > 0) {
			scanf("%d%d%d", &a, &b, &c), a--, b--;
			p = tbl + a, p->to[p->len] = b, p->c[p->len] = c, p->len++;
			p = tbl + b, p->to[p->len] = a, p->c[p->len] = c, p->len++;
		}
		printf("%d\n", search());
	}
	return 0;
}