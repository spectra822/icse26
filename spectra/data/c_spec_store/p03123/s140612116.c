//AWTF2019-D
#include<stdio.h>
#include<stdbool.h>
#define prime 10000000019

void llswap(long long *a,long long *b){long long c;c=(*a);(*a)=(*b);(*b)=c;}
long long llsankaku(long long x){return ((1+x)*x)/2;}

long long calcul(long long p,long long q,long long z,long long *r,long long *b){
  long long f=0,cnt=0,w,i;
  (*r)=0;(*b)=0;
  if(p<q){f=1;llswap(&p,&q);}
  i=0;
  while(z>=0){
    w=z/q;
    cnt+=(w+1);
    (*r)+=i*(w+1);
    (*b)+=llsankaku(w);
    z-=p;
    i++;
  }
  if(f){llswap(r,b);}
  return cnt;
}

void calc(long long p,long long q,long long k,long long *r,long long *b){
  long long st,fi,te,c;
  st=0;fi=prime*2000;
  while(st<=fi){
    te=(st+fi)/2;
    c=calcul(p,q,te,r,b);
    if(c==k){break;}
    if(c<k){st=te+1;}
    if(c>k){fi=te-1;}
  }
}

typedef struct{
  long long xz;
  long long yz;
}point;

point vector_minus(point a,point b){
  point r;
  r.xz=a.xz-b.xz;
  r.yz=a.yz-b.yz;
  return r;
}

//gaiseki
long long crossproduct(point a,point b){
  return a.xz*b.yz-a.yz*b.xz;
}

bool ispossible(long long r,long long b,long long k){
  long long st,fi,te,zr,zb;
  long long fr,fb,sr,sb;
  st=1;fi=prime-1;
  while(st<=fi){
    te=(st+fi)/2;
    calc(te,prime-te,k,&zr,&zb);
    if(zr<=r && zb<=b){return true;}
    if(zr>r && zb>b){return false;}
    if(zr>r){st=te+1;sr=zr;sb=zb;}
    else{fi=te-1;fr=zr;fb=zb;}
  }
  //Is (r,b) on above the line{(fr,fb),(sr,sb)}(fr<sr)?
  point tg,l1,l2;
  tg.xz=r;tg.yz=b;
  l1.xz=fr;l1.yz=fb;
  l2.xz=sr;l2.yz=sb;
  if(crossproduct(vector_minus(l2,l1),vector_minus(tg,l1))>=0){return true;}
  return false;
}

long long solve(long long r,long long b){
  long long st=0,fi=2222222,te;
  while(st<=fi){
    te=(st+fi)/2;
    if(ispossible(r,b,te)){st=te+1;}
    else{fi=te-1;}
  }
  return fi;
}

int main(){
  long long r,b;
  scanf("%lld%lld",&r,&b);
  printf("%lld\n",solve(r,b)-1);//-1 : empty box
  return 0;
}
