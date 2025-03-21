// AOJ 2747 Curtain
// 2018.4.26 bal4u

#include <stdio.h>

// バッファを経ずstdinから数値を得る
//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0, c = getchar_unlocked();
	if (c == '-') { c = getchar_unlocked();
		do n = 10*n + (c & 0xf), c = getchar_unlocked(); while (c >= '0');
		return -n;
	}
	do n = 10*n + (c & 0xf), c = getchar_unlocked(); while (c >= '0');
	return n;
}

#define INF 20002

int x[102], y[102];

int main()
{
	int N, a, b, c, i;
	int xmin, xmax, ymin, ymax;
	long long win, cur;

	while (N = in()) {
		for (i = 0; i < N; i++) x[i] = in(), y[i] = in();
		x[N] = x[0], y[N] = y[0];
 
		xmin = ymin = INF, xmax = ymax = -INF;
		for (i = 0; i < 4; i++) {
			a = in(), b = in();
			if (a < xmin) xmin = a;
			if (a > xmax) xmax = a;
			if (b < ymin) ymin = b;
			if (b > ymax) ymax = b;
		}

		win = cur = 0;
		for (i = 0; i < N; i++) if (x[i] == x[i+1]) {
			cur += (long long)x[i] * (y[i]-y[i+1]);
			a = x[i]; if (a > xmax) a = xmax;
			if (xmin > a) a = xmin;
			b = y[i]; if (b > ymax) b = ymax;
			if (ymin > b) b = ymin;
			c = y[i+1]; if (c > ymax) c = ymax;
			if (ymin > c) c = ymin;
			win += (long long)a * (b-c);
		}
		printf("%lld\n", win-cur);
	}
	return 0;
}
