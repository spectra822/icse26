#include<stdio.h>

int main(void){
  int n;
  scanf("%d",&n);

  int s[n] , k = 0 , min = 101;
  for(int i = 0;i < n;i ++){
    scanf("%d",&s[i]);
    k += s[i];
    if(s[i]%10 == 0){
      s[i] = 101;
    }
    if(min > s[i]){
      min = s[i];
    }
  }

  int ans = k;
  if(k%10 == 0){
    if(min == 101){
    ans = 0;
    }
    else{
      ans = k - min;
    }
  }
  
  printf("%d\n",ans);

  return 0;
}