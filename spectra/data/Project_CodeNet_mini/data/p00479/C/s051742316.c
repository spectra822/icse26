#include<stdio.h>
int main(){
	int n,ai,bi,i,k,c;
	scanf("%d",&n);
	scanf("%d",&k);
	for(i=0;i<k;i++){
		scanf("%d%d",&ai,&bi);
		if(n+1-ai<ai)ai=n+1-ai;
		if(n+1-bi<bi)bi=n+1-bi;
		if(ai>bi)c=(bi-1)%3+1;
		else c=(ai-1)%3+1;
		printf("%d\n",c);
	}
	return 0;
}
