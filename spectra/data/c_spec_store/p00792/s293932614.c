// AOJ 1212: Mirror Illusion
// 2018.1.23 bal4u@uu

#include <stdio.h>
#include <string.h>

char mir[9][9][9][9];
int mv[4][2] = {{50,50},{-50,50},{-50,-50},{50,-50}};
int tr[2][4] = {{3,2,1,0},{1,0,3,2}};

int main()
{
	int n, i, v, x, y, d, wall;
	char s[5];

	while (scanf("%d", &n) && n >= 0) {
		memset(mir, 0, sizeof(mir));

		for (i = 0 ; i < n ; i++) {
			scanf("%s%d%d", s, &x, &y);
			if (*s == 'x') mir[x][y][x+1][y] = 1;
			else           mir[x][y][x][y+1] = 1;
		}

		x = 50, y = 0, d = 0, wall = 1;
		for (v = 1, i = 0; ; i++, v = !v) {
			if (i >= 2) {
				if (x == 100 && y == 50 && d == 0) { x = 75, y = 25; break; }
				if (wall && (!x || !y || x == 800 || y == 800)) break;
			}

	        x += mv[d][0], y += mv[d][1], wall = 1;

			if (v) {
				if (mir[x/100][(y-50)/100][x/100][(y+50)/100]) d = tr[v][d], wall = 0;
			} else {
				if (mir[(x-50)/100][y/100][(x+50)/100][y/100]) d = tr[v][d], wall = 0;
			}
		}
		printf("%d %d\n", x, y);
	}
	return 0;
}
