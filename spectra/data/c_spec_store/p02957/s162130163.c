#include<stdio.h>


 int main()
{
long int a,b,k;

scanf("%ld %ld",&a,&b);


if ((a+b) % 2 !=0)
{
printf("IMPOSSIBLE");
  return 0;
}

printf("%d",(a+b)/2);   
   
}