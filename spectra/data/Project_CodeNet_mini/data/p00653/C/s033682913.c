// AOJ 1068: School of Killifish
// 2017.12.14 bal4u@uu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INF 0x7fffffff

int pool[9000000];
int **seg;
int h, w;
int r1, c1, r2, c2, g;

void update(int r, int c, int x)
{
	int c2, t, a;

	r += h - 1;
	c += w - 1;
	seg[r][c] = x;

	while (r >= 0) {
		c2 = c;
		while (c2) {
			if (!(c2 & 1)) c2--;
			t = c2, c2 >>= 1;
			a = seg[r][t++]; if (a > seg[r][t]) a = seg[r][t];
			seg[r][c2] = a;
		}
		if (r == 0) break;

		if (!(r & 1)) r--;
		t = r, r >>= 1;
		a = seg[t++][c]; if (a > seg[t][c]) a = seg[t][c];
		seg[r][c] = a;
	}
}
 
int query2(int l, int r, int k)
{
	int m, lmin, rmin;

	if (c2 <= l || r <= c1) return INF;
    if (c1 <= l && r <= c2) return seg[g][k];
     
	k <<= 1, m = (l + r) >> 1;
    lmin = query2(l, m, ++k);
    rmin = query2(m, r, ++k);
    if (lmin > rmin) lmin = rmin; 
    return lmin;
}
 
int query(int l, int r, int k)
{
	int m, lmin, rmin;

    if (r2 <= l || r <= r1) return INF;
    if (r1 <= l && r <= r2) { g = k; return query2(0, w, 0); }
    
	k <<= 1, m = (l + r) >> 1;
    lmin = query(l, m, ++k);
    rmin = query(m, r, ++k);
    if (lmin > rmin) lmin = rmin;
    return lmin;
}
 
int main()
{
	int R, C, Q, h2, w2, r, c, v, i;

    while (scanf("%d%d%d", &R, &C, &Q) && R > 0) {

		h = w = 1;
		while (h < R) h <<= 1;
		while (w < C) w <<= 1;

		h2 = (h << 1) - 1, w2 = (w << 1) - 1;

		memset(pool, 0, sizeof(pool));
		seg = malloc(h2 * sizeof(int *));
		for (r = 0; r < h2; r++) seg[r] = pool + r*w2;

        for (r = 0; r < R; r++) for (c = 0; c < C; c++)
			scanf("%d", &v), update(r, c, v);

        for (i = 0; i < Q; i++) {
			scanf("%d%d%d%d", &r1, &c1, &r2, &c2);
			r2++, c2++;
            printf("%d\n", query(0, h, 0));
        }

		free(seg);
    }
    return 0;
}