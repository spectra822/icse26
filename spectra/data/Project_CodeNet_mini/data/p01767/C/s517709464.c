#include <stdio.h>
#include <stdlib.h>

int compare(const void *a, const void *b) {
	return *(int *)a - *(int *)b;
}

int upperBound(int data[], int n, int key) {
	int l = 0, r = n - 1;

	while (l <= r) {
		int m = (l + r) / 2;

		if (data[m] > key)
			r = m - 1;
		else
			l = m + 1;
	}

	return l;
}

int a[300000], b[300000];
long long c[300000], sum[300001];

int main(void) {
	int i;
	int n, m;

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%d", a + i);
	scanf("%d", &m);
	for (i = 0; i < m; i++)
		scanf("%d", b + i);
	for (i = 0; i < m; i++)
		scanf("%lld", c + i);

	qsort(a, n, sizeof(int), &compare);

	for (i = 1; i <= n; i++)
		sum[i] = sum[i - 1] + a[i - 1];

	for (i = 0; i < m; i++)
		puts(sum[upperBound(a, n, b[i])] >= c[i] ? "Yes" : "No");

	return 0;
}