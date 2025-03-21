// AOJ 1055 Huge Family
// 2018.2.3 bal4u@uu

#include <stdio.h>
#include <string.h>

#define MAX 100002

/* UNION-FIND library */
int id[MAX], size[MAX];
void init(int n) { int i; for (i = 0; i < n; i++) id[i] = i, size[i] = 1; }
int root(int i) { while (i != id[i]) id[i] = id[id[i]], i = id[i]; return i; }
int connected(int p, int q) { return root(p) == root(q); }
void unite(int p, int q)
{
    int i = root(p), j = root(q); if (i == j) return;
    if (size[i] < size[j]) id[i] = j, size[j] += size[i]; else id[j] = i, size[i] += size[j];
}
/* UNION-FIND library */

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

int f[MAX][2]; 
int max[MAX], cnt[MAX];

void check(int k, int f)
{
	if (!cnt[k] || f > max[k]) {
		cnt[k] = 1;
		max[k] = f;
	} else if (f == max[k]) cnt[k]++;
}

int main()
{
	int n, a, b, i, k, ans;

	while (n = in()) {
		init(n);

		for (i = 0; i < n; i++) {
			a = in(), f[i][0] = in();
			b = in(), f[i][1] = in();
			unite(i, a);
			unite(i, b);
		}

		memset(cnt, 0, sizeof(cnt));
		for (i = 0; i < n; i++) {
			k = root(i);
			check(k, f[i][0]), check(k, f[i][1]);
		}

		ans = 1;
		for (i = 0; i < n; i++) {
			if (cnt[i]) ans = ans * (cnt[i] >> 1) % 10007;
		}
		printf("%d\n", ans);
	}
	return 0;
}

