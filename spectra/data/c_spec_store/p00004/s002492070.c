#include <stdio.h>
#include <math.h>
int main(void){
    double a,b,c,d,e,f,aa,bb,cc,x,y,bai;
    while(scanf("%lf %lf %lf %lf %lf %lf",&a,&b,&c,&d,&e,&f)!=EOF){
        bai=d/a;
        aa=a*bai;
        bb=b*bai;
        cc=c*bai;
        y=(f-cc)/(e-bb);
        x=(c-b*y)/a;
        printf("%.3f %.3f\n",x,y);
    }
        
        
        
        
    
    
    
}
