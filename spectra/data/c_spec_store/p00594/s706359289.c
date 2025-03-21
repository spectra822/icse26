#include<stdio.h>
#include<stdlib.h>

int a[1000001];
int cmp(const void *s,const void *b){
return (*(int *)b)-(*(int *)s);
}
int main(void){
int n,m,k;
int i,j;
while(scanf("%d",&n),n){
m=0;
for(i=0;i<n;i++){
scanf("%d",&a[i]);
}
qsort(a,n,sizeof(int),cmp);

for(i=0;i<n;i++){
for(j=i+1;j<n+1;j++){
if(a[i]!=a[j]){
if(m<j-i){
m=j-i;
k=a[i];
}
i=j-1;
break;
}
}
}
if(n/2<m)printf("%d\n",k);
else puts("NO COLOR");
}
return 0;}