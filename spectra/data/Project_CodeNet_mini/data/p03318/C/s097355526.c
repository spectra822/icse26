#include<stdio.h>
int S(long int x){
	int r=0;
	while(x>0){r+=x%10;x/=10;}
	return r;
}

int main(){
  long int n,i,j,x=1,y,r,s;
  double m,o;
  scanf("%ld",&n);
  for(i=0;i<n;i++){
    printf("%ld\n",x);
    r=++x;
  	m=(double)x/S(x);
  	for(j=0,s=10;j<15;j++,s*=10L){
  		y=s*(x/s+1)-1;o=(double)y/S(y);
  		if(o<m){m=o;r=y;}
  	}
    x=r;
  }
}
