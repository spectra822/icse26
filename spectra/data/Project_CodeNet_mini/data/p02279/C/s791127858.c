#include <stdio.h>
struct Node {
  int parent;
  int left;
  int right;
};
int n;
struct Node tree[100000];
int dipth[100000];
void getdip(int,int);
void printtree(int);
int main(){
  int i,id,j,num,p,l,root;
  scanf("%d",&n);
  for(i=0;i<n;i++)tree[i].parent=tree[i].left=tree[i].right=-1;
  for(i=0;i<n;i++){
    scanf("%d %d",&id,&num);
    for(j=0;j<num;j++){
      scanf("%d",&p);
      if(j==0)tree[id].left=p;
      else tree[l].right=p;
      tree[p].parent=id;
      l=p;
    }
  }
  for(i=0;i<n;i++){
    if(tree[i].parent==-1)root=i;
  }
  getdip(root,0);
  for(i=0;i<n;i++)printtree(i);
  return 0;
}
void getdip(int r,int d){
  dipth[r]=d;
  if(tree[r].right!=-1)getdip(tree[r].right,d);
  if(tree[r].left!=-1)getdip(tree[r].left,d+1);
}
void printtree(int i){
  int m,j=0;
  printf("node %d: parent = %d, depth = %d, ",i,tree[i].parent,dipth[i]);
  if(tree[i].parent==-1)printf("root, [");
  else if(tree[i].left==-1)printf("leaf, [");
  else printf("internal node, [");
  m=tree[i].left;
  while(m!=-1){
    if(j!=0)printf(", ");
    printf("%d",m);
    m=tree[m].right;
    j++;
  }
  printf("]\n");
}


