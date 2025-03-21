#include <stdio.h>

int main()
{
	long long T[3], A[3], B[3];
	scanf("%lld %lld", &(T[1]), &(T[2]));
	scanf("%lld %lld", &(A[1]), &(A[2]));
	scanf("%lld %lld", &(B[1]), &(B[2]));
	if (A[1] * T[1] + A[2] * T[2] == B[1] * T[1] + B[2] * T[2]) {
		printf("infinity\n");
		fflush(stdout);
		return 0;
	}
	
	if (A[1] > B[1]) {
		A[1] += B[1];
		B[1] = A[1] - B[1];
		A[1] -= B[1];
		A[2] += B[2];
		B[2] = A[2] - B[2];
		A[2] -= B[2];
	}
	if ((B[1] - A[1]) * T[1] > (A[2] - B[2]) * T[2]) printf("0\n");
	else if ((B[1] - A[1]) * T[1] % ((A[2] - B[2]) * T[2] - (B[1] - A[1]) * T[1]) == 0) printf("%lld\n", (B[1] - A[1]) * T[1] / ((A[2] - B[2]) * T[2] - (B[1] - A[1]) * T[1]) * 2);
	else printf("%lld\n", (B[1] - A[1]) * T[1] / ((A[2] - B[2]) * T[2] - (B[1] - A[1]) * T[1]) * 2 + 1);
	fflush(stdout);
	return 0;
}