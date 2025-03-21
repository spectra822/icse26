#include <stdio.h>

int main(void){
	int n,k,i;
	int p[100][2];
	double menseki=0.0;
	scanf("%d",&n);
	
	for(i=0;i<n;i++){
		scanf("%d %d",&p[i][0],&p[i][1]);
	}
	
	for(i=0;i<n;i++){
		menseki+=(double)((p[i][0]-p[(i+1)%n][0])*(p[i][1]+p[(i+1)%n][1]));
	}
	printf("%.1lf\n",menseki/2.0);
	return 0;
}