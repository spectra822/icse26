#include <stdio.h>
void enumeration(int result[],int used[],int n,int d){
    int i;
    if(d>=n){
        for(i=0;i<n;i++){
            if(i==0)printf("%d",result[i]);
            else printf(" %d",result[i]);
        }
        printf("\n");
        return;
    }
    
    int used2[n-d-1];
    int j,k;
    for(i=0;i<n-d;i++){
        result[d]=used[i];
        for(j=0,k=0;j<n-d;j++)if(j!=i)used2[k++]=used[j];
        enumeration(result,used2,n,d+1);
    }
    
    return;
}
int main(void){
    int i;
    
    int n;
    scanf("%d\n",&n);
    
    int used[n];
    for(i=0;i<n;i++)used[i]=i+1;
    
    int result[n];
    
    enumeration(result,used,n,0);
    
    return 0;
}
