#include <stdio.h>

int main()
{
	int i, N, K, A[200001];
	scanf("%d %d", &N, &K);
	for (i = 1; i <= N; i++) scanf("%d", &(A[i]));
	
	int k, min = 0, B[200002], tmp;
	for (k = 1; k <= K && min < N; k++) {
		min = N;
		for (i = 1; i <= N + 1; i++) B[i] = 0;
		for (i = 1; i <= N; i++) {
			if (A[i] >= i) B[1]++;
			else B[i-A[i]]++;
			if (A[i] >= N - i) B[N+1]--;
			else B[i+A[i]+1]--;
		}
		for (i = 1, tmp = 0; i <= N; i++) {
			tmp += B[i];
			A[i] = tmp;
			if (A[i] < min) min = A[i];
		}
	}
	for (i = 1; i < N; i++) printf("%d ", A[i]);
	printf("%d\n", A[N]);
	fflush(stdout);
	return 0;
}