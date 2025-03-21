#include<stdio.h>

int  n , yaku[101] = {0};

int num(int a){
  int c = 0;
  for(int i = 2;i <= n;i ++){
    if(yaku[i] >= a-1) c ++;
  }

  return c;
}

int main(void){
  scanf("%d",&n);


  for(int i = 2;i <= n;i ++){
    int a = i , waru = 2;
    while(a > 1){
      while(a%waru == 0){
        a /= waru;
        yaku[waru] ++;
      }
      waru ++; 
    }
  }

  int ans = num(75) + num(25)*(num(3)-1) + num(15)*(num(5)-1) + num(5)*(num(5)-1)*(num(3)-2)/2;

  printf("%d\n",ans);
  
  return 0;
}