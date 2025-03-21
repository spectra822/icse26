#include <stdio.h>


int main(void) {
    int h, m, s, cur_sec, remaining;
    while (scanf("%d%d%d", &h, &m, &s) == 3 &&
           h != -1 && m != -1 && s != -1) {
        cur_sec = h * 3600 + m * 60 + s;
        remaining = 2 * 3600 - cur_sec;
        printf("%02d:%02d:%02d\n",
               remaining / 3600,
               (remaining % 3600) / 60,
               remaining % 60);
        remaining *= 3;
        printf("%02d:%02d:%02d\n",
               remaining / 3600,
               (remaining % 3600) / 60,
               remaining % 60);
    }

    return 0;
}