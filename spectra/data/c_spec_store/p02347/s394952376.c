#include <stdio.h>          // printf(), scanf()
#include <stdlib.h>         // qsort()

#define MAX_N 1000000
static const int nil = -1;

typedef struct point_tbl
{
	int id;
	int x, y;
} point;

typedef struct node_tbl
{
	int location;
	int l, r;
} node;

point p[MAX_N];
node t[MAX_N];
int pid[MAX_N];
int n;
int np;
int n_pid;

int
cmpx_func(const void *l_, const void *r_)
{
	const point* l = (const point*) l_;
	const point* r = (const point*) r_;

	if (l->x < r->x)
		return -1;

	if (l->x > r->x)
		return 1;

	return 0;
}

int
cmpy_func(const void *l_, const void *r_)
{
	const point* l = (const point*) l_;
	const point* r = (const point*) r_;

	if (l->y < r->y)
		return -1;

	if (l->y > r->y)
		return 1;

	return 0;
}

int
makeKDTree(int l, int r, int depth)
{
	if (l >= r)
		return nil;

	if (r - l >= 2)
	{
		if (depth % 2 == 0)
			qsort(&p[l], r - l, sizeof(point), cmpx_func);
		else
			qsort(&p[l], r - l, sizeof(point), cmpy_func);
	}

	int mid = (l + r) / 2;
	int s = np++;
	t[s].location = mid;
	t[s].l = makeKDTree(l, mid, depth + 1);
	t[s].r = makeKDTree(mid + 1, r, depth + 1);
	return s;
}

void
find(int v, int sx, int tx, int sy, int ty, int depth)
{
	int x = p[t[v].location].x;
	int y = p[t[v].location].y;

	if (sx <= x && x <= tx && sy <= y && y <= ty)
		pid[n_pid++] = p[t[v].location].id;

	if (depth % 2 == 0)
	{
		if (t[v].l != nil)
		{
			if (sx <= x)
				find(t[v].l, sx, tx, sy, ty, depth + 1);
		}

		if (t[v].r != nil)
		{
			if (x <= tx)
				find(t[v].r, sx, tx, sy, ty, depth + 1);
		}
	}
	else
	{
		if (t[v].l != nil)
		{
			if (sy <= y)
				find(t[v].l, sx, tx, sy, ty, depth + 1);
		}

		if (t[v].r != nil)
		{
			if (y <= ty)
				find(t[v].r, sx, tx, sy, ty, depth + 1);
		}
	}
}

int
cmpi_func(const void *l_, const void *r_)
{
	const int* l = (const int*) l_;
	const int* r = (const int*) r_;

	if (*l < *r)
		return -1;

	if (*l > *r)
		return 1;

	return 0;
}

int
main(int argc, char** argv)
{
	int x, y;
	int sx, sy;
	int tx, ty;
	int q;
	int i, j;

	scanf("%d", &n);
	for (i = 0; i < n; ++i)
	{
		scanf("%d %d", &x, &y);
		p[i].id = i;
		p[i].x = x;
		p[i].y = y;
		t[i].l = t[i].r = nil;
	}

	np = 0;
	int root = makeKDTree(0, n, 0);

	scanf("%d", &q);
	for (i = 0; i < q; ++i)
	{
		scanf("%d %d %d %d", &sx, &tx, &sy, &ty);
		n_pid = 0;
		find(root, sx, tx, sy, ty, 0);
		qsort(pid, n_pid, sizeof(int), cmpi_func);

		for (j = 0; j < n_pid; ++j)
			printf("%d\n", pid[j]);

		printf("\n");
	}

	return 0;
}