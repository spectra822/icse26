#include <stdio.h>

int main(void) {

  int n,s;
  scanf("%d %d", &n, &s);
  int a[n];
  for (int i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }
  long mod = 998244353;
  long dp[n][s+1][2];
  for (int i = 0; i < n; i++) {
    for (int j = 0; j <= s; j++) {
      dp[i][j][0] = 0;
      dp[i][j][1] = 0;
    }
  }
  dp[0][0][0] = 1;
  dp[0][0][1] = 1;
  if (a[0] <= s) {
    dp[0][a[0]][0] = 1;
    dp[0][a[0]][1] = 1;
  }
  for (int i = 1; i < n; i++) {
    for (int j = 0; j <= s; j++) {
      dp[i][j][0] += dp[i-1][j][0];
      if (j+a[i] <= s) {
        dp[i][j+a[i]][0] += dp[i-1][j][0];
        dp[i][j+a[i]][0] %= mod;
      }
    }
    dp[i][0][0]++;
    if (a[i] <= s) {
      dp[i][a[i]][0]++;
      dp[i][a[i]][0] %= mod;
    }
    for (int j = 0; j <= s; j++) {
      dp[i][j][1] = dp[i-1][j][1]+dp[i][j][0];
      dp[i][j][1] %= mod;
    }
  }
  printf("%ld\n", dp[n-1][s][1]);

  return 0;
}