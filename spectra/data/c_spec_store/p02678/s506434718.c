#include<stdio.h>
#include<stdlib.h>
typedef struct E{
	int to;
	struct E *next;
}edge;
int N, M, d[1<<17], que[1<<17], l=0, r=0;
edge G[1<<17], *nil;
void push(int i, int j){
	edge *X = (edge*)malloc(sizeof(edge));
	(*X).to = j;
	(*X).next = G[i].next;
	G[i].next = X;
	return;
}
int main(){
	scanf("%d%d", &N, &M);
	for(int i=0; i<=N; i++){
		d[i] = -1;
		G[i].next = nil;
	}
	for(int i=0; i<M; i++){
		int a, b;
		scanf("%d%d", &a, &b);
		push(a, b);
		push(b, a);
	}
	d[1] = 0;
	que[r++] = 1;
	while(l != r){
		int i = que[l++];
		edge *x = G[i].next;
		while(x != nil){
			int j = (*x).to;
			if(d[j] == -1){
				d[j] = i;
				que[r++] = j;
			}
			x = (*x).next;
		}
	}
	puts("Yes");
	for(int i=2; i<=N; i++){
		printf("%d\n", d[i]);
	}
	return 0;
}