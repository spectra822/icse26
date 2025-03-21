// AOJ 2236 Rabbit Plays Games!
// 2018.2.10 bal4u

#include <stdio.h>
#include <stdlib.h>

typedef struct { long long a; int d; } T;
T tbl[40002];
int h[40002], a[40002], d[40002], s[40002];

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

int cmp(T *a, T *b) { return a->a * b->d > b->a * a->d; }

int main()
{
	int n, i, k, sz;
	long long turn, ans;

	n = in();
	for (i = 0; i <= n; i++) h[i] = in(), a[i] = in(), d[i] = in(), s[i] = in();
	
	sz = 0, ans = turn = 0;
	for (i = 1; i <= n; i++) {
		k = a[i] - d[0];
		if (k <= 0) continue;
		if (a[0] <= d[i]) { puts("-1"); return 0; }

		turn += k; if (s[i] > s[0]) ans += k;
		tbl[sz].d = k;
		tbl[sz++].a = ((long long)h[i]-d[i]+a[0]-1)/(a[0]-d[i]);
	}
	qsort(tbl, sz, sizeof(T), cmp);

	for (i = 0; i < sz; i++) {
		ans += turn*tbl[i].a - tbl[i].d;
		if (h[0] <= ans) { puts("-1"); return 0; }
		turn -= tbl[i].d;
	}
	printf("%lld\n", ans);
	return 0;
}
