#include <stdio.h>
#define N_MAX 100000
#define L_MAX 20
void fill(int *a, int l, int r, int x) {
	for(int i = l; i <= r; ++i) {
		a[i] = x;
	}
	return;
}
int find_root(int *a, int x) {
	int s[L_MAX + 1];
	int k = 0;
	while(a[x] >= 1) {
		s[++k] = x;
		x = a[x];
	}
	while(k) {
		a[s[k--]] = x;
	}
	return x;
}
void unite_set(int *a, int x, int y) {
	x = find_root(a, x);
	y = find_root(a, y);
	if(a[x] < a[y]) {
		a[x] += a[y];
		a[y] = x;
	} else {
		a[y] += a[x];
		a[x] = y;
	}
	return;
}
int set_size(int *a, int x) {
	return -a[find_root(a, x)];
}
int main(int argc, char **argv) {
	int n, m, k;
	scanf("%i%i%i", &n, &m, &k);
	int s[N_MAX + 1];
	fill(s, 1, n, -1);
	int rmv[N_MAX + 1];
	fill(rmv, 1, n, 1);
	while(m--) {
		int a, b;
		scanf("%i%i", &a, &b);
		if(find_root(s, a) != find_root(s, b)) {
			unite_set(s, a, b);
		}
		++rmv[a];
		++rmv[b];
	}
	while(k--) {
		int c, d;
		scanf("%i%i", &c, &d);
		if(find_root(s, c) == find_root(s, d)) {
			++rmv[c];
			++rmv[d];
		}
	}
	for(int i = 1; i <= n; ++i) {
		printf("%i%c", set_size(s, i) - rmv[i], i == n ? '\n' : ' ');
	}
	return 0;
}