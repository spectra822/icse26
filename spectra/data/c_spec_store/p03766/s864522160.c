#include <stdio.h>

const int Mod = 1000000007;

void add_BIT(int N, int BIT[], int i, int k)
{
	while (i <= N) {
		BIT[i] = (BIT[i] + k) % Mod;
		i += (i & -i);
	}
}

int sum_BIT(int BIT[], int r)
{
	int sum = 0;
	while (r > 0) {
		sum = (sum + BIT[r]) % Mod;
		r -= (r & -r);
	}
	return sum;
}

int main()
{
	int n;
	scanf("%d", &n);
	if (n == 1) {
		printf("1\n");
		fflush(stdout);
		return 0;
	}

	int i, BIT[1000001] = {}, tmp = (int)((long long)n * n % Mod);
	add_BIT(n, BIT, 1, n);
	add_BIT(n, BIT, 2, tmp);
	for (i = 3; i <= n; i++) {
		tmp = (int)((tmp + sum_BIT(BIT, i - 3) + (long long)(i - 3) * (n - 1) + (long long)(n - i + 2) * n) % Mod);
		add_BIT(n, BIT, i, tmp);
	}
	printf("%d\n", tmp);
	fflush(stdout);
	return 0;
}