// AOJ 3130 Calculation Training
// 2020.1.14 bal4u

#include <stdio.h>

typedef long long ll;

int main()
{
	ll N; int i, A, B;
	
	scanf("%lld%d%d", &N, &A, &B);
	N %= 12;
	i = 0; while (i < N) {
		A = A-B, ++i;
		if (i == N) break;
		B = A+B, ++i;
	}
	printf("%d %d\n", A, B);
	return 0;
}

