#include<stdio.h>
int main(){
    int i,l,a=0,c=0,b[256]={0};
    char s[100];
    scanf("%s",s);
    for(l=0;s[l];l++)b[s[l]]++;
    while(l){
        for(i=0;i<256;i++){
            if(b[i]){
                a++;
                l--;
                c++;
                b[i]--;
            }
            else{
                if(c>3)a-=c-3;
                c=0;
            }
        }
    }
    printf("%d\n",a);
    return 0;
}