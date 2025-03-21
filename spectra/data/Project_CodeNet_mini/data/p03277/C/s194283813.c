#include<stdio.h>
#include<stdlib.h>

typedef long long int int64;

void initBit(int *bit){
  int n=bit[0];
  for(int i=1;i<=n;i++) bit[i]=0;
}

void inc(int *bit,int x){
  const int n=bit[0];
  for(int i=x;i<=n;i+=i&-i) bit[i]++;
}

int getSum(int *bit,int x){
  int res=0;
  for(int i=x;i>0;i-=i&-i) res+=bit[i];
  return res;
}

int64 count(int m,int *a,int n){
  static int *bit=NULL;
  if(bit==NULL){
    bit=(int *)calloc(2*n+1+1,sizeof(int));
    bit[0]=2*n+1;
  }
  initBit(bit);
  int64 cnt=0;
  int sum=n+1;
  inc(bit,sum);
  for(int i=0;i<n;i++){
    sum+=(a[i]<m?-1:1);
    cnt+=getSum(bit,sum);
    inc(bit,sum);
  }
  return cnt;
}

void run(void){
  int n;
  scanf("%d",&n);
  int *a=(int *)calloc(n,sizeof(int));
  int i;
  for(i=0;i<n;i++) scanf("%d",a+i);
  int l=1;
  int r=1000000000+1;
  while(r-l>1){
    int m=(l+r)/2;
    int64 cnt=count(m,a,n);
    if(4*cnt>=(int64)n*(n+1)){
      l=m;
    } else {
      r=m;
    }
  }
  printf("%d\n",l);
}

int main(void){
  run();
  return 0;
}
