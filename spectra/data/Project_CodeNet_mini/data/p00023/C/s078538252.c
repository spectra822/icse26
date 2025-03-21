#include <stdio.h>
#define SQ(x) ((x) * (x))
 
typedef struct{
    double x;
    double y;
    double r;
} CIRCLE;
 
int main(void)
{
    CIRCLE a, b;
    int n;
     
    scanf("%d", &n);
     
    while (n-- != 0){
        scanf("%lf%lf%lf%lf%lf%lf", &a.x, &a.y, &a.r, &b.x, &b.y, &b.r);
         
        if (SQ(a.x - b.x) + SQ(a.y - b.y) > SQ(a.r + b.r)){
            printf("0\n");
        }
         
        else if (SQ(a.r + b.r) > SQ(a.x - b.x) + SQ(a.y - b.y) && SQ(a.x - b.x) + SQ(a.y - b.y) > SQ(a.r - b.r)){
            printf("1\n");
        }
         
        else if (SQ(a.x - b.x) + SQ(a.y - b.y) < SQ(a.r - b.r)){
            if (a.r > b.r){
                printf("2\n");
            }
            else {
                printf("-2\n");
            }
        }
        else {
            printf("1\n");
        }
    }
     
    return (0);
}