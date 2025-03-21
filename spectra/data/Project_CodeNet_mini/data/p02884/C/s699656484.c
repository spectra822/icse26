#include<stdio.h>
double MIN(double a,double b){return a<b?a:b;}
int main(){
  int n,m,i,j,k,a,b,e[610],c[610][610]={};
  double s,min=1e9,d[1010]={};
  scanf("%d %d",&n,&m);
  for(i=0;i<=n;i++)d[i]=1e9;
  d[n]=0;
  for(i=0;i<=n;i++)e[i]=-1;
  while(m--){
    scanf("%d %d",&i,&j);
    c[i][j]=1;
  }
  for(i=n-1;i;i--){
      s=b=a=0;
      for(j=i;j<=n;j++){
	if(c[i][j]){
	  s+=d[j]+1;
	  if(b==0||d[b]<d[j])b=j;
	  a++;
	}
      }
      d[i]=s/a;
      if(a>1)e[i]=b;
      //printf("%lf ",d[i][k]);
  }//printf("\n");
  min=d[1];
  for(k=1;k<=n;k++){//printf("%d\n",e[k]);
    if(e[k]==-1)continue;
    for(j=0;j<n;j++)d[j]=1e9;
    d[n]=0;
    for(i=n-1;i;i--){
      s=a=0;
      for(j=i;j<=n;j++){
	if(c[i][j]==0||(i==k&&j==e[k]))continue;
	s+=d[j]+1;
	a++;
      }
      d[i]=s/a;
      //for(j=1;j<=n;j++)printf("%d:%lf ",j,d[j]);printf("\n");
    }//printf("\n");
    if(min>d[1])min=d[1];
  }
  printf("%.10lf\n",min);
  return 0;
}
