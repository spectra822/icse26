#include <stdio.h>
#include <stdlib.h>
#define int long long
#define p (int)(1e9 + 7)

int MOD(int a){
	a %= p;
	return a >= 0 ? a : a + p;
}

int power(int a, int N){
	if(N == 0){
		return 1;
	}
	else if(N % 2 == 0){
		return power(MOD(a * a), N / 2);
	}
	else{
		return MOD(a * power(a, N - 1));
	}
}

signed main(){
	int M = ((int)1 << 20);
	int N, i, x;
	scanf("%lld", &N);
	int *a = (int *)malloc(sizeof(int) * (N + 1));
	int *s = (int *)malloc(sizeof(int) * (N + 1));
	s[0] = 0;
	int *Onum = (int *)malloc(sizeof(int) * (N + 1));
	Onum[0] = 0;
	for(i = 1; i <= N; i++){
		scanf("%lld", &a[i]);
		s[i] = (s[i - 1] ^ a[i]);
		Onum[i] = Onum[i - 1] + (s[i] == 0 ? 1 : 0);
	}
/*	printf("s:\n");
	for(i = 0; i <= N; i++){
		printf("%lld ", s[i]);
	}
	printf("\n");
	printf("Onum:\n");
	for(i = 0; i <= N; i++){
		printf("%lld ", Onum[i]);
	}
	printf("\n");
*/	int *prev = (int *)malloc(sizeof(int) * M);
	for(i = 0; i < M; i++){
		prev[i] = 0;
	}
	int *dp = (int *)malloc(sizeof(int) * M);
	for(i = 0; i < M; i++){
		dp[i] = 0;
	}
	int *sum = (int *)malloc(sizeof(int) * M);
	for(i = 0; i < M; i++){
		sum[i] = 0;
	}
	int *Osum = (int *)malloc(sizeof(int) * M);
	for(i = 0; i < M; i++){
		Osum[i] = 1;
	}
	for(i = 1; i <= N; i++){
		x = s[i];
		dp[x] = MOD(sum[x] * (Onum[i] - Onum[prev[x]]) + Osum[x]);
		Osum[x] = MOD(Osum[x] + sum[x] * (Onum[i] - Onum[prev[x]]));
		sum[x] = MOD(sum[x] + dp[x]);
/*		if(prev[x] == -1){
			dp[x] = 1;
			sum[x] = 1;
		}
		else{
			dp[x] = MOD(sum[x] * (Onum[i] - Onum[prev[x]]) + 1);
			sum[x] = MOD(sum[x] + dp[x]);
		}
*/		prev[x] = i;
//		printf("i = %lld\n", i);
//		printf("dp[%lld] = %lld\n", x, dp[x]);
//		printf("sum[%lld] = %lld\n", x, sum[x]);
	}
	int ans = 0;
	if(s[N] == 0){
		ans = power(2, Onum[N] - 1);
		for(i = 1; i < M; i++){
			ans = MOD(ans + sum[i]);
		}
	}
	else{
		ans = dp[s[N]];
	}
/*	for(i = 1; i < M; i++){
		if(s[N] == 0){
			ans = MOD(ans + sum[i]);
		}
		else if(s[N] == i){
			ans = MOD(ans + dp[i]);
		}
	}
	if(s[N] == 0){
		ans = MOD(ans + power(2, Onum[N] - 1));
	}
*/	printf("%lld\n", ans);
	return 0;
}