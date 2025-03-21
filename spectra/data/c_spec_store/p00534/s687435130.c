#include<stdio.h>
int main(){

  int n,m,hi[1001][1001],k[1001],t[1001],i,j;

    scanf("%d%d",&n,&m);

  for(i=1;i<=n;i++){
    scanf("%d",&k[i]);
  }

  for(i=1;i<=m;i++){
    scanf("%d",&t[i]);
  }


  for(i=0;i<=m;i++){
    for(j=0;j<=n;j++){
    hi[i][j]=1000000000;
  }
  }



  for(i=0;i<=m;i++){
    hi[i][0]=0;
  }

  for(i=1;i<=m;i++){
    for(j=1;j<=n;j++){
      hi[i][j]=k[j]*t[i]+(hi[i-1][j-1]);
      if(hi[i][j]>hi[i-1][j]) hi[i][j]=hi[i-1][j];
    }
  }

  printf("%d\n",hi[m][n]);

  return 0;
}