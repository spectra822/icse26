// Aizu 1108: A Long Ride on a Railway
// 2017.9.16 bal4u@uu

#include <stdio.h>
#include <string.h>

typedef struct { int a, b, d, f; } T;
T tbl[25]; int n, m;
int ans[12], tmp[12], len, num;

void combi(int k, int a, int w)
{
	int i, b;

	for (b = 1; b <= n; b++) {
		if (b == a) continue;
		for (i = 0; i < m; i++) {
			if ((tbl[i].a == a && tbl[i].b == b || tbl[i].a == b && tbl[i].b == a) && !tbl[i].f) {
				tbl[i].f = 1, tmp[k] = b;
				combi(k+1, b, w + tbl[i].d);
				tbl[i].f = 0;
			}
		}
	}
	if (w > len) num = k, len = w, memcpy(ans, tmp, sizeof(int)*num);
}

int main()
{
	int i, a, b;

	while (scanf("%d%d", &n, &m) && n) {
		for (i = 0; i < m; i++) scanf("%d%d%d", &tbl[i].a, &tbl[i].b, &tbl[i].d), tbl[i].f = 0;
		for (len = num = 0, a = 1; a <= n; a++) for (b = 1; b <= n; b++) {
			if (b == a) continue;
			for (i = 0; i < m; i++) {
				if ((tbl[i].a == a && tbl[i].b == b || tbl[i].b == a && tbl[i].a == b) && !tbl[i].f) {
					tbl[i].f = 1;
					tmp[0] = a, tmp[1] = b, combi(2, b, tbl[i].d);
					tbl[i].f = 0;
				}
			}
		}
		printf("%d\n", len);
		printf("%d", ans[0]);
		for (i = 1; i < num; i++) printf(" %d", ans[i]);
		printf("\n");
    }
	return 0;
}