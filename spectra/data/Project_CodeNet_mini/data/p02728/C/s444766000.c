#include<stdio.h>
long long M=1e9+7;
int mbk(long long a,int n,int m){return n?(mbk((a*a)%m,n/2,m)*(n%2?a:1))%m:1;}
int inv(int a,int m){return mbk((long long)a,m-2,m);}
int ta[200010],nt[400010],to[400010],tS[400010];
long long tu[200010],ANS[200020],tans[200020];
//sが親でtから帰ってきた時の処理 変えるやつ
void fc(int s,int t){tans[s]=tans[s]*tans[t]       %M;}
//fcの逆処理　変えるやつ
void ic(int s,int t){tans[s]=tans[s]*inv(tans[t],M)%M;}
//すべての子の処理が終わった時の処理　変えるやつ
void fp(int s){tans[s]=tans[s]*inv(tS[s],M)%M;}
//fpの逆処理　変えるやつ
void ip(int s){tans[s]=tans[s]*tS[s]       %M;}
//木DPの関数
void tDP(int s){//printf("!%d\n",s);
  long long i;
  tu[s]=1;
  for(i=ta[s];i+1;i=nt[i]){
    if(tu[to[i]])continue;
    tDP(to[i]);
    fc(s,to[i]);
    tS[s]+=tS[to[i]];
  }
  fp(s);
}
//根をsからtにする奴
void chrt(int s,int t){
  ip(s);
  ic(s,t);
  ip(t);
  tS[s]-=tS[t];
  tS[t]+=tS[s];
  fp(s);
  fc(t,s);
  fp(t);
}
//全方位やる奴
void atdp(int s){//printf("!!%d %d\n",s,cc[s]);
  int i;
  tu[s]=2;
  ANS[s]=tans[s];
  for(i=ta[s];i+1;i=nt[i]){
    if(tu[to[i]]==2)continue;
    chrt(s,to[i]);
    atdp(to[i]);
    chrt(to[i],s);
  }
}
//呼びだす奴
void atDP(int v,int *a,int *b){
  int i,I=1;
  for(i=0;i<v;i++)ta[i+I]=-1;
  for(i=0;i<v;i++)tS[i+I]=1;
  for(i=0;i<v;i++)tans[i+I]=1;
  for(i=0;i<v-1;i++){
    nt[i]=ta[to[i+v-1]=a[i]];
    nt[i+v-1]=ta[to[i]=b[i]];
    ta[a[i]]=i;
    ta[b[i]]=i+v-1;
  }
  tDP(I);
  atdp(I);
}
int main(){
  int n,i,a[200010],b[200010];
  long long p=1;
  scanf("%d",&n);
  for(i=0;i<n-1;i++)scanf("%d %d",&a[i],&b[i]);
  for(i=1;i<=n;i++)p=p*i%M;
  atDP(n,a,b);
  for(i=0;i<n;i++)printf("%lld\n",ANS[i+1]*p%M);
  return 0;
}
