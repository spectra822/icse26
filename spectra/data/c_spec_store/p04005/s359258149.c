#include<stdio.h>

int main(){
  long X[3];
  scanf("%ld%ld%ld",&X[0],&X[1],&X[2]);
  if (X[0]%2==0||X[1]%2==0||X[2]%2==0){
    puts("0");
  }else{
    int m,max=0;
    for (int i = 0; i < 3; i++){
      if(max<X[i]){
        max = X[i];
        m = i;
        }
    }
    X[m]=1;
    printf("%ld",X[0]*X[1]*X[2]);
  }
  
  return 0;
}