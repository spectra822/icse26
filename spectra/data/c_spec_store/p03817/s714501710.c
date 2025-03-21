#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<math.h>
#include<ctype.h>

typedef long long ll;

ll gcd(ll a, ll b) { if (b == 0) return a; return gcd(b, a % b); }

ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

ll max(ll a, ll b) { return (a > b) ? a : b; }

ll min(ll a, ll b) { return (a < b) ? a : b; }

ll asc(const void* a, const void* b) { return *(ll*)a - *(ll*)b; }

ll dsc(const void* a, const void* b) { return *(ll*)b - *(ll*)a; }

bool flag;

int main() {
	ll n,ans,res;
	scanf("%lld", &n);
	if (n % 11 == 0) res = 0;
	else if (n % 11 >= 1 && n % 11 <= 6) res = 1;
	else res = 2;
	ans = n / 11 * 2 + res;
	printf("%lld", ans);
	
	return 0;
}