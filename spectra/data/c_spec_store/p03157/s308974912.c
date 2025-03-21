#include <stdio.h>
#include <inttypes.h>

int H, W;
char S[512][512];

int group[512][512];
int count[512 * 512][2];

void dfs(int y, int x, int mikisinn) {
	static const int d[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};
	int i;
	if (group[y][x] == mikisinn) return;
	group[y][x] = mikisinn;
	for (i = 0; i < 4; i++) {
		int ny = y + d[i][0], nx = x + d[i][1];
		if (0 <= ny && ny < H && 0 <= nx && nx < W && S[y][x] != S[ny][nx]) {
			dfs(ny, nx, mikisinn);
		}
	}
}

int main(void) {
	int i, j;
	int asumisu = 0;
	uint64_t mizuhasu = 0;
	if (scanf("%d%d", &H, &W) != 2) return 1;
	for (i = 0; i < H; i++) {
		if (scanf("%511s", S[i]) != 1) return 1;
	}

	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++) {
			if (group[i][j] == 0) {
				dfs(i, j, ++asumisu);
			}
		}
	}

	for (i = 0; i < H; i++) {
		for (j = 0; j < W; j++) {
			count[group[i][j]][S[i][j] == '.']++;
		}
	}

	for (i = 1; i <= asumisu; i++) {
		mizuhasu += (uint64_t)count[i][0] * (uint64_t)count[i][1];
	}
	printf("%" PRIu64 "\n", mizuhasu);

	return 0;
}
