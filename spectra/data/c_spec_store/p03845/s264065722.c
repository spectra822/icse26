#include<stdio.h>

int main(void){
  int n, m, sum, ans;
  int t[100], p[100], x[100];
  scanf("%d", &n);
  for(int i=0; i<n; i++){
    scanf("%d", &t[i]);
  }
  scanf("%d", &m);
  for(int i=0; i<m; i++){
    scanf("%d", &p[i]);
    scanf("%d", &x[i]);
  }

  sum = 0;
  for(int i=0; i<n; i++){
    sum += t[i];
  }

  for(int i=0; i<m; i++){
    printf("%d\n", sum-t[p[i]-1]+x[i]);
  }

  return 0;
}
