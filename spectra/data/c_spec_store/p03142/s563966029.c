#include <stdio.h>
#include <stdlib.h>

int N, M;
int ec[114514];
int* es[114514];

void ae(int f, int t) {
	es[f] = realloc(es[f], sizeof(*es[f]) * (ec[f] + 1));
	if (es[f] == NULL) exit(2);
	es[f][ec[f]++] = t;
}

int sansyo[114514];

int next_count[2];
int next_buffer[2][114514];

int answer[114514];

int main(void) {
	int i;
	int phase;
	if (scanf("%d%d", &N, &M) != 2) return 1;
	for (i = 1; i <= N - 1 + M; i++) {
		int A, B;
		if (scanf("%d%d", &A, &B) != 2) return 1;
		ae(A, B);
		sansyo[B]++;
	}
	next_count[0] = 0;
	for (i = 1; i <= N; i++) {
		if (sansyo[i] == 0) next_buffer[0][next_count[0]++] = i;
	}

	phase = 0;
	while (next_count[phase] > 0) {
		next_count[1 - phase] = 0;
		for (i = 0; i < next_count[phase]; i++) {
			int target = next_buffer[phase][i];
			int j;
			for (j = 0; j < ec[target]; j++) {
				if (--sansyo[es[target][j]] == 0) {
					answer[es[target][j]] = target;
					next_buffer[1 - phase][next_count[1 - phase]++] = es[target][j];
				}
			}
		}
		phase = 1 - phase;
	}
	for (i = 1; i <= N; i++) {
		printf("%d\n", answer[i]);
	}
	return 0;
}

/*

一番上(根)はどこからも参照されてない
→ そこからの参照を消せば、次の階層がどこからも参照されなくなるはず
→ 繰り返す

*/
