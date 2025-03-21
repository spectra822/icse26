#include<stdio.h>

int main(){
  int j=0;
  char S[11];
  char ans[11];
  scanf("%s",S);

  for (int i = 0; i < 11; i++)
  {
    if (S[i]=='B'){ 
      if (j>0)
      {
        j--;
      }else{
        j=0;
      }
    }else{
      ans[j++]=S[i];
      if(S[i]=='\0'){ break; }
    }
  }

  printf("%s",ans);

  return 0;
}