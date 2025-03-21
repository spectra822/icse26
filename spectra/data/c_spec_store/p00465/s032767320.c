// AOJ 0542: Authentication Level
// 2018.1.28 bal4u

#include <stdio.h>
#include <string.h>

#define QMAX 150000
typedef struct { int t; short r, c; } QUE;
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
//	if (qsize == 0) return 0;
//	*n = que[0].node, *t = que[0].t, *c = que[0].c;
	que[0] = que[--qsize];
	min_heapify(0);
}

void enq(int r, int c, int t)
{
	int i, min;
	QUE qt;

	i = qsize++;
	que[i].r = r, que[i].c = c, que[i].t = t;
	while (i > 0 && que[min = PARENT(i)].t > que[i].t) {
		qt = que[i], que[i] = que[min], que[min] = qt;
		i = min;
	}
}

int l[501][501];
int level[2][100001], lsz[2];
int mv[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
char mk[501][501];

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

int main()
{
    int R, W, H, X, Y;
	int i, j, r, c, r2, c2, t, max, ans;

    while (R = in()) {
        for (i = 0; i < 2; i++) {
			W = in(), H = in(), X = in()-1, Y = in()-1;
			for (r = 0; r < H; r++) for (c = 0; c < W; c++) l[r][c] = in();

			memset(mk, 0, sizeof(mk));
			qsize = 0, level[i][0] = max = 0, lsz[i] = 1;
			enq(Y, X, l[Y][X]), mk[Y][X] = 1;
			while (qsize) {
				t = que[0].t, r = que[0].r, c = que[0].c, deq();
				if (t > max) max = t;
				level[i][lsz[i]++] = max;

				for (j = 0; j < 4; j++) {
					r2 = r + mv[j][0], c2 = c + mv[j][1];
					if (r2 < 0 || r2 >= H || c2 < 0 || c2 >= W) continue;
					if (mk[r2][c2]) continue;
					mk[r2][c2] = 1;				// 同一部屋は２度とQに入れない
					enq(r2, c2, l[r2][c2]);
				}
			}
		}

		ans = 0x7ffffff;
		for (i = 0; i <= R; i++) {
			j = R - i;
			if (i < lsz[0] && j < lsz[1]) {
				t = level[0][i] + level[1][j];
				if (t < ans) ans = t;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}

