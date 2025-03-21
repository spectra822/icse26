// AOJ 1328 Find the Outlier
// 2018.2.9 bal4u

#include <stdio.h>

int n;
double v[10];

double calc(int x, int k)
{
	int i, j;
	double t, s;

	s = 0;
	for (i = 0; i < n; i++) if (i != k && i != x) {
        t = v[i];
		for (j = 0; j < n; j++) {
			if (j != i && j != k && j != x)	t = (t*(k-j)) /(i-j);
		}
        s += t;
	}
	return s;
}
 
int main()
{
	int d, i, j;
	double t;

	while (scanf("%d", &d) && d) {
		n = d+3;
		for (i = 0; i < n; i++) scanf("%lf", v+i);
		for (i = 0; i < n; i++) {
			for (j = 0; ; j++) {
				if (j == n) goto done;
				if (j != i) {
					t = calc(i, j) - v[j];
					if (t < -0.1 || t > 0.1) break;
				}
			}
		}
done:	printf("%d\n", i);
	}
	return 0;
}
