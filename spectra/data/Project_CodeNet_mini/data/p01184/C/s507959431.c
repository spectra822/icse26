// AOJ 2061: International Party
// 2017.11.8 bal4u@uu

#include <stdio.h>
#include <string.h>
#define TM 0
#if TM
#include <time.h>
#endif

#define HASHSIZ 61
typedef struct { char *s; int id; } HASH;
HASH hash[HASHSIZ+2], *hashend = hash+HASHSIZ;			// Hash table

int lookup(char *s)
{
	int w = strlen(s);
	int i = (101 * *s + 103 * *(s+w-1) + 107 * w) % HASHSIZ;
	HASH *tp = hash + i;

	while (tp->s != NULL) {
		if (!strcmp(tp->s, s)) return tp->id;
		if (++tp == hashend) tp = hash;
	}
	return -1;
}

int insert(char *s, int id)
{
	int w = strlen(s);
	int i = (101 * *s + 103 * *(s+w-1) + 107 * w) % HASHSIZ;
	HASH *tp = hash + i;

	while (tp->s != NULL) {
		if (!strcmp(tp->s, s)) return 0;
		if (++tp == hashend) tp = hash;
	}
	tp->s = s, tp->id = id;
	return 1;
}

int f[22], m;
char name[31][22]; int sz;

int check(int pat)
{
	int i, j, k, s;
	int g[6];

	for (i = 0; i < m; i++) {
		if (!(f[i] & pat)) return 0;
	}

	for (s = 0, k = pat, i = 0; k; i++, k >>= 1) if (k & 1) g[s++] = 1 << i;  
	for (i = 0; i < m; i++) {
		for (j = 0; j < s; j++) {
			if (g[j] & f[i]) g[j] |= f[i] & pat;
		}
	}
	for (k = g[0], i = 1; i < s; i++) if (g[i] & k) k |= g[i]; 
	return k == pat;
}

int main()
{
	int cno = 0, n, i, j, id, ans;
	char buf[22];
#if TM
	clock_t start, end;
	start = clock();
#endif

	while (scanf("%d%d", &n, &m) && n > 0) {
		if (cno++ > 0) putchar('\n');
		memset(hash, 0, sizeof(hash));
		memset(f, 0, sizeof(f));

		id = 1, sz = 0;
		while (n--) {
			scanf("%s", name[sz]);
			if (insert(name[sz], id)) sz++, id <<= 1;
		}

		for (i = 0; i < m; i++) {
			scanf("%d", &j);
			while (j--) {
				scanf("%s", buf);
				id = lookup(buf);
				f[i] |= id;
			}
		}

		ans = -1;
		for (i = 1; i <= 5; i++) {
			for (j = (1 << i) - 1; j < (1 << sz); ) {
				int x, y;
				if (check(j)) { ans = j, id = i; goto done; }
				x = j & ~(j - 1);
				y = j + x;
				j = (((j & ~y) / x) >> 1) | y;
			}
		}
done:	if (ans < 0) puts("Impossible");
		else {
			printf("%d\n", id);
			for (id = 1, i = 0; i < sz; i++, id <<= 1) {
				if (ans & id) puts(name[i]);
			}
		}
	}
#if TM
	end = clock();
	printf("time %lf\n", (double)(end-start)/CLOCKS_PER_SEC);
#endif
	return 0;
}