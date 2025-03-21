#include <stdio.h>

int main()
{
	int i, H, W, K;
	char S[12][1002];
	scanf("%d %d %d", &H, &W, &K);
	for (i = 1; i <= H; i++) scanf("%s", &(S[i][1]));
	
	int j, k, t[12], b[12], flag[12] = {}, count[12], ans = 1 << 30, tmp;
	flag[H] = 1;
	while (flag[H+1] == 0) {
		t[0] = 1;
		for (i = 0; t[i] <= H; i++) {
			count[i] = 0;
			for (b[i] = t[i]; flag[b[i]] == 0; b[i]++);
			t[i+1] = b[i] + 1;
		}
		for (j = 1, tmp = i - 1; j <= W; j++) {
			for (i = 0; t[i] <= H; i++) {
				for (k = t[i]; k <= b[i]; k++) if (S[k][j] == '1') count[i]++;
				if (count[i] > K) break;
			}
			if (t[i] <= H) {
				for (i = 0; t[i] <= H; i++) {
					count[i] = 0;
					for (k = t[i]; k <= b[i]; k++) if (S[k][j] == '1') count[i]++;
					if (count[i] > K) break;
				}
				if (t[i] <= H) break;
				else tmp++;
			}
		}
		if (j > W && tmp < ans) ans = tmp; 
		
		for (i = 1; i <= H && flag[i] == 1; i++);
		for (flag[i--] = 1; i >= 1; flag[i--] = 0);
	}
	
	printf("%d\n", ans);
	fflush(stdout);
	return 0;
}