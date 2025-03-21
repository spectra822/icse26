#include <stdio.h>
#include <stdlib.h>

typedef struct _stack{
    int data;
    struct _stack *next;
}STACK;
typedef struct _pool{
    int area;
    int x;
    struct _pool *next;
}POOL;
void output(POOL *p){
    if(p==NULL)return;
    
    output(p->next);
    printf(" %d",p->area);
    return;
}

int main(void){
    char in;
    int x=1;
    STACK *stack,*tmp;
    stack=NULL;
    POOL *pool,*p;
    pool=NULL;
    while(scanf("%c",&in)==1){
        switch(in){
            case '\\':
                tmp=(STACK*)malloc(sizeof(STACK));
                tmp->data=x;
                if(stack==NULL){
                    tmp->next=NULL;
                }else{
                    tmp->next=stack;
                }
                stack=tmp;
                break;
            case '_':
                break;
            case '/':
                if(stack==NULL)break;
                
                if(pool==NULL){
                    pool=(POOL*)malloc(sizeof(POOL));
                    pool->area=x-stack->data;
                    pool->x=stack->data;
                    pool->next=NULL;
                }else{
                    if(stack->data<pool->x){
                        p=pool->next;
                        while(p!=NULL&&p->x>stack->data){
                            p->area+=pool->area;
                            p=pool;
                            pool=pool->next;
                            free(p);
                            p=pool->next;
                        }
                        pool->area+=x-stack->data;
                        pool->x=stack->data;
                    }else{
                        p=(POOL*)malloc(sizeof(POOL));
                        p->area=x-stack->data;
                        p->x=stack->data;
                        p->next=pool;
                        pool=p;
                    }
                }
                tmp=stack;
                stack=stack->next;
                free(tmp);

                break;
        }
        x++;
    }
    
    int sum=0,count=0;
    p=pool;
    while(p!=NULL){
        sum+=p->area;
        count++;
        p=p->next;
    }
    printf("%d\n%d",sum,count);
    output(pool);
    printf("\n");

    return 0;
}

