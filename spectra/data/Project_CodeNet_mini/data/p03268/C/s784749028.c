#include <stdio.h>
#include <stdlib.h>

int main()
{
	long long N, K;
	scanf("%lld %lld", &N, &K);
	if (K % 2 == 1) printf("%lld\n", (N / K) * (N / K) * (N / K));
	else printf("%lld\n", (N / K) * (N / K) * (N / K) + ((N + K / 2) / K) * ((N + K / 2) / K) * ((N + K / 2) / K));
	fflush(stdout);
	return 0;
}