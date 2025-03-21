#include <stdio.h>
#include <stdlib.h>

#define HASH 100003

typedef struct List {
	struct List *next;
	long long v, l, r;
} list;

long long gcd(long long a, long long b)
{
	if (a > b) {
		a ^= b;
		b ^= a;
		a ^= b;
	}
	if (a == 0) return b;
	else return gcd(b % a, a);
}

int main()
{
	long long N, X, D;
	scanf("%lld %lld %lld", &N, &X, &D);
	if (X == 0 || D == 0) {
		if (X == 0 && D == 0) printf("1\n");
		else if (D == 0) printf("%lld\n", N + 1);
		else printf("%lld\n", N * (N - 1) / 2 + 1);
		fflush(stdout);
		return 0;
	}
	
	long long G = gcd(llabs(X), llabs(D)), Y;
	X /= G;
	D /= G;
	if (D < 0) {
		Y = X;
		X = X + D * (N - 1);
		D *= -1;
	} else Y = X + D * (N - 1);
	
	int h, i;
	long long V, L, R;
	list *hash[HASH] = {}, d[200001], *p;
	d[0].v = 0;
	d[0].l = 0;
	d[0].r = D;
	d[0].next = NULL;
	hash[0] = &(d[0]);
	for (i = 1; i <= N; i++) {
		L = (X * 2 + D * (i - 1)) * i / 2;
		R = (Y * 2 - D * (i - 1)) * i / 2 + D;
		V = (L % D + D) % D;
		h = V % HASH;
		for (p = hash[h]; p != NULL; p = p->next) if (p->v == V && p->l <= R && p->r >= L) break;
		if (p == NULL) {
			d[i].v = V;
			d[i].l = L;
			d[i].r = R;
			d[i].next = hash[h];
			hash[h] = &(d[i]);
		} else {
			p->l = (p->l < L)? p->l: L;
			p->r = (p->r > R)? p->r: R;
		}
	}
	
	long long ans = 0;
	for (h = 0; h < HASH; h++) {
		for (p = hash[h]; p != NULL; p = p->next) ans += (p->r - p->l) / D;
	}
	printf("%lld\n", ans);
	fflush(stdout);
	return 0;
}