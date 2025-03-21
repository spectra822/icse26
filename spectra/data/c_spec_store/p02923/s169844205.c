#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>



void swap (int *x, int *y) {
  int temp;

  temp = *x;
  *x = *y;
  *y = temp;

  return;
}


int gcd(int a, int b){
  int c;

  while (b > 0){
    c = a % b;
    a = b;
    b = c;
  }

  return a;
}

long int modpow(long int a,long int n,long int mod){
  long int ans=1;
  while(n>0){
    if(n & 1){
      ans=ans*a%mod;
    }
    a=a*a%mod;
    n/=2;
  }
  return ans;
}

long int modinv(long int a,long int mod){
  return modpow(a,mod-2,mod);
}

int max(int a,int b){
  if(a<b){
    return b;
  }
  else{
    return a;
  }
}

int min(int a,int b){
  if(a<b){
    return a;
  }
  else{
    return b;
  }
}

void chmax(int *a,int b){
  if(*a < b){
    *a = b;
  }

  return;
}

void chmin(int *a,int b){
  if(*a > b){
    *a =b;
  }

  return;
}

int main(void){
  int n;
  scanf("%d",&n);
  int h[n+10];
  for(int i=0;i<n+10;i++){
    h[i]=0;
  }
  for(int i=0;i<n;i++){
    scanf("%d",&h[i]);
  }
  int max=0;
  int count=0;
  for(int i=0;i<n-1;i++){
    if(h[i+1]<=h[i]){
      count++;
    }else{
      count=0;
    }
    chmax(&max,count);
  }
  printf("%d\n",max);
  return 0;
}