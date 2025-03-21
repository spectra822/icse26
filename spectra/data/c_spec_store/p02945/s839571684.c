#include <stdio.h>
int main(){
int a,b,c,d,e,max=-1000;
scanf ("%d%d",&a,&b);
c=a+b;
d=a-b;
e=a*b;
if (max<c){
max=c;
}
if (max<d){
max=d;
}
if (max<e){
max=e;
}
printf("%d",max);
return 0;
}
