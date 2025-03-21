#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>

typedef int32_t i32;
typedef int64_t i64;

#define MAX(a,b) ((a)>(b)?(a):(b))
#define ALLOC(size,type) ((type*)calloc((size),sizeof(type)))

typedef struct index_val {
  i32 k;
  i64 v;
} node;

void run (void) {
  i32 n, m, k;
  scanf ("%" SCNi32 "%" SCNi32 "%" SCNi32, &n, &m, &k);
  i32 *a = ALLOC (n, i32);
  for (i32 i = 0; i < n; ++i) {
    scanf ("%" SCNi32, a + i);
  }
  i64 *dp = ALLOC (n, i64);
  for (i32 i = 0; i < n; ++i) {
    dp[i] = a[i];
  }
  node *d = ALLOC (n, node);
  for (i32 i = 2; i <= k; ++i) {
    i32 f = 0;
    i32 b = 0;
    d[0] = (node){i - 2, dp[i - 2]};
    for (i32 j = i - 1; j < n; ++j) {
      if (d[f].k == j - m - 1) ++f;
      i64 v = d[f].v + (i64) i * a[j];
      while (f <= b && d[b].v <= dp[j]) --b;
      d[++b] = (node) {j, dp[j]};
      dp[j] = v;
    }
  }
  i64 ans = 0;
  for (i32 i = k - 1; i < n; ++i) {
    if (ans < dp[i]) {
      ans = dp[i];
    }
  }
  printf("%" PRIi64 "\n", ans);
}

int main (void) {
  run();
  return 0;
}
