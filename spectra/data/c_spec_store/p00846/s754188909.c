// AOJ 1267: How I Mathematician Wonder What You Are!
// 2017.12.18 bal4u@uu

#include <stdio.h>
#include <string.h>
#include <math.h>

#define EPS 1e-8

typedef struct { double x, y; } PP;
typedef struct { PP s, e; } LINE;
PP p[51];

PP a[5] = {{0,0},{10000,0},{10000,10000},{0,10000},{0,0}};

int dcmp(double x)
{
	if (fabs(x) < EPS) return 0;
	return x < 0 ? -1 : 1;
}

double cross(double ax, double ay, double bx, double by) { return ax*by - ay*bx; }

void lineIntersection(PP *p, LINE *a, PP *vs, PP *ve)
{
    double a1, a2;

	a1 = cross(ve->x  - vs->x, ve->y  - vs->y,
			   a->s.x - vs->x, a->s.y - vs->y);
	a2 = cross(ve->x  - vs->x, ve->y  - vs->y,
			   a->e.x - vs->x, a->e.y - vs->y);
	p->x = (a->s.x*a2 - a->e.x*a1) / (a2-a1);
	p->y = (a->s.y*a2 - a->e.y*a1) / (a2-a1);
}

int convex_cut(LINE *u, int n, PP *p, PP *po)
{
	int i, d1, d2, top = 0;

    for (i = 0; i < n; i++) {
        d1 = dcmp(cross(u->e.x - u->s.x, u->e.y - u->s.y,
						p[i].x - u->s.x, p[i].y - u->s.y));
        d2 = dcmp(cross(u->e.x - u->s.x, u->e.y - u->s.y,
				      p[i+1].x - u->s.x, p[i+1].y - u->s.y));
        if (d1 >= 0) po[top++] = p[i];
        if (d1*d2 < 0) lineIntersection(po + top++, u, p+i, p+i+1);
    }
	po[top].x = po[0].x, po[top].y = po[0].y;
    return top;
}

int main()
{
	int n, i, x, y, k, k1, k2;
	PP pol[2][100];
	LINE u;

	while(scanf("%d", &n) && n > 0) {
		for (i = 0; i < n; i++) {
			scanf("%d%d", &x, &y);
			p[i].x = x, p[i].y = y;
		}
		p[n] = p[0];

		k = 4, memcpy(pol[0], a, sizeof(a));

		for (k1 = 0, k2 = 1, i = 0; i < n; i++, k1 = k2, k2 = !k2) {
			u.s = p[i], u.e = p[i+1];
			k = convex_cut(&u, k, pol[k1], pol[k2]);
			if (k == 0) break;
		}
		puts(k > 0 ? "1" : "0");
	}
	return 0;
}