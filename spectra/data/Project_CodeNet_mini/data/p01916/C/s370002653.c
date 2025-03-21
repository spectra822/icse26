#include<stdio.h>
#include<string.h>

int main(void)
{
  char str[1010];
  int a[30]={};
  int i;
  int sum=0;
  
  scanf("%s",str);
  for(i=0;str[i];i++)
    a[str[i]-'a']=!a[str[i]-'a'];
  for(i=0;i<30;i++)
    sum+=a[i];
  
  printf("%d\n",sum/2);
  return 0;
}