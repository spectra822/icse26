// AOJ 2488 Tree Construction
// 2018.2.28 bal4u

#include <stdio.h>
#include <string.h>

#define ABS(a)  ((a)>=0?(a):-(a))
int x[1001], y[1001];
int dp[1001][1001];

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = 10*n + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

int main()
{
	int n, i, j, l, t;

	n = in();
	for (i = 0; i < n; i++) x[i] = in(), y[i] = in();

	memset(dp, 0x10, sizeof(dp));
	for (i = 0; i < n; i++) dp[i][i] = 0;

	for (l = 0; l < n; l++) for (i = 0; i+l < n; i++) for (j = i; j-i < l; j++) {
		t = dp[i][j] + dp[j+1][i+l] + ABS(x[i]-x[j+1]) + ABS(y[j]-y[i+l]);
		if (t < dp[i][i+l]) dp[i][i+l] = t;
	}
	printf("%d\n", dp[0][n-1]);
	return 0;
}
