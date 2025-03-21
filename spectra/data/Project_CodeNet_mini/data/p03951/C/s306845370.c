#include<stdio.h>

int main(){
  int N,ans=0;
  scanf("%d",&N);
  char S[N+1];
  char T[N+1];
  scanf("%s",S);
  scanf("%s",T);

  int i=N-1;
  int j=i;
  while (i>=0)
  {
    int i=N-1;
    while (j>=0&&S[i]!=T[j])
    {
      j--;
    }
    if(j>=0){
      while (j>=0&&S[i]==T[j]){ i--; j--; }
      if (j<0){
        ans=2*N-(N-i-1);
        break;
      }
    }else
    {
      ans=2*N-(N-i-1);
      break;
    }
  }

  printf("%d",ans);

  return 0;
}