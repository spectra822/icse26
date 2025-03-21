#include <stdio.h>

int main(void)
{
    int a=0,b=0;
    scanf("%d %d",&a,&b);
    printf("%d",a-2*b>0 ? a-2*b:0);
    return 0;
}
