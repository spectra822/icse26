#include <stdio.h>
int main(void){
	char a[1000];
	int i;
	scanf("%s",a);
	for(i=0;a[i]!='\0';i++){
		if('D'<=a[i]&&a[i]<='Z')a[i]-=3;
		else a[i]+=23;
	}
	printf("%s\n",a);
	return 0;
}

