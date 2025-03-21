#include <stdio.h>

#define MEW 112345

int N, W;
int w[128], v[128];

int ayaneru[MEW];

int main(void) {
	int i;
	if (scanf("%d%d", &N, &W) != 2) return 1;
	for (i = 0; i < N; i++) {
		if (scanf("%d%d", &w[i], &v[i]) != 2) return 1;
	}
	for (i = 0; i < MEW; i++) {
		ayaneru[i] = W + 1;
	}
	ayaneru[0] = 0;
	for (i = 0; i < N; i++) {
		int j;
		for (j = MEW - 1; j >= v[i]; j--) {
			if (ayaneru[j - v[i]] + w[i] < ayaneru[j]) ayaneru[j] = ayaneru[j - v[i]] + w[i];
		}
	}
	for (i = MEW - 1; i >= 0; i--) {
		if (ayaneru[i] <= W) {
			printf("%d\n", i);
			return 0;
		}
	}
	puts("error!");
	return 0;
}
