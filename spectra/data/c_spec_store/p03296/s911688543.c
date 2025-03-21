#include <stdio.h>

int main()
{
	int i, N, a[101], count = 0;
	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%d", &(a[i]));
	for (i = 2; i <= N; i++) {
		if (a[i] == a[i-1]) {
			count++;
			i++;
		}
	}
	printf("%d\n", count);
	fflush(stdout);
	return 0;
}