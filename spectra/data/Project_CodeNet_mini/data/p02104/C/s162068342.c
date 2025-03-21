// AOJ 3006: Chairs
// 2017.10.4 bal4u@uu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX		100003
int p[MAX];
int sp[MAX], top;
int *q[MAX], hi[MAX];
int ans[MAX];

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

int main()
{
	int n, a, i, j;
	
	n = in();
	for (i = 1; i <= n; i++) {
		p[i] = a = in();
		hi[a]++;
	}
	for (i = 1; i <= n; i++) q[i] = malloc(hi[i]*sizeof(int));
	memset(hi, 0, (n+1)<<2);
	for (i = 1; i <= n; i++) {
		a = p[i];
		q[a][hi[a]++] = i;
	}

	top = 0;
	for (j = 0; j < 2; j++) for (i = 1; i <= n; i++) {
		while (hi[i]) sp[top++] = q[i][--hi[i]];
		if (!ans[i] && top) ans[i] = sp[--top];
    }
   
	for (i = 1; i <= n; i++) printf("%d\n", ans[i]);
	return 0;
}
