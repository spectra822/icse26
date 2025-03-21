#include <stdio.h>

int main (void){
  
  int N;
  
  scanf("%d", &N);
  
  int A, B;
  
  scanf("%d %d", &A, &B);
  
  int i;
  
  int count=0;
  
  int sum;
  
  int a, b, c, d, e;
  
  for (i=1; i<=N; i++){   
      e = i % 10;
      d = ((i-e)/10) % 10;
      c = ((i-10*d-e)/100) % 10;
      b = ((i-100*c-10*d-e)/1000) % 10;
      a = ((i-1000*b-100*c-10*d-e)/10000) % 10;
      sum = a+b+c+d+e;
    if (A <= sum && sum <= B)
    {count = count + i;}
  }
  printf("%d", count);
  
  return 0;
}