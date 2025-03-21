#include <stdio.h>

int a[1000];
int tmp[1000];

int main(void)
{
	int n, q, i, b, m, e;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", a + i);
	}
	scanf("%d", &q);
	while (q--) {
		scanf("%d%d%d", &b, &m, &e);
		for (i = b; i < e; i++) {
			tmp[i] = a[i];
		}
		e -= b;
		m -= b;
		for (i = 0; i < e; i++) {
			a[b + i] = tmp[b + (i + m) % e];
		}
	}
	for (i = 0; i < n; i++) {
		printf("%d%c", a[i], " \n"[i + 1 == n]);
	}
	return 0;
}

