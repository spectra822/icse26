#include <stdio.h>

int main() {
    int a,b,c,d,e;
    scanf("%d %d %d %d %d",&a,&b,&c,&d,&e);
    if(a == 0) {
        printf("1");
    } else if(b == 0) {
        printf("2");
    } else if(c == 0) {
        printf("3");
    } else if(d == 0) {
        printf("4");
    } else if(e == 0) {
        printf("5");
    }
}