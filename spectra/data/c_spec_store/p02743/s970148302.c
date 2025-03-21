#include <stdio.h>
#include <math.h>
int main(){
  long double a,b,c,d;
  scanf("%Lf %Lf %Lf",&a,&b,&c);
  d=c-a-b; //展開は誤差の元　項が増える
  if(d*d>4.0L*a*b && d>0) //d<0 でも成立してしまう 2sqrt(ab)>0よりd>0
    puts("Yes");
  else
    puts("No");
  return 0;
}
