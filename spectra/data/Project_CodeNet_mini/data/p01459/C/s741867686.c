// AOJ 2342 Light Road
// 2018.4.8 bal4u

#include <stdio.h>

#define QMAX 51000
typedef struct { char r, c, d, a, b; } Q;
Q que[QMAX+2]; int top, end;
char map[103][103];
char mk[103][103][4][11][11];
int  mv[4][2] = {{-1,0},{0,1},{1,0},{0,-1}};
int  ma[4][4] = {{0,-1,-1,1},{-1,0,1,-1},{-1,1,0,-1},{1,-1,-1,0}};
int  mb[4][4] = {{0,1,-1,-1},{1,0,-1,-1},{-1,-1,0,1},{-1,-1,1,0}};

int main()
{
	int H, W, A, B, r, c, d, a, b, nr, nc, nd, na, nb, ans;
	int sr, sc, gr, gc;
	char buf[20];

	fgets(buf, 20, stdin), sscanf(buf, "%d%d%d", &H, &W, &A), B = A;
	for (r = 0; r < H; r++) {
		fgets(map[r], 103, stdin);
		for (c = 0; c < W; c++) {
			if (map[r][c] == 'S') sr = r, sc = c;
			if (map[r][c] == 'G') gr = r, gc = c;
		}
	}
	if (sr == H-1 || map[sr+1][sc] == '#') { puts("-1"); return 0; }
	que[0].r = sr+1, que[0].c = sc, que[0].d = 2, que[0].a = que[0].b = 0;
	for (a = 0; a <= A; a++) for (b = 0; b <= B; b++) mk[sr][sc][0][a][b] = 1;
	top = 0, end = 1;
	ans = 100;
	while (top != end) {
		r = que[top].r, c = que[top].c, d = que[top].d, a = que[top].a, b = que[top].b;
		if (++top == QMAX) top = 0;
		if (r == gr && c == gc) {
			if (a+b < ans) ans = a+b;
			continue;
		}
		if (mk[r][c][d][a][b]) continue;
		mk[r][c][d][a][b] = 1;
		for (nd = 0; nd < 4; nd++) {
			nr = r + mv[nd][0], nc = c + mv[nd][1], na = ma[d][nd], nb = mb[d][nd];
			if (na < 0 && nb < 0) continue;
			if (nr < 0 || nr >= H || nc < 0 || nc >= W || map[nr][nc] == '#') continue;
			que[end].r = nr, que[end].c = nc, que[end].d = nd;
			if (na > 0) {
				if (a+1 > A || map[r][c] == 'S') continue;
				if (mk[nr][nc][nd][a+1][b]) continue;
				que[end].a = a+1, que[end].b = b;
			} else if (nb > 0) {
				if (b+1 > B || map[r][c] == 'S') continue;
				if (mk[nr][nc][nd][a][b+1]) continue;
				que[end].a = a, que[end].b = b+1;
			} else if (!na)	{
				que[end].a = a, que[end].b = b;
				if (mk[nr][nc][nd][a][b]) continue;
			}
			if (++end == QMAX) end = 0;
		}
	}
	if (ans > 20) puts("-1");
	else printf("%d\n", ans);
	return 0;
}
