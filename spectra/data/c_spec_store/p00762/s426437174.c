#include <stdio.h>
#define N_MAX 4

/*                 front  1  2  3  4  5  6 */
char right[7][7] = { { 0, 0, 0, 0, 0, 0, 0 },   /* top */
                     { 0, 0, 3, 5, 2, 4, 0 },   /* 1   */
                     { 0, 4, 0, 1, 6, 0, 3 },   /* 2   */
                     { 0, 2, 6, 0, 0, 1, 5 },   /* 3   */
                     { 0, 5, 1, 0, 0, 6, 2 },   /* 4   */
                     { 0, 3, 0, 6, 1, 0, 4 },   /* 5   */
                     { 0, 0, 4, 2, 5, 3, 0 } }; /* 6   */

#define RIGHT(top, front)  (right[(int)(top)][(int)(front)])
#define BOTTOM(top, front) (7 - top)
#define BACK(top, front)   (7 - front)
#define LEFT(top, front)   (7 - RIGHT(top, front))

/* ------ */

char height_map[N_MAX * 2 + 1][N_MAX * 2 + 1],
    top_map[N_MAX * 2 + 1][N_MAX * 2 + 2];

void init()
{
    int x, y;
    for(y = 0; y < N_MAX * 2 + 1; y++)
        for(x = 0; x < N_MAX * 2 + 1; x++)
            height_map[y][x] = top_map[y][x] = 0;
}

void put(char top, char front)
{
    int x = N_MAX, y = N_MAX, newfront, newtop, newx, newy, max;

    while(1)
    {
        max = 0;

        /* front */
        if(height_map[y - 1][x] < height_map[y][x] && front > 3 && front > max)
            newfront = top, newtop = BACK(top, front),
                newx = x, newy = y - 1, max = front;

        if(height_map[y + 1][x] < height_map[y][x]
           && BACK(top, front) > 3 && BACK(top, front) > max)
            newfront = BOTTOM(top, front), newtop = front,
                newx = x, newy = y + 1, max = BACK(top, front);

        if(height_map[y][x - 1] < height_map[y][x]
           && LEFT(top, front) > 3 && LEFT(top, front) > max)
            newfront = front, newtop = RIGHT(top, front),
                newx = x - 1, newy = y, max = LEFT(top, front);

        if(height_map[y][x + 1] < height_map[y][x]
           && RIGHT(top, front) > 3 && RIGHT(top, front) > max)
            newfront = front, newtop = LEFT(top, front),
                newx = x + 1, newy = y, max = RIGHT(top, front);

        if(!max)
            break;
        else
            front = newfront, top = newtop, x = newx, y = newy;
    }

    height_map[y][x]++, top_map[y][x] = top;
}

void count_and_print()
{
    int x, y, count[7];

    for(x = 1; x <= 6; x++)
        count[x] = 0;

    for(y = 0; y < N_MAX * 2 + 1; y++)
        for(x = 0; x < N_MAX * 2 + 1; x++)
            count[(int)top_map[y][x]]++;

    for(x = 1; x < 6; x++)
        printf("%d ", count[x]);
    printf("%d\n", count[x]);
}

int main(void)
{
    int n;

    while(scanf("%d", &n), n)
    {
        int t, f;

        init();

        while(n--)
        {
            scanf("%d %d", &t, &f);
            put(t, f);
        }

        count_and_print();
    }

    return 0;
}