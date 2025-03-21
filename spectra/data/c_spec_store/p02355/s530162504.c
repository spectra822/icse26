// AOJ DSL_3_B The Smallest Window II
// 2018.5.6 bal4u@uu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif
int in()
{
	int n = 0, c = gc();
	do n = 10*n + (c & 0xf), c = gc(); while (c >= '0');
	return n;
}

#define MAX_N 100003
int a[MAX_N], f[MAX_N];

int main()
{
	int N, K, i, j, s, t, ans;

	N = in(), K = in();
	if (N < K) { puts("0"); return 0; }
	for (i = 0; i < N; i++) a[i] = in();

	s = 0, i = j = 0;
	while (s < K && j < N) {
		t = a[j++];
		if (t <= K) {
			if (f[t] == 0) s++;
			f[t]++;
		}
	}
	if (s < K) goto ng;
	while ((t = a[i]) > K || f[t] > 1) {
		if (t <= K) f[t]--;
		i++;
	}
	ans = j-i;

	while (j < N) {
		t = a[j++];
		if (t <= K) f[t]++;
		while ((t = a[i]) > K || f[t] > 1) {
			if (t <= K) f[t]--;
			i++;
		}
		if (j-i < ans) ans = j-i;
	}
	printf("%d\n", ans);
	return 0;
ng: puts("0");
	return 0;
}

