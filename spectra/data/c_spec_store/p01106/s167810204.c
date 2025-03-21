// AOJ 1621: Folding a Ribbon
// 2017.12.30 bal4u@uu

#include <stdio.h>
#include <string.h>

char ans[62];
char low[62];

int main()
{
	int n, k;
	long long i, j;

	while (scanf("%d%lld%lld", &n, &i, &j) && n > 0) {
		i--, j--;
		for (k = 1; k <= n; k++) {
			low[n-k] = (i >> (n-k)) & 1;
			if (!low[n-k]) i = ~i;
		}
		for (k = 1; k <= n; k++) {
			ans[k] = (((j >> (n-k)) & 1) == low[k-1])? 'L': 'R';
			if (!low[k-1]) j = ~j;
		}
		ans[n+1] = 0;
		puts(ans+1);
	}
	return 0;
}