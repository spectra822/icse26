#include <stdio.h>

int main(void) {
	const char *A = "Alice", *B = "Bob", *D = "Draw";
	int T1, T2, R1, R2;
	if (scanf("%d%d%d%d", &T1, &T2, &R1, &R2) != 4) return 1;
	if (R1 < 0 || R2 < 0) {
		puts(T1 < T2 ? A : (T1 > T2 ? B : D));
	} else {
		puts(R1 > R2 ? A : (R1 < R2 ? B : D));
	}
	return 0;
}

