#include<stdio.h>
int X[]={1,0,-1,0};
int Y[]={0,1,0,-1};
int main(){
  char d[300][300]={};
  int n,i,j,k,c=0,t,r,x[100010],y[100010],ny,nx;
  scanf("%d",&n);
  for(i=0;i<n;i++){
    for(j=0;j<n;j++)scanf(" %c",&d[i+1][j+1]);
  }
  for(i=0;i<n;i++){
    for(j=0;j<n;j++){
      if(d[i+1][j+1]=='x')continue;
      d[y[t=0]=i+1][x[0]=j+1]='x';
      c++;
      for(r=1;r-t;t++){
	for(k=0;k<4;k++){
	  ny=y[t]+Y[k];
	  nx=x[t]+X[k];
	  if(d[ny][nx]-'o')continue;
	  d[y[r]=ny][x[r]=nx]='x';
	  r++;
	}
      }
    }
  }
  printf("%d\n",(c-1)/3);
  return 0;
}