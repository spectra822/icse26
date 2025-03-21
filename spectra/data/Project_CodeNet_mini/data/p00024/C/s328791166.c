#include<stdio.h>

int main(void){

float v;
int n;

while(scanf("%f",&v) != EOF){

n=(int)((4.9*v*v/9.8/9.8)+5)/5;
n=n+1;
printf("%d\n",n);
}
return 0;
}
