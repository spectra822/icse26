#include <stdio.h>

int get_uint() {
    int n = 0;
    int c = getchar_unlocked();
    if(c < 48 || 57 < c) return c;
    while(47 < c && c < 58) n = 10 * n + (c & 0xf), c = getchar_unlocked();
    return n;
}
void put_uint(int n) {
    if(!n) {
        putchar_unlocked('0');
        return;
    }
    char buf[11];
    int i = 0;
    while(n) buf[i++] = (char)(n % 10 + '0'), n /= 10;
    while(i--)putchar_unlocked(buf[i]);
}

typedef struct Node {
    int edge_to[100];
    int edge_cost[100];
    int edge_size;
    int cost;
    int visited;
} Node;
void dijkstra_noheap(Node *node, const int n) {
    for(int i = 0; i < n; ++i) node[i].cost = -1, node[i].visited = 0;
    node[0].cost = 0;
    while(1) {
        Node *next = NULL;
        for(Node *it = node; it != node + n; ++it) {
            if(it->visited || it->cost < 0) continue;
            if(next == NULL || it->cost < next->cost) next = it;
        }
        if(next == NULL) break;
        next->visited = 1;
        Node u = *next;
        for(int i = 0; i < u.edge_size; ++i) {
            int to = u.edge_to[i];
            int cost = u.cost + u.edge_cost[i];
            if(node[to].cost < 0 || cost < node[to].cost) node[to].cost = cost;
        }
    }
}
int main(int argc, char **argv) {
    int n = get_uint();
    Node node[n];
    for(int i = 0; i < n; ++i) {
        int u = get_uint();
        int k = node[u].edge_size = get_uint();
        for(int j = 0; j < k; ++j) {
            node[u].edge_to[j] = get_uint();
            node[u].edge_cost[j] = get_uint();
        }
    }
    dijkstra_noheap(node, n);
    for(int i = 0; i < n; ++i) put_uint(i), putchar_unlocked(' '), put_uint(node[i].cost), putchar_unlocked('\n');
    return 0;
}

