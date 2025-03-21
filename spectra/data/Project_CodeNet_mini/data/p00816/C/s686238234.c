#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int func(char* s, int n, int m)
{
    int i, sum=0;
    char* p=s;
    for(i=0;i<n;++i) if (m&(1<<i)) {
        char t=s[i+1];
        s[i+1]=0;
        sum+=atoi(p);
        s[i+1]=t;
        p=s+i+1;
    }
    return sum+atoi(p);
}

int main(void)
{
    int target;
    char paper[10];
    while (scanf("%d%s", &target, paper), target) {
        int n=strlen(paper);
        int i, res=0, best=-1, cnt=0;
        for(i=(1<<(n-1));i<(1<<n);++i) {
            int t=func(paper, n, i);
            if (t<=target) {
                if (best<t) {
                    best=t; res=i; cnt=1;
                }
                else if (best==t) {
                    ++cnt;
                }
            }
        }
        if (cnt!=1) {
            puts(!cnt ? "error" : "rejected");
        }
        else {
            printf("%d ", best);
            for(i=0;i<n;++i) {
                putchar(paper[i]);
                if (res&(1<<i)) putchar(i==n-1?'\n':' ');
            }
        }
    }
    return 0;
}