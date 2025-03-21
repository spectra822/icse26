#include<stdio.h>

int main(void){
  int railroad[10]={};
  int car;
  int i=0;
  while((scanf("%d",&car))!=EOF){
    if(car==0){//出ていく
      i--;
      printf("%d\n",railroad[i]);
    }else{//入ってくる
      railroad[i]=car;
      i++;
    }
  }

  return 0;
}

