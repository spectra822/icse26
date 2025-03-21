#include<stdio.h>

int main(){
    long long int n,m;
    scanf("%lld%lld",&n,&m);

    long long int sum;
    if(m==1){
        sum=0;
    }else if((m/2-n)<0){
        sum=m/2;
    }else if((m/2-n)<2){
        sum=n;
    }else{
        sum=n+(m/2-n)/2;
    }
    printf("%lld",sum);
    return 0;
}