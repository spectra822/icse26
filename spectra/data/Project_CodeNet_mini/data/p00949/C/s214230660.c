// AOJ 1370 Hidden Anagrams
// 2018.2.8 bal4u

#include <stdio.h>
#include <string.h>

#define HASHSIZ		10007
typedef struct { short f[26]; } HASH;
HASH hash[HASHSIZ+2], *hashend = hash+HASHSIZ;			// Hash table

void insert(short *f)
{
	int i;
	unsigned long long k;
	HASH *tp;

	f[0]++;
	k = 0; for (i = 0; i < 26; i+=2) k = (k << 4) + f[i];
	tp = hash + (int)(k % HASHSIZ);
	while (tp->f[0]) {
		if (!memcmp(tp->f, f, 52)) goto done;
		if (++tp == hashend) tp = hash;
	}
	memcpy(tp->f, f, 52);
done:
	f[0]--;
}

int lookup(short *f)
{
	int i;
	unsigned long long k;
	HASH *tp;

	f[0]++;
	k = 0; for (i = 0; i < 26; i+=2) k = (k << 4) + f[i];
	tp = hash + (int)(k % HASHSIZ);
	while (tp->f[0]) {
		if (!memcmp(tp->f, f, 52)) { f[0]--; return 1; }
		if (++tp == hashend) tp = hash;
	}
	f[0]--;
	return 0;
}

char sa[4004]; int wa;
char sb[4004]; int wb;
short f[26];

int main()
 {
	int i, k, w;
	char *p, *q;

	fgets(p=sa, 4004, stdin); while (*p > ' ') *p -= 'a', p++; wa = p - sa;
	fgets(p=sb, 4004, stdin); while (*p > ' ') *p -= 'a', p++; wb = p - sb;
	w = wa; if (w > wb) w = wb;

    for (k = w; k > 0; k--) {
		memset(hash, 0, sizeof(hash));

		memset(f, 0, sizeof(f));
		p = sa; for (i = 0; i < k; i++) f[*p++]++;
		insert(f);

		i = wa - k, q = sa; while (i--) {
			f[*q++]--, f[*p++]++;
			insert(f);
		}

		memset(f, 0, sizeof(f));
		p = sb; for (i = 0; i < k; i++) f[*p++]++;
		if (lookup(f)) goto done;

		i = wb - k, q = sb; while (i--) {
			f[*q++]--, f[*p++]++;
			if (lookup(f)) goto done;
		}
    }
done:
	printf("%d\n", k);
    return 0;
}
