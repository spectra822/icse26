#include<stdio.h>
#include<stdlib.h>
int a[110],b[110],c[110],n;
double f(int i,int j,int k){
  int w=0,l;
  if(j==0)return 0;
  for(l=0;l<n;l++){
    if(j&(1<<l))w+=c[l]*20;
  }
  return abs(b[k]-b[i])/2000.0*(w+70);
}
double d[20][1<<16]={};
int fr[20][1<<16]={};
int main(){
  int i,j,k,r[110];
  scanf("%d",&n);
  for(i=0;i<n;i++)scanf("%d %d %d",&a[i],&b[i],&c[i]);
  for(i=0;i<n;i++){
    for(j=0;j<(1<<n);j++)d[i][j]=1e18;
  }//printf("a\n");
  for(i=0;i<n;i++){
    for(j=0;j<(1<<n);j++)fr[i][j]=-1;
  }
  for(i=0;i<n;i++)d[i][1<<i]=0;
  for(j=0;j<(1<<n);j++){
    for(i=0;i<n;i++){
      if((1<<i)&j==0)continue;
      for(k=0;k<n;k++){
	if(j&(1<<k))continue;
	if(d[k][j+(1<<k)]>d[i][j]+f(i,j,k)){
	  d[k][j+(1<<k)]=d[i][j]+f(i,j,k);
	  fr[k][j+(1<<k)]=i;
	}
      }
    }
  }//printf("b\n");
  /*for(i=0;i<n;i++){
    for(j=0;j<(1<<n);j++)printf("%f ",d[i][j]);printf("\n");
  }
  for(i=0;i<n;i++){
    for(j=0;j<(1<<n);j++)printf("%d ",fr[i][j]);printf("\n");
    }//*/
  k=j-1;
  for(i=j=0;i<n;i++){
    if(d[i][k]<d[j][k])j=i;
  }//printf("%d %d\n",j,fr[j][k]);
  r[n-1]=j;
  for(i=1;i<n;i++){//printf("%d:",j);
    r[n-i-1]=fr[r[n-i]][k];
    k-=(1<<r[n-i]);
    //j=fr[r[n-i-1]][k];
  }//printf("d\n");
  //for(i=0;i<n;i++)printf("%d ",r[i]);printf("\n");
  for(i=0;i<n-1;i++)printf("%d ",a[r[i]]);
  printf("%d\n",a[r[i]]);
  return 0;
}