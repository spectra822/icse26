#include <stdio.h>

int main(void) {
	int N,Q;
	int i;
	char names[50][32]={"kogakubu10gokan"};
	char* answer=names[0];
	scanf("%d%d",&N,&Q);
	for(i=1;i<=N;i++) {
		int year;
		scanf("%d%s",&year,names[i]);
		if(year<=Q)answer=names[i];
	}
	puts(answer);
	return 0;
}