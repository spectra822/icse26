#include <stdio.h>

int main()
{
	int L, R, d;
	scanf("%d %d %d", &L, &R, &d);
	printf("%d\n", R / d - (L - 1) / d);
	fflush(stdout);
	return 0;
}