#include<stdio.h>

int main(void){

int n,ca=0,cb=0,cc=0,cd=0,ce=0,cf=0;
double h;

scanf("%d",&n);
for(int i=1; i<=n; i++){
scanf("%lf",&h);
if(h<165.0){
ca++;
}
else if(h>=165.0&&h<170.0){
cb++;
}
else if(h>=170.0&&h<175.0){
cc++;
}
else if(h>=175.0&&h<180.0){
cd++;
}
else if(h>=180.0&&h<185.0){
ce++;
}
else if(h>=185.0){
cf++;
}
}

printf("1:");
for(int i=0;i<ca;i++){
printf("*");
}
printf("\n");
printf("2:");
for(int i=0;i<cb;i++){
printf("*");
}
printf("\n");
printf("3:");
for(int i=0;i<cc;i++){
printf("*");
}
printf("\n");
printf("4:");
for(int i=0;i<cd;i++){
printf("*");
}
printf("\n");
printf("5:");
for(int i=0;i<ce;i++){
printf("*");
}
printf("\n");
printf("6:");
for(int i=0;i<cf;i++){
printf("*");
}
printf("\n");

return 0;
}

