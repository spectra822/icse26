// AOJ 1634 Balance Scale
// bal4u 2019.8.12

#include <stdio.h>
#include <string.h>

//// 入出力関係
#if 1
#define gc() getchar_unlocked()
#define pc(c) putchar_unlocked(c)
#else
#define gc() getchar()
#define pc(c) putchar(c)
#endif

int in() {   // 非負整数の入力
	int n = 0, c = gc();
	do n = 10 * n + (c & 0xf); while ((c = gc()) >= '0');
	return n;
}

void out(int n) { // 整数の表示（出力）
	int i;
	char b[20];

	if (!n) pc('0');
	else {
		if (n < 0) pc('-'), n = -n;
		i = 0; while (n) b[i++] = n % 10 + '0', n /= 10;
		while (i--) pc(b[i]);
		
	}
	pc('\n');
}

//// ハッシュ関数
#define HASHSIZ 1000003
typedef struct { int n, b; } HA;
int ha1[HASHSIZ+5], *hae1 = ha1 + HASHSIZ;
HA  ha2[HASHSIZ+5], *hae2 = ha2 + HASHSIZ;

int lookup1(int n) {
	int *p = ha1 + n % HASHSIZ;
	while (*p) {
		if (*p == n) return 1;
		if (++p == hae1) p = ha1;
	}
	return 0;
}

void insert1(int n) {
	int *p = ha1 + n % HASHSIZ;
	while (*p) {
		if (*p == n) return;
		if (++p == hae1) p = ha1;
	}
	*p = n;
}

int lookup2(int n, int b) {
	HA *p = ha2 + n % HASHSIZ;
	while (p->n) {
		if (p->n == n) {
			if (p->b == b-1) { p->b = b; return 1; }
			return 0;
		}
		if (++p == ha2) p = ha2;
	}
	return 0;
}

void insert2(int n) {
	HA *p = ha2 + n % HASHSIZ;
	while (p->n) {
		if (p->n == n) return;
		if (++p == ha2) p = ha2;
	}
	p->n = n, p->b = 1;
}

//// 本問題関連
#define INF 0x7fffffff
#define ABS(x)  ((x)>=0?(x):-(x))
int q[60000];   // 3^10
int a[102];
int w[12];
		
int main()
{
	int n, m, i, j, end, x, ans;
	
	while (n = in()) {
		m = in();
		for (i = 0; i < n; i++) a[i] = in();
		for (i = 0; i < m; i++) w[i] = in();
		q[0] = 0, end = 1;
		for (i = 0; i < m; i++) {
			int e = end;
			for (j = 0; j < e; j++) {
				q[end++] = q[j] + w[i];
				q[end++] = q[j] - w[i];
			}
		}
		memset(ha1, 0, sizeof(ha1));
		for (i = 0; i < end; i++) if (q[i] > 0) insert1(q[i]);
		x = 0, ans = 0; for (i = 0; i < n; i++) if (!lookup1(a[i])) {
			if (x == 0) {
				int t; ans = INF;
				memset(ha2, 0, sizeof(ha2));
				for (j = 0; j < end; j++) {
					if ((t = ABS(a[i]-q[j])) < ans) ans = t;
					insert2(t);
				}
				x = 1;
			} else {
				int t, r = 0; x++, ans = INF;
				for (j = 0; j < end; j++) {
					t = ABS(a[i]-q[j]);
					if (lookup2(t, x)) {
						if (t < ans) ans = t;
						r = 1;
					}
				}
				if (r == 0) { ans = -1; break; }
			}
		}
		out(ans);
	}
	return 0;
}
