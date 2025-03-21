#include <stdio.h>

int main(){
	int i,j,k;
	int a,b,c;
	int n[200]={0};
	while(1){
		scanf("%d",&a);
		if(a==0){
			break;
		}
		b=0;
		while(a){
			n[b]=a%8;
			a/=8;
			b++;
		}
		
		
		n[b]=0;
		c=0;
		i=0;
		while(i<=b){
			
			if(n[i]>3){
				n[i]++;
			}
			if(n[i]>5){
				n[i]++;
			}
			i++;
		}
		for(i=b-1;i>=0;i--){
			printf("%d",n[i]);
		}
		printf("\n");
	}
}