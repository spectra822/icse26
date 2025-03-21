#include <stdio.h>
#include <string.h>

char str[10001];

int main(void)
{
	while (scanf("%s", str) != EOF){
		int joi = 0;
		int ioi = 0;
		int i;
		
		for (i = 0; i < strlen(str) - 2; i++){
			if (strncmp(str + i, "JOI", 3) == 0){
				joi++;
			}
			if (strncmp(str + i, "IOI", 3) == 0){
				ioi++;
			}
		}
		printf("%d\n", joi);
		printf("%d\n", ioi);
	}
	
	return 0;
}