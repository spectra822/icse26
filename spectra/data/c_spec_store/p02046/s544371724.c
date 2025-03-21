#include <stdio.h>
#include <stdlib.h>
int main()
{int  x,y,t;

  while(scanf("%d%d",&x,&y)!=EOF)
 { x=abs(x),y=abs(y);
  if(x+y==1)t=1;  
  else
    if( (x%2) && (y%2) )t=x+y-1; 
  else
    if( !(x%2) && !(y%2) )t=x+y;
  else if( x && y) t=x+y;
   else t=x+y+1;
printf("%d\n",t);

}





return 0;}
