#include<stdio.h>
int main(){
  int X[]={1,2,1,-1,-2,-1};
  int Y[]={1,0,-1,-1,0,1};
  int w,h,i,j,k,nx,ny,s,t,r,x[10000],y[10000],d[110][210]={2};
  scanf("%d %d",&w,&h);
  for(i=1;i<=h;i++){
    for(j=1;j<=w;j++)scanf("%d",&d[i][j*2+i%2]);
  }
  x[0]=y[0]=t=s=0;
  for(r=1;r-t;t++){
    for(i=0;i<6;i++){
      nx=x[t]+X[i];
      ny=y[t]+Y[i];
      if(nx<0||ny<0||h+1<ny||w*2+4<nx)continue;
      if(d[ny][nx])continue;
      d[ny][nx]=2;
      x[r  ]=nx;
      y[r++]=ny;
    }
  }
  /*for(i=0;i<h+2;i++){
    for(j=0;j<w*2+4;j++)printf("%d",d[i][j]);printf("\n");
    }//*/
  for(i=1;i<=h;i++){
    for(j=1;j<=w;j++){
      if(d[i][j*2+i%2]-1)continue;
      for(k=0;k<6;k++){
	if(d[i+Y[k]][j*2+i%2+X[k]]==2)s++;
      }
    }
  }
  printf("%d\n",s);
  return 0;
}
  