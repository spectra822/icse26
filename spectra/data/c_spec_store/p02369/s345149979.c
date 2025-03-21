#include "stdlib.h"
#include "stdio.h"
#include "string.h"



/**************************
*  Structure declaration  *
**************************/

struct edge {
    int tgt;
    int cost;
};

struct edge_list_node {
    struct edge e;
    struct edge_list_node *nxt;
};
    
struct edge_list {
    struct edge_list_node* front;
    struct edge_list_node* back;
    unsigned int num_edge;
};

struct adjcency_list {
    struct edge_list* src;
    unsigned int num_vertex;
};
/***********************************
*  Function prototype declaration  *
***********************************/

// ??£??\???????????????????????????
// in1 : ??°?????????????????°
// in2 : ??°??????????????°
// out : ??£??\?????????????????????
struct adjcency_list* make_adjcency_list(int num_vertex);

// ??£??\????????????????????????
// in1 : ??£??\?????????
// in2 : ??????source
// in3 : ??????{tgt,cost}???
// out : void
void push_edge(struct adjcency_list* graph,
	       int src,
	       struct edge e);


/*************************
*  Function declaration  *
*************************/


struct adjcency_list* make_adjcency_list(int V) {

    int i;
    
    // ??£??\???????????¬??? ?????¢????¢????
    struct adjcency_list* graph;
    graph = (struct adjcency_list* )malloc(sizeof(struct adjcency_list));
    
    // ????????°????????????????????????
    graph->src = (struct edge_list*) malloc(sizeof(struct edge_list) * V);
    for( i=0; i<V; i++ ) {
	graph->src[i].front = NULL;
	graph->src[i].back  = NULL;
	graph->src[i].num_edge  = 0;
    }
    // ??£??\??????????????§??????
    graph->num_vertex = V;
    
    return graph;
}


// ??£??\????????????????????????
// in1 : ??£??\?????????
// in2 : ??????source
// in3 : ??????{tgt,cost}???
// out : void
void push_edge(struct adjcency_list* graph,
	       int source,
	       struct edge _edge) {

    struct edge_list_node *n,*p;
    
    n = (struct edge_list_node*)malloc(sizeof(struct edge_list_node));
    n->e = _edge;
    n->nxt = NULL;
    
    if( graph->src[source].front == NULL )  // there is no nodes in the list.
	graph->src[source].front = n;
    else 
	graph->src[source].back->nxt = n;
    graph->src[source].back = n;
    graph->src[source].num_edge ++;
    
}

void dump_adjcency_list(const struct adjcency_list* g) {

    int V = g->num_vertex;
    int i;

    struct edge_list_node* n;
	
    for( i=0; i<V; i++ ) {
	n = g->src[i].front;
	printf("%d --> ",i);
	while( n != NULL ) {
	    printf("%3d ",n->e.tgt, n->e.cost);
	    n = n->nxt;
	}
	printf("\n");
    }
}

/********************************************************************************************/
/********************************************************************************************/
/********************************************************************************************/

int is_cyclic(struct adjcency_list* g) {
    int* in;
    int i,j,k,V;
    int flag;
    struct edge_list_node* n;

    V = g->num_vertex;
    in = (int*)malloc(sizeof(int)*V);
    for( i=0; i<V; i++) in[i] = 0;

    // ??\?¬???°?¨????
    for( i=0; i<V; i++ ) {
	n = g->src[i].front;
	while( n != NULL ) {
	    in[n->e.tgt]++;
	    n = n->nxt;
	}
    }
	
    for( j=0; j<V; j++ ) {
	flag = 1;
	// ??\?¬???° == 0 ???????????¢???
	for( i=0; i<V; i++ ) {
	    if( in[i] == 0 ) {
		in[i] = -1;
		flag = 0; // 0???????????????	      
		n = g->src[i].front;
		while( n != NULL ) {
		    in[n->e.tgt]--;
		    n = n-> nxt;
		}
		break;
	    }
	}
	if( flag ) return 1;
    }
    return 0;
}

int main(void) {

    // ??\?????¨?????°
    int V,E;
    struct adjcency_list *graph;

    // ?¨??????¨?????°
    int i,s,t;
    struct edge e;

    // ????????????
    int res;

    // ??\?????????
    scanf("%d %d",&V,&E);
    graph = make_adjcency_list(V);

    for( i=0; i<E; i++ ) {
	scanf("%d %d",&s,&t);
	e.tgt = t;
	e.cost = 0;
	push_edge(graph,s,e);
    }
//    dump_adjcency_list(graph);
    
    // ?¨????
    res = is_cyclic(graph);

    printf("%d\n",res);

    return 0;
}