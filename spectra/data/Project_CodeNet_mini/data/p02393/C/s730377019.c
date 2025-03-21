#include<stdio.h>
int main(void){
  int a,b,c,d,e,f;
  scanf("%d %d %d",&a,&b,&c);
  if( a <= b && b <= c )
  d=a,e=b,f=c;
  else if (a <= c && c <= b )
  d=a,e=c,f=b;
  else if (b <= a && a <= c )
  d=b,e=a,f=c;
  else if (b <= c && c <= a )
  d=b,e=c,f=a;
  else if (c <= a && a <= b )
  d=c,e=a,f=b;
  else if (c <= b && b <= a )
  d=c,e=b,f=a;


  printf("%d %d %d\n",d,e,f);

return 0;


}

