#include <stdio.h>

char str[128][128];
int area_id[128][128];

void DFS(int i, int j, int H, int W){
	if (i + 1 < H){
		if (str[i][j] == str[i+1][j] && area_id[i+1][j] == (i + 1) * W + j){
			area_id[i+1][j] = area_id[i][j];
			DFS(i + 1, j, H, W);
		}
	}
	
	if (i - 1 >= 0){
		if (str[i][j] == str[i-1][j] && area_id[i-1][j] == (i - 1) * W + j){
			area_id[i-1][j] = area_id[i][j];
			DFS(i - 1, j, H, W);
		}
	}
	
	if (j + 1 < W){
		if (str[i][j] == str[i][j+1] && area_id[i][j+1] == i * W + (j + 1)){
			area_id[i][j+1] = area_id[i][j];
			DFS(i, j + 1, H, W);
		}
	}
	
	if (j - 1 >= 0){
		if (str[i][j] == str[i][j-1] && area_id[i][j-1] == i * W + (j - 1)){
			area_id[i][j-1] = area_id[i][j];
			DFS(i, j - 1, H, W);
		}
	}
}
	

int main(void)
{
	int H, W, i, j, cnt;
	char area_num[128 * 128];
	
	while (1){
		scanf("%d %d", &H, &W);
		
		if (H == 0 && W == 0){
			break;
		}
		
		//
		
		for (i = 0; i < H; i++){
			for (j = 0; j < W; j++){
				area_id[i][j] = i * W + j;
			}
		}
				
		for (i = 0; i < 128 * 128; i++){
			area_num[i] = 0;
		}
		
		cnt = 0;
		
		//
		
		for (i = 0; i < H; i++){
			scanf("%s", str[i]);
		}
		
		for (i = 0; i < H; i++){
			for (j = 0; j < W; j++){
				DFS(i, j, H, W);
			}
		}
		
		for (i = 0; i < H; i++){
			for (j = 0; j < W; j++){
				area_num[area_id[i][j]] = 1;
			}
		}
		
		for (i = 0; i < H; i++){
			for (j = 0; j < W; j++){
				if (area_num[i * W + j] == 1){
					cnt++;
				}
			}
		}
		
		printf("%d\n", cnt);
	}
	
	return (0);
}