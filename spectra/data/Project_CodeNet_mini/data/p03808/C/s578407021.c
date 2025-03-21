#include <stdio.h>

int main()
{
	long long i, N, A[100001];
	scanf("%lld", &N);
	for (i = 0; i < N; i++) scanf("%lld", &(A[i]));
	A[N] = A[0];

	long long sum = 0, diff[100001];
	for (i = 1; i <= N; i++) {
		sum += A[i];
		diff[i] = A[i] - A[i-1];
	}
	if (sum % (N * (N + 1) / 2) != 0) printf("NO\n");
	else {
		sum /= N * (N + 1) / 2;
		for (i = 1, diff[0] = 0; i <= N; i++) {
			diff[i] = (sum - diff[i]) / N;
			if (diff[i] < 0 || diff[i] > sum) break;
			else diff[0] += diff[i];
		}
		if (i <= N || diff[0] != sum) printf("NO\n");
		else {
			for (i = 1; i <= N; i++) A[N] -= diff[i] * (N - i + 1);
			if (A[N] != 0) printf("No\n");
			else printf("YES\n");
		}
	}
	fflush(stdout);
	return 0;
}
