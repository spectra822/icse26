#include <stdio.h>

const int Mod = 998244353;

typedef struct {
	int key, id;
} data;

void merge_sort(data x[], int n)
{
	static data y[200001] = {};
	if (n <= 1) return;
	merge_sort(&(x[0]), n/2);
	merge_sort(&(x[n/2]), (n+1)/2);
	
	int i, p, q;
	for (i = 0, p = 0, q = n/2; i < n; i++) {
		if (p >= n/2) y[i] = x[q++];
		else if (q >= n) y[i] = x[p++];
		else y[i] = (x[p].key < x[q].key)? x[p++]: x[q++];
	}
	for (i = 0; i < n; i++) x[i] = y[i];
}

void add_BIT(int N, int BIT[], int i, int k)
{
	while (i <= N) {
		BIT[i] += k;
		i += (i & -i);
	}
}

int sum_BIT(int BIT[], int r)
{
	int sum = 0;
	while (r > 0) {
		sum += BIT[r];
		r -= (r & -r);
	}
	return sum;
}

int main()
{
	int i, j, m, n, N, tmp;
	data d[200001];
	scanf("%d", &N);
	for (i = 1; i <= N; i++) scanf("%d %d", &(d[i-1].key), &(d[i-1].id));
	merge_sort(d, N);
	for (i = 0, m = 1; i < N; i++, m++) {
		for (j = i, tmp = d[i].key; j < N && d[j].key == tmp; j++) {
			d[j].key = d[j].id;
			d[j].id = m;
		}
		j = i - 1;
	}
	merge_sort(d, N);
	for (i = 0, n = 1; i < N; i++, n++) {
		for (j = i, tmp = d[i].key; j < N && d[j].key == tmp; j++) d[j].key = n;
		j = i - 1;
	}

	long long pow[200001];
	for (i = 1, pow[0] = 1; i <= N; i++) pow[i] = pow[i-1] * 2 % Mod;
	
	int BIT[200001] = {};
	long long ans = (pow[N] - 1 + Mod) * N % Mod;
	for (i = 0; i < N; i++) {
		for (j = i; j < N && d[j].key == d[i].key; j++) ans += pow[sum_BIT(BIT, d[j].id - 1)] + pow[i - sum_BIT(BIT, d[j].id)];
		ans = (ans + (Mod - pow[i]) * (j - i)) % Mod;
		
		for (j = i; j < N && d[j].key == d[i].key; j++) add_BIT(m, BIT, d[j].id, 1);
		i = j - 1;
	}
	for (i = 1; i <= m; i++) BIT[i] = 0;
	for (i = N - 1; i >= 0; i--) {
		for (j = i; j >= 0 && d[j].key == d[i].key; j--) ans += pow[sum_BIT(BIT, d[j].id - 1)] + pow[N - i - 1 - sum_BIT(BIT, d[j].id)];
		ans = (ans + (Mod - pow[N-i-1]) * (i - j)) % Mod;
		
		for (j = i; j >= 0 && d[j].key == d[i].key; j--) add_BIT(m, BIT, d[j].id, 1);
		i = j + 1;
	}
	
	for (i = 0; i < N; i++) {
		d[i].key ^= d[i].id;
		d[i].id ^= d[i].key;
		d[i].key ^= d[i].id;
	}
	merge_sort(d, N);

	for (i = 0; i < N; i++) {
		for (j = i; j < N && d[j].key == d[i].key; j++);
		ans = (ans + (Mod - pow[i]) * (j - i)) % Mod;
		i = j - 1;
	}
	for (i = N - 1; i >= 0; i--) {
		for (j = i; j >= 0 && d[j].key == d[i].key; j--);
		ans = (ans + (Mod - pow[N-i-1]) * (i - j)) % Mod;
		i = j + 1;
	}
	
	printf("%lld\n", ans);
	fflush(stdout);
	return 0;
}