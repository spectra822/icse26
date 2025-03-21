#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* constant */

#define MAX_K   (5000)
#define MAX_N   (1000)

/* typedef */

/* global variables */

static int ais[MAX_K], bis[MAX_K];

/* subroutines */

int get_len(int an, int bn, int *ais, int *bis, int k0) {
  int ai, aj, bi, b;

  ai = 0;
  for (bi = k0; bi < bn; bi++) {
    if (ai >= an) return bi - k0;
    b = bis[bi];
    aj = ai;
    while (aj < an && ais[aj] != b) aj++;
    if (aj >= an) return bi - k0;
    ai = aj + 1;
  }

  return bn - k0;
}

/* main */

int main(int argc, char **argv) {
  int an, bn, i, k0, len, max_len;

  scanf("%d", &an);
  scanf("%d", &bn);

  for (i = 0; i < an; i++) scanf("%d", ais + i);
  for (i = 0; i < bn; i++) scanf("%d", bis + i);

  max_len = 0;

  for (k0 = 0; k0 < bn; k0++) {
    if (k0 + max_len > bn) break;

    len = get_len(an, bn, ais, bis, k0);
    if (max_len < len) max_len = len;
  }

  printf("%d\n", max_len);

  return 0;
}