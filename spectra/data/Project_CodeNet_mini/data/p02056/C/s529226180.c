#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<inttypes.h>

typedef int32_t i32;
typedef int64_t i64;

typedef struct binary_heap {
  void *array;
  size_t heap_size;
  size_t max_size;
  size_t val_size;
  int (*cmp) (const void *, const void *);
} heap;

heap* new_binary_heap (const size_t val_size, int (*cmp_func) (const void *, const void *)) {
  heap *h = (heap *) calloc (1, sizeof (heap));
  h->array = malloc (val_size * (1 + 1));
  h->heap_size = 0;
  h->max_size = 1;
  h->val_size = val_size;
  h->cmp = cmp_func;
  return h;
}

int is_empty (const heap *h) {
  return h->heap_size == 0;
}

static inline void heap_func_swap (void * restrict a, void * restrict b, size_t val_size) {
  if ((val_size & 7) == 0) {
    uint64_t *p = (uint64_t *) a;
    uint64_t *q = (uint64_t *) b;
    val_size /= sizeof (uint64_t);
    while (val_size--) {
      const uint64_t tmp = *p;
      *p++ = *q;
      *q++ = tmp;
    }
  } else {
    uint8_t *p = (uint8_t *) a;
    uint8_t *q = (uint8_t *) b;
    while (val_size--) {
      const uint8_t tmp = *p;
      *p++ = *q;
      *q++ = tmp;
    }
  }
}

static inline void heap_func_copy (void * restrict dst, const void * restrict src, size_t val_size) {
  if ((val_size & 7) == 0) {
    const uint64_t *p = (const uint64_t *) src;
    uint64_t *q = (uint64_t *) dst;
    val_size /= sizeof (uint64_t);
    while (val_size--) {
      *q++ = *p++;
    }
  } else {
    const uint8_t *p = (const uint8_t *) src;
    uint8_t *q = (uint8_t *) dst;
    while (val_size--) {
      *q++ = *p++;
    }
  }
}

void push (heap * const h, const void *val) {
  if (h->heap_size == h->max_size) {
    h->max_size = 2 * h->max_size + 1;
    h->array = realloc (h->array, h->val_size * (h->max_size + 1));
  }
  h->heap_size++;
  uint8_t * const array = (uint8_t *) h->array;
  size_t k = h->heap_size;
  const size_t val_size = h->val_size;
  int (* const cmp) (const void *, const void *) = h->cmp;
  heap_func_copy(array + k * val_size, val, val_size);
  while (k > 1) {
    size_t parent = k / 2;
    if (cmp (array + parent * val_size, array + k * val_size) <= 0) {
      return;
    }
    heap_func_swap (array + parent * val_size, array + k * val_size, val_size);
    k = parent;
  }
}

void pop (heap * const h, void *res) {
  uint8_t * const array = (uint8_t *) h->array;
  const size_t val_size = h->val_size;
  if (res != NULL) {
    heap_func_copy (res, array + val_size, val_size);
  }
  heap_func_copy (array + val_size, array + val_size * h->heap_size, val_size);
  h->heap_size--;
  int (* const cmp) (const void *, const void *) = h->cmp;
  const size_t n = h->heap_size;
  size_t k = 1;
  while (2 * k  + 1 <= n) {
    const int c = cmp (array + val_size * 2 * k, array + val_size * (2 * k + 1));
    const size_t next = 2 * k + (c <= 0 ? 0 : 1);
    if (cmp (array + val_size * k, array + val_size * next) <= 0) return;
    heap_func_swap (array + val_size * k, array + val_size * next, val_size);
    k = next;
  }
  if (2 * k <= n && cmp (array + val_size * k, array + val_size * 2 * k) > 0) {
    heap_func_swap (array + val_size * k, array + val_size * 2 * k, val_size);
  }
}

typedef int32_t edge_weight;

typedef struct directed_edge {
  int32_t vertex;
  int32_t next;
  edge_weight cost;
} graph_edge;

typedef struct directedGraph {
  graph_edge *edge;
  int32_t *start;
  int32_t pointer;
  int32_t vertex_num;
  int32_t edge_max_size;
} graph;

graph* new_graph (const int vertex_num) {
  graph *g = (graph *) calloc (1, sizeof (graph));
  g->edge = (graph_edge *) calloc (1, sizeof (graph_edge));
  g->start = (int32_t *) calloc (vertex_num, sizeof (int32_t));
  g->pointer = 0;
  g->vertex_num = vertex_num;
  g->edge_max_size = 1;
  for (int32_t i = 0; i < vertex_num; ++i) {
    g->start[i] = -1;
  }
  return g;
}

void add_edge (graph *g, int32_t from, int32_t to, edge_weight cost) {
  if (g->pointer == g->edge_max_size) {
    g->edge_max_size *= 2;
    g->edge = (graph_edge *) realloc (g->edge, sizeof (graph_edge) * g->edge_max_size);
  }
  g->edge[g->pointer] = (graph_edge) {to, g->start[from], cost};
  g->start[from] = g->pointer++;
}

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))
#define ALLOC(size,type) ((type*)calloc((size),sizeof(type)))

typedef struct node {
  i32 v;
  i64 d;
} node;

int cmp_node (const void *a, const void *b) {
  i64 d = ((node *)a)->d - ((node *)b)->d;
  return d == 0 ? 0 : d < 0 ? -1 : 1;
}

void run (void) {
  i32 n, m, k;
  scanf ("%" SCNi32 "%" SCNi32 "%" SCNi32, &n, &m, &k);
  i32 *p = ALLOC (3 * n, i32);
  i32 *c = p + n;
  i32 *t = c + n;
  for (i32 i = 0; i < 3 * n; ++i) {
    scanf ("%" SCNi32, p + i);
  }
  const i32 sup = 1000000000 + 1;
  graph *g = new_graph (2 * n);
  for (i32 i = 0; i < n; ++i) {
    add_edge (g, i, i + n, sup - p[i]);
  }
  while (m--) {
    i32 a, b, d;
    scanf ("%" SCNi32 "%" SCNi32 "%" SCNi32, &a, &b, &d);
    a--; b--;
    add_edge (g, a, b, d);
    add_edge (g, b, a, d);
    a += n; b += n;
    add_edge (g, a, b, d);
    add_edge (g, b, a, d);
  }
  i64 *dp = ALLOC (2 * n, i64);
  for (i32 i = 1; i < 2 * n; ++i) {
    dp[i] = (i64) 1000000001 * 2 * n;
  }
  heap *h = new_binary_heap (sizeof (node), cmp_node);
  push (h, &(node){0, 0});
  while (!is_empty (h)) {
    node t;
    pop (h, &t);
    if (t.d > dp[t.v]) continue;
    for (i32 p = g->start[t.v]; p != -1; p = g->edge[p].next) {
      i32 u = g->edge[p].vertex;
      i64 d = t.d + g->edge[p].cost;
      if (d >= dp[u]) continue;
      dp[u] = d;
      push (h, &(node){u, d});
    }
  }
  i64 *max = ALLOC (k + 1, i64);
  for (i32 i = 1; i <= k; ++i) {
    max[i] = 2 - (i64)1000000001 * 2 * n;
  }
  for (i32 i = 0; i < n; ++i) {
    i64 v = (sup - dp[i + n]) - dp[i] + t[i];
    max[c[i]] = MAX (max[c[i]], v);
  }
  for (i32 i = 1; i <= k; ++i) {
    printf ("%" PRIi64 "\n", max[i]);
  }
}

int main (void) {
  run();
  return 0;
}

