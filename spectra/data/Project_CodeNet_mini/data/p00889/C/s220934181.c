// AOJ 1310: Find the Multiples
// 2017.10.3 bal4u@uu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZ 300017
typedef struct { int b; int v; } HASH;
HASH hash[HASHSIZ+2], *hashend = hash + HASHSIZ;

int lookup(int b)
{
	HASH *p = hash + b % HASHSIZ;
	while (p->b) {
		if (p->b == b) return p->v;
		if (++p == hashend) p = hash;
	}
	return 0;
}

void insert(int b)
{
	HASH *p = hash + b % HASHSIZ;
	while (p->b) {
		if (p->b == b) { p->v++; return; }
		if (++p == hashend) p = hash;
	}
	p->b = b, p->v = 1;
}

int a[100002];
int b[100002];
int tr[10][6];

int main()
{
	int n, s, w, q, g, i, k, ans;

	tr[0][2] = tr[2][2] = tr[4][2] = tr[6][2] = tr[8][2] = tr[0][5] = tr[5][5] = 1;

    while (scanf("%d%d%d%d", &n, &s, &w, &q) && n > 0) {
		g = s;
		for (i = 0; i < n; i++) {
			a[i] = (g/7) % 10;
			if (g & 1) g = (g >> 1) ^ w;
			else g >>= 1;
		}

		ans = 0;
		if (q == 2 || q == 5) {
			for (k = 0, i = 0; i < n; i++) {
				if (a[i]) k++;
				if (tr[a[i]][q]) ans += k;
			}
		} else {
			memset(hash, 0, sizeof(hash));
			for (k = 1, b[n] = 0, i = n-1; i >= 0; i--){
				b[i] = (k*a[i] + b[i+1]) % q;
				k = ((k<<3)+(k<<1)) % q;
			}
			for (i = 0; i < n; i++) {
				if (a[i]) insert(b[i]+1);
				ans += lookup(b[i+1]+1);
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}