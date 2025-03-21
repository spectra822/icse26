#include<stdio.h>
int main()
{
	int n;
	scanf("%d", &n);
	char s[1000006];
	scanf("%s", s);
	int q;
	scanf("%d", &q);
	int k[102];
	int i, j;
	for (i = 0; i < q; i++)
		scanf("%d", &k[i]);
	long long int ans;
	long long int d, m, dm;
	for (j = 0; j < q; j++)
	{
		ans = 0;
		d = m = dm = 0;
		for (i = 0; i < k[j]; i++)
		{
			if (s[i] == 'D')
				d++;
			if (s[i] == 'M')
			{
				m++;
				dm += d;
			}
			if (s[i] == 'C')
				ans += dm;
		}
		for (i = k[j]; i < n; i++)
		{
			if (s[i - k[j]] == 'D')
			{
				dm -= m;
				d--;
			}
			if (s[i - k[j]] == 'M')
				m--;
			if (s[i] == 'D')
				d++;
			if (s[i] == 'M')
			{
				m++;
				dm += d;
			}
			if (s[i] == 'C')
				ans += dm;
		}
		printf("%lld\n", ans);
	}
	return 0;
}