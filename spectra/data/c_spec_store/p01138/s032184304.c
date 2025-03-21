#include <stdio.h>
#include <string.h>


int main(void)
{
	int n;
	int i, j;
	int depature;
	int arrival;
	int time[24 * 3600];
	int hour, min, sec;
	int max;
	
	while (1){
		scanf("%d", &n);
		if (n == 0){
			break;
		}

		memset(time, 0, sizeof(time));
		
		for (i = 0; i < n; i++){
			scanf("%d:%d:%d", &hour, &min, &sec);
			depature = hour * 3600 + min * 60 + sec;
			
			scanf("%d:%d:%d", &hour, &min, &sec);
			arrival = hour * 3600 + min * 60 + sec;

			for (j = depature; j < arrival; j++){
				time[j]++;
			}

		}
		
		max = 0;
		for (i = 0; i < 24 * 3600; i++){
			if (max < time[i]){
				max = time[i];
			}
		}
		
		printf("%d\n", max);
	}
	
	return (0);
}
	