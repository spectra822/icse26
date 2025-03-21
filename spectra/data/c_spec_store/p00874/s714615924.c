#include <stdio.h>
#define max(X, Y) ((X)>(Y)?(X):(Y))
int main(void)
{
    int w, d;
    while (scanf("%d%d", &w, &d), w) {
        int i, a[21]={0}, b[21]={0}, res;
        for(i=0;i<w;++i) { int t; scanf("%d", &t); a[t]++; }
        for(i=0;i<d;++i) { int t; scanf("%d", &t); b[t]++; }
        res=0;
        for(i=1;i<=20;++i) res+=i*max(a[i], b[i]);
        printf("%d\n", res);
    }
    return 0;
}