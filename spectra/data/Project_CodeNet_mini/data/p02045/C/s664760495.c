#include <stdio.h>
#include <stdlib.h>

int A, B, C, D;

int nigeru(int x, int y, int isSrc) {
	int cost = 0;
	if (x < A) cost += A - x;
	if (C < x) cost += x - C;
	if (y < B) cost += B - y;
	if (D < y) cost += y - D;
	if (isSrc && cost > 0) cost--;
	return cost;
}

int main(void) {
	int N;
	while (scanf("%d", &N) == 1 && N > 0) {
		int X[128], Y[128];
		int i;
		int mikakosi = 0;
		if (scanf("%d%d%d%d", &A, &B, &C, &D) != 4) return 1;
		for (i = 0; i <= N; i++) {
			if (scanf("%d%d", &X[i], &Y[i]) != 2) return 1;
		}
		for (i = 1; i <= N; i++) {
			int naka = abs(X[i - 1] - X[i]) + abs(Y[i - 1] - Y[i]);
			int simakaze = nigeru(X[i - 1], Y[i - 1], 1) + nigeru(X[i], Y[i], 0);
			mikakosi += naka < simakaze ? naka : simakaze;
		}
		printf("%d\n", mikakosi);
	}
	return 0;
}

