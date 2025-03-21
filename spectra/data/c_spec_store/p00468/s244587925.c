#include <stdio.h>

int main(void)
{
	int student[501][501];
	int list[501];
	int n, m;
	int i, j;
	int p1, p2;
	int loop;
	int count;
	
    
    while (1){
    	scanf("%d", &n);
    	scanf("%d", &m);
    	
        if ((n | m) == 0){
            break;
        }
        
        
    	for (i = 0; i <= 500; i++){
    		list[i] = 0;
    		for (j = 0; j <= 500; j++){
    			student[i][j] = 0;
    		}
    	}
    	
    	for (i = 0; i < m; i++){
    		scanf("%d%d", &p1, &p2);
    		student[p1][p2] = 1;
    		student[p2][p1] = 1;
    	}
    	

    	for (i = 2; i <= n; i++){
    		if (student[1][i] == 1){
    			list[i] = 1;
    		}
    	}
    	
    	for (i = 2; i <= n; i++){
    		if (student[1][i] == 1){
    			for (j = 2; j <= n; j++){
    				if (student[i][j] == 1){
  						list[j] = 1;
    				}
    			}
    		}
    	}
    	
    	count = 0;
    	for (i = 2; i <= n; i++){
    		count += list[i];
    	}
    	printf("%d\n", count);
    }
    
	return (0);
}