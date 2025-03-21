// Aizu Vol-1 0190: Eleven Puzzle
// 2017.8.23 bal4u@uu
// ???????????¢?´¢??????????????\??????????????§??¶????????§??????
// ????????????????????????16?????????????????§??§???OK???
// 1????????????????????§8??????4??????????????§4096????????¶??????

#include <stdio.h>

#define MAX 500000
typedef unsigned long long UL;

typedef struct { UL s; char m; } HASH;
typedef struct { UL s; char b1, b2; } QUE;
#define HASHSIZ 900001ULL
HASH hash[HASHSIZ + 5], *hashend = hash + HASHSIZ;
QUE Q[MAX + 5], *top, *end, *qmax = Q + MAX;

int lookup(UL s)
{
	HASH *p = hash + s % HASHSIZ;
	while (p->s) {
		if (p->s == s) return p->m;
		if (++p == hashend) p = hash;
	}
	return -1;
}

int insert(UL s, char m)
{
	HASH *p = hash + s % HASHSIZ;
	while (p->s) {
		if (p->s == s) return 0;
		if (++p == hashend) p = hash;
	}
	p->s = s, p->m = m;
	return 1;
}

int move[13][5] = {
	/*  0 */{ 2, -1 },
	/*  1 */{ 2, 5, -1 },
	/*  2 */{ 0, 1, 3, 6, -1 },
	/*  3 */{ 2, 7, -1 },
	/*  4 */{ 5, -1 },
	/*  5 */{ 1, 4, 6, 9, -1 },
	/*  6 */{ 2, 5, 7, 10, -1 },
	/*  7 */{ 3, 6, 8, 11, -1 },
	/*  8 */{ 7, -1 },
	/*  9 */{ 5, 10, -1 },
	/* 10 */{ 6, 9, 11, 12, -1 },
	/* 11 */{ 7, 10, -1 },
	/* 12 */{ 10, -1 } };

UL swap(UL s, int p1, int sp)
{
	UL n1;
	p1 = (12 - p1) << 2, sp = (12 - sp) << 2;
	n1 = (s >> p1) & 0xf;
	s &= ~(0xfULL << p1);
	s |= (n1 << sp);
	return s;
}

int sach(UL s, int b1, int b2, int mode, int step, int lim)
{
	int i, j, x, b[2];
	UL s2;

	top = end = Q;
	end->s = s, end->b1 = b1, end->b2 = b2, end++, end->s = 0, end++;
	while (top < end) {
		s = top->s, b[0] = top->b1, b[1] = top->b2, top++;
		if (!s) { step++, end->s = 0, end++; continue; }
		if (step > lim) break;
//	printf("%#15llx, b1 %2d, b2 %2d, step %2d\n", s, b[0], b[1], step);
		for (i = 0; i < 2; i++) {
			for (j = 0; (x = move[b[i]][j]) >= 0; j++) {
				if (x == b[0] || x == b[1]) continue;
				s2 = swap(s, x, b[i]);
				if (mode) { if (lookup(s2) >= 0) return step; }
				else if (!insert(s2, step)) continue;
				end->s = s2;
				if (i) end->b1 = b[0], end->b2 = x;
				else   end->b1 = x, end->b2 = b[1];
				end++;
			}
		}
	}
	return step;
}

int main()
{
	int i, ans, p, b1, b2;
	UL s;
	int lim = 16;

	s = 0x123456789ab0ULL, insert(s, 0);
	sach(s, 0, 12, 0, 1, lim);
	while (1) {
		b1 = -1;
		for (s = i = 0; i < 13; i++) {
			scanf("%d", &p);
			if (i == 0 && p < 0) return 0;
			if (!p) { if (b1 < 0) b1 = i; else b2 = i; }
			s = (s << 4) | p;
		}
		if ((ans = lookup(s)) < 0) {
			if ((ans = sach(s, b1, b2, 1, 1, 4)) > 4) ans = -1;
			else ans += lim;
		}
		printf(ans < 0 ? "NA\n" : "%d\n", ans);	
	}
	return 0;
}