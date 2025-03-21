#include<stdio.h>
#include<stdlib.h>

typedef long long int int64;

#define MAX(a,b) ((a)>(b)?(a):(b))
#define MIN(a,b) ((a)<(b)?(a):(b))

typedef struct item{
  int w,s,v;
} node;

int cmp(const void *a,const void *b){
  node *p=(node *)a;
  node *q=(node *)b;
  return (p->s+p->w)-(q->s+q->w);
}

void run(void){
  int n;
  scanf("%d",&n);
  node *p=(node *)calloc(n,sizeof(node));
  int i,j;
  for(i=0;i<n;i++){
    int w,s,v;
    scanf("%d%d%d",&w,&s,&v);
    p[i]=(node){w,s,v};
  }
  qsort(p,n,sizeof(node),cmp);
  const int m=20000;
  int64 *dp=(int64 *)calloc(m+1,sizeof(int64));
  for(i=0;i<n;i++){
    for(j=p[i].s;j>=0;j--){
      int k=j+p[i].w;
      dp[k]=MAX(dp[k],dp[j]+p[i].v);
    }
  }
  int64 ans=0;
  for(i=0;i<=m;i++) ans=MAX(ans,dp[i]);
  printf("%lld\n",ans);
}

int main(void){
  run();
  return 0;
}
