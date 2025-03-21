#include <stdio.h>

int main (void){
  
  int A, B, C, X;
  
  scanf("%d", &A);
  scanf("%d", &B);
  scanf("%d", &C);
  scanf("%d", &X);
  
  int i, j, k;
  
  int count=0;
  
  for (i=0; i<=A; i++){
   for (j=0; j<=B; j++){
     for (k=0; k<=C; k++){
       
      if ( 500*i + 100*j + 50*k == X)
      { count = count + 1;}
       
     }
   }
  }
  
  printf("%d", count);
  
  return 0;
}