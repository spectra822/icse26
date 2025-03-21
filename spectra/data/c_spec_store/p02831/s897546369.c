//C-Snack

#include <stdio.h>



int main(void) {
    long int a;
    long int b;
    scanf("%ld%ld", &a, &b);
    //printf("%d%d\n", a, b);
    long int i;
    for (i = 1;i <= b + 1;i++) {
        if ((a * i) % b == 0) {
            printf("%ld\n", a * i);
            break;
          }

      }
    return 0;

  }
