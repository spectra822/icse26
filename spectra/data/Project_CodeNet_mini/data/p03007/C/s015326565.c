#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <math.h>
#include <limits.h>
#define Max(a, b) ((a) > (b) ? (a) : (b))
#define Min(a, b) ((a) > (b) ? (b) : (a))
#define abs(x) ((x) > 0 ? (x) : -(x))
#define MOD (ll)1000000007 //10^9 + 7
#define endl printf("\n")
typedef long long ll;
#define MAX_N (1 << 17)

int
asc(const void *a, const void *b)
{
  ll x = *(ll *)a, y = *(ll *)b;
  if (x > y) return  1;
  if (x < y) return -1;
  return 0;
}

long long
dfs(int f, int b, int l, int sign, ll *a)
{
  if (f == l) {
    ll sum = a[l];
    if (sign == 1) {
      for (int i = l + 1; i <= b - 1; i++) {
	printf("%lld %lld\n", sum, a[i]);
	sum -= a[i];
      }
      printf("%lld %lld\n", a[b], sum);
      sum = a[b] - sum;
      return sum;
    } else {
      for (int i = l + 1; i <= b; i++) {
	printf("%lld %lld\n", sum, a[i]);
	sum -= a[i];
      }
      return sum;
    }
  }
  if (b == l + 1) {
    ll sum = a[l + 1];
    if (sign == 1) {
      for (int i = f; i <= l; i++) {
	printf("%lld %lld\n", sum, a[i]);
	sum -= a[i];
      }
      return sum;
    } else {
      for (int i = f; i < l; i++) {
	printf("%lld %lld\n", sum, a[i]);
	sum -= a[i];
      }
      printf("%lld %lld\n", a[l], sum);
      sum = a[l] - sum;
      return sum;
    }
  }
  if (sign == 1) {
    printf("%lld %lld\n", a[b], a[f]);
    ll x = dfs(f + 1, b - 1, l, -sign, a);
    printf("%lld %lld\n", a[b] - a[f], x);
    return a[b] - a[f] - x;
  } else {
    printf("%lld %lld\n", a[f], a[b]);
    ll x = dfs(f + 1, b - 1, l, -sign, a);
    printf("%lld %lld\n", a[f] - a[b], x);
    return a[f] - a[b] - x;
  }
}
      
    

int
main(int argc, char *argv[])
{
  int n; ll a[100010];
  scanf("%d", &n);
  ll sum = 0;
  for (int i = 0; i < n; i++) {
    scanf("%lld", &a[i]);
    sum += abs(a[i]);
  }
  qsort(a, n, sizeof(ll), asc);

  if (a[0] >= 0) {
    printf("%lld\n", sum - a[0] - a[0]);
    ll x = a[0];
    for (int i = 1; i < n - 1; i++) {
      printf("%lld %lld\n", x, a[i]);
      x -= a[i];
    } printf("%lld %lld\n", a[n - 1], x);
  }
  else if (a[n - 1] <= 0) {
    printf("%lld\n", sum + a[n - 1] + a[n - 1]);
    ll x = a[n - 1];
    for (int i = 0; i < n - 1; i++) {
      printf("%lld %lld\n", x, a[i]);
      x -= a[i];
    }
  }
  else {
    printf("%lld\n", sum);
    int l = 0, r = n, med;
    while (r - l > 1) {
      med = (l + r) / 2;
      if (a[med] < 0) l = med;
      else r = med;
    } //printf("l : %d\n", l);
    dfs(0, n - 1, l, 1, a);
  }
  return 0;
}
    
    
