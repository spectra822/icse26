#include <stdio.h>

char souti(char a, char b) {
	return a == 'T' && b == 'F' ? 'F' : 'T';
}

int N;
char P[114514];

int main(void) {
	int i;
	char notomamiko;
	if (scanf("%d", &N) != 1) return 1;
	for (i = 0; i < N; i++) {
		char hoge[4];
		if (scanf("%3s", hoge) != 1) return 1;
		P[i] = hoge[0];
	}
	notomamiko = souti(P[0], P[1]);
	for (i = 2; i < N; i++) {
		notomamiko = souti(notomamiko, P[i]);
	}
	printf("%c\n", notomamiko);
	return 0;
}

