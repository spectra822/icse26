#include<stdio.h>
int a[400005], b[400005];
int h[400005], l;
int comp_h(int x, int y)
{
	if (a[h[x]] > a[h[y]])
		return 1;
	else
		return -1;
}
void swap_h(int x, int y)
{
	int f = h[x];
	h[x] = h[y];
	h[y] = f;
	return;
}
void push(int ne)
{
	h[l] = ne;
	int p = l;
	l++;
	for (; p > 0; p = (p - 1) / 2)
		if (comp_h((p - 1) / 2, p) > 0)
			swap_h((p - 1) / 2, p);
	return;
}
int pop()
{
	l--;
	swap_h(0, l);
	int p = 0;
	for (;;)
	{
		if (2 * p + 2 < l)
		{
			if (comp_h(2 * p + 1, 2 * p + 2) > 0)
			{
				if (comp_h(p, 2 * p + 2) > 0)
					swap_h(p, 2 * p + 2);
				p = 2 * p + 2;
			}
			else
			{
				if (comp_h(p, 2 * p + 1) > 0)
					swap_h(p, 2 * p + 1);
				p = 2 * p + 1;
			}
		}
		else if (2 * p + 1 < l)
		{
			if (comp_h(p, 2 * p + 1) > 0)
				swap_h(p, 2 * p + 1);
			p = 2 * p + 1;
		}
		else
			break;
	}
	return h[l];
}
int main()
{
	int n;
	scanf("%d", &n);
	int i;
	for (i = 0; i < n - 1; i++)
	{
		i *= 2;
		scanf("%d %d", &a[i], &b[i]);
		a[i]--;
		b[i]--;
		a[i + 1] = b[i];
		b[i + 1] = a[i];
		i /= 2;
	}
	l = 0;
	for (i = 0; i < 2 * n - 2; i++)
		push(i);
	int c[400005];
	for (i = 0; i < 2 * n - 2; i++)
		c[i] = pop();
	c[2 * n - 2] = 2 * n - 2;
	a[2 * n - 2] = -1;
	int depth[200005];
	for (i = 0; i < n; i++)
		depth[i] = -1;
	int min, mid, max;
	int q[200005];
	depth[0] = 1;
	q[0] = 0;
	l = 1;
	while (l > 0)
	{
		l--;
		i = q[l];
		min = -1;
		max = 2 * n - 2;
		while (max - min > 1)
		{
			mid = (max + min) / 2;
			if (a[c[mid]] < i)
				min = mid;
			else
				max = mid;
		}
		while (a[c[max]] == i)
		{
			if (depth[b[c[max]]] < 0)
			{
				depth[b[c[max]]] = depth[i] + 1;
				q[l] = b[c[max]];
				l++;
			}
			max++;
		}
	}
	int s = 0;
	for (i = 0; i < n; i++)
		if (depth[s] < depth[i])
			s = i;
	for (i = 0; i < n; i++)
		depth[i] = -1;
	depth[s] = 1;
	q[0] = s;
	l = 1;
	while (l > 0)
	{
		l--;
		i = q[l];
		min = -1;
		max = 2 * n - 2;
		while (max - min > 1)
		{
			mid = (max + min) / 2;
			if (a[c[mid]] < i)
				min = mid;
			else
				max = mid;
		}
		while (a[c[max]] == i)
		{
			if (depth[b[c[max]]] < 0)
			{
				depth[b[c[max]]] = depth[i] + 1;
				q[l] = b[c[max]];
				l++;
			}
			max++;
		}
	}
	max = 0;
	for (i = 0; i < n; i++)
		if (max < depth[i])
			max = depth[i];
	if ((max + 1) % 3 > 0)
		printf("First\n");
	else
		printf("Second\n");
	return 0;
}