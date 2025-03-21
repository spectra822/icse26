#include<stdio.h>
int main ()
{
    double x,y;
    int l;
    scanf("%d", &l);
    y=l/3.0;
    x=y*y*y;
    printf("%.12lf\n", x);
}
