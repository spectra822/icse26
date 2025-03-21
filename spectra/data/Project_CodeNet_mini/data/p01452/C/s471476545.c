#include<stdio.h>
#define N 1000000007

typedef long long int lli;

lli memo[220001];

void inittable(lli n){
  lli i;

  memo[1]=1;

  for(i=2;i<=n;i++){
    memo[(int)i]=(i*memo[(int)(i-1)])%N;
  }
}

lli extgcd(lli a,lli b,lli *x,lli *y){
  lli d=a;

  if(b!=0){
    d=extgcd(b,a%b,y,x);

    *y-=(a/b)*(*x);
  }
  else{
    *x=1;
    *y=0;
  }

  return d;
}

lli mod_inv(lli a,lli m){
  lli x,y;

  extgcd(a,m,&x,&y);

  return (m+x%m)%m;
}

lli mod_cmb(lli n,lli r,lli m){
  lli a1,a2,a3;

  if((n<0)||(r<0)||(n<r)){
    return 0;
  }

  a1=memo[n];
  a2=memo[r];
  a3=memo[n-r];

  return a1*mod_inv(a2*a3%m,m)%m;
}

int main(){
  int x,y,k;
  int i,j;
  lli ans;
  lli xgr,ygr;

  scanf("%d %d %d",&x,&y,&k);

  inittable(x+y+2*k);
  memo[0]=1;
  ans=0;

  for(i=0;i<=k;i++){
    xgr=(mod_cmb(x+2*(k-i),k-i,N)-mod_cmb(x+2*(k-i),k-i-1,N)+N)%N;
    ygr=(mod_cmb(y+2*i,i,N)-mod_cmb(y+2*i,i-1,N)+N)%N;

    ans=(ans+((xgr*ygr)%N)*mod_cmb(x+y+2*k,y+2*i,N))%N;
  }
  printf("%d\n",(ans+N)%N);

  return 0; 
}