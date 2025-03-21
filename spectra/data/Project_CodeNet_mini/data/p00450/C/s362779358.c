#include <stdio.h>

int go[100000];

int main(void)
{
	int n;
	
	while (scanf("%d", &n), n != 0){
		int i, j;
		int cnt;
		
		for (i = 0; i < n; i++) scanf("%d", go + i);
		for (i = 1; i < n; i += 2){
			if (go[i - 1] != go[i]){
				for (j = i - 1; j >= 0 && go[j] != go[i]; j--){
					go[j] = go[i];
				}
			}
		}
		for (i = cnt = 0; i < n; i++) cnt += !go[i];
		printf("%d\n", cnt);
	}
	
	return 0;
}