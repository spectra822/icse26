#include <stdio.h>
#include <math.h>

#define EPS 1e-5

int main (void) {
    int q;
    double px, x;
    while (scanf("%d", &q) != EOF && q != -1) {
        px = (double)q / 2;
        do {
            x = px - (px*px*px - q) / (3*px*px);
            px = x;
        } while (fabs(x*x*x - q) >= EPS * q);
        printf("%.6lf\n", x);
    }
    return 0;
}