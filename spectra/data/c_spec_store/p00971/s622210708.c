#include <stdio.h>
#include <string.h>
#define SMAX 4000
int next0[2][SMAX+2], next1[2][SMAX+2], dp[SMAX+2][SMAX+2];

int dfs(int aloc, int bloc);
void scns(int aloc, int bloc);
int main(void)
{
  int i, alen, blen;
  char a[SMAX+2], b[SMAX+2];
  scanf("%s", a + 1);
  scanf("%s", b + 1);
  a[0] = b[0] = '?';
  alen = strlen(a);
  blen = strlen(b);
  memset(dp, -1, sizeof(dp));
  dp[alen][blen] = 0;
  next0[0][alen] = next1[0][alen] = next0[0][alen-1] = next1[0][alen-1] = alen;
  next0[1][blen] = next1[1][blen] = next0[1][blen-1] = next1[1][blen-1] = blen;
  for (i = alen - 2; i >= 0; i--) {
    if (a[i+1] == '0') {
      next0[0][i] = i + 1;
      next1[0][i] = next1[0][i+1];
    } else {
      next0[0][i] = next0[0][i+1];
      next1[0][i] = i + 1;
    }
  }
  for (i = blen - 2; i >= 0; i--) {
    if (b[i+1] == '0') {
      next0[1][i] = i + 1;
      next1[1][i] = next1[1][i+1];
    } else {
      next0[1][i] = next0[1][i+1];
      next1[1][i] = i + 1;                                                                                                  }
  }
  scns(0, 0);
  putchar_unlocked('\n');
}

int dfs(int aloc, int bloc)
{
  int res, ans = SMAX + 2;
  if (dp[aloc][bloc] != -1) return dp[aloc][bloc];
  res = dfs(next0[0][aloc], next0[1][bloc]);
  if (ans > res) ans = res;
  res = dfs(next1[0][aloc], next1[1][bloc]);
  if (ans > res) ans = res;
  return dp[aloc][bloc] = ans + 1;
}

void scns(int aloc, int bloc)
{
  if (dfs(aloc, bloc) == dfs(next0[0][aloc], next0[1][bloc]) + 1) {
    putchar_unlocked('0');
    scns(next0[0][aloc], next0[1][bloc]);
  } else if (dfs(aloc, bloc) == dfs(next1[0][aloc], next1[1][bloc]) + 1) {
    putchar_unlocked('1');
    scns(next1[0][aloc], next1[1][bloc]);
  }
}
