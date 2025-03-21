// AOJ 3055 Don't Burn Kotatsu Turtle
// 2019.4.7 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//// 高速入力
#if 1
#define gc() getchar_unlocked()
#define pc(x) putchar_unlocked(x)
#else
#define gc() getchar()
#define pc(x) putchar(x)
#endif
int in()    // 非負整数の入力
{
	int n = 0, c = gc();
	//	while (isspace(c)) c = gc();
	do n = 10 * n + (c & 0xf), c = gc(); while (c >= '0');
	return n;
}

void ins(char *s)  // 文字列の入力　スペース以下の文字で入力終了
{
	do *s = gc();
	while (*s++ > ' ');
	*(s - 1) = 0;
}


//// 優先度付きキュー（ダイクストラ法用）
#define MAX 500000
typedef struct { long long t; short r, c; } QUE;
QUE que[MAX]; int qsize;

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
		qt = que[i]; que[i] = que[min]; que[min] = qt;
		min_heapify(min);
	}
}

void deq()
{
	que[0] = que[--qsize];
	min_heapify(0);
}

void enq(int r, int c, long long t)
{
	int i, min;
	QUE qt;

	i = qsize++;
	que[i].t = t, que[i].r = r, que[i].c = c;
	while (i > 0 && que[min = PARENT(i)].t > que[i].t) {
		qt = que[i]; que[i] = que[min]; que[min] = qt;
		i = min;
	}
}


//// 本問題関連
#define MAXV 1005
char vis[MAXV][MAXV];
char map[MAXV][MAXV]; int H, W;
char bomb[MAXV][MAXV];
int A, B;
int mv[8][2] = { {-1,0},{0,1},{1,0},{0,-1},{-1,-1},{-1,1},{1,1},{1,-1} };
int tt[8][2];

long long dijkstra(int sr, int sc, int gr, int gc)
{
	int i, k, r, c, f, g, rr, cc;
	long long t;

	enq(sr, sc, 0);
	while (qsize) {
		r = que[0].r, c = que[0].c, t = que[0].t, deq();
		if (r == gr && c == gc) return t;
		if (vis[r][c]) continue;
		vis[r][c] = 1;

		f = bomb[r][c], k = (2-f) << 2;
		for (i = 0; i < k; i++) {
			rr = r + mv[i][0], cc = c + mv[i][1];
			if (rr < 1 || rr > H || cc < 1 || cc > W) continue;
			g = (map[rr][cc] == '#');
			if (f && g) continue;
			if ((i < 4 || g) && !vis[rr][cc]) enq(rr, cc, t + tt[i][g]);
		}
	}
	return -1LL;
}


int main()
{
	int i, r, c, sr, sc, tr, tc;
	long long ans;

	H = in(), W = in(), A = in(), B = in();
	for (r = 1; r <= H; r++) {
		ins(map[r]+1);
		for (c = 1; c <= W; c++) {
			if (map[r][c] == '*') {
				bomb[r][c] = 1;
				for (i = 0; i < 8; i++)
					bomb[r + mv[i][0]][c + mv[i][1]] = 1;
			}
			else if (map[r][c] == 's') sr = r, sc = c;
			else if (map[r][c] == 'g') tr = r, tc = c;
		}
	}
	for (i = 0; i < 4; i++) tt[i][0] = A, tt[i][1] = A + B;
	A <<= 1;
	for (; i < 8; i++) tt[i][0] = A, tt[i][1] = A + B;

	ans = dijkstra(sr, sc, tr, tc);
	if (ans >= 0) printf("%lld\n", ans);
	else puts("INF");
	return 0;
}

