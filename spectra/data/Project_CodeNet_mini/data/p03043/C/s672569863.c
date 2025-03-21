#include<stdio.h>

int main(){
  int N,K;
  scanf("%d%d",&N,&K);
  int multi=1,i=N;
  int denomi[N];
  long double nume=0;
  while (i>0){
    denomi[i-1]=0;
    while (K>multi*i){
      multi*=2;
    }
    denomi[i-1]+=multi*N;
    i--;
  }

  for (int j = 0; j < N; j++)
  {
    nume+=denomi[0]/denomi[j];
  }
  

  printf("%.12Lf",nume/denomi[0]);
  

  return 0;
}