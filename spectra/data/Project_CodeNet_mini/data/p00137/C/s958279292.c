#include <stdio.h>

int main(){
	int count=0,counter;
	int a,b,c;
	int i,j,k;
	int x,y[8];
	int cter;
	
	scanf("%d",&counter);
	while(counter>count){
		scanf("%d",&x);
		cter=10;
		c=0;
		printf("Case %d:\n",count+1);
		while(c<cter){
			
			x*=x;
			x/=100;
			x%=10000;
			c++;
			printf("%d\n",x);
		}
		count++;
	}
	return 0;
}