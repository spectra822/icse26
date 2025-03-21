// AOJ 1258: Book Replacement
// 2017.10.22 bal4u@uu

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct { int stu, seq, id; } T;
T req[5002]; int len;
int desk[12][5001]; int hi[12];
int book[101][2];

int cmp(T *a, T *b)
{
	if (a->seq - b->seq) return (a->seq - b->seq);
	return a->stu - b->stu;
}

int main()
{
	int m, c, n, i, j, id, ans;
	int from, pos, tmp, id2, t;

	while (scanf("%d%d%d", &m, &c, &n) && m > 0) {
		memset(hi, 0, sizeof(hi)), memset(book, 0, sizeof(book));
		tmp = m + 1;
		for (len = i = 0; i < n; i++) {
			scanf("%d", &t); 
			for (j = 0; j < t; j++) {
				scanf("%d", &id);
				req[len].stu = i, req[len].seq = j, req[len++].id = id;
				if (book[id][0] == 0) {
					book[id][0] = tmp, book[id][1] = hi[tmp], desk[tmp][hi[tmp]++] = id;
				}
			}
		}
		qsort(req, len, sizeof(T), cmp);

		for (ans = 0, i = 0; i < len; i++) {
			id = req[i].id;
			from = book[id][0], pos = book[id][1];

			for (j = pos+1; j < hi[from]; j++) {
				t = desk[from][j], book[t][1]--;
				desk[from][j-1] = desk[from][j];
			}
			hi[from]--, ans += from;

			if (hi[1] == c) {
				for (tmp = 2; tmp <= m && hi[tmp] == c; tmp++);
				desk[tmp][hi[tmp]++] = id, ans += tmp;

				id2 = desk[1][0];
				for (j = 1; j < hi[1]; j++) {
					t = desk[1][j], book[t][1]--;
					desk[1][j-1] = desk[1][j];
				}
				hi[1]--, ans++;

				for (j = 2; j <= m && hi[j] == c; j++);
				pos = hi[j]; if (j == tmp) pos--;
				desk[j][pos] = id2; hi[j]++;
				book[id2][0] = j, book[id2][1] = pos;
				ans += j + tmp; hi[tmp]--;
			}
			
			book[id][0] = 1, book[id][1] = hi[1];
			desk[1][hi[1]++] = id, ans++;
		}
		printf("%d\n", ans);
	}
	return 0;
}