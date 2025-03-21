#include<stdio.h>
typedef struct card{
  char c;
  int val;
  int num;
}card;
void quicksort(card*,int,int);
int partition(card*,int,int);
int main(){

  int i,j,n,flag=0;

  scanf("%d",&n);
  card A[n];
  for(i=0;i<n;i++){
    scanf(" %c%d",&A[i].c,&A[i].val);
    A[i].num=i;
  }
  quicksort(A,0,n-1);
  for(i=0;i<n-1;i++){
    for(j=i+1;j<n;j++){
      if(A[i].val==A[j].val && A[i].num>A[j].num){
	flag=1;
	break;
      }
    }
    if(flag==1) break;
  }
  
  if(flag==1) printf("Not stable\n");
  else printf("Stable\n");
  for(i=0;i<n;i++){
    printf("%c %d\n",A[i].c,A[i].val);
  }
  return 0;
}
void quicksort(card *A,int p,int r){

  int q;
  if(p<r){
    q=partition(A,p,r);
    quicksort(A,p,q-1);
    quicksort(A,q+1,r);
  }
}
int partition(card *A,int p,int r){

  int i,j;
  int x;
  card swap;

  i=p-1;
  x=A[r].val;

  for(j=p;j<r;j++){
    if(A[j].val<=x){
      i++;
      swap=A[i];
      A[i]=A[j];
      A[j]=swap;
    }
  }
  swap=A[i+1];
  A[i+1]=A[r];
  A[r]=swap;
  return i+1;
}

