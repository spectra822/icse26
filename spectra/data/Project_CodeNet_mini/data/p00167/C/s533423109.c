#include <stdio.h>


int main(void) {
    int a[100], n, i, u, swap_count, t;

    while (scanf("%d", &n) == 1 && n) {
        for (i = 0; i < n; i++) {
            scanf("%d", &(a[i]));
        }
        swap_count = 0;
        for (u = n - 1; u > 0; u--) {
            for (i = 0; i < u; i++) {
                if (a[i] > a[i+1]) {
                    t = a[i];
                    a[i] = a[i+1];
                    a[i+1] = t;
                    swap_count++;
                }
            }
        }
        printf("%d\n", swap_count);
    }
    return 0;
}