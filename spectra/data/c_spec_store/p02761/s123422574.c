#include<stdio.h>

int main(){
  int N,M,num=0;
  scanf("%d%d",&N,&M);
  int s[N],c[M];
  int d[]={100,10,1};
  int digit[N];
  for (int i = 0; i < N; i++){digit[i]=-1;}
  
  if (M==0){
    switch (N)
    {
    case 1:
      num=0;
      break;
    case 2:
      num=10;
      break;
    case 3:
      num=100;
      break;
    default:
      break;
    }
  }else{
    for (int i = 0; i < M; i++)
    {
      scanf("%d%d",&s[i],&c[i]);
      if (digit[s[i]-1]==-1)
      {
        digit[s[i]-1]=c[i]*d[3-N+(s[i]-1)];
      }else if (digit[s[i]-1]/d[3-N+(s[i]-1)]!=c[i])
      {
        num=-1;
      }
    }

    if (num!=-1)
    {
      for (int i = 0; i < N; i++)
      {
        if (digit[i]!=-1)
        {
          num+=digit[i];
        }else if (N>1&&i==0&&digit[i]!=0){
          num+=d[3-N+i];
        }
      }
    }
  }

  if (N>1&&s[0]==1&&c[0]==0)
  {
    puts("-1");
  }else{
    printf("%d",num);
  }
  
  return 0;
}