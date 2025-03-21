#include <stdio.h>
#define N 1000000
int A[N];
int Partition(int p, int r){
  int x, i, j, tmp;
  x = A[r];
  i = p-1;
  for(j = p; j < r; j++){
    if(A[j] <= x){
      i++;
      tmp = A[i];
      A[i] = A[j];
      A[j] = tmp;
} }
  tmp = A[i+1];
  A[i+1] = A[r];
  A[r] = tmp;
  return i+1;
}
 int main(){
  int n, i, x;
  scanf("%d", &n);
  for(i = 1; i <= n; i++){
    scanf("%d", &A[i]);
  }
  x = Partition(1, n);
 for(i = 1; i <= n; i++){
  if(i == x){
    printf("[%d]",A[i]);
} else {
    printf("%d",A[i]);
  }
if(i < n) {
    printf(" ");
  }
 }
  printf("\n");
  return 0;
}
