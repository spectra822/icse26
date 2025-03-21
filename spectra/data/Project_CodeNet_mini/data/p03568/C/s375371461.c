#include<stdio.h>
#

int main(){

int N,A,odd=1,exp=1;
scanf("%d",&N);
for (int i = 0; i < N; i++){
    scanf("%d",&A);
    if (A%2==0){ odd*=2;}
}

for (int i = 1; i <= N; i++){exp*=3;}

printf("%d",exp-odd);

return 0;

}