// AOJ GRL_4_B Path/Cycle - Topological Sort
// 2018.4.26 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_V 10002
int V;   // 頂点数
int *to[MAX_V], hi[MAX_V];
int q[MAX_V], top, end;
int count[MAX_V];

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0;
	int c = getchar_unlocked();
	do n = (n<<3)+(n<<1) + (c & 0xf), c = getchar_unlocked();
	while (c >= '0');
	return n;
}

void topological_sort()
{
    int i, j, k;

//  for (i = 0; i < V; i++) for (j = 0; j < hi[i]; j++) count[to[i][j]]++;

    top = end = 0;
    for (i = 0; i < V; i++) if (!count[i]) q[end++] = i;
    while (top < end) {
		i = q[top++];
        printf("%d\n", i);
        for (j = 0; j < hi[i]; j++) {
            k = to[i][j];
            if (--count[k] == 0) q[end++] = k;
        }
    }
}

int main()
{
	int E, s, t, i, j;
	int *memo;

	V = in(), E = in();
	memo = malloc(E<<3);
	j = 0; for (i = 0; i < E; i++) {
		memo[j++] = s = in(), memo[j++] = t = in();
		hi[s]++;
	}
	for (i = 0; i < V; i++) if (hi[i]) to[i] = malloc(hi[i]<<2);
	memset(hi, 0, V<<2);
	j = 0; while (E--) {
		s = memo[j++], t = memo[j++];
		to[s][hi[s]++] = t;
		count[t]++;
	}

	topological_sort();
	return 0;
}
