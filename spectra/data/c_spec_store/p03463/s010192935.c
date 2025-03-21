#include <stdio.h>

int main()
{
	int N, A, B;
	scanf("%d %d %d", &N, &A, &B);
	if ((B - A) % 2 == 0) printf("Alice\n");
	else printf("Borys\n");
	fflush(stdout);
	return 0;
}