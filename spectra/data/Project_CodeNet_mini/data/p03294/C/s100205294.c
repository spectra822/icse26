#include<stdio.h>

int main(){

int ans=0,max=0,sum = 0;
int N;
scanf("%d",&N);
int a[N];
for (int i = 0; i < N; i++){
    scanf("%d",&a[i]);
    ans += a[i]-1; 
}

printf("%d",ans);

return 0;

}