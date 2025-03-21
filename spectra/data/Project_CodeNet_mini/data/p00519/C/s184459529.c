#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int untin;
	int limit;
} taxi_t;

typedef struct {
	taxi_t taxi;
	int loads_num;
	int loads_cap;
	int *loads;
} mati_t;

void add_load(mati_t *mati, int to) {
	if(mati->loads_num>=mati->loads_cap) {
		mati->loads_cap*=2;
		if(mati->loads_cap<=0)mati->loads_cap=1;
		if(mati->loads==NULL) {
			mati->loads=(int*)malloc(sizeof(int)*mati->loads_cap);
		} else {
			mati->loads=(int*)realloc(mati->loads,sizeof(int)*mati->loads_cap);
		}
	}
	mati->loads[mati->loads_num++]=to;
}

typedef struct {
	short town;
	short kaisu;
} status_t;

int heap_size;
status_t status_heap[5000*5001];
int status_mincost[5000][5001];
char in_heap[5000][5001];

int read_cost(status_t stat) {
	return status_mincost[stat.town][stat.kaisu]-1;
}

void update_cost(status_t stat,int cost) {
	if(status_mincost[stat.town][stat.kaisu]==0 ||
	status_mincost[stat.town][stat.kaisu]-1>cost) {
		status_mincost[stat.town][stat.kaisu]=cost+1;
	}
}

void adjust_heap(int idx) {
	int min_idx=idx;
	if(idx*2+1<heap_size) {
		if(read_cost(status_heap[min_idx])>read_cost(status_heap[idx*2+1])) {
			min_idx=idx*2+1;
		}
		if(idx*2+2<heap_size) {
			if(read_cost(status_heap[min_idx])>read_cost(status_heap[idx*2+2])) {
				min_idx=idx*2+2;
			}
		}
	}
	if(min_idx!=idx) {
		status_t tmp=status_heap[idx];
		status_heap[idx]=status_heap[min_idx];
		status_heap[min_idx]=tmp;
		adjust_heap(min_idx);
	} else {
		if(idx>0)adjust_heap(idx/2);
	}
}

void insert_heap(status_t stat,int cost) {
	int prev_cost=read_cost(stat);
	if(prev_cost<0 || cost<prev_cost) {
		update_cost(stat,cost);
		if(!in_heap[stat.town][stat.kaisu]) {
			in_heap[stat.town][stat.kaisu]=1;
			status_heap[heap_size]=stat;
			adjust_heap(heap_size++);
		}
	}
}

status_t get_heap(void) {
	status_t ret=status_heap[0];
	in_heap[ret.town][ret.kaisu]=0;
	status_heap[0]=status_heap[--heap_size];
	adjust_heap(0);
	return ret;
}

int N,K;
taxi_t taxi[5000];
mati_t mati[5000];

int main(void) {
	int i;
	int answer;
	status_t initial={0,0};
	if(scanf("%d%d",&N,&K)!=2)return 1;
	for(i=0;i<N;i++) {
		if(scanf("%d%d",&taxi[i].untin,&taxi[i].limit)!=2)return 1;
	}
	for(i=0;i<K;i++) {
		int A,B;
		if(scanf("%d%d",&A,&B)!=2)return 1;
		A--;B--;
		add_load(&mati[A],B);
		add_load(&mati[B],A);
	}
	/* haba yuusen tansaku */
	insert_heap(initial,0);
	while(heap_size>0) {
		status_t cur_status=get_heap();
		int cur_cost=read_cost(cur_status);
		status_t next_status;
		if(cur_status.town==N-1) {
			/* mokutekiti ni tuita */
			printf("%d\n",cur_cost);
			break;
		}
		/* tugi no mati ni iku */
		if(cur_status.kaisu>0) {
			next_status.kaisu=cur_status.kaisu-1;
			for(i=0;i<mati[cur_status.town].loads_num;i++) {
				next_status.town=mati[cur_status.town].loads[i];
				insert_heap(next_status,cur_cost);
			}
		}
		/* kakin site kono mati de taxi ni noru */
		next_status.town=cur_status.town;
		next_status.kaisu=taxi[cur_status.town].limit;
		insert_heap(next_status,cur_cost+taxi[cur_status.town].untin);
	}
	/* atosimatu */
	for(i=0;i<N;i++) {
		if(mati[i].loads!=NULL)free(mati[i].loads);
	}
	return 0;
}