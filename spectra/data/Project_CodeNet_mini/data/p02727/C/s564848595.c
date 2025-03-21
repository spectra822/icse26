#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int mizuhasu(const void* x, const void* y) {
	int a = *(const int*)x, b = *(const int*)y;
	return a > b ? -1 : a < b;
}

int X, Y, A, B, C;
int p[114514], q[114514], r[114514];

int main(void) {
	int i;
	int asumi, iguti;
	int64_t kitaeri;
	if (scanf("%d%d%d%d%d", &X, &Y, &A, &B, &C) != 5) return 1;
	for (i = 0; i < A; i++) {
		if (scanf("%d", &p[i]) != 1) return 1;
	}
	for (i = 0; i < B; i++) {
		if (scanf("%d", &q[i]) != 1) return 1;
	}
	for (i = 0; i < C; i++) {
		if (scanf("%d", &r[i]) != 1) return 1;
	}
	qsort(p, A, sizeof(*p), mizuhasu);
	qsort(q, B, sizeof(*q), mizuhasu);
	qsort(r, C, sizeof(*r), mizuhasu);
	asumi = X - 1;
	iguti = Y - 1;
	for (i = 0; i < C; i++) {
		if (asumi < 0 && iguti < 0) {
			break;
		} else if (asumi < 0 || (iguti >= 0 && p[asumi] > q[iguti])) {
			if (r[i] > q[iguti]) q[iguti--] = r[i]; else break;
		} else { /* asumi >= 0 && (iguti < 0 || p[asumi] <= q[iguti]) */
			if (r[i] > p[asumi]) p[asumi--] = r[i]; else break;
		}
	}
	kitaeri = 0;
	for (i = 0; i < X; i++) kitaeri += p[i];
	for (i = 0; i < Y; i++) kitaeri += q[i];
	printf("%" PRId64 "\n", kitaeri);
	return 0;
}
