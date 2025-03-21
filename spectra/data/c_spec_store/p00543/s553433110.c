#include <stdio.h>
int main(void)
{
	int a[1000],k,n,m;
	int i,j;
	int temp;
	scanf("%d %d",&n,&m);
	for(i=1;i<=n;i++)scanf("%d",&a[i]);
	k=1;
	do{
		for(i=1,j=2;i<n,j<=n;i++,j++){
			if(a[i]%k>a[j]%k){
				temp=a[i];
				a[i]=a[j];
				a[j]=temp;
			}
		}
		k++;
	}while(k<=m);
	for(i=1;i<=n;i++)printf("%d\n",a[i]);
	return 0;
}
