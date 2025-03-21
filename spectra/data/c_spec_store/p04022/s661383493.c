//set many funcs template
//Ver.20181228
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<stdbool.h>
#include<time.h>
#define inf 1072114514
#define llinf 4154118101919364364
#define mod 1000000007
#define pi 3.1415926535897932384

int max(int a,int b){if(a>b){return a;}return b;}
int min(int a,int b){if(a<b){return a;}return b;}
int zt(int a,int b){return max(a,b)-min(a,b);}
int round(int a,int b){if((a%b)*2 >= b){return (a/b)+1;}return a/b;}
int ceil(int a,int b){if(a%b==0){return a/b;}return (a/b)+1;}
int gcd(int a,int b){int c;while(b!=0){c=a%b;a=b;b=c;}return a;}
int lcm(int a,int b){int c=gcd(a,b);a/=c;return a*b;}
int nCr(int a,int b){int i,r=1;for(i=1;i<=b;i++){r*=(a+1-i);r/=i;}return r;}
int nHr(int a,int b){return nCr(a+b-1,b);}
int fact(int a){int i,r=1;for(i=1;i<=a;i++){r*=i;}return r;}
int pow(int a,int b){int i,r=1;for(i=1;i<=b;i++){r*=a;}return r;}
int dsum(int x){int r=0;while(x){r+=(x%10);x/=10;}return r;}
int dsumb(int x,int b){int r=0;while(x){r+=(x%b);x/=b;}return r;}
int sankaku(int x){return ((1+x)*x)/2;}
long long llmax(long long a,long long b){if(a>b){return a;}return b;}
long long llmin(long long a,long long b){if(a<b){return a;}return b;}
long long llzt(long long a,long long b){return llmax(a,b)-llmin(a,b);}
long long llround(long long a,long long b){if((a%b)*2 >= b){return (a/b)+1;}return a/b;}
long long llceil(long long a,long long b){if(a%b==0){return a/b;}return (a/b)+1;}
long long llgcd(long long a,long long b){long long c;while(b!=0){c=a%b;a=b;b=c;}return a;}
long long lllcm(long long a,long long b){long long c=llgcd(a,b);a/=c;return a*b;}
long long llnCr(long long a,long long b){long long i,r=1;for(i=1;i<=b;i++){r*=(a+1-i);r/=i;}return r;}
long long llnHr(long long a,long long b){return llnCr(a+b-1,b);}
long long llfact(long long a){long long i,r=1;for(i=1;i<=a;i++){r*=i;}return r;}
long long llpow(long long a,long long b){long long i,r=1;for(i=1;i<=b;i++){r*=a;}return r;}
long long lldsum(long long x){long long r=0;while(x){r+=(x%10);x/=10;}return r;}
long long lldsumb(long long x,long long b){long long r=0;while(x){r+=(x%b);x/=b;}return r;}
long long llsankaku(long long x){return ((1+x)*x)/2;}
double dbmax(double a,double b){if(a>b){return a;}return b;}
double dbmin(double a,double b){if(a<b){return a;}return b;}
double dbzt(double a,double b){return dbmax(a,b)-dbmin(a,b);}
int sortfncsj(const void *a,const void *b){if(*(int *)a>*(int *)b){return 1;}if(*(int *)a==*(int *)b){return 0;}return -1;}
int sortfnckj(const void *a,const void *b){if(*(int *)a<*(int *)b){return 1;}if(*(int *)a==*(int *)b){return 0;}return -1;}
int llsortfncsj(const void *a,const void *b){if(*(long long *)a>*(long long *)b){return 1;}if(*(long long *)a==*(long long *)b){return 0;}return -1;}
int llsortfnckj(const void *a,const void *b){if(*(long long *)a<*(long long *)b){return 1;}if(*(long long *)a==*(long long *)b){return 0;}return -1;}
int dbsortfncsj(const void *a,const void *b){if(*(double *)a>*(double *)b){return 1;}if(*(double *)a==*(double *)b){return 0;}return -1;}
int dbsortfnckj(const void *a,const void *b){if(*(double *)a<*(double *)b){return 1;}if(*(double *)a==*(double *)b){return 0;}return -1;}
int strsortfncsj(const void *a,const void *b){return strcmp((char *)a,(char *)b);}
int strsortfnckj(const void *a,const void *b){return strcmp((char *)b,(char *)a);}
int chsortfncsj(const void *a,const void *b){if(*(char *)a>*(char *)b){return 1;}if(*(char *)a==*(char *)b){return 0;}return -1;}
int chsortfnckj(const void *a,const void *b){if(*(char *)a<*(char *)b){return 1;}if(*(char *)a==*(char *)b){return 0;}return -1;}

void shuffledget(int x[],int n){
    srand(time(0));
    int i,b[524288],p,c;
    for(i=0;i<n;i++){
        b[i]=i;
    }
    for(i=n;i>=1;i--){
        p=rand()%i;
        c=b[i-1];b[i-1]=b[p];b[p]=c;
    }
    for(i=0;i<n;i++){
        scanf("%d",&x[b[i]]);
    }
}

int dx4[4]={1,-1,0,0};
int dy4[4]={0,0,1,-1};
int dx8[8]={-1,-1,-1,0,0,1,1,1};
int dy8[8]={-1,0,1,-1,1,-1,0,1};

int search(int x,int a[],int n){
    int st=0,fi=n-1,te;
    while(st<=fi){
        te=(st+fi)/2;
        if(a[te]<x){st=te+1;}else{fi=te-1;}
    }
    return st;
}

void prarr(int arr[],int n){
  int i;
  for(i=0;i<n;i++){
    if(i){printf(" ");}
    printf("%d",arr[i]);
  }
  printf("\n");
  return;
}

typedef struct{
long long val;
long long node;
}sd;

int sdsortfnc(const void *a,const void *b){
if(((sd*)a)->val < ((sd*)b)->val){return -1;}
if(((sd*)a)->val > ((sd*)b)->val){return 1;}
return 0;
}

long long pl[100005],dpl[100005],trpl[100005],ls=0;
void makepl(){
  bool fl[2222]={0};
  long long i,j;
  for(i=2;i<2222;i++){
    if(fl[i]){continue;}
    pl[ls]=i;
    dpl[ls]=i*i;
    trpl[ls]=i*i*i;
    ls++;
    for(j=2*i;j<2222;j+=i){
      fl[j]=1;
    }
  }
  return;
}

long long llsqr(long long x){
  long long st=1,fi=1000000000,te;
  while(st<=fi){
    te=(st+fi)/2;
    if(te*te<x){st=te+1;}
    else{fi=te-1;}
  }
  return st;
}

int main(void){
  makepl();
  long long i,j,n,m,k,a[100005],b,c=0,h,w,r=0,l,t;
  long long st,fi,te;
  sd dat[100005];
  bool tfl[100005]={0};
  scanf("%lld",&n);
  for(i=0;i<n;i++){
    scanf("%lld",&t);
    w=t;
    for(j=0;j<ls;j++){
      while(t%pl[j]==0){t/=pl[j];}
      while(w%trpl[j]==0){w/=trpl[j];}
    }
    if(t>100000){
      l=llsqr(t);
      if(l*l!=t){r++;continue;}
    }
    a[c]=w;
    c++;
  }
  if(c==0){
    printf("%lld\n",r);
    return 0;
  }
  qsort(a,c,sizeof(long long),llsortfncsj);
  t=0;w=1;
  dat[0].val=a[0];
  for(i=1;i<c;i++){
    if(a[i-1]!=a[i]){
      dat[t].node=w;
      t++;
      w=1;
      dat[t].val=a[i];
    }
    else{w++;}
  }
  dat[t].node=w;
  t++;
  dat[t].val=llinf;
  for(i=0;i<t;i++){
    if(tfl[i]){continue;}
    tfl[i]=1;
    if(dat[i].val==1){r++;continue;}
    w=1;
    h=dat[i].val;
    for(j=0;j<ls;j++){
      while(h%pl[j]==0){h/=pl[j];}
      if(dat[i].val%pl[j]==0){
        if(dat[i].val%dpl[j]==0){
          w*=pl[j];
          if(w>10000000000){w=-1;break;}
        }
        else{
          w*=pl[j];
          if(w>10000000000){w=-1;break;}
          w*=pl[j];
          if(w>10000000000){w=-1;break;}
        }
      }
    }
    if(w==-1){r+=dat[i].node;continue;}
    if(h>100000){
      l=llsqr(h);
      w*=l;
      if(w>10000000000){w=-1;}
    }
    else{
      w*=h;
      if(w>10000000000){w=-1;}
      w*=h;
      if(w>10000000000){w=-1;}
    }
    if(w==-1){r+=dat[i].node;continue;}
    st=0;fi=t-1;
    while(st<=fi){
      te=(st+fi)/2;
      if(dat[te].val<w){st=te+1;}
      else{fi=te-1;}
    }
    if(dat[st].val!=w){r+=dat[i].node;continue;}
    tfl[st]=1;
    r+=llmax(dat[i].node,dat[st].node);
  }
  printf("%lld\n",r);
  return 0;
}
