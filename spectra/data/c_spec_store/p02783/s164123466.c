#include <stdio.h>

int main () {
	int a, b, c;
	scanf ("%d %d", &a, &b);
	c = a/b;
	if (a % b != 0) {
		c++;
	}
	printf ("%d\n", c);
}