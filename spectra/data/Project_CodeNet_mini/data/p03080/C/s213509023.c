#include <stdio.h>

int main(void) {
	int N;
	char s[128] = "";
	int kitaeri = 0;
	int i;
	if (scanf("%d", &N) != 1) return 1;
	if (scanf("%127s", s) != 1) return 1;
	for (i = 0; i < N; i++) {
		if (s[i] == 'R') kitaeri++; else kitaeri--;
	}
	puts(kitaeri > 0 ? "Yes" : "No");
	return 0;
}
