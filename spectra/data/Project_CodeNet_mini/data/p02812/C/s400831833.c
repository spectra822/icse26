#include <stdio.h>

int main(void)
{
    int n=0,count=0;
    char string[51]={};
    scanf("%d",&n);
    scanf("%s",string);

    for(int i=0;i<n-2;i++){
        if(string[i]=='A' && string[i+1]=='B' && string[i+2]=='C'){
            count+=1;
            i+=2;
        }
    }

    printf("%d",count);
    return 0;
}
