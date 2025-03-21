#include <stdio.h>
#include <stdlib.h>
#define int long long
#define p 998244353

int gcd(int a, int b){
	if(b == 0){
		return a;
	}
	else{
		return gcd(b, a % b);
	}
}

signed compare(const void *a, const void *b){
	int sub = *(int *)a - *(int *)b;
	if(sub < 0){
		return -1;
	}
	else if(sub == 0){
		return 0;
	}
	else{
		return 1;
	}
}

signed main(){
	int N, i, ans = 1;
	scanf("%lld", &N);
	int *A = (int *)malloc(sizeof(int) * N);
	for(i = 0; i < N; i++){
		scanf("%lld", &A[i]);
	}
	qsort(A, N, sizeof(int), compare);
	for(i = 0; i < N; i++){
		ans = (ans * gcd(A[i], i)) % p;
	}
	printf("%lld\n", ans);
	return 0;
}