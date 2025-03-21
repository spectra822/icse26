#include<stdio.h>

int main(void){
  int a,b,c;
  scanf("%d %d %d",&a,&b,&c);
  a-=b;
  while(a>0){
    a--;;
    c--;
    if(c==0){
      break;
    }
  }
  printf("%d\n",c);
}
