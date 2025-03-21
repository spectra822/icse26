#if 0
cat <<EOF >mistaken-paste
#endif
// thx Ebi-chan!

#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define BIG 2000000007
#define VERYBIG 20000000000000007LL

#define MOD 1000000007
#define FOD  998244353
typedef uint64_t ull;
typedef  int64_t sll;

#define N_MAX 1048576

#ifdef __cplusplus
#include <queue>
#include <stack>
#include <tuple>
#include <set>
#include <map>
#include <string>
#include <algorithm>
#include <functional>
#include <array>

using std::queue;
using std::priority_queue;
using std::stack;
using std::tuple;
using std::set;
using std::map;
using std::vector;
using std::greater;
using std::pair;
using std::string;
using std::get;

template <typename T, typename U>
pair<T, U> operator+(pair<T, U> l, pair<T, U> r) {
	return pair<T, U>(l.first + r.first, l.second + r.second);
}

#endif

#ifndef M_PI
#define M_PI 3.14159265358979323846264338327950
#endif

typedef struct {
	sll a;
	sll b;
} hwll;

typedef struct {
	sll a;
	sll b;
	sll c;
} hwllc;

typedef struct {
	hwll a;
	hwll b;
} linell;

typedef struct {
	double a;
	double b;
} hwreal;

sll n, m;
sll h, w;
sll k;
sll q;
sll va, vb, vc, vd, ve, vf;
ull ua, ub, uc, ud, ue, uf;
long double vra, vrb, vrc;
double vda, vdb, vdc;
char ch, dh;

ull umin (ull x, ull y) {
	return (x < y) ? x : y;
}

ull umax (ull x, ull y) {
	return (x > y) ? x : y;
}

sll smin (sll x, sll y) {
	return (x < y) ? x : y;
}

sll smax (sll x, sll y) {
	return (x > y) ? x : y;
}

ull gcd (ull x, ull y) {
	if (y == 0) {
		return x;
	} else {
		return gcd(y, x % y);
	}
}

ull bitpow (ull a, ull x, ull modulo) {
	ull result = 1;
	while (x) {
		if (x & 1) {
			result *= a;
			result %= modulo;
		}
		x /= 2;
		a = (a * a) % modulo;
	}
	return result;
}

ull divide (ull a, ull b, ull modulo) {
	return (a * bitpow(b, modulo - 2, modulo)) % modulo;
}

ull udiff (ull a, ull b) {
	if (a >= b) {
		return a - b;
	} else {
		return b - a;
	}
}

sll sdiff (sll a, sll b) {
	if (a >= b) {
		return a - b;
	} else {
		return b - a;
	}
}

int bitcount (ull n) {
	int result = 0;
	while (n) {
		if (n & 1) result++;
		n /= 2;
	}
	return result;
}

#define BEGCMP(NAME) int32_t NAME (const void *left, const void *right)
#define DEFLR(TYPE) TYPE l=*(TYPE*)left,r=*(TYPE*)right
#define CMPRET(L, R) if((L)<(R))return-1;if((L)>(R))return+1

// int32_t pullcomp (const void *left, const void *right) {
// 	ull l = *(ull*)left;
// 	ull r = *(ull*)right;
// 	if (l < r) {
// 		return -1;
// 	}
// 	if (l > r) {
// 		return +1;
// 	}
// 	return 0;
// }
BEGCMP(pullcomp){
	DEFLR(ull);
	CMPRET(l, r);
	return 0;
}
BEGCMP(prevcomp){
	DEFLR(sll);
	CMPRET(r, l);
	return 0;
}
BEGCMP(psllcomp){
	DEFLR(sll);
	CMPRET(l, r);
	return 0;
}
BEGCMP(pcharcomp){
	DEFLR(char);
	CMPRET(l, r);
	return 0;
}
BEGCMP(pdoublecomp){
	DEFLR(double);
	CMPRET(l, r);
	return 0;
}

int32_t pstrcomp (const void *left, const void *right) {
	char* l = *(char**)left;
	char* r = *(char**)right;

	return strcmp(l, r);
}

BEGCMP(phwllABcomp){
	DEFLR(hwll);
	CMPRET(l.a, r.a);
	CMPRET(l.b, r.b);
	return 0;
}
BEGCMP(phwllREVcomp){
	DEFLR(hwll);
	CMPRET(l.b, r.b);
	CMPRET(l.a, r.a);
	return 0;
}
BEGCMP(ptriplecomp){
	DEFLR(hwllc);
	CMPRET(l.a, r.a);
	CMPRET(l.b, r.b);
	CMPRET(l.c, r.c);
	return 0;
}
BEGCMP(ptripleREVcomp){
	DEFLR(hwllc);
	CMPRET(l.b, r.b);
	CMPRET(l.a, r.a);
	CMPRET(l.c, r.c);
	return 0;
}
BEGCMP(ptripleCABcomp){
	DEFLR(hwllc);
	CMPRET(l.c, r.c);
	CMPRET(l.a, r.a);
	CMPRET(l.b, r.b);
	return 0;
}
BEGCMP(phwrealcomp){
	DEFLR(hwreal);
	CMPRET(l.a, r.a);
	CMPRET(l.b, r.b);
	return 0;
}

int32_t pquadcomp (const void *left, const void *right) {
	linell l = *(linell*)left;
	linell r = *(linell*)right;

	sll ac = phwllABcomp(&(l.a), &(r.a));
	if (ac) return ac;
	sll bc = phwllABcomp(&(l.b), &(r.b));
	if (bc) return bc;

	return 0;
}
int32_t pfracomp (const void *left, const void *right) {
	hwllc l = *(hwllc*)left;
	hwllc r = *(hwllc*)right;

	CMPRET(l.a * r.b, l.b * r.a);
	return 0;
}
bool isinrange (sll left, sll x, sll right) {
	return (left <= x && x <= right);
}

bool isinrange_soft (sll left, sll x, sll right) {
	return (left <= x && x <= right) || (left >= x && x >= right);
}

void sw (sll *l, sll *r) {
	sll t = *l;
	*l = *r;
	*r = t;
}

ull frac[N_MAX * 3], invf[N_MAX * 3];
ull ncr (sll n, sll r, ull m) {
	if (n < 0 || r < 0 || n < r) return 0;
	return frac[n] * (invf[r] * invf[n - r] % m) % m;
}

sll a[N_MAX + 5];
// ull a[N_MAX + 5];
// sll a[3001][3001];
sll b[N_MAX + 5];
// ull b[N_MAX + 5];
// sll b[3001][3001];
sll c[N_MAX + 5];
sll d[N_MAX + 5];
sll e[N_MAX * 4];
char s[N_MAX + 1];
// char s[3010][3010];
char t[N_MAX + 1];
// char t[3010][3010];
char u[N_MAX + 1];
hwll xy[N_MAX + 5];
hwllc tup[N_MAX + 5];
sll table[3005][3005];
ull gin[N_MAX];
// here we go

hwll ivals[N_MAX];

// ull seg[524288], lazy[524288], base = 262144;
ull seg[524288][4], base = 262144;
ull ssize[524288];
// void eval (ull i) {
// 	seg[i] = (seg[i] + (lazy[i] * ssize[i])) % MOD;
// 	if (i < base) {
// 		lazy[i * 2] = (lazy[i * 2] + lazy[i]) % MOD;
// 		lazy[i * 2 + 1] = (lazy[i * 2 + 1] + lazy[i]) % MOD;
// 	}
// 	lazy[i] = 0;
// }
// ull query_ (ull l, ull r, ull x, ull beg, ull end, ull i) {
// 	bool iscont = (l <= beg && end <= r);
// 	if (iscont) {
// 		lazy[i] = (lazy[i] + x) % MOD;
// 	}
// 	eval(i);
// 	if (r <= beg || end <= l) return 0;
// 	if (l <= beg && end <= r) {
// 		return seg[i];
// 	}
// 	ull med = (beg + end) / 2;
// 	ull vl = query_(l, r, x, beg, med, i);
// 	ull vr = query_(l, r, x, med, end, i);
// 	seg[i] = (seg[i * 2] + seg[i * 2 + 1]) % MOD;
// 	return vl + vr;
// }
// ull query (ull l, ull r, ull x) {
// 	return query_(l, r, x, 0, base, 1);
// }

// void add (ull v, ull x, ull key) {
// 	v += base;
// 	while (v) {
// 		seg[v][key] = (seg[v][key] + x) % MOD;
// 		v >>= 1;
// 	}
// }
// ull find (ull l, ull r, ull key) {
// 	ull x = 0;
// 	for ((l += base), (r += base); l < r; (l >>= 1), (r >>= 1)) {
// 		if (l % 2) x += seg[l++][key];
// 		if (r % 2) x += seg[--r][key];
// 	}
// 	return v % MOD;
// }

ull dp[N_MAX][4], ss[N_MAX][4];

ull solve () {
	sll i, j, ki, li;
	// ull result = 0;
	sll result = 0;
	double dresult = 0;
	// ull maybe = 0;
	sll maybe = 0;
	// ull sum = 0;
	sll sum = 0;
	sll item;
	sll *dpcell;

	const ull inv2 = (MOD + 1) / 2;

	for (i = base * 2 - 1; i; i--) {
		ssize[i] = ((i < base) ? (ssize[i * 2] + ssize[i * 2 + 1]) : 1) % MOD;
	}

	for (i = 0; i < n; i++) {
		xy[i] = (hwll){a[i], b[i]};
	}
	qsort(xy, n, sizeof(hwll), phwllABcomp);
	for (i = 0; i < n; i++) {
		a[i] = xy[i].a;
		b[i] = xy[i].b;
	}

	for (i = 0; i < n; i++) {
		c[i] = smax((i ? c[i - 1] : 0), b[i]);
		// printf("%lld\n", c[i]);
	}
	for (i = n - 1; i >= 0; i--) {
		d[i] = smin(((i < n - 1) ? d[i + 1] : VERYBIG), b[i]);
		// printf("%lld\n", d[i]);
	}

	for (i = 0; i < n; i++) {
		sll ok, ng;

		if (i == 0 || c[i - 1] <= b[i]) {
			xy[i].a = i;
		} else {
			ok = -1;
			ng = i;
			while (ok + 1 < ng) {
				sll med = (ok + ng) / 2;
				if (c[med] > b[i]) {
					ng = med;
				} else {
					ok = med;
				}
			}
			xy[i].a = ng;
		}

		if (i == n - 1 || d[i + 1] >= b[i]) {
			xy[i].b = i;
		} else {
			ok = n;
			ng = i;
			while (ng + 1 < ok) {
				sll med = (ok + ng) / 2;
				if (d[med] < b[i]) {
					ng = med;
				} else {
					ok = med;
				}
			}
			xy[i].b = ng;
		}
	}
	qsort(xy, n, sizeof(hwll), phwllABcomp);
	// xy[n].a = n;
	// xy[n].b = n;
	for (i = 0; i <= n + 1; i++) {
		e[i] = -1;
	}
	for (i = 0; i < n; i++) {
		xy[i].a++;
		xy[i].b++;
		// printf("[%lld %lld]\n", xy[i].a, xy[i].b);

		e[xy[i].b] = xy[i].a;
	}
	dp[0][0] = ss[0][0] = bitpow(2, n, MOD);
	dp[0][2] = ss[0][2] = bitpow(2, n, MOD);
	for (i = 1; i <= n; i++) {

		// sll l = xy[i].a, r = xy[i].b;

		if (e[i] >= 0) {
			sll l = e[i], r = i;
			// printf("[%lld <- %lld]\n", l, r);
			for (ki = 0; ki < 2; ki++) {
				dp[i][ki] = ss[l - 1][1 - ki] * bitpow(inv2, r - l + 1, MOD) % MOD;
				// printf("%lld..\n", dp[i][ki]);
				dp[i][ki] += (MOD + ss[r - 1][3 - ki] - ss[l - 1][3 - ki]) * bitpow(inv2, r, MOD) % MOD;
				// printf("%lld..\n", dp[i][ki]);
				dp[i][ki] %= MOD;

				dp[i][2 + ki] = dp[i][ki] * bitpow(2, i, MOD) % MOD;
			}
		}

		// printf("%lld/%lld (%lld/%lld)\n", dp[i][0], dp[i][1], dp[i][2], dp[i][3]);

		for (ki = 0; ki < 4; ki++) {
			ss[i][ki] = (ss[i - 1][ki] + dp[i][ki]) % MOD;
			// printf("s %lld ", ss[i][ki]);
		}
		// puts("");
	}

	result = (MOD + ss[n][0] - ss[n][1]) % MOD;

	// query(0, 1, 1);
	// for (i = 0; i <= n; i++) {
	// 	sll l = xy[i].a;
	// 	sll r = xy[i].b + 1;

	// 	sll pl = (i ? xy[i - 1].a : 0);

	// 	ull dpi = query(pl, l, 0);
	// 	query(l, r, dpi);
	// }
	// result = query(n + 1, n + 2, 0);
	// add(0, 1, 0);
	// add(0, 1, 2);
	// for (i = 0; i < n; i++) {
	// 	sll l = xy[i].a;
	// 	sll r = xy[i].b + 1;

		
	// }

	printf("%lld\n", result);
	// printf("%.15f\n", dresult);
	// puts(s);

	return 0;

	success:
	// puts("YES");
	puts("Yes");
	// printf("%llu\n", result);
	// puts("0");
	// puts("First");
	return 0;

	fail:
	// puts("NO");
	puts("No");
	// puts("0");
	// puts("-1");
	// puts("-1 -1 -1");
	// puts("Second");
	return 1;
}

int32_t main (int argc, char *argv[]) {
	int32_t i, j;

	n = 4;
	m = 0;

	// scanf("%llu", &m);
	// scanf("%llu%llu", &h, &w);
	scanf("%llu", &n, &m);
	// scanf("%llu", &k, &n, &m);
	// scanf("%llu%llu", &h, &w);
	// scanf("%llu", &q);
	// scanf("%lld%lld", &va, &vb, &vc, &vd);
	// va--;
	// vb--;
	// scanf("%llu%llu%llu%llu", &ua, &ub, &uc, &ud, &ue);
	// scanf("%s", s);
	// scanf("%s", t);
	// scanf("%s", u);
	// scanf("%llu", &k);
	// scanf("%lld", &m);
	// for (i = 0; i < n; i++) {
	// 	// scanf("%lld", &a[i]);
	// 	scanf("%lld", &d[i]);
	// }
	// scanf("%llu", &q);
	for (i = 0; i < n; i++) {
		// scanf("%lld%lld", &xy[i].a, &xy[i].b);
		// scanf("%lld%lld%lld", &tup[i].a, &tup[i].b, &tup[i].c);
		// scanf("%lld", &c[i]);

		scanf("%lld", &a[i]);
		scanf("%lld", &b[i]);
		// scanf("%lld", &c[i]);
		// scanf("%lld", &d[i]);
		// a[i]--;
		// b[i]--;
		// c[i]--;
		// d[i]--;
		// xy[i].a--;
		// xy[i].b--;
		// tup[i].a--;
		// tup[i].b--;
	}
	// scanf("%llu", &m);
	// scanf("%llu", &q);
	// for (i = 0; i < q; i++) {
	// 	// scanf("%lld%lld", &a[i], &b[i]);
	// 	// scanf("%lld", &b[i]);
	// 	// a[i]--;
	// 	// b[i]--;
	// 	// scanf("%lld", &c[i]);
	// 	scanf("%lld", &d[i]);
	// 	scanf("%lld", &e[i]);
	// 	// c[i]--;
	// 	// d[i]--;
	// }

	// for (i = 0; i < q; i++) {
	// 	// scanf("%lld%lld", &xy[i].a, &xy[i].b);
	// 	scanf("%lld", &c[i]);
	// 	// xy[i].a--;
	// 	// xy[i].b--;
	// }

	// for (i = 0; i < h; i++) {
	// 	for (j = 0; j < w; j++) {
	// 		scanf("%lld", &table[i][j]);
	// 		// table[i][j]--;
	// 	}
	// }
	// for (i = 0; i < h; i++) {
	// 	scanf("%s", s[i]);
	// }
	// scanf("%llu", &q);

	solve();

	return 0;
}
