#include <stdio.h>
#include <string.h>

typedef struct {
	char name[30];
	int score;
} TEAM;
	
	
int main(void)
{
	int n, i, j, f = 0;
	int win, lose, draw;
	TEAM team[10], temp;
	

	while (1){
		scanf("%d", &n);
		
		if (n == 0){
			break;
		}
		
		for (i = 0; i < n; i++){
			scanf("%s %d %d %d", team[i].name, &win, &lose, &draw);
			team[i].score = win * 3 + draw;
		}
		
		for (i = 0; i < n; i++){
			for (j = n - 1; j > i; j--){
				if (team[j].score > team[j-1].score){
					strcpy(temp.name, team[j-1].name);
					temp.score = team[j-1].score;
					
					strcpy(team[j-1].name, team[j].name);
					team[j-1].score = team[j].score;
					
					strcpy(team[j].name, temp.name);
					team[j].score = temp.score;
				}
			}
		}
		if (f == 1){
			puts("");
		}
		for (i = 0; i < n; i++){
			printf("%s,%d\n", team[i].name, team[i].score);	
			f = 1;
		}
	}
	
	return (0);
}