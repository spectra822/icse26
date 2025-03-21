#include <stdio.h>
#include <string.h>
#pragma warning(disable : 4996)

int main()
{
    int A, B, C, D;
    int i;
    int a[101] = {0};
    int b[101] = {0};
    int c[100] = { 0 };
    int time = 0;

    scanf("%d %d %d %d", &A, &B, &C, &D);

    for (i = A; i <= B; i++) {
        a[i] = 1;
    }

    for (i = C; i <= D; i++) {
        b[i] = 1;
    }

    for (i = 0; i <= 100; i++) {
        c[i] = a[i] + b[i];
        if (c[i] == 2)
            time++;
    }

 
    if (time == 0)
        printf("%d", time);
    else
    printf("%d", time-1);

    return 0;
}