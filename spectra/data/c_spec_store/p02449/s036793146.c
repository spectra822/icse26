#include <stdio.h>

int main(void)
{
    int n;
    scanf("%d", &n);

    int A[9];
    int next_A[9];
    int prev_A[9];
    int i;
    for (i = 0; i < n; i++) {
        scanf("%d", &A[i]);
        next_A[i] = A[i];
        prev_A[i] = A[i];
    }

    int flag = 0;
    int j, tmp, k, mid;
    if (n == 1) {
        printf("1\n");
    }
    else {
        /* search for previous permutation */
        for (i = n - 2; i >= 0; i--) {
            if (prev_A[i] > prev_A[i + 1]) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            for (j = n - 1; j > i; j--) {
                if (prev_A[j] < prev_A[i]) {
                    tmp = prev_A[j];
                    prev_A[j] = prev_A[i];
                    prev_A[i] = tmp;
                    break;
                }
            }
            mid = (n - i - 1) / 2;
            for (k = 1; k <= mid; k++) {
                tmp = prev_A[i + k];
                prev_A[i + k] = prev_A[n - k];
                prev_A[n - k] = tmp;
            }
            /* print the previous permutation */
            printf("%d", prev_A[0]);
            for (i = 1; i < n; i++) printf(" %d", prev_A[i]);
            putchar('\n');
        }
        
        /* print the given sequence */
        printf("%d", A[0]);
        for (i = 1; i < n; i++) printf(" %d", A[i]);
        putchar('\n');

        /* search for next permutation */
        flag = 0;
        for (i = n - 2; i >= 0; i--) {
            if (next_A[i] < next_A[i + 1]) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            for (j = n - 1; j > i; j--) {
                if (next_A[j] > next_A[i]) {
                    tmp = next_A[j];
                    next_A[j] = next_A[i];
                    next_A[i] = tmp;
                    break;
                }
            }
            mid = (n - i - 1) / 2;
            for (k = 1; k <= mid; k++) {
                tmp = next_A[i + k];
                next_A[i + k] = next_A[n - k];
                next_A[n - k] = tmp;
            }
            /* print the next permutation */
            printf("%d", next_A[0]);
            for (i = 1; i < n; i++) printf(" %d", next_A[i]);
            putchar('\n');
        }
    }

    return 0;
}
