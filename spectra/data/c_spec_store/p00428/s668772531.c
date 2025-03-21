#include<stdio.h>

int main(void){
	int n,m;
	while(1){
		scanf("%d %d",&n,&m);
		if(n==0 && m==0)break;
		int q[n][m],i,j=0;
		while(j<n){
			i=0;
			while(i<m){
				scanf("%d",&q[j][i]);
				i++;
			}
			j++;
		}
		int cnt[m];
		for(i=0;i<n;i++)for(j=0;j<m;j++){
			if(!i)cnt[j] = 0;
			cnt[j] += q[i][j];
		}
		int max,maxed[m];
		for(i=0;i<m;i++)maxed[i] = 0;
		for(i=0;i<m;i++){
			if(i)printf(" ");
			max = -1;
			for(j=0;j<m;j++){
				if(!maxed[j]){
					if(max == -1)max = j;
					else if(cnt[max] < cnt[j])max = j;
				}
			}
			printf("%d",max+1);
			maxed[max] = 1;
		}
		printf("\n");
	}
}
