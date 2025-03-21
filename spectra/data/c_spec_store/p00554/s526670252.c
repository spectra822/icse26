#include <stdio.h>
int main(void){
	int n,m;
	int a[1000],b[1000];
	int i,j,k;
	int count1=0,count2=0;
	int temp;
	scanf("%d %d",&n,&m);
	for(i=1;i<=m;i++){
		scanf("%d %d",&a[i],&b[i]);
		if(a[i]>=n){
			a[i]=b[i]=0;
			count1++;
		}
	}
	if(m-1>count1){
		for(i=1;i<=m;i++)b[i]=n-a[i];
		for(i=1;i<m;i++){
			for(j=i+1;j<=m;j++){
				if(b[i]>b[j]){
					temp=b[i];
					b[i]=b[j];
					b[j]=temp;
				}
			}
		}
		for(i=1;i<=m-count1-1;i++)count2+=b[i];
	}
	printf("%d\n",count2);
	return 0;
}
