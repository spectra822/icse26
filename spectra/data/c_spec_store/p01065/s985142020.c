// AOL 1580 Barter
// 2018.2.18 bal4u

#include <stdio.h>
#include <string.h>

#define BASE 300
#define DBASE 600
int dp[101][BASE+2][DBASE+2];

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

int main()
{
	int n, x, y, a, b, c, d, i, j, k, ans;

	n = in();
	x = in(), y = in();
	memset(dp, -1, sizeof(dp));
    dp[0][0][BASE] = 0;

	for (i = 0; i < n; i++) {
		a = in(), b = in(), c = in(), d = in();
		for (j = 0; j <= BASE; j++) for (k = 0; k <= DBASE; k++) {
			if (dp[i][j][k] < 0) continue;
			if (dp[i+1][j][k] < dp[i][j][k]) dp[i+1][j][k] = dp[i][j][k];
			if (x >= j + a && dp[i+1][j+a][k-b] < dp[i][j][k]) dp[i+1][j+a][k-b] = dp[i][j][k]; 
            if (dp[i+1][j][k+c] < dp[i][j][k]+d) dp[i+1][j][k+c] = dp[i][j][k]+d;
        }
    }

    ans = 0;
	for (j = 0; j <= x; j++) for (k = 0; k <= 600; k++) {
		if (ans < dp[n][j][k] && y+BASE >= k) ans = dp[n][j][k];
	}
    printf("%d\n", ans);
	return 0;
}
