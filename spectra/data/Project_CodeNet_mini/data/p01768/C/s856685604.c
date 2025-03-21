#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) (((a) < (b)) ? (a) : (b))

#define INIT_CAP 10

typedef struct {
	int *to, cap, size;
} AdjList;

typedef struct {
	char name[11];
	int cost;
} Rec;

int n;
AdjList adj[5000];
Rec ing[5000];

void init(int n) {
	int i;
	for (i = 0; i < n; i++) {
		adj[i].to = malloc(sizeof(int) * INIT_CAP);
		adj[i].cap = INIT_CAP;
		adj[i].size = 0;
	}
}

void add(int from, int to) {
	if (adj[from].size == adj[from].cap) {
		adj[from].cap <<= 1;
		adj[from].to = realloc(adj[from].to, sizeof(int) * adj[from].cap);
	}
	adj[from].to[adj[from].size++] = to;
}

int searchIdx(char str[]) {
	int i;

	for (i = 0; i < n; i++)
		if (!strcmp(str, ing[i].name))
			break;

	return i;
}

int min, visited[5000];

void dfs(int i) {
	int j;

	visited[i] = 1;
	min = min(min, ing[i].cost);

	for (j = 0; j < adj[i].size; j++) {
		int to = adj[i].to[j];
		if (!visited[to])
			dfs(to);
	}
}

int searchMinCost(int i) {
	min = 100000;
	memset(visited, 0, sizeof visited);

	dfs(i);

	return ing[i].cost = min;
}

int main(void) {
	int i;
	int m;
	int ans;

	scanf("%d", &n);
	for (i = 0; i < n; i++)
		scanf("%s %d", ing[i].name, &ing[i].cost);

	scanf("%d", &m);
	init(n);
	while (m--) {
		char s[11], t[11];
		int idx_s, idx_t;

		scanf("%s %s", s, t);
		idx_s = searchIdx(s);
		idx_t = searchIdx(t);

		add(idx_s, idx_t);
		add(idx_t, idx_s);
	}

	ans = 0;
	for (i = 0; i < n; i++)
		ans += searchMinCost(i);

	printf("%d\n", ans);

	return 0;
}