// AOJ 1070 FIMO sequence
// 2018.3.22 bal4u

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//#define getchar_unlocked()  getchar()
int in()
{
	int n = 0, c = getchar_unlocked();
while (c < '0') c = getchar_unlocked();
	do n = 10*n + (c & 0xf), c = getchar_unlocked(); while (c >= '0');
	return n;
}

#define FH   0        // First half
#define SH   1        // Second half
#define ALL  2
#define MAX 200005

int que[2][MAX]; int qt[2], qe[2];
int min[2][MAX]; int at[2], ae[2];
int max[2][MAX]; int zt[2], ze[2];
#define size(id)  (qe[id]-qt[id])
#define minSZ(id) (ae[id]-at[id])
#define maxSZ(id) (ze[id]-zt[id])

int del(int id);
void add(int id, int a)
{
	if (id == ALL) {
		add(SH, a);
		if (size(FH) < size(SH)) add(FH, del(SH));
		return;
	}
	que[id][qe[id]++] = a;
	if (size(id) == 1) {
		min[id][ae[id]++] = a, max[id][ze[id]++] = a;
	} else if (id == FH) {
		if (min[id][ae[id]-1] > a) min[id][ae[id]++] = a;
		if (max[id][ze[id]-1] < a) max[id][ze[id]++] = a;
	} else {
		while (minSZ(id) > 0 && min[id][ae[id]-1] > a) ae[id]--;
		while (maxSZ(id) > 0 && max[id][ze[id]-1] < a) ze[id]--;
		min[id][ae[id]++] = a, max[id][ze[id]++] = a;
	}
}

int del(int id)
{
	int a;
	if (id == ALL) {
		a = del(FH);
		if (size(FH) < size(SH)) add(FH, del(SH));
	} else if (id == FH) {
		a = que[id][--qe[id]];
		if (min[id][ae[id]-1] == a) ae[id]--;
		if (max[id][ze[id]-1] == a) ze[id]--;
	} else {
		a = que[id][qt[id]++];
		if (min[id][at[id]] == a) at[id]++;
		if (max[id][zt[id]] == a) zt[id]++;
	}
	return a;
}

int gmin(int id, int th)
{
	if (id == FH) return min[id][ae[id]-th];
	else          return min[id][at[id]+th-1];
}

int gmax(int id, int th)
{
	if (id == FH) return max[id][ze[id]-th];
	else          return max[id][zt[id]+th-1];
}

int main()
{
	int q, op, a;

    while (q = in()) {
		qt[FH] = qt[SH] = qe[FH] = qe[SH] = 0;
		at[FH] = at[SH] = ae[FH] = ae[SH] = 0;
		zt[FH] = zt[SH] = ze[FH] = ze[SH] = 0;

		while (q--) {
			op = in();
			if      (op == 0) { add(ALL, in()); continue; }
			else if (op == 1) a = del(ALL);
			else if (op == 2) a = gmin(FH, 1);
			else if (op == 3) a = gmin(SH, 1);
			else if (op == 4) a = gmin(FH, in());
			else if (op == 5) a = gmin(SH, in());
			else if (op == 6) a = gmax(FH, 1);
			else if (op == 7) a = gmax(SH, 1);
			else if (op == 8) a = gmax(FH, in());
			else              a = gmax(SH, in());
			printf("%d\n", a);
		}
		puts("end");
	}
	return 0;
}
