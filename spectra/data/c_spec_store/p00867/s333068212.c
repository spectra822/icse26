// AOJ 1288 Digits on the Floor
// 2018.4.5 bal4u

#include <stdio.h>
#include <string.h>

#define MAX 1002

/* UNION-FIND library */
int id[MAX], size[MAX];
void init(int n) { int i; for (i = 0; i < n; i++) id[i] = i, size[i] = 1; }
int root(int i) { while (i != id[i]) id[i] = id[id[i]], i = id[i]; return i; }
int connected(int p, int q) { return root(p) == root(q); }
void unite(int p, int q)
{
    int i = root(p), j = root(q); if (i == j) return;
    if (size[i] < size[j]) id[i] = j, size[j] += size[i]; else id[j] = i, size[i] += size[j];
}

#define PeqP(a,b)  (((a.x)==(b.x))&&((a.y)==(b.y)))
typedef struct { int x, y; } PP;
typedef struct { PP s, e; } SEG;
typedef struct { char n; SEG u[5]; char p; } T;
T t[MAX];
SEG   u[MAX]; int n;
char  f[MAX][MAX];
short uid[MAX][MAX];
short ans[10];

PP vset(int x, int y) { PP r; r.x = x, r.y = y; return r; }
PP vsub(PP p1, PP p2) { PP r; r.x = p1.x - p2.x, r.y = p1.y - p2.y; return r; }
PP vmul(PP p1, PP p2) { PP r;
	r.x = p1.x * p2.x - p1.y * p2.y, r.y = p1.x * p2.y + p1.y * p2.x; return r; }
int dot(PP a, PP b) { return a.x * b.x + a.y * b.y; };

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0, c = getchar_unlocked();
	do n = 10*n + (c & 0xf), c = getchar_unlocked(); while (c >= '0');
	return n;
}

void check256(T *id)
{
	int i, j, k1, k2;
	PP p0[2], p1[2], p2[2];
	PP p;

	j = 0;
	for (i = 0; i < id->n; i++) {
		if (f[id->u[i].s.x][id->u[i].s.y] == 1) {
			p0[j] = id->u[i].s, p1[j++] = id->u[i].e;
		} else if (f[id->u[i].e.x][id->u[i].e.y] == 1) {
			p0[j] = id->u[i].e, p1[j++] = id->u[i].s;
		}
	}
	for (i = 0; i < id->n; i++) {
		if      (!PeqP(id->u[i].s, p0[0]) && PeqP(id->u[i].e, p1[0]))
			p2[0] = id->u[i].s;
		else if (!PeqP(id->u[i].e, p0[0]) && PeqP(id->u[i].s, p1[0]))
			p2[0] = id->u[i].e;
		if      (!PeqP(id->u[i].s, p0[1]) && PeqP(id->u[i].e, p1[1]))
			p2[1] = id->u[i].s;
		else if (!PeqP(id->u[i].e, p0[1]) && PeqP(id->u[i].s, p1[1]))
			p2[1] = id->u[i].e;
	}
	p = vmul(vsub(p0[0],p1[0]), vset(0,1));
	k1 = dot(vsub(p2[0], p1[0]), p);

	p = vmul(vsub(p0[1],p1[1]), vset(0,1));
	k2 = dot(vsub(p2[1], p1[1]), p);

	if      (k1 > 0 && k2 > 0) ans[2]++;
	else if (k1 < 0 && k2 < 0) ans[5]++;
	else                       ans[6]++;
}

int pOnSeg(PP p, SEG u)
{
	int x1 = u.s.x, y1 = u.s.y, x2 = u.e.x, y2 = u.e.y;
	int d;

	if (PeqP(p, u.s) || PeqP(p, u.e)) return 0;
	if (x1 > x2) { d = x1, x1 = x2, x2 = d; d = y1, y1 = y2, y2 = d; }
	return x1 <= p.x && p.x <= x2 &&
		((y1 <= y2 && y1 <= p.y && p.y <= y2) ||
		(y1 > y2 && y2 <= p.y && p.y <= y1))
		&& (p.y - y1)*(x2 - x1) == (y2 - y1)*(p.x - x1);
}

void check08(T *id)
{
	int i, j;
	for (i = 1; i <= n; i++) if (root(i) == i) {
		for (j = 0; j < id->n; j++) {
			if (pOnSeg(u[i].s, id->u[j])) { ans[8]++; return; }
			if (pOnSeg(u[i].e, id->u[j])) { ans[8]++; return; }
		}
	}
	ans[0]++;
}

void check37(T *id)
{
	int i, j;

	for (i = 0; i < id->n; i++) {
		if (f[id->u[i].s.x][id->u[i].s.y] > 1 && f[id->u[i].e.x][id->u[i].e.y] > 1) {
			for (j = 1; j <= n; j++) if (root(j) == j) {
				if (pOnSeg(u[j].s, id->u[i])) { ans[3]++; return; }
				if (pOnSeg(u[j].e, id->u[i])) { ans[3]++; return; }
			}
		}
	}
	ans[7]++;
}

int main()
{
	int i, j, k, s;
	int x1, y1, x2, y2;

	while (n = in()) {
		memset(ans, 0, sizeof(ans));
		memset(t, 0, sizeof(T)*(n+1));
		memset(f, 0, sizeof(f));
		memset(uid, 0, sizeof(uid));
		init(n+1);

		for (i = 1; i <= n; i++) {
			x1 = in(), y1 = in(), x2 = in(), y2 = in();
			u[i].s.x = x1, u[i].s.y = y1;
			u[i].e.x = x2, u[i].e.y = y2;
			if (f[x1][y1]) unite(uid[x1][y1], i);
			else uid[x1][y1] = i;
			f[x1][y1]++;
			if (f[x2][y2]) unite(uid[x2][y2], i);
			else uid[x2][y2] = i;
			f[x2][y2]++;
		}
		for (i = 1; i <= n; i++) {
			j = root(i);
			k = t[j].n++, t[j].u[k] = u[i];
			if (f[u[i].s.x][u[i].s.y] > 1) t[j].p++;
			if (f[u[i].e.x][u[i].e.y] > 1) t[j].p++;
		}

		s = 0;
		for (i = 1; i <= n; i++) if (t[i].n >= 2) {
			s += t[i].n;
			if      (t[i].n == 2 && t[i].p == 2) ans[4]++;
			else if (t[i].n == 4 && t[i].p == 6) ans[9]++;
			else if (t[i].n == 4 && t[i].p == 8) check08(t+i);
			else if (t[i].n == 5 && t[i].p == 8) check256(t+i);
			else if (t[i].n == 3 && t[i].p == 4) check37(t+i);
		}
		s += ans[4] + ans[3] + ans[8];
		ans[1] = n-s;
		printf("%d", ans[0]);
		for (i = 1; i < 10; i++) printf(" %d", ans[i]);
		putchar('\n');
	}
	return 0;
}
