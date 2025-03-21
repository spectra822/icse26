#if 0
cat <<EOF >mistaken-paste
#endif
// thx Ebi-chan!

// #pragma GCC optimize("unroll-loops")
// #pragma GCC optimize("O3")

#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

#define BIG 2000000007LL
#define VERYBIG 2000000000000000007LL
#define ULTRABIG 300000000000000000000LL

#define MOD 1000000007LL
#define FOD  998244353LL
#define HOD 1000000009LL
#define IOD  100000007LL
typedef uint64_t ull;
typedef  int64_t sll;

#define N_MAX 1048576

#ifdef __cplusplus
#include <queue>
#include <stack>
// #include <tuple>
#include <set>
#include <map>
#include <string>
#include <algorithm>
// #include <functional>
// #include <array>
#include <iostream>

using std::queue;
using std::priority_queue;
using std::stack;
// using std::tuple;
using std::set;
using std::map;
using std::vector;
using std::greater;
using std::pair;
using std::string;
// using std::get;
// using std::function;
// using std::array;
using std::cin;
using std::cout;
using std::endl;

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

double dmin (double x, double y) {
	return (x < y) ? x : y;
}

double dmax (double x, double y) {
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
	hwll l = *(hwll*)left;
	hwll r = *(hwll*)right;

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
	if (*l == *r) return;
	sll t = *l;
	*l = *r;
	*r = t;
}

void uw (ull *l, ull *r) {
	if (*l == *r) return;
	ull t = *l;
	*l = *r;
	*r = t;
}

ull frac[N_MAX * 10], invf[N_MAX * 10];
void f_init (sll n, sll m) {
	frac[0] = 1;
	for (sll i = 1; i <= n; i++) {
		frac[i] = frac[i - 1] * i % m;
	}

	invf[n] = divide(1, frac[n], m);
	for (sll i = n - 1; i >= 0; i--) {
		invf[i] = invf[i + 1] * (i + 1) % m;
	}
}
ull ncr (sll n, sll r, ull m) {
	if (n < 0 || r < 0 || n < r) return 0;
	return frac[n] * (invf[r] * invf[n - r] % m) % m;
}

sll a[N_MAX * 5];
// ull a[N_MAX + 5];
// sll a[3001][3001];
sll b[N_MAX * 5];
// ull b[N_MAX + 5];
// sll b[3001][3001];
sll c[N_MAX * 5];
sll d[N_MAX * 5];
sll e[N_MAX * 4];
char s[N_MAX + 1];
// char s[3010][3010];
char t[N_MAX + 1];
// char t[3010][3010];
char u[N_MAX + 1];
hwll xy[N_MAX * 4];
hwllc tup[N_MAX * 4];
// sll table[3005][3005];
sll table[2005][2005];
ull gin[N_MAX];
// here we go

ull parent[201910], size[201910], edges[201910];
void init (ull n) {
	for (sll i = 0; i < n; i++) {
		parent[i] = i;
		size[i] = 1;
		edges[i] = 0;
	}
}
ull find (ull x) {
	if (parent[x] == x) return x;
	return parent[x] = find(parent[x]);
}
bool unite (ull v, ull u) {
	v = find(v);
	u = find(u);

	edges[v]++;

	if (v == u) return false;

	if (size[v] < size[u]) {
		ull tmp = v;
		v = u;
		u = tmp;
	}
	size[v] += size[u];
	edges[v] += edges[u];
	parent[u] = v;
	return true;
}

sll us[N_MAX], ulen = 0;

sll dp[5050][5050], dq[5050][5050];

sll pow2[N_MAX], inv2[N_MAX];

sll solve () {
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

	// f_init(n * 5 + 5);

	const sll inv = (MOD + 1) / 2;

	pow2[0] = 1;
	inv2[0] = 1;
	for (i = 1; i <= n + m; i++) {
		pow2[i] = (pow2[i - 1] * 2) % MOD;
		inv2[i] = (inv2[i - 1] * inv) % MOD;
	}

	for (i = 0; i <= n; i++) {

		for (j = 1; j <= m; j++) {
			if (i == 0) {
				dp[i][j] = 1;
			} else {
				dp[i][j] = ((j + 1) * dp[i - 1][j] + dq[i - 1][j - 1] * pow2[j - 1]) % MOD;
			}

			dq[i][j] = (dq[i][j - 1] + (dp[i][j] * j % MOD) * inv2[j]) % MOD;
			

			// printf("%lld %lld: %lld %lld\n", i, j, dp[i][j], dq[i][j]);
		}
	}
	result = dp[n][m];

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
	// puts("No");
	// puts("0");
	puts("-1");
	// puts("-1 -1 -1");
	// puts("Second");
	return 1;
}

int32_t main (int argc, char *argv[]) {
	int32_t i, j;

	n = 3;
	m = 0;
	h = 5;

	// scanf("%llu", &m);
	// scanf("%lld", &w);
	// scanf("%lld%lld", &h, &w);
	scanf("%lld%lld", &n, &m);
	// scanf("%lld", &k, &n, &m);
	// scanf("%llu%llu", &h, &w);
	// scanf("%lld", &q);
	// scanf("%lld%lld", &va, &vb, &vc, &vd);
	// va--;
	// vb--;
	// scanf("%llu%llu%llu%llu", &ua, &ub, &uc, &ud, &ue);
	// scanf("%s", s);
	// scanf("%s", t);
	// scanf("%s", u);
	// scanf("%lld", &k);
	// scanf("%lld", &m);
	// scanf("%lld", &n);
	// for (i = 0; i < n; i++) {
	// 	// scanf("%s", s[i]);
	// 	scanf("%lld", &c[i]);
	// }
	// scanf(" %c", &ch);
	// scanf("%llu", &q);
	for (i = 0; i < 0; i++) {

		// scanf("%lld%lld", &xy[i].a, &xy[i].b);
		// scanf("%lld%lld%lld", &tup[i].a, &tup[i].b, &tup[i].c);
		// scanf("%lld", &c[i]);

		scanf("%lld", &a[i]);
		// scanf("%lld", &b[i]);
		// scanf("%lld", &c[i]);
		// scanf("%lld", &d[i]);
		// scanf("%lld", &e[i]);
		a[i]--;
		// b[i]--;
		// c[i]--;
		// d[i]--;
		// xy[i].a--;
		// xy[i].b--;
		// tup[i].a--;
		// tup[i].b--;
	}
	// scanf("%lld%lld", &va, &vb);
	// scanf("%llu", &m);
	// scanf("%llu", &q);
	// scanf("%s", t);
	// for (i = 0; i < n; i++) {
	// 	// scanf("%lld%lld", &xy[i].a, &xy[i].b);
	// 	// xy[i].a--;
	// 	// xy[i].b--;
	// 	// scanf("%lld", &a[i], &b[i]);
	// 	// scanf("%lld", &b[i]);
	// 	// a[i]--;
	// 	// b[i]--;
	// 	scanf("%lld", &c[i]);
	// 	// scanf("%lld", &d[i]);
	// 	// scanf("%lld", &e[i]);
	// 	c[i]--;
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
	// for (i = 0; i < n; i++) {
	// 	scanf("%s", s[i]);
	// }
	// for (i = 0; i < n; i++) {
	// 	scanf("%s", t[i]);
	// }
	// scanf("%llu", &q);
	// for (i = 0; i < q; i++) {
	// 	scanf("%lld%lld%lld", &e[i], &c[i], &d[i]);
	// 	c[i]--;
	// }

	solve();

	return 0;
}
