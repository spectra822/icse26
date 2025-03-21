#include<stdio.h>

int a[100010];
void dfs(int n){
	int t=a[n];
	while(a[t]!=-1){
		int temp=a[t];
		a[t]=-1;
		t=temp;
	}
	return;
}
int main(){
	int n,k;
	scanf("%d%d",&n,&k);
	for(int i=1;i<=n;i++)scanf("%d",a+i);
	if(n==k){
		int x=a[1]-1;
		int flag=1;
		for(int i=1;i<=n;i++)flag&=(a[i]-i+n)%n==x;
		puts(flag?"Yes":"No");
	}else{
		int cnt=0;
		for(int i=1;i<=n;i++)if(a[i]!=-1)dfs(i),cnt++;
		puts((n-cnt)%2&&k%2?"No":"Yes");
	}
}

