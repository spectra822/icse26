#include<stdio.h>
int main(){
  int n,m,i,j,k,l,min,d;
  int ic[150],is[2][150][10];
  int c[80][150][11];
  while(scanf("%d %d",&n,&m),n||m){
    int c[80][150][11]={0};
    for(i=0;i<80;i++){
      for(j=1;j<150;j++){
	for(k=0;k<11;k++)c[i][j][k]=2100000000;
      }
    }
    for(i=0;i<11;i++)c[1][1][i]=0;
    for(i=0;i<n;i++){
      scanf("%d",&ic[i]);
      for(j=0;j<ic[i];j++){
	scanf("%d %d",&is[0][i][j],&is[1][i][j]);
      }
    }
    for(i=0;i<=m;i++){
      for(j=0;j+1<n;j++){
	for(k=0;k<ic[j];k++){
	  for(l=0;l<ic[j+1];l++){
	    d=(is[1][j][k]+is[1][j+1][l])*abs(is[0][j][k]-is[0][j+1][l]);
	    //printf("d%d from %d %d to %d %d\n",
	    //	   d,is[0][j][k],is[1][j][k],is[0][j+1][l],is[1][j+1][l]);
	    if(c[i][j+1][l]>c[i][j][k]+d)c[i][j+1][l]=c[i][j][k]+d;
	  }
	  if(j+2==n)continue;
	  for(l=0;l<ic[j+2];l++){
	    d=(is[1][j][k]+is[1][j+2][l])*abs(is[0][j][k]-is[0][j+2][l]);
	    //printf("d%d from %d %d to %d %d\n",
	    //	   d,is[0][j][k],is[1][j][k],is[0][j+2][l],is[1][j+2][l]);
	    if(c[i+1][j+2][l]>c[i][j][k]+d)c[i+1][j+2][l]=c[i][j][k]+d;
	  }
	}
      }
    }
    /*for(i=0;i<=m;i++){
      for(j=0;j<n;j++){
	for(k=0;k<ic[j];k++)printf("%d ",c[i][j][k]);printf("\n");
      }printf("\n");
      }//*/
    min=2100000210;
    for(i=0;i<=m;i++){
      for(j=0;j<ic[n-1];j++){
	if(min>c[i][n-1][j])min=c[i][n-1][j];
      }
      if(m==i)continue;
      for(j=0;j<ic[n-2];j++){
	if(min>c[i][n-2][j])min=c[i][n-2][j];
      }
    }
    printf("%d\n",min);
  }
  return 0;
}


	    
	      