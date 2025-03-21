// AOJ Vol3-0383 Heat Strokes
// 2018.12.22

//#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int A, B, X;
	int c, ans;

	scanf("%d%d%d", &A, &B, &X);
	if (A >= 2 * B) ans = ((X - 1) / 500 + 1) * B;
	else {
		ans = X / 1000 * A;
		c = X % 1000;
		if (c) {
			if (c <= 500 && B < A) ans += B;
			else ans += A;
		}
	}
	printf("%d\n", ans);
	return 0;
}
