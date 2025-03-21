#include<stdio.h>
int x[200000],y[200000];
int main(){
  int min,i,j,nx,ny,t,r,w,h;
  char m[101][101];
  int X[]={0,1, 0,-1};
  int Y[]={1,0,-1, 0};
  while(scanf("%d %d",&w,&h),w||h){
    int c[101][101]={0};
    for(i=0;i<h;i++){
      for(j=0;j<w;j++){
	scanf(" %c",&m[i][j]);
	if(m[i][j]=='&'){
	  m[i][j]='.';
	  y[0]=i;
	  x[t=0]=j;
	  c[i][j]=1;
	}
      }
    }
    for(r=1;r-t;t++){
      for(i=0;i<4;i++){
	nx=x[t]+X[i];
	ny=y[t]+Y[i];
	if(nx<0||w<=nx||ny<0||h<=ny)continue;
	if(m[y[t]][x[t]]==m[ny][nx]){
	  if(c[y[t]][x[t]]<c[ny][nx]||0==c[ny][nx]){
	    c[ny][nx]=c[y[t]][x[t]];
	    x[r  ]=nx;
	    y[r++]=ny;
	  }
	}
	else{
	  if(c[y[t]][x[t]]+1<c[ny][nx]||0==c[ny][nx]){
	    c[ny][nx]=c[y[t]][x[t]]+1;
	    x[r  ]=nx;
	    y[r++]=ny;
	  }
	}
      }
    }
    /*for(i=0;i<h;i++){
      for(j=0;j<w;j++)printf("%d",c[i][j]);
      printf("\n");
      }*/
    min=w;
    for(i=0;i<w;i++){
      if(c[0  ][i]/2<min)min=c[0  ][i]/2;
      if(c[h-1][i]/2<min)min=c[h-1][i]/2;
    }
    for(i=0;i<h;i++){
      if(c[i][0  ]/2<min)min=c[i][0  ]/2;
      if(c[i][w-1]/2<min)min=c[i][w-1]/2;
    }
    printf("%d\n",min);
  }
  return 0;
}