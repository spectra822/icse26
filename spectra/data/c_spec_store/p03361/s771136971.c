#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)

int main()
{
    int H, W,i,j;
    char u, d, r, l;
    char s[51][60] = {""};

    scanf("%d %d", &H, &W);

    for (i = 0; i < H; i++) {
        scanf("%s", s[i]);
    }

    for (i = 0; i < H; i++) {
        for (j = 0; j < W; j++) {

            if (i - 1 < 0)
                u = 0;
            else
                u = s[i - 1][j];

            if (j - 1 < 0)
                l = 0;
            else
                l = s[i][j - 1];

            d = s[i + 1][j];
            r = s[i][j + 1];

            if (s[i][j] == '#') {
                if (u == '#' || d == '#' || r == '#' || l == '#')
                    continue;
                else {
                    printf("No");
                        return 0;
                }
            }
        }
    }


    printf("Yes");
      

    return 0;
}
