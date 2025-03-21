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

int gcd(int a,int b){
  if(a<b){
    swap(&a,&b);
  }

  if(b==0){
    return a;
  }

  int r=a%b;
  while(r!=0){
    a = b;
    b = r;
    r = (a%b);
  }

  return b;
}

/* クイックソート */
int dn(const void*a,const void*b){return*(int*)b-*(int*)a;}


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

/****************************************\
| Thank you for viewing my code:)        |
| Written by RedSpica a.k.a. RanseMirage |
| Twitter:@asakaakasaka                  | 
\****************************************/

int main(void){
  int h,w,k;
  scanf("%d%d%d",&h,&w,&k);

  for(int i=0;i<=h;i++){
    for(int j=0;j<=w;j++){

      int now=(w*i)+(h*j)-2*i*j;

      if(now==k){
        printf("Yes\n");

        return 0;
      }

    }
  }

  printf("No\n");

  return 0;
}