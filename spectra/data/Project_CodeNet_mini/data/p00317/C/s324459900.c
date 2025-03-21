// AOJ 0322: Slates
// 2019.2.24 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#if 1
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif
int in()
{
	int n = 0, c = gc();
	do n = 10 * n + (c & 0xf), c = gc(); while (c >= '0');
	return n;
}

int ins(char *s, char *r)
{
	char *ss = s;
	int n;

	do *s = gc();
	while (*s++ > ' ');
	*--s = 0;
	n = s - ss;
	while (--s >= ss) *r++ = *s;
	*r = 0;
	return n;
}

int N;
char W[50003][205], R[50003][205];
char *w[50003], *r[50003];
char slate[205], res[205];

int cmp(const void *a, const void *b)
{
	return strcmp(*(char **)a, *(char **)b);
}

// Binary Search
int search(char *s, int n, int idx, int part)
{
	int k, mid, low, high;

	low = 0, high = N;
	if (part) {
		while (low < high) {
			mid = (low + high) >> 1;
			if (strncmp(idx ? r[mid] : w[mid], s, n) <= 0) low = mid + 1; else high = mid;
		}
		k = low - 1;
		low = 0, high = N;
		while (low < high) {
			mid = (low + high) >> 1;
			if (strncmp(idx ? r[mid] : w[mid], s, n) < 0) low = mid + 1; else high = mid;
		}
		return k - low + 1;
	}
	else {
		while (low < high) {
			mid = (low + high) >> 1;
			k = strcmp(idx ? r[mid] : w[mid], s);
			if (!k) return 1;
			if (k < 0) low = mid + 1; else high = mid;
		}
	}
	return 0;
}

int main()
{
	int M, i, k, n, one, ans, part, f_res;
	char *s;

	N = in(), M = in(), one = 0;
	for (i = 0; i < N; i++)
		if (ins(w[i] = W[i], r[i] = R[i]) == 1) one++;
	qsort(w, N, sizeof(char *), cmp);
	qsort(r, N, sizeof(char *), cmp);

	while (M--) {
		n = ins(slate, res);
		for (k = 0; k < n; k++) if (slate[k] == '?') break;
		part = f_res = 0, s = slate;
		if (res[0] == '*') {
			slate[--n] = 0, part = 1;
			if (k >= n) k = -1;
		}
		else if (slate[0] == '*') {
			res[--n] = 0, part = 1, s = res, f_res = 1;
			if (k >= n+1) k = -1;
			else k = n - k;
		}
		else if (k >= n) k = -1;

		if (k >= 0) {
			if (n == 1) ans = part ? N : one;
			else {
				ans = 0; for (i = 'a'; i <= 'z'; i++) {
					s[k] = i;
					ans += search(s, n, f_res, part);
				}
			}
		} else ans = search(s, n, f_res, part);
		printf("%d\n", ans);
	}
	return 0;
}

