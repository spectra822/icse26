#include<stdio.h>
int main()
{
    int a,b,c,i,sum=0,l;

    scanf("%d %d %d",&a,&b,&c);

    if(a>b)
    {
        for(i=b;i>0;i--)
    {
        if(a%i==0 && b%i==0) sum++;

        if(sum==c) l = i;

        if(sum==c) break;

        else continue;
    }
        printf("%d\n",l);

    }

     else if(a<b)
    {
        for(i=a;i>0;i--)
    {
        if(a%i==0 && b%i==0) sum++;

        if(sum==c) l = i;

        if(sum==c) break;

        else continue;
    }
        printf("%d\n",l);

    }

    else if(a==b)
    {
        for(i=a;i>0;i--)
    {
        if(a%i==0 && b%i==0) sum++;

        if(sum==c) l = i;

        if(sum==c) break;

        else continue;
    }
        printf("%d\n",l);

    }

return 0;
}