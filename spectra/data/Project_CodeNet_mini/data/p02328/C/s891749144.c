#include<stdio.h>
#define MAX 100001
struct rect {
  long long int height;
  long long int pos;
};
long long int table[MAX];
long long int large_histogram(long long int w);
int main(void)
{
  long long int i, j, w, temp, max = 0;
  scanf("%lld", &w);
  for (i = 0; i < w; i++) scanf("%lld", &table[i]);
  temp = large_histogram(w);
  if (max < temp) max = temp;
  printf("%lld\n", max);
}
long long int large_histogram(long long int w)
{
  long long int i, sp = 0, max = 0;
  struct rect stack[MAX];
  table[w] = 0;
  for (i = 0; i <= w; i++) {
    struct rect r;
    r.height = table[i];
    r.pos = i;
    if (!sp || stack[sp-1].height < r.height) stack[sp++] = r;
    else if (stack[sp-1].height > r.height){
      long long int target = i;
      while (sp && stack[sp-1].height >= r.height) {
        struct rect pre = stack[--sp];
        long long int area = pre.height * (i - pre.pos);
        if (max < area) max = area;
        target = pre.pos;
      }
      r.pos = target;
      stack[sp++] = r;
    }
  }
  return max;
}
