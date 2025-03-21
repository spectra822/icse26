// AOJ 2431: House Moving
// 2017.12.30 bal4u@uu

#include <stdio.h>

long long seg[262145]; int sz;		// 2^18 = 262144
char buf[600000], *p;

int in()
{
	int n = 0;
	while (*p >= '0') n = 10*n + (*p++ & 0xf);
	p++;
	return n;
}

// update kth value to v
void update(int k, long long v)
{
	int t;
	k += sz-1;
	seg[k] = v;
	while (k > 0) {
		if (!(k & 1)) k--;
		t = k, k >>= 1;
		v = seg[t++]; if (v < seg[t]) v = seg[t];
		seg[k] = v;
	}
}

// get max value in [a, b)
long long query(int a, int b, long long k, int l, int r) 
{
	int m;
	long long lmax, rmax;

	if (r <= a || b <= l) return 0;
    if (a <= l && r <= b) return seg[k];
	k <<= 1, m = (l + r) >> 1;
    lmax = query(a, b, ++k, l, m);
    rmax = query(a, b, ++k, m, r);
    if (lmax < rmax) lmax = rmax; 
    return lmax;
}

int main()
{
	int n, x, i;
	long long ans;

	fgets(p=buf, 10, stdin), n = in();

	sz = 1; while (sz < n) sz <<= 1;

	fgets(p=buf, sizeof(buf), stdin);
	for (i = 0; i < n; i++) {
		x = in();
		update(x, (long long)x + query(1, x, 0, 0, sz));
	}

	ans = (((long long)n*(n+1)) >> 1) - query(1, n+1, 0, 0, sz);
	printf("%lld\n", ans);
	return 0;
}