#include <stdio.h>
int counter(int z){
    if(z==0) return 0;
    else return counter(z>>1)+(z&1);
}
int main(void)
{
    int n=0,max=0,count=0,flag=1;
    int a[20]={},x[20][20]={},y[20][20]={};
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&a[i]);
        for(int j=0;j<a[i];j++){
            scanf("%d %d",&x[i][j],&y[i][j]);
        }
    }
    for(int i=0;i<(1<<n);i++){
        flag=1;
        for(int j=0;j<n;j++){
            if(!(i&(1<<j))) continue;
            for(int k=0;k<a[j];k++){
                if((i>>(x[j][k]-1)&1)^y[j][k]){
                    flag=0;
                    break;
                }
            }
        }
        // 矛盾がなかった時
        if(flag==1){
            count=counter(i);
            if(max<count) max=count;
        }
    }
    printf("%d",max);
    return 0;
}

void zeros(int *a){
    for(int i=0;i<20;i++) a[i]=0;
}
