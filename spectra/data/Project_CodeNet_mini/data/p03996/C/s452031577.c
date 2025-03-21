#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

#define lli long long int
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
#define	abs(a) ((a)<0?-(a):(a))

typedef struct data {
	struct data *prev;
	struct data *next;
	int id;
	int count;
} data;



int main(void){
	/* === input paramater === */
	int n;
	int m;
	int q;
	int *a;
	/* === operate paramater === */
	int i;
	data *d;
	data *p;
	bool *complete;
	int allow;

	/* === input === */
	scanf("%d%d%d",&n,&m,&q);
	a = calloc(sizeof(int),q+1);
	for(i=1;i<=q;i++){
		scanf("%d",&a[i]);
	}
	/* === prepare === */
	d = calloc(sizeof(data),m+1);
	for(i=0;i<=m;i++){
		d[i].id = i;
	}
	p = d;
	d[0].count = n;
	for(i=q;i>0;i--){
		if(d[a[i]].count == 0){
			d[a[i]].prev = p;
			p->next = &d[a[i]];
			p = &d[a[i]];
		}
		d[a[i]].count = min(d[a[i]].count+1,d[a[i]].prev->count);
	}
	/* === core === */
	complete = calloc(sizeof(bool),m+1);
	allow = 0;
	while(d != NULL && d->count == n){
		complete[d->id] = true;
		while(complete[allow])allow++;
		d = d->next;
	}
	while(d != NULL){
		if(d->id != allow){
			printf("No\n");
			return 0;
		}
		complete[allow] = true;
		while(complete[allow]) allow++;
		d = d->next;
	}
	printf("Yes\n");

	return 0;
}