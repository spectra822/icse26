// AOJ 341 Repeated Spell
// 2017.10.26

#include <stdio.h>
#include <string.h>

#define M 1000000007
long long a[1001][1001];
char t[1001], b[1001];

int main()
{
	int i, j, st, sb;

	scanf("%s%s", t, b);
	st = strlen(t);
	sb = strlen(b);
	for (i = 0; i <= st; i++) a[i][0] = 1;
	for (i = 1; i <= st; i++) {
		for (j = 0; j < sb; j++) {
			a[i][j+1] = a[i-1][j+1] % M;
			if (t[i-1] == b[j]) {
				a[i][j+1] = (a[i-1][j+1] + a[i-1][j]) % M;
			}
		}
	}
	printf("%lld\n", a[st][sb]);
	return 0;
}