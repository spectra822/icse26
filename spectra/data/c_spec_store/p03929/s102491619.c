#include<stdio.h>
int main()
{
	long long int n, k;
	scanf("%lld %lld", &n, &k);
	long long int ans = 0, i;
	n *= 7;
	for (i = 1; i <= n % 693; i++)
		if (i % 7 > 1)
			if (9 * i % 11 == k)
				ans++;
	long long int count = 0;
	for (i = 1; i <= 693; i++)
		if (i % 7 > 1)
			if (9 * i % 11 == k)
				count++;
	ans += count * (n / 693);
	for (i = 1; i <= 7; i++)
		if (i % 7 > 1)
			if (9 * i % 11 == k)
				ans--;
	for (i = n - 6; i <= n; i++)
		if (i % 7 > 1)
			if (i * 9 % 11 == k)
				ans--;
	printf("%lld\n", ans);
	return 0;
}