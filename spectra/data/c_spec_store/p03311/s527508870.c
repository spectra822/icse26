#include <stdio.h>
#include <stdlib.h>

int cmpnum(const void * n1, const void * n2) {
	if (*(long *)n1 > *(long *)n2)
	{
		return 1;
	}
	else if (*(long *)n1 < *(long *)n2)
	{
		return -1;
	}
	else
	{
		return 0;
	}
}

int main(void) {

  long n;
  scanf("%ld", &n);
  long a[n];
  for (long i = 0; i < n; i++) {
    scanf("%ld", &a[i]);
    a[i] -= i+1;
  }
  qsort(a, n, sizeof(long), cmpnum);
  long all = 0;
  for (long i = 1; i < n; i++) {
    all += a[i]-a[0];
  }
  long sadness = all;
  long min = all;
  long level = a[0];
  long width,height;
  for (long i = 0; i < n; i++) {
    if (a[i+1] == level) {
      continue;
    }
    width = i+1;
    if (n-width*2 <= 0) {
      break;
    }
    height = a[i+1]-a[i];
    if (height*(n-width*2) <= sadness) {
      level = a[i+1];
      sadness -= height*(n-width*2);
      min = sadness;
    } else {
      height = sadness/(n-width*2);
      level += height;
      sadness -= height*(n-width*2);
      if (sadness <= min) {
        min = sadness;
      }
      sadness = -(sadness-(n-width*2));
      if (sadness <= min) {
        min = sadness;
      }
      break;
    }
  }
  printf("%ld\n", min);

  return 0;
}