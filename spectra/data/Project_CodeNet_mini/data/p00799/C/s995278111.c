// AOJ 1219: Pump up Batteries
// 2017.10.23 bal4u@uu

#include <stdio.h>
#include <string.h>

#define QMAX 102
int que[104], top, end;

typedef struct { char use; int t, r, i, n, u[51], c[51]; } T; // r:remain time
T tbl[102], *tp, *tend;

int main() 
{
	int n, lim, i, u, c, t, ans;

	while (scanf("%d%d", &n, &lim) && n > 0) {
		for (tp = tbl, tend = tp + n; tp < tend; tp++) {
			tp->use = 1, tp->i = 0;
			for (i = 0; scanf("%d", &u) && u > 0; i++)
				scanf("%d", &c), tp->u[i] = u, tp->c[i] = c;
			tp->n = i, tp->r = tp->u[0];
		}

		ans = 0, top = end = 0;
		for (t = 1; t <= lim; t++) {
			for (tp = tbl, i = 0; i < n; i++, tp++) {
				if (tp->use) {
					tp->t = t;
					if (--tp->r == 0) {
						tp->use = 0, tp->r = tp->c[tp->i];
						que[end] = i; if (++end == QMAX) end = 0;
					}
				}
			}
			if (end == top) continue;
			for (tp = tbl, i = 0; i < n; i++, tp++) {
				if (tp->t != t && tp->use == 0) {
					if (i == que[top]) tp->r--;
					else ans++;
				}
			}
			if (top != end) {
				tp = tbl + que[top];
				if (tp->r == 0) {
					tp->use = 1;
					if (++tp->i == tp->n) tp->i = 0;
					tp->r = tp->u[tp->i];
					if (++top == QMAX) top = 0;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0; 
}