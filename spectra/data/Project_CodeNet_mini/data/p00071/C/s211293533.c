#include <stdio.h>

const int dir[][2] = {{0, -1}, {-1, 0}, {0, 1}, {1, 0}};

void explode(char field[10][10], int px, int py) {
    int i, j, x, y;
    field[py][px] = '0';
    for (i = 0; i < 4; i++) {
        for (j = 1; j <= 3; j++) {
            x = px + j * dir[i][0];
            y = py + j * dir[i][1];
            if (x < 1 || 8 < x || y < 1 || 8 < y) break;
            if (field[y][x] == '1') explode(field, x, y);
        }
    }
}

int main(void) {
    char field[10][10];
    int N, n, i, sx, sy;

    gets(field[0]);
    sscanf(field[0], "%d", &N);

    for (n = 1; n <= N; n++) {
        for (i = 0; i <= 8; i++) {
            gets(&(field[i][1]));
        }
        gets(field[0]);
        sscanf(field[0], "%d", &sx);
        gets(field[0]);
        sscanf(field[0], "%d", &sy);

        explode(field, sx, sy);

        printf("Data %d:\n", n);
        for (i = 1; i <= 8; i++) {
            puts(&(field[i][1]));
        }
    }
    return 0;
}