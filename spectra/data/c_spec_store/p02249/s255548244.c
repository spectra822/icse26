// AOJ ALDS1_14_C Pattern Search
// 2018.5.13 bal4u

#include <stdio.h>
#include <string.h>

#if 1
#define gc() getchar_unlocked()
#else
#define gc() getchar()
#endif

int in()
{
	int n = 0, c = gc();
	do n = 10*n + (c & 0xf), c = gc(); while (c >= '0');
	return n;
}

#define MOD 1000000007LL
#define C1  401
#define C2  397

#define MAX_L 1005
char text[MAX_L][MAX_L]; int H, W;
char pat[MAX_L][MAX_L]; int R, C;
int  a[MAX_L][MAX_L], b[MAX_L][MAX_L];
int  t[MAX_L][MAX_L];

void genHash(int res[MAX_L][MAX_L], char s[MAX_L][MAX_L], int h, int w)
{
	int r, c;
	long long x, y, k;

	memset(t, 0, sizeof(t));
	memset(res, 0, sizeof(res));

	x = 1, y = 1;
	for (c = 0; c < C; c++) x = (x*C1) % MOD;
	for (r = 0; r < R; r++) y = (y*C2) % MOD;

	for (r = 0; r < h; r++) {
		k = 0;
		for (c = 0; c < C; c++) k = (k*C1 + s[r][c]) % MOD;
		for (c = 0; c <= w-C; c++) {
			t[r][c] = (int)k;
			if (c + C < w) k = (k*C1-s[r][c]*x+s[r][c+C]) % MOD;
			if (k < 0) k += MOD;
		}
	}

	for (c = 0; c < w; c++) {
		k = 0;
		for (r = 0; r < R; r++) k = (k*C2+t[r][c]) % MOD;
		for (r = 0; r <= h-R; r++) {
			res[r][c] = (int)k;
			if (r+R < h) k = (k*C2-t[r][c]*y+t[r+R][c]) % MOD;
			if (k < 0) k += MOD;
		}
	}
}

int main()
{
	int r, c;
	char ch, *p;

	H = in(), W = in();
	for (r = 0; r < H; r++) {
		p = text[r];
		while ((ch = gc()) > ' ') *p++ = ch;
		*p = 0;
	}

	R = in(), C = in();
	for (r = 0; r < R; r++) {
		p = pat[r];
		while ((ch = gc()) > ' ') *p++ = ch;
		*p = 0;
	}

	genHash(a, text, H, W);
	genHash(b, pat, R, C);

	for (r = 0; r <= H-R; r++) for (c = 0; c <= W-C; c++) {
		if (a[r][c] == b[0][0]) printf("%d %d\n", r, c);
	}
	return 0;
}
