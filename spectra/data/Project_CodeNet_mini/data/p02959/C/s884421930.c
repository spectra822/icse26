#include <stdio.h>
int main(){
  int N;
  long long int A[200000],B[200000];
  long long int S=0LL;
  scanf("%d",&N);
  for(int i=1;i<=N+1;i++) 
    scanf("%lld",A+i);
  for(int i=1;i<=N;i++) 
    scanf("%lld",B+i);
  B[0]=0;
  B[N+1]=0LL;
  long long int C=0;
  for(int i=1;i<=N+1;i++){
    S+=A[i]>B[i-1]?B[i-1]:A[i];
    A[i]=A[i]>B[i-1]?A[i]-B[i-1]:0;
    S+=A[i]>B[i]?B[i]:A[i];
    B[i]=A[i]>B[i]?0:B[i]-A[i];
  }
  printf("%lld\n",S);
  return 0;
}