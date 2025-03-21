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
	int i, N, M;
	char S[52][52] = {};
	scanf("%d %d", &N, &M);
	for (i = 1; i <= N; i++) scanf("%s", &(S[i][1]));

	int j, k, l, m = 0, n = 1, dist[2501], q[2501], head, tail;
	list *adj[2603] = {}, d[30000];
	edge e[30000];
	for (i = N; i >= 1; i--) {
		for (j = M; j >= 1; j--) {
			if (S[i][j] != 'o') continue;
			else S[i][j] = '.';
			for (k = 1; k <= N * M; k++) dist[k] = -1;
			q[0] = (i - 1) * M + j;
			dist[q[0]] = 0;
			for (head = 0, tail = 1; head < tail; head++) {
				k = (q[head] - 1) / M + 1;
				l = (q[head] - 1) % M + 1;
				if (S[k+1][l] == '.' && dist[k*M+l] == -1) {
					dist[k*M+l] = dist[q[head]] + 1;
					q[tail++] = k * M + l;
				}
				if (S[k][l+1] == '.' && dist[(k-1)*M+l+1] == -1) {
					dist[(k-1)*M+l+1] = dist[q[head]] + 1;
					q[tail++] = (k - 1) * M + l + 1;
				}
			}
			for (head--; head >= 0 && head >= tail - 100; head--) {
				e[m*2].id = m * 2;
				e[m*2].tail = N * M + n;
				e[m*2].head = q[head];
				e[m*2].cap = 1;
				e[m*2].cost = -dist[q[head]];
				e[m*2+1].id = m * 2 + 1;
				e[m*2+1].tail = q[head];
				e[m*2+1].head = N * M + n;
				e[m*2+1].cap = 0;
				e[m*2+1].cost = dist[q[head]];
				d[m*2].e = &(e[m*2]);
				d[m*2+1].e = &(e[m*2+1]);
				d[m*2].next = adj[N*M+n];
				d[m*2+1].next = adj[q[head]];
				adj[N*M+n] = &(d[m*2]);
				adj[q[head]] = &(d[m*2+1]);
				m++;
			}
			n++;
		}
	}
	for (i = 1; i < n; i++) {
		e[m*2].id = m * 2;
		e[m*2].tail = N * M + n;
		e[m*2].head = N * M + i;
		e[m*2].cap = 1;
		e[m*2].cost = 0;
		e[m*2+1].id = m * 2 + 1;
		e[m*2+1].tail = N * M + i;
		e[m*2+1].head = N * M + n;
		e[m*2+1].cap = 0;
		e[m*2+1].cost = 0;
		d[m*2].e = &(e[m*2]);
		d[m*2+1].e = &(e[m*2+1]);
		d[m*2].next = adj[N*M+n];
		d[m*2+1].next = adj[N*M+i];
		adj[N*M+n] = &(d[m*2]);
		adj[N*M+i] = &(d[m*2+1]);
		m++;
	}
	for (i = 1; i <= N * M; i++) {
		e[m*2].id = m * 2;
		e[m*2].tail = i;
		e[m*2].head = N * M + n + 1;
		e[m*2].cap = 1;
		e[m*2].cost = 0;
		e[m*2+1].id = m * 2 + 1;
		e[m*2+1].tail = N * M + n + 1;
		e[m*2+1].head = i;
		e[m*2+1].cap = 0;
		e[m*2+1].cost = 0;
		d[m*2].e = &(e[m*2]);
		d[m*2+1].e = &(e[m*2+1]);
		d[m*2].next = adj[i];
		d[m*2+1].next = adj[N*M+n+1];
		adj[i] = &(d[m*2]);
		adj[N*M+n+1] = &(d[m*2+1]);
		m++;
	}
	
	int b[2603] = {};
	b[N*M+n] = -(n - 1);
	b[N*M+n+1] = n - 1;
	printf("%lld\n", -succesive_shortest_path(N * M + n + 1, m * 2, adj, e, b));
	fflush(stdout);
	return 0;
}