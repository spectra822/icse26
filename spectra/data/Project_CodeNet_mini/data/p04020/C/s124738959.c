#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i, N;
	long long A[100001];
	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%lld", &(A[i]));

	long long ans = 0;
	for (i = 1; i < N; i++) {
		ans += A[i] / 2;
		if (A[i+1] > 1 && A[i] % 2 == 1) {
			A[i+1]--;
			ans++;
		}
	}
	ans += A[N] / 2;

	printf("%lld\n", ans);
	fflush(stdout);
	return 0;
}