#include<stdio.h>
int MAX(int a,int b){return a<b?b:a;}
int q[1000000],C[100010];
int ta[100010],nt[200010],fr[200010],to[200010],co[200010];
int f[100010];
int dfs(int v,int e,int s,int d){
  int max=d,i,r;
  for(i=ta[s];i+1;i=nt[i]){//printf("f%d t%d\n",fr[i],to[i]);
    if(f[to[i]])continue;
    //printf("s%d t%d c%d d%d max%d g%d\n",s,to[i],co[i],d,max,g);
    f[to[i]]=1;
    C[to[i]]=C[s]+co[i];
    max=MAX(max,dfs(v,e,to[i],d+co[i]));//printf("r%d max%d->",r,max);
  }//printf("s%d max%d\n",s,max);
  return max;
}
int bfs(int v,int e,int s,int *g){
  int t,r,i,max=0;
  for(i=0;i<v;i++)C[i]=1000000000;
  C[q[0]=s]=t=0;//printf("a\n");
  for(r=1;r-t;t++){
    for(i=ta[q[t]];i+1;i=nt[i]){//printf("%d %d\n",fr[i],to[i]);
      if(C[to[i]]>C[fr[i]]+co[i]){
	C[to[i]]=C[fr[i]]+co[i];
        if(max<C[to[i]]){
	  max=C[to[i]];
	  *g=to[i];
	}
	q[r++]=to[i];
      }
    }//printf("\n");
  }//printf("%d\n",r);
  return max;
}
int tyokkei(int v,int e,int *a,int *b,int *c){
  int i,max=0,g;
  for(i=0;i<v;i++){
    ta[i]=-1;
    C[i]=1000000000;
    f[i]=0;
  }
  C[0]=0;
  f[0]=1;
  for(i=0;i<e;i++){
    nt[i]=ta[a[i]];
    fr[i]=a[i];
    to[i]=b[i];
    co[i]=c[i];
    ta[a[i]]=i;
    nt[i+e]=ta[b[i]];
    fr[i+e]=b[i];
    to[i+e]=a[i];
    co[i+e]=c[i];
    ta[b[i]]=i+e;    
  }//printf("a\n");
  //for(i=0;i<2*e;i++)printf("%d %d\n",fr[i],to[i]);printf("\n");
  max=dfs(v,e*2,0,0);//printf("g%d\n",g);
  for(i=0;i<v;i++){
    if(max==C[i])g=i;
    C[i]=1000000000;
    f[i]=0;
  }
  C[g]=0;
  f[g]=1;
  return dfs(v,e*2,g,0);
}
int main(){
  int n,a[100010],b[100010],c[100010],i;
  scanf("%d",&n);
  for(i=0;i<n-1;i++)scanf("%d %d %d",&a[i],&b[i],&c[i]);
  printf("%d\n",tyokkei(n,n-1,a,b,c));
  return 0;
}