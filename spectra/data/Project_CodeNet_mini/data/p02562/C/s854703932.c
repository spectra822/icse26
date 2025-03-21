#include <stdio.h>
#include <stdlib.h>

typedef struct {
	long long key;
	int id;
} data;

typedef struct {
	data *obj;
	int size;
} min_heap;

void push(data x, min_heap* h)
{
	int i = ++(h->size), j = i >> 1;
	data tmp;
	h->obj[i] = x;
	while (j > 0) {
		if (h->obj[i].key < h->obj[j].key) {
			tmp = h->obj[j];
			h->obj[j] = h->obj[i];
			h->obj[i] = tmp;
			i = j;
			j >>= 1;
		} else break;
	}
}

data pop(min_heap* h)
{
	int i = 1, j = 2;
	data output = h->obj[1], tmp;
	h->obj[1] = h->obj[(h->size)--];
	while (j <= h->size) {
		if (j < h->size && h->obj[j^1].key < h->obj[j].key) j ^= 1;
		if (h->obj[j].key < h->obj[i].key) {
			tmp = h->obj[j];
			h->obj[j] = h->obj[i];
			h->obj[i] = tmp;
			i = j;
			j <<= 1;
		} else break;
	}
	return output;
}

typedef struct {
	int id, head, tail, flow, cap, cost;
} edge;

typedef struct List {
	struct List *next;
	edge *e;
} list;

const long long sup = (long long)1 << 60, inf = -sup;

long long succesive_shortest_path(int N, int M, list* adj[], edge e[], int b[])
{
	int i, j, k, u, w, *flag = (int*)malloc(sizeof(int) * (N + 1)), *def = (int*)malloc(sizeof(int) * (N + 1));
	long long ans = 0, *dist = (long long*)malloc(sizeof(long long) * (N + 1)), *pi = (long long*)malloc(sizeof(long long) * (N + 1));
	edge **prev = (edge**)malloc(sizeof(edge*) * (N + 1));
	list *p;
	data d;
	min_heap h_def, h_dist;
	h_def.size = 0;
	h_def.obj = (data*)malloc(sizeof(data) * (N + 1));
	h_dist.obj = (data*)malloc(sizeof(data) * (M * 2 + 1));
	for (i = 0; i < M; i++) ans += (long long)e[i].cost * e[i].flow;
	for (i = 1; i <= N; i++) pi[i] = sup;
	for (i = 1; i <= N; i++) {
		for (p = adj[i], def[i] = b[i]; p != NULL; p = p->next) def[i] += p->e->flow - e[(p->e->id)^1].flow;
		if (def[i] < 0) {
			d.key = def[i];
			d.id = i;
			push(d, &h_def);
			
			if (pi[i] == sup) {
				pi[i] = 0;
				for (j = 1; j <= N; j++) {
					for (k = 0, flag[0] = 0; k < M; k++) {
						if (e[k].flow == e[k].cap) continue;
						u = e[k].tail;
						w = e[k].head;
						if (pi[u] != sup && pi[w] > pi[u] + e[k].cost) {
							flag[0] = 1;
							pi[w] = pi[u] + e[k].cost;
						}
					}
					if (flag[0] == 0) break;
				}
				if (j > N) return inf;
			}
		}
	}
	
	int s, t, min;
	while (h_def.size > 0) {
		d = pop(&h_def);
		s = d.id;
		for (u = 1; u <= N; u++) {
			flag[u] = 0;
			dist[u] = sup;
			prev[u] = NULL;
		}
		dist[s] = 0;
		h_dist.size = 0;
		d.key = 0;
		d.id = s;
		push(d, &h_dist);
		
		while (h_dist.size > 0) {
			d = pop(&h_dist);
			u = d.id;
			if (flag[u] != 0) continue;
			else flag[u] = 1;
			
			for (p = adj[u]; p != NULL; p = p->next) {
				w = p->e->head;
				if (p->e->flow == p->e->cap) continue;
				else if (dist[w] > dist[u] + p->e->cost + pi[u] - pi[w]) {
					dist[w] = dist[u] + p->e->cost + pi[u] - pi[w];
					prev[w] = p->e;
					d.key = dist[w];
					d.id = w;
					push(d, &h_dist);
				}
			}
		}
		for (t = 1; t <= N; t++) if (dist[t] != sup && def[t] > 0) break;
		if (t > N) return sup;
		
		for (u = t, min = (-def[s] < def[t])? -def[s]: def[t]; prev[u] != NULL; u = prev[u]->tail) {
			if (min > prev[u]->cap - prev[u]->flow) min = prev[u]->cap - prev[u]->flow;
		}
		for (u = t; prev[u] != NULL; u = prev[u]->tail) {
			i = prev[u]->id;
			if (e[i^1].flow > 0) {
				e[i^1].flow -= min;
				e[i].cap -= min;
			} else {
				e[i].flow += min;
				e[i^1].cap += min;
			}
			ans += (long long)e[i].cost * min;
		}
		for (i = 1; i <= N; i++) if (dist[i] != sup) pi[i] += dist[i];
		
		def[s] += min;
		def[t] -= min;
		if (def[s] < 0) {
			d.key = def[s];
			d.id = s;
			push(d, &h_def);
		}
	}
	
	free(flag);
	free(dist);
	free(def);
	free(pi);
	free(prev);
	free(h_def.obj);
	free(h_dist.obj);
	return ans;
}

int main()
{
	int i, j, N, K, A[51][51] = {};
	scanf("%d %d", &N, &K);
	for (i = 1; i <= N; i++) {
		for (j = 1; j <= N; j++) scanf("%d", &(A[i][j]));
	}
	
	int k, u, w;
	list *adj[103] = {}, d[6000];
	edge e[6000];
	for (u = 1, k = 0; u <= N; u++) {
		for (w = N + 1; w <= N * 2; w++) {
			e[k*2].id = k * 2;
			e[k*2].tail = u;
			e[k*2].head = w;
			e[k*2].cap = 1;
			e[k*2].cost = -A[u][w-N];
			e[k*2+1].id = k * 2 + 1;
			e[k*2+1].tail = w;
			e[k*2+1].head = u;
			e[k*2+1].cap = 0;
			e[k*2+1].cost = A[u][w-N];
			d[k*2].e = &(e[k*2]);
			d[k*2+1].e = &(e[k*2+1]);
			d[k*2].next = adj[u];
			d[k*2+1].next = adj[w];
			adj[u] = &(d[k*2]);
			adj[w] = &(d[k*2+1]);
			k++;
		}
	}
	for (w = 1, u = N * 2 + 1; w <= N; w++) {
		e[k*2].id = k * 2;
		e[k*2].tail = u;
		e[k*2].head = w;
		e[k*2].cap = K;
		e[k*2].cost = 0;
		e[k*2+1].id = k * 2 + 1;
		e[k*2+1].tail = w;
		e[k*2+1].head = u;
		e[k*2+1].cap = 0;
		e[k*2+1].cost = 0;
		d[k*2].e = &(e[k*2]);
		d[k*2+1].e = &(e[k*2+1]);
		d[k*2].next = adj[u];
		d[k*2+1].next = adj[w];
		adj[u] = &(d[k*2]);
		adj[w] = &(d[k*2+1]);
		k++;
	}
	for (u = N + 1, w = N * 2 + 2; u <= N * 2; u++) {
		e[k*2].id = k * 2;
		e[k*2].tail = u;
		e[k*2].head = w;
		e[k*2].cap = K;
		e[k*2].cost = 0;
		e[k*2+1].id = k * 2 + 1;
		e[k*2+1].tail = w;
		e[k*2+1].head = u;
		e[k*2+1].cap = 0;
		e[k*2+1].cost = 0;
		d[k*2].e = &(e[k*2]);
		d[k*2+1].e = &(e[k*2+1]);
		d[k*2].next = adj[u];
		d[k*2+1].next = adj[w];
		adj[u] = &(d[k*2]);
		adj[w] = &(d[k*2+1]);
		k++;
	}
	
	int b[103] = {}, argmax = 0;
	long long max = 0, tmp;
	for (i = 1; i <= N * K; i++) {
		b[N*2+1] = -i;
		b[N*2+2] = i;
		tmp = -succesive_shortest_path(N * 2 + 2, k * 2, adj, e, b);
		if (tmp != sup && max < tmp) {
			max = tmp;
			argmax = i;
		}
	}
	printf("%lld\n", max);
	
	char ans[52][52];
	for (i = 1; i <= N; i++) for (j = 1; j <= N; j++) ans[i][j] = '.';
	b[N*2+1] = -argmax;
	b[N*2+2] = argmax;
	for (j = 0; j < k; j++) {
		e[j*2].flow = 0;
		e[j*2+1].cap = 0;
	}
	succesive_shortest_path(N * 2 + 2, k * 2, adj, e, b);
	for (j = 0; j < k; j++) {
		u = e[j*2].tail;
		w = e[j*2].head;
		if (u <= N && w <= N * 2 && e[j*2].flow == 1) ans[u][w-N] = 'X';
	}
	for (i = 1; i <= N; i++) printf("%s\n", &(ans[i][1]));
	fflush(stdout);
	return 0;
}